#ifndef JOYPAD_HPP
#define JOYPAD_HPP
#include <cstdint>
class Joypad {
        public:
                enum class Keys : std::uint8_t {
                        RIGHT  = 0x01,
                        LEFT   = 0x02,
                        UP     = 0x04,
                        DOWN   = 0x08,
                        A      = 0x10,
                        B      = 0x20,
                        SELECT = 0x40,
                        START  = 0x80
                };
                explicit Joypad() = default;
                bool key_pressed(Keys key) noexcept;
                void key_released(Keys key) noexcept;
                std::uint8_t get_output(std::uint8_t joyp_register_value) noexcept;
        private:
                std::uint8_t state{0};
};
#endif
