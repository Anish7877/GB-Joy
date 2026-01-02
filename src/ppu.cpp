#include "../include/ppu.hpp"
#include "../include/bus.hpp"
#include <stdexcept>

void PPU::connect_to_bus(const std::shared_ptr<Bus>& bus) noexcept{
        this->bus = bus;
}

void PPU::update_stat_mode(std::uint8_t mode) noexcept{
        current_mode = mode;
        std::uint8_t stat{bus->read(stat_addr)};

        stat &= 0xFC;

        stat |= (mode & 0x03);

        bus->write(stat_addr, stat);

        // stat interrupts
        bool request_interrupt{false};

        if(mode == 0 && (stat & (1<<3))) request_interrupt = true;
        if(mode == 1 && (stat & (1<<4))) request_interrupt = true;
        if(mode == 2 && (stat & (1<<5))) request_interrupt = true;

        if(request_interrupt) bus->request_interrupt(1);
}

void PPU::compare_ly_lyc() noexcept{
        std::uint8_t ly{bus->read(ly_addr)};
        std::uint8_t lyc{bus->read(lyc_addr)};
        std::uint8_t stat{bus->read(stat_addr)};

        if(lyc == ly){
                stat |= 0x04;

                if(stat & 0x04){
                        bus->request_interrupt(1);
                }
        }
        else{
                stat &= ~(0x04);
        }
        bus->write(stat_addr, stat);
}

void PPU::render_scanline(){
}

// PPU.cpp
void PPU::tick(unsigned int cycles){
        if(!bus) throw std::runtime_error("PPU Error: Bus not connected");
        std::uint8_t lcdc{bus->read(lcdc_addr)};

        if(!(lcdc & 0x80)){
                internal_cycles = 0;
                current_mode = 0;
                bus->write(ly_addr, 0);

                std::uint8_t stat{bus->read(stat_addr)};
                stat &= 0xFC;
                bus->write(stat_addr, stat);
                return;
        }

        internal_cycles += cycles;

        switch (current_mode){
                case 2:
                        if(internal_cycles == 0){
                                sprite_buffer.clear();
                                sprite_buffer.reserve(10);

                                std::uint8_t lcdc{bus->read(lcdc_addr)};
                                std::uint8_t ly{bus->read(ly_addr)};
                                std::uint8_t sprite_height{static_cast<std::uint8_t>((lcdc & 0x04) ? 16 : 8)};

                                for(int i{0};i<40;++i){
                                        std::uint16_t addr{static_cast<std::uint16_t>(0xFE00 + (i*4))};

                                        std::uint8_t sprite_y{bus->read(addr)};

                                        if((ly+16) >= sprite_y && (ly+16) < (sprite_height + sprite_y)){
                                                ObjectAttribute obj{};
                                                obj.y = sprite_y;
                                                obj.x = bus->read(addr+1);
                                                obj.tile_index = bus->read(addr+2);
                                                obj.flags = bus->read(addr+3);

                                                sprite_buffer.push_back(obj);
                                                if(sprite_buffer.size() >= 10) break;
                                        }
                                }
                        }
                        if(internal_cycles >= 80){
                                internal_cycles -= 80;
                                update_stat_mode(3);
                        }
                        break;
                case 3:
                        if(internal_cycles >= 172){
                                internal_cycles -= 172;
                                update_stat_mode(0);
                                // render scan line
                                render_scanline();
                        }
                        break;
                case 0:
                        if(internal_cycles >= 204){
                                internal_cycles -= 204;
                                update_stat_mode(1);

                                std::uint8_t current_ly{bus->read(ly_addr)};
                                bus->write(ly_addr, current_ly+1);

                                compare_ly_lyc();

                                if(bus->read(ly_addr) == 144){
                                        update_stat_mode(1);
                                        frame_complete = true;
                                        bus->request_interrupt(0);
                                }
                                else{
                                        update_stat_mode(2);
                                }
                        }
                        break;
                case 1:
                        if(internal_cycles >= 456){
                                internal_cycles -= 456;

                                std::uint8_t current_ly{bus->read(ly_addr)};

                                if(current_ly < 153){
                                        bus->write(ly_addr, current_ly+1);
                                        compare_ly_lyc();
                                }
                                else{
                                        bus->write(ly_addr, 0);
                                        compare_ly_lyc();
                                        update_stat_mode(2);
                                }
                        }
                        break;
        }
}

std::uint8_t PPU::get_lcdc() const noexcept{
        return bus->read(lcdc_addr);
}

std::uint8_t PPU::get_stat() const noexcept{
        return bus->read(stat_addr);
}

std::uint8_t PPU::get_scx() const noexcept{
        return bus->read(scx_addr);
}

std::uint8_t PPU::get_scy() const noexcept{
        return bus->read(scy_addr);
}

std::uint8_t PPU::get_ly() const noexcept{
        return bus->read(ly_addr);
}

std::uint8_t PPU::get_lyc() const noexcept{
        return bus->read(lyc_addr);
}

std::uint8_t PPU::get_bgp() const noexcept{
        return bus->read(bgp_addr);
}

std::uint8_t PPU::get_wx() const noexcept{
        return bus->read(wx_addr);
}

std::uint8_t PPU::get_wy() const noexcept{
        return bus->read(wy_addr);
}
