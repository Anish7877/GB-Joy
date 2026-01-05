#include "../include/apu.hpp"
#include "../include/bus.hpp"

static constexpr std::uint8_t DUTY_CYCLES[4][8] = {
    {0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 0}
};

APU::APU() {
    ch1 = {}; ch2 = {}; ch3 = {}; ch4 = {};
}

void APU::connect_to_bus(const std::shared_ptr<Bus>& bus) noexcept{
        this->bus = bus;
}

void APU::tick(int cycles) {
    if (!audio_master_enable) return;

    frame_sequencer_timer += cycles;
    if (frame_sequencer_timer >= 8192) {
        frame_sequencer_timer -= 8192;
        step_frame_sequencer();
    }

    ch1.timer -= cycles;
    if (ch1.timer <= 0) {
        int freq{((ch1.nr14 & 7) << 8) | ch1.nr13};
        ch1.timer += (2048 - freq) * 4;

        ch1.duty_index = (ch1.duty_index + 1) % 8;
    }

    ch2.timer -= cycles;
    if (ch2.timer <= 0) {
        int freq{((ch2.nr24 & 7) << 8) | ch2.nr23};
        ch2.timer += (2048 - freq) * 4;

        ch2.duty_index = (ch2.duty_index + 1) % 8;
    }

    ch3.timer -= cycles;
    if (ch3.timer <= 0) {
        int freq{((ch3.nr34 & 7) << 8) | ch3.nr33};
        ch3.timer += (2048 - freq) * 2;

        ch3.position_counter = (ch3.position_counter + 1) % 32;
    }

    ch4.timer -= cycles;
    if (ch4.timer <= 0) {
        static constexpr int divisors[8]{8, 16, 32, 48, 64, 80, 96, 112};
        int divisor_code{ch4.nr43 & 0x07};
        int shift_clock_freq{(ch4.nr43 >> 4) & 0x0F};

        int current_period{divisors[divisor_code] << shift_clock_freq};
        ch4.timer += current_period;

        int xor_result{(ch4.lfsr & 1) ^ ((ch4.lfsr >> 1) & 1)};
        ch4.lfsr >>= 1;
        ch4.lfsr |= (xor_result << 14);

        if (ch4.nr43 & 0x08) {
            ch4.lfsr &= ~(1 << 6);
            ch4.lfsr |= (xor_result << 6);
        }
    }
}

void APU::step_frame_sequencer() {
    frame_sequencer_step = (frame_sequencer_step + 1) % 8;

    if (frame_sequencer_step % 2 == 0) {
        step_lengths();
    }

    if (frame_sequencer_step == 2 || frame_sequencer_step == 6) {
        step_sweeps();
    }

    if (frame_sequencer_step == 7) {
        step_envelopes();
    }
}

void APU::step_lengths() {
    if (ch1.nr14 & 0x40 && ch1.length_counter > 0) {
        ch1.length_counter--;
        if (ch1.length_counter == 0) ch1.enabled = false;
    }
    if (ch2.nr24 & 0x40 && ch2.length_counter > 0) {
        ch2.length_counter--;
        if (ch2.length_counter == 0) ch2.enabled = false;
    }
    if (ch3.nr34 & 0x40 && ch3.length_counter > 0) {
        ch3.length_counter--;
        if (ch3.length_counter == 0) ch3.enabled = false;
    }
    if (ch4.nr44 & 0x40 && ch4.length_counter > 0) {
        ch4.length_counter--;
        if (ch4.length_counter == 0) ch4.enabled = false;
    }
}

void APU::step_envelopes() {
    auto update_envelope = [](int& vol, int& timer, std::uint8_t nr_reg, bool& enabled) {
        if (!enabled) return;

        int period = nr_reg & 0x07;
        if (period == 0) return;

        timer--;
        if (timer <= 0) {
            timer = period;
            bool direction = nr_reg & 0x08;

            if (direction) {
                if (vol < 15) vol++;
            } else {
                if (vol > 0) vol--;
            }
        }
    };

    update_envelope(ch1.volume, ch1.envelope_timer, ch1.nr12, ch1.enabled);
    update_envelope(ch2.volume, ch2.envelope_timer, ch2.nr22, ch2.enabled);
    update_envelope(ch4.volume, ch4.envelope_timer, ch4.nr42, ch4.enabled);
}

void APU::step_sweeps() {
    if (!ch1.sweep_enabled) return;

    ch1.sweep_timer--;
    if (ch1.sweep_timer <= 0) {
        int period{(ch1.nr10 >> 4) & 0x07};
        int shift{ch1.nr10 & 0x07};

        if (period == 0) period = 8;
        ch1.sweep_timer = period;

        if (period > 0 && shift > 0) {
            int new_freq{calculate_sweep_freq()};
            if (new_freq <= 2047 && shift > 0) {
                ch1.shadow_frequency = new_freq;
                ch1.nr13 = new_freq & 0xFF;
                ch1.nr14 = (ch1.nr14 & 0xF8) | ((new_freq >> 8) & 0x07);
                calculate_sweep_freq();
            }
        }
    }
}

int APU::calculate_sweep_freq() {
    int new_freq = ch1.shadow_frequency >> (ch1.nr10 & 0x07);
    if (ch1.nr10 & 0x08) new_freq = ch1.shadow_frequency - new_freq;
    else new_freq = ch1.shadow_frequency + new_freq;

    if (new_freq > 2047) ch1.enabled = false;
    return new_freq;
}

void APU::trigger_ch1() {
    ch1.enabled = true;
    if (ch1.length_counter == 0) ch1.length_counter = 64;

    ch1.volume = (ch1.nr12 >> 4);
    ch1.envelope_timer = ch1.nr12 & 0x07;

    ch1.shadow_frequency = ((ch1.nr14 & 7) << 8) | ch1.nr13;
    int sweep_period{(ch1.nr10 >> 4) & 0x07};
    int sweep_shift{ch1.nr10 & 0x07};
    ch1.sweep_timer = (sweep_period == 0) ? 8 : sweep_period;
    ch1.sweep_enabled = (sweep_period > 0 || sweep_shift > 0);
    if (sweep_shift > 0) calculate_sweep_freq();
}

void APU::trigger_ch2() {
    ch2.enabled = true;
    if (ch2.length_counter == 0) ch2.length_counter = 64;
    ch2.volume = (ch2.nr22 >> 4);
    ch2.envelope_timer = ch2.nr22 & 0x07;
}

void APU::trigger_ch3() {
    ch3.enabled = true;
    if (ch3.length_counter == 0) ch3.length_counter = 256;
    ch3.position_counter = 0;
}

void APU::trigger_ch4() {
    ch4.enabled = true;
    ch4.lfsr = 0x7FFF;
    if (ch4.length_counter == 0) ch4.length_counter = 64;
    ch4.volume = (ch4.nr42 >> 4);
    ch4.envelope_timer = ch4.nr42 & 0x07;
}


std::uint8_t APU::read(std::uint16_t addr) {
    if (addr >= 0xFF30 && addr <= 0xFF3F) {
        return ch3.wave_ram[addr - 0xFF30];
    }

    switch (addr) {
        case 0xFF10: return ch1.nr10 | 0x80;
        case 0xFF11: return ch1.nr11 | 0x3F;
        case 0xFF12: return ch1.nr12;
        case 0xFF13: return 0xFF;
        case 0xFF14: return ch1.nr14 | 0xBF;

        case 0xFF15: return 0xFF;
        case 0xFF16: return ch2.nr21 | 0x3F;
        case 0xFF17: return ch2.nr22;
        case 0xFF18: return 0xFF;
        case 0xFF19: return ch2.nr24 | 0xBF;

        case 0xFF1A: return ch3.nr30 | 0x7F;
        case 0xFF1B: return 0xFF;
        case 0xFF1C: return ch3.nr32 | 0x9F;
        case 0xFF1D: return 0xFF;
        case 0xFF1E: return ch3.nr34 | 0xBF;

        case 0xFF1F: return 0xFF;
        case 0xFF20: return ch4.nr41 | 0xFF;
        case 0xFF21: return ch4.nr42;
        case 0xFF22: return ch4.nr43;
        case 0xFF23: return ch4.nr44 | 0xBF;

        case 0xFF24: return nr50;
        case 0xFF25: return nr51;
        case 0xFF26:
            return (audio_master_enable << 7) |
                   (ch4.enabled << 3) |
                   (ch3.enabled << 2) |
                   (ch2.enabled << 1) |
                   (ch1.enabled << 0) | 0x70;
    }
    return 0xFF;
}

void APU::write(std::uint16_t addr, std::uint8_t data) {
    if (addr >= 0xFF30 && addr <= 0xFF3F) {
        ch3.wave_ram[addr - 0xFF30] = data;
        return;
    }

    if (!audio_master_enable && addr != 0xFF26) return;

    switch (addr) {
        case 0xFF10: ch1.nr10 = data; break;
        case 0xFF11: ch1.nr11 = data; ch1.length_counter = 64 - (data & 0x3F); break;
        case 0xFF12: ch1.nr12 = data; break;
        case 0xFF13: ch1.nr13 = data; break;
        case 0xFF14:
            ch1.nr14 = data;
            if (data & 0x80) trigger_ch1();
            break;

        case 0xFF16: ch2.nr21 = data; ch2.length_counter = 64 - (data & 0x3F); break;
        case 0xFF17: ch2.nr22 = data; break;
        case 0xFF18: ch2.nr23 = data; break;
        case 0xFF19:
            ch2.nr24 = data;
            if (data & 0x80) trigger_ch2();
            break;

        case 0xFF1A: ch3.nr30 = data; break;
        case 0xFF1B: ch3.nr31 = data; ch3.length_counter = 256 - data; break;
        case 0xFF1C: ch3.nr32 = data; break;
        case 0xFF1D: ch3.nr33 = data; break;
        case 0xFF1E:
            ch3.nr34 = data;
            if (data & 0x80) trigger_ch3();
            break;

        case 0xFF20: ch4.nr41 = data; ch4.length_counter = 64 - (data & 0x3F); break;
        case 0xFF21: ch4.nr42 = data; break;
        case 0xFF22: ch4.nr43 = data; break;
        case 0xFF23:
            ch4.nr44 = data;
            if (data & 0x80) trigger_ch4();
            break;

        case 0xFF24: nr50 = data; break;
        case 0xFF25: nr51 = data; break;
        case 0xFF26:
            audio_master_enable = (data & 0x80);
            if (!audio_master_enable) {
                nr50 = 0; nr51 = 0;
            }
            break;
    }
}


float APU::get_sample() const {
    if (!audio_master_enable) return 0.0f;

    float output_ch1{0.0f};
    float output_ch2{0.0f};
    float output_ch3{0.0f};
    float output_ch4{0.0f};

    if (ch1.enabled) {
        int duty{(ch1.nr11 >> 6) & 0x03};
        std::uint8_t wave_val{DUTY_CYCLES[duty][ch1.duty_index]};
        output_ch1 = wave_val ? (float)ch1.volume / 15.0f : -(float)ch1.volume / 15.0f;
    }

    if (ch2.enabled) {
        int duty{(ch2.nr21 >> 6) & 0x03};
        std::uint8_t wave_val{DUTY_CYCLES[duty][ch2.duty_index]};
        output_ch2 = wave_val ? (float)ch2.volume / 15.0f : -(float)ch2.volume / 15.0f;
    }

    if (ch3.enabled && (ch3.nr30 & 0x80)) {
        std::uint8_t sample_byte{ch3.wave_ram[ch3.position_counter / 2]};
        int sample{(ch3.position_counter % 2 == 0) ? (sample_byte >> 4) : (sample_byte & 0x0F)};

        int vol_code{(ch3.nr32 >> 5) & 0x03};
        if (vol_code == 0) sample = 0;
        else if (vol_code == 2) sample >>= 1;
        else if (vol_code == 3) sample >>= 2;

        output_ch3 = ((float)sample / 7.5f) - 1.0f;
    }

    if (ch4.enabled) {
        output_ch4 = (ch4.lfsr & 1) ? -(float)ch4.volume / 15.0f : (float)ch4.volume / 15.0f;
    }

    float left{0.0f};
    float right{0.0f};

    if (nr51 & 0x10) left += output_ch1;
    if (nr51 & 0x20) left += output_ch2;
    if (nr51 & 0x40) left += output_ch3;
    if (nr51 & 0x80) left += output_ch4;

    if (nr51 & 0x01) right += output_ch1;
    if (nr51 & 0x02) right += output_ch2;
    if (nr51 & 0x04) right += output_ch3;
    if (nr51 & 0x08) right += output_ch4;

    float vol_left{(float)((nr50 >> 4) & 0x07) / 7.0f};
    float vol_right{(float)(nr50 & 0x07) / 7.0f};
    return (left * vol_left + right * vol_right) / 4.0f;
}
