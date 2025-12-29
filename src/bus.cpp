#include "../include/bus.hpp"
#include "../include/cpu.hpp"
#include "../include/cartridge.hpp"

void Bus::insert_cartridge(const std::shared_ptr<Cartridge>& cart){
        cartridge = cart;
}

void Bus::connect_joypad(const std::shared_ptr<Joypad>& joypad){
        this->joypad = joypad;
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
        else if(addr == 0xFF00){
                return joypad->get_output(io_registers[0x00]);
        }
        else if(addr > 0xFF00 && addr <= 0xFF7F){
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
                if(addr == 0xFF04){
                        io_registers[addr-0xFF04] = 0;
                        return true;
                }
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

void Bus::key_down(Joypad::Keys key){
        bool key_down{joypad->key_pressed(key)};
        if(key_down){
                request_interrupt(4);
        }
}

void Bus::key_up(Joypad::Keys key){
        joypad->key_released(key);
}

void Bus::request_interrupt(std::uint8_t bit){
        std::uint8_t current_if{read(0xFF0F)};
        std::uint8_t new_if{static_cast<std::uint8_t>(current_if|(1<<bit))};
        write(0xFF0F, new_if);
}

void Bus::inc_div(){
        io_registers[4]++;
}
