#include "../include/bus.hpp"
#include "../include/cpu.hpp"
#include "../include/cartridge.hpp"
#include <stdexcept>

void Bus::insert_cartridge(const std::shared_ptr<Cartridge>& cart) noexcept{
        cartridge = cart;
}

void Bus::connect_joypad(const std::shared_ptr<Joypad>& joypad) noexcept{
        this->joypad = joypad;
}

std::uint8_t Bus::read(std::uint16_t addr){
        if(!cartridge) throw std::runtime_error("Bus Error: Cartridge not inserted");
        if(!joypad) throw std::runtime_error("Bus Error: Joypad not connected");
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

void Bus::write(std::uint16_t addr, std::uint8_t data){
        if(addr >= 0x000 && addr < 0x8000){
                cartridge->write(addr, data);
        }
        else if(addr >= 0x8000 && addr <= 0x9FFF){
                vram[addr-0x8000] = data;
        }
        else if(addr >= 0xA000 && addr <= 0xBFFF){
                cartridge->write(addr, data);
        }
        else if(addr >= 0xC000 && addr <= 0xDFFF){
                wram[addr-0xC000] = data;
        }
        else if(addr >= 0xE000 && addr <= 0xFDFF){
                wram[addr-0xE000] = data;
        }
        else if(addr >= 0xFE00 && addr <= 0xFE9F){
                oam[addr-0xFE00] = data;
        }
        else if(addr >= 0xFF00 && addr <= 0xFF7F){
                if(addr == 0xFF04){
                        io_registers[4] = 0;
                        return;
                }
                if(addr == 0xFF46){
                        start_dma_transfer(data);
                        return;
                }
                io_registers[addr-0xFF00] = data;
        }
        else if(addr >= 0xFF80 && addr <= 0xFFFE){
                hram[addr-0xFF80] = data;
        }
        else if(addr == 0xFFFF){
                interrupt_enable_register = data;
        }
}

void Bus::key_down(Joypad::Keys key){
        if(!joypad) throw std::runtime_error("Bus Error: Joypad not connected");
        bool key_down{joypad->key_pressed(key)};
        if(key_down){
                std::uint8_t joyp_reg{read(0xFF00)};
                std::uint8_t output{joypad->get_output(joyp_reg)};
                write(0xFF00, output);
                request_interrupt(4);
        }
}

void Bus::key_up(Joypad::Keys key){
        if(!joypad) throw std::runtime_error("Bus Error: Joypad not connected");
        joypad->key_released(key);
        std::uint8_t joyp_reg{read(0xFF00)};
        std::uint8_t output{joypad->get_output(joyp_reg)};
        write(0xFF00, output);
}

void Bus::request_interrupt(std::uint8_t bit) noexcept{
        std::uint8_t current_if{read(0xFF0F)};
        std::uint8_t new_if{static_cast<std::uint8_t>(current_if|(1<<bit))};
        write(0xFF0F, new_if);
}

void Bus::inc_div() noexcept{
        io_registers[4]++;
}

void Bus::start_dma_transfer(std::uint8_t data) noexcept{
        std::uint16_t start_addr{static_cast<std::uint16_t>(data << 8)};

        for(int i{0};i<160;++i){
                std::uint8_t byte{read(start_addr + i)};
                oam[i] = byte;
        }
}
