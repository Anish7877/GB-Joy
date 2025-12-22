#ifndef CARTRIDGE_HPP
#define CARTRIDGE_HPP
#include <cstdint>
#include <vector>
#include <string_view>
class Cartridge {
        public:
                explicit Cartridge() = default;
                bool load(std::string_view path);
                std::uint8_t read(std::uint16_t addr);
                bool write(std::uint16_t addr, std::uint8_t data);
        private:
                std::vector<std::uint8_t> rom{};
                std::vector<std::uint8_t> eram{};

                // banking system due to window limit in gameboy
                // i.e. it can only see 0x0000 - 0x7FFF for
                // cartridge it will help to check which page is
                // in the memory and how to fetch is it is not
                std::uint8_t rom_bank_value{1};
                std::uint8_t ram_bank_value{0};

                bool ram_enabled{false};
                bool banking_mode{false};

                void setup_tables();
};
#endif
