#include "../include/joypad.hpp"

bool Joypad::key_pressed(Keys key) noexcept{
    bool previously_unset{!(state & static_cast<std::uint8_t>(key))};
    state |= static_cast<std::uint8_t>(key);
    return previously_unset;
}

void Joypad::key_released(Keys key) noexcept{
    state &= ~static_cast<std::uint8_t>(key);
}

std::uint8_t Joypad::get_output(std::uint8_t joyp_reg) noexcept{
    std::uint8_t output{0xCF};
    if (!(joyp_reg & 0x20)) {
        if (state & (std::uint8_t)Keys::START)  output &= ~0x08;
        if (state & (std::uint8_t)Keys::SELECT) output &= ~0x04;
        if (state & (std::uint8_t)Keys::B)      output &= ~0x02;
        if (state & (std::uint8_t)Keys::A)      output &= ~0x01;
    }
    if (!(joyp_reg & 0x10)) {
        if (state & (std::uint8_t)Keys::DOWN)   output &= ~0x08;
        if (state & (std::uint8_t)Keys::UP)     output &= ~0x04;
        if (state & (std::uint8_t)Keys::LEFT)   output &= ~0x02;
        if (state & (std::uint8_t)Keys::RIGHT)  output &= ~0x01;
    }
    return output;
}
