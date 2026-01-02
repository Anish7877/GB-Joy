#ifndef CARTRIDGE_HPP
#define CARTRIDGE_HPP
#include <cstdint>
#include <string>
#include <vector>
#include <string_view>
class Cartridge {
        public:
                explicit Cartridge() = default;
                bool load(std::string_view path);
                std::uint8_t read(std::uint16_t addr);
                bool write(std::uint16_t addr, std::uint8_t data);
                std::string get_cartridge_title() const noexcept {return title;}
                std::uint8_t get_cgb_flag() const noexcept {return cgb_flag;}
                std::uint8_t get_cartridge_type() const noexcept {return cartridge_type;}
                std::size_t get_rom_size() const noexcept {return rom_size;}
                std::uint8_t get_checksum() const noexcept {return checksum;}

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

                std::string title{};
                std::uint8_t cgb_flag{};
                std::uint8_t cartridge_type{};
                std::size_t rom_size{};
                std::uint8_t checksum{};
};
#endif
