#include "../include/ppu.hpp"
#include "../include/bus.hpp"
#include <algorithm>
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

                if(stat & 0x40){
                        bus->request_interrupt(1);
                }
        }
        else{
                stat &= ~(0x04);
        }
        bus->write(stat_addr, stat);
}

void PPU::run_oam_search(){
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
                        obj.oam_index = i;

                        sprite_buffer.emplace_back(std::move(obj));
                        if(sprite_buffer.size() >= 10){
                                break;
                        }
                }
        }
        std::sort(sprite_buffer.begin(), sprite_buffer.end(),
                        [](const ObjectAttribute& a, const ObjectAttribute& b) {
                        if (a.x != b.x) return a.x > b.x;
                        return a.oam_index > b.oam_index;
                        }
                 );
}

void PPU::render_scanline(){
        if(!bus) throw std::runtime_error("PPU Error : Bus not connected");
        std::uint8_t lcdc{bus->read(lcdc_addr)};
        std::uint8_t ly{bus->read(ly_addr)};
        std::uint8_t scx{bus->read(scx_addr)};
        std::uint8_t scy{bus->read(scy_addr)};
        std::uint8_t bgp{bus->read(bgp_addr)};
        std::uint8_t wx{bus->read(wx_addr)};
        std::uint8_t wy{bus->read(wy_addr)};

        std::uint16_t lcd_enable{static_cast<std::uint16_t>(lcdc & 0x80)};
        std::uint16_t window_tile_map_area{static_cast<std::uint16_t>((lcdc & 0x40) ? 0x9C00 : 0x9800)};
        std::uint16_t window_enable{static_cast<std::uint16_t>(lcdc & 0x20)};
        std::uint16_t bg_window_tile_data_area{static_cast<std::uint16_t>((lcdc & 0x10) ? 0x8000 : 0x8800)};
        std::uint16_t bg_tile_map_area{static_cast<std::uint16_t>((lcdc & 0x08) ? 0x9C00 : 0x9800)};
        std::uint16_t obj_size{static_cast<std::uint16_t>((lcdc & 0x04) ? 8*16 : 8*8)};
        std::uint16_t sprite_height{static_cast<std::uint16_t>(obj_size == 8*16 ? 16 : 8)};
        std::uint16_t obj_enable{static_cast<std::uint16_t>(lcdc & 0x02)};
        std::uint16_t priority{static_cast<std::uint16_t>(lcdc & 0x01)};

        // Background Rendering
        if(lcd_enable){
                std::uint8_t bg_priority[160]{0};
                if(priority){
                        for (int x{0}; x < 160; ++x) {
                                std::uint8_t map_x{static_cast<std::uint8_t>(scx + x)};
                                std::uint8_t map_y{static_cast<std::uint8_t>(scy + ly)};

                                std::uint16_t tile_col{static_cast<std::uint16_t>(map_x>>3)};
                                std::uint16_t tile_row{static_cast<std::uint16_t>(map_y>>3)};

                                std::uint16_t tile_map_address{static_cast<std::uint16_t>(bg_tile_map_area + (tile_row * 32) + tile_col)};

                                std::uint8_t tile_index{bus->read(tile_map_address)};

                                std::uint16_t tile_data_addr{};

                                if (bg_window_tile_data_area == 0x8000) {
                                        tile_data_addr = 0x8000 + (tile_index * 16);
                                } else {
                                        std::int8_t signed_index{static_cast<std::int8_t>(tile_index)};
                                        tile_data_addr = 0x9000 + (signed_index * 16);
                                }

                                std::uint8_t line_in_tile{static_cast<std::uint8_t>((map_y % 8) * 2)};

                                std::uint8_t byte1{bus->read(tile_data_addr + line_in_tile)};
                                std::uint8_t byte2{bus->read(tile_data_addr + line_in_tile + 1)};

                                std::uint8_t bit_index{static_cast<std::uint8_t>(7 - (map_x % 8))};

                                std::uint8_t low_bit{static_cast<std::uint8_t>((byte1 >> bit_index) & 0x01)};
                                std::uint8_t high_bit{static_cast<std::uint8_t>((byte2 >> bit_index) & 0x01)};

                                std::uint8_t color_id{static_cast<std::uint8_t>((high_bit << 1) | low_bit)};

                                bg_priority[x] = color_id;
                                std::uint8_t shade{static_cast<std::uint8_t>((bgp >> (color_id * 2)) & 0x03)};

                                video_buffer[ly * 160 + x] = colors[shade];
                        }
                }

                // Window rendering
                if (ly == 0) window_line_counter = 0;

                if (window_enable && ly >= wy && wx <= 166){
                        for (int x{0}; x < 160; ++x) {

                                if (x >= wx - 7){ //  hardware quirk of plus 7
                                        // this is due to the wx behaviour it is always
                                        // +7 from its original value
                                        std::uint8_t map_x{static_cast<std::uint8_t>(x - (wx - 7))};

                                        std::uint8_t map_y{static_cast<std::uint8_t>(window_line_counter)};

                                        std::uint16_t tile_col{static_cast<std::uint16_t>(map_x>>3)};
                                        std::uint16_t tile_row{static_cast<std::uint16_t>(map_y>>3)};

                                        std::uint16_t tile_map_addr{static_cast<std::uint16_t>(
                                                        window_tile_map_area + (tile_row * 32) + tile_col)};
                                        std::uint8_t tile_index = bus->read(tile_map_addr);

                                        std::uint16_t tile_data_addr{};
                                        if (bg_window_tile_data_area == 0x8000) {
                                                tile_data_addr = 0x8000 + (tile_index * 16);
                                        } else {
                                                std::int8_t signed_index{static_cast<std::int8_t>(tile_index)};
                                                tile_data_addr = 0x9000 + (signed_index * 16);
                                        }

                                        std::uint8_t line_in_tile{static_cast<std::uint8_t>((map_y % 8) * 2)};
                                        std::uint8_t byte1{bus->read(tile_data_addr + line_in_tile)};
                                        std::uint8_t byte2{bus->read(tile_data_addr + line_in_tile + 1)};

                                        std::uint8_t bit_index{static_cast<std::uint8_t>(7 - (map_x % 8))};
                                        std::uint8_t lo{static_cast<std::uint8_t>((byte1 >> bit_index) & 0x01)};
                                        std::uint8_t hi{static_cast<std::uint8_t>((byte2 >> bit_index) & 0x01)};;
                                        std::uint8_t color_id{static_cast<std::uint8_t>((hi << 1) | lo)};

                                        bg_priority[x] = color_id;

                                        std::uint8_t shade{static_cast<std::uint8_t>((bgp >> (color_id * 2)) & 0x03)};
                                        video_buffer[ly * 160 + x] = colors[shade];
                                }
                        }

                        window_line_counter++;
                }

                // Sprite Rendering
                if(obj_enable){
                        for (const auto& sprite : sprite_buffer) {
                                std::int16_t sprite_x{static_cast<std::int16_t>(sprite.x - 8)};
                                std::int16_t sprite_y{static_cast<std::int16_t>(sprite.y - 16)};

                                std::uint8_t palette_use_obp1{static_cast<std::uint8_t>(sprite.flags & 0x10)};
                                std::uint8_t x_flip{static_cast<std::uint8_t>(sprite.flags & 0x20)};
                                std::uint8_t y_flip{static_cast<std::uint8_t>(sprite.flags & 0x40)};
                                std::uint8_t bg_priority_flag{static_cast<std::uint8_t>(sprite.flags & 0x80)};

                                std::int16_t line{static_cast<std::int16_t>(ly - sprite_y)};

                                if (y_flip) {
                                        line = sprite_height - 1 - line;
                                }

                                std::uint8_t tile_idx{sprite.tile_index};

                                if (sprite_height == 16) tile_idx &= 0xFE;

                                std::uint16_t data_addr{static_cast<std::uint16_t>(0x8000 + (tile_idx * 16) + (line * 2))};
                                std::uint8_t byte1{bus->read(data_addr)};
                                std::uint8_t byte2{bus->read(data_addr + 1)};

                                for (int p{0}; p < 8; ++p) {
                                        int pixel_x{sprite_x + p};

                                        if (pixel_x < 0 || pixel_x >= 160) continue;

                                        int bit_idx{x_flip ? p : (7 - p)};

                                        std::uint8_t lo{static_cast<std::uint8_t>((byte1 >> bit_idx) & 0x01)};
                                        std::uint8_t hi{static_cast<std::uint8_t>((byte2 >> bit_idx) & 0x01)};
                                        std::uint8_t color_id{static_cast<std::uint8_t>((hi << 1) | lo)};

                                        if (color_id == 0) continue;

                                        if (bg_priority_flag && bg_priority[pixel_x] != 0) continue;

                                        std::uint16_t palette_addr{palette_use_obp1 ? obp1_addr : obp0_addr};
                                        std::uint8_t palette{bus->read(palette_addr)};

                                        std::uint8_t shade{static_cast<std::uint8_t>((palette >> (color_id * 2)) & 0x03)};

                                        video_buffer[ly * 160 + pixel_x] = colors[shade];
                                }
                        }
                }
        }
}

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
                                        run_oam_search();
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
                                        run_oam_search();
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
