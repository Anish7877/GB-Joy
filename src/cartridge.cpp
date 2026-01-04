#include "../include/cartridge.hpp"
#include <filesystem>
#include <fstream>
#include <ios>
#include <string_view>
#include <vector>

bool Cartridge::load(std::string_view path){
        if(!std::filesystem::exists(path.data())) throw std::runtime_error("Cartridge Error: Rom File doesn't exists");
        std::ifstream file{path.data(), std::ios::binary | std::ios::ate};
        if(!file.is_open()) return false;

        std::streamsize size{file.tellg()};
        file.seekg(0,std::ios::beg);
        rom.resize(size);

        if(!file.read(reinterpret_cast<char*>(rom.data()), size)){
                return false;
        }
        setup_tables();
        for(int i{0x134};i<=0x142;++i){
                title.push_back(static_cast<char>(rom[i]));
        }
        cgb_flag = rom[0x143];
        cartridge_type = rom[0x147];
        rom_size = 32 * (1 << rom[0x148]);
        checksum = rom[0x14D];
        return true;
}

void Cartridge::setup_tables(){
        if(rom.size() < 0x150) return;

        std::uint8_t ram_size_code{rom[0x149]};
        std::size_t ram_size{0};
        switch(ram_size_code){
                case 0x02: ram_size = 1<<13; break;
                case 0x03: ram_size = 1<<15; break;
                case 0x04: ram_size = 1<<17; break;
                case 0x05: ram_size = 1<<16; break;
                default: ram_size = 0;
        }
        if(ram_size > 0){
                eram.resize(ram_size);
        }
}

std::uint8_t Cartridge::read(std::uint16_t addr){
        if (cartridge_type >= 0x01 && cartridge_type <= 0x03) {
                if (addr < 0x4000) {
                        if (banking_mode == 1) {
                                std::uint32_t bank{static_cast<std::uint32_t>(ram_bank_value << 5)};
                                if (rom.size() <= 512 * 1024) bank = 0;

                                return rom[(bank * 0x4000 + addr) % rom.size()];
                        }
                        return rom[addr];
                }
                else if (addr >= 0x4000 && addr < 0x8000) {
                        std::uint32_t bank{rom_bank_value};

                        if (rom.size() > 512 * 1024) {
                                bank |= (ram_bank_value << 5);
                        }

                        std::uint32_t offset{(bank * 0x4000) + (addr - 0x4000)};
                        return rom[offset % rom.size()];
                }
        }
        else if (cartridge_type >= 0x0F && cartridge_type <= 0x13) {
                if (addr < 0x4000) {
                        return rom[addr];
                }
                else if (addr >= 0x4000 && addr < 0x8000) {
                        std::uint32_t bank{rom_bank_value};
                        std::uint32_t offset{(bank * 0x4000) + (addr - 0x4000)};
                        return rom[offset % rom.size()];
                }
        }
        else {
                if (addr < 0x8000) return rom[addr];
        }

        if (addr >= 0xA000 && addr <= 0xBFFF) {
                if (!ram_enabled) return 0xFF;

                if (cartridge_type >= 0x0F && cartridge_type <= 0x13 && ram_bank_value >= 0x08) {
                        return 0x00;
                }

                std::uint32_t current_ram_bank{0};

                if (banking_mode == 1 || (cartridge_type >= 0x0F && cartridge_type <= 0x13)){
                        current_ram_bank = ram_bank_value;
                }

                if (eram.empty()) return 0xFF;

                std::size_t offset{static_cast<std::size_t>((current_ram_bank * 0x2000) + (addr - 0xA000))};
                if (offset < eram.size()){
                        return eram[offset];
                }
        }
        return 0xFF;
}

bool Cartridge::write(std::uint16_t addr, std::uint8_t data){
        if (cartridge_type >= 0x01 && cartridge_type <= 0x03) {
                if(addr < 0x2000){
                        ram_enabled = ((data & 0x0F) == 0x0A);
                        return true;
                }
                if(addr >= 0x2000 && addr < 0x4000){
                        rom_bank_value = data & 0x1F;
                        if(!rom_bank_value) rom_bank_value = 1;
                        return true;
                }
                if(addr >= 0x4000 && addr < 0x6000){
                        ram_bank_value = data & 0x03;
                        return true;
                }
                if(addr >= 0x6000 && addr < 0x8000){
                        banking_mode = data & 0x01;
                        return true;
                }
        }
        else if (cartridge_type >= 0x0F && cartridge_type <= 0x13) {
                if(addr < 0x2000){
                        ram_enabled = ((data & 0x0F) == 0x0A);
                        return true;
                }
                if(addr >= 0x2000 && addr < 0x4000){
                        rom_bank_value = data & 0x7F;
                        if(!rom_bank_value) rom_bank_value = 1;
                        return true;
                }
                if(addr >= 0x4000 && addr < 0x6000){
                        ram_bank_value = data;
                        return true;
                }
                if(addr >= 0x6000 && addr < 0x8000){
                        return true;
                }
        }

        if(addr >= 0xA000 && addr <= 0xBFFF){
                if(ram_enabled){
                        if (cartridge_type >= 0x0F && cartridge_type <= 0x13 && ram_bank_value >= 0x08) return true;

                        std::uint32_t current_ram_bank{0};
                        if (banking_mode == 1 || (cartridge_type >= 0x0F && cartridge_type <= 0x13)) {
                                current_ram_bank = ram_bank_value;
                        }

                        if (eram.empty()) return true;

                        std::size_t offset{(current_ram_bank * 0x2000) + (addr - 0xA000)};
                        if(offset < eram.size()){
                                eram[offset] = data;
                        }
                }
                return true;
        }
        return false;
}
