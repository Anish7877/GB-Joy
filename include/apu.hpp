#ifndef APU_HPP
#define APU_HPP
#include <cstdint>
#include <array>
#include <memory>

class Bus;
class APU {
        public:
                APU();
                void connect_to_bus(const std::shared_ptr<Bus>& bus);

                void tick(int cycles);

                std::uint8_t read(std::uint16_t addr);
                void write(std::uint16_t addr, std::uint8_t data);

                float get_sample() const;

        private:
                std::shared_ptr<Bus> bus{};
                bool audio_master_enable{false};

                int frame_sequencer_step{0};
                int frame_sequencer_timer{0};

                void step_frame_sequencer();
                void step_lengths();
                void step_envelopes();
                void step_sweeps();

                struct Channel1 {
                        bool enabled{false};

                        std::uint8_t nr10{0}, nr11{0}, nr12{0}, nr13{0}, nr14{0};

                        int timer{0};
                        int duty_index{0};

                        int length_counter{0};

                        int volume{0};
                        int envelope_timer{0};

                        int sweep_timer{0};
                        int shadow_frequency{0};
                        bool sweep_enabled{false};

                        std::uint8_t output{0};
                } ch1;

                struct Channel2 {
                        bool enabled{false};
                        std::uint8_t nr21{0}, nr22{0}, nr23{0}, nr24{0};

                        int timer{0};
                        int duty_index{0};
                        int length_counter{0};

                        int volume{0};
                        int envelope_timer{0};

                        std::uint8_t output{0};
                } ch2;

                struct Channel3 {
                        bool enabled{false};
                        std::uint8_t nr30{0}, nr31{0}, nr32{0}, nr33{0}, nr34{0};

                        std::array<std::uint8_t, 16> wave_ram{};

                        int timer{0};
                        int position_counter{0};
                        int length_counter{0};

                        std::uint8_t output{0};
                } ch3;

                struct Channel4 {
                        bool enabled{false};
                        std::uint8_t nr41{0}, nr42{0}, nr43{0}, nr44{0};

                        int timer{0};
                        std::uint16_t lfsr{0x7FFF};
                        int length_counter{0};

                        int volume{0};
                        int envelope_timer{0};

                        std::uint8_t output{0};
                } ch4;

                std::uint8_t nr50{0};
                std::uint8_t nr51{0};
                std::uint8_t nr52{0};

                std::uint8_t get_duty_output(int duty_type, int step);
                int calculate_sweep_freq();
                void trigger_ch1();
                void trigger_ch2();
                void trigger_ch3();
                void trigger_ch4();
};
#endif
