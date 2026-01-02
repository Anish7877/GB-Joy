#include "../include/cartridge.hpp"
#include <filesystem>
#include <fstream>
#include <ios>
#include <string_view>

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
        // rom header is 0x0100 - 0x014F
        // and from this we can have so much info like ram size, cartridge name etc.
        if(rom.size() < 0x150) return;

        std::uint8_t ram_size_code{rom[0x149]};
        std::size_t ram_size{0};
        switch(ram_size_code){
                case 0x02: ram_size = 1<<13; break; // 8KB (1 Bank)
                case 0x03: ram_size = 1<<15; break; // 32KB(4 Banks)
                case 0x04: ram_size = 1<<17; break; // 128KB(16 Banks)
                case 0x05: ram_size = 1<<16; break; // 64KB(8 Banks)
                default: ram_size = 0;
        }
        if(ram_size > 0){
                eram.resize(ram_size);
        }
}

std::uint8_t Cartridge::read(std::uint16_t addr){
        if (addr < 0x8000){

                std::uint32_t bank{rom_bank_value};
                if (banking_mode == 0){
                        bank |= (ram_bank_value << 5);
                }

                if (addr < 0x4000){
                        return rom[addr];
                }
                std::uint32_t offset{static_cast<std::uint32_t>((bank * 0x4000) + (addr - 0x4000))};

                return rom[offset % rom.size()];
        }


        if (addr >= 0xA000 && addr <= 0xBFFF) {
                if (!ram_enabled) return 0xFF;
                std::uint32_t current_ram_bank{0};
                if (banking_mode == 1){
                        current_ram_bank = ram_bank_value;
                }

                std::size_t offset{static_cast<std::size_t>((current_ram_bank * 0x2000) + (addr - 0xA000))};
                if (offset < eram.size()){
                        return eram[offset];
                }
        }
        return 0xFF;
}

bool Cartridge::write(std::uint16_t addr, std::uint8_t data){
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
        if(addr >= 0xA000 && addr <= 0xBFFF){
                if(ram_enabled){
                        std::uint32_t current_ram_bank{0};
                        if (banking_mode == 1) {
                                current_ram_bank = ram_bank_value;
                        }
                        std::size_t offset = (current_ram_bank * 0x2000) + (addr - 0xA000);
                        if(offset < eram.size()){
                                eram[offset] = data;
                        }
                }
                return true;
        }
        return false;
}
