#include "../include/bus.hpp"
#include "../include/cartridge.hpp"
#include <cstdint>

void Bus::insert_cartridge(const std::shared_ptr<Cartridge>& cart){
        cartridge = cart;
}

std::uint8_t Bus::read(std::uint16_t addr){
        if(addr >= 0x000 && addr < 0x8000){
                return cartridge->read(addr);
        }
        else if(addr >= 0x8000 && addr <= 0x9FFF){
                return vram[addr-0x8000];
        }
        else if(addr >= 0xA000 && addr <= 0xBFFF){
                return cartridge->read(addr);
        }
        else if(addr >= 0xC000 && addr <= 0xDFFF){
                return wram[addr-0xC000];
        }
        else if(addr >= 0xE000 && addr <= 0xFDFF){
                return wram[addr-0xE000];
        }
        else if(addr >= 0xFE00 && addr <= 0xFE9F){
                return oam[addr-0xFE00];
        }
        else if(addr >= 0xFF00 && addr <= 0xFF7F){
                return io_registers[addr-0xFF00];
        }
        else if(addr >= 0xFF80 && addr <= 0xFFFE){
                return hram[addr-0xFF80];
        }
        else if(addr == 0xFFFF){
                return interrupt_enable_register;
        }
        return 0xFF;
}

bool Bus::write(std::uint16_t addr, std::uint8_t data){
        if(addr >= 0x000 && addr < 0x8000){
                cartridge->write(addr, data);
                return true;
        }
        else if(addr >= 0x8000 && addr <= 0x9FFF){
                vram[addr-0x8000] = data;
                return true;
        }
        else if(addr >= 0xA000 && addr <= 0xBFFF){
                cartridge->write(addr, data);
                return true;
        }
        else if(addr >= 0xC000 && addr <= 0xDFFF){
                wram[addr-0xC000] = data;
                return true;
        }
        else if(addr >= 0xE000 && addr <= 0xFDFF){
                wram[addr-0xE000] = data;
                return true;
        }
        else if(addr >= 0xFE00 && addr <= 0xFE9F){
                oam[addr-0xFE00] = data;
                return true;
        }
        else if(addr >= 0xFF00 && addr <= 0xFF7F){
                io_registers[addr-0xFF00] = data;
                return true;
        }
        else if(addr >= 0xFF80 && addr <= 0xFFFE){
                hram[addr-0xFF80] = data;
                return true;
        }
        else if(addr == 0xFFFF){
                interrupt_enable_register = data;
                return true;
        }
        return false;
}
