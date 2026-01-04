#include "../include/screen.hpp"
#include "../include/bus.hpp"
#include "../include/cpu.hpp"
#include "../include/ppu.hpp"
#include "../include/cartridge.hpp"
#include <exception>
#include <iostream>

int main(int argc, char** argv) {
        try{
                if(argc < 2){
                        throw std::runtime_error("Usage : GBJoy <path-to-gameboy-rom>");
                }
                // 1. Setup Components
                auto bus = std::make_shared<Bus>();
                auto cpu = std::make_shared<CPU>();
                auto ppu = std::make_shared<PPU>();
                auto joypad = std::make_shared<Joypad>();
                auto cart = std::make_shared<Cartridge>(); // Load your ROM

                // 2. Connect
                cart->load(std::string(argv[1]));
                cpu->connect_to_bus(bus);
                cpu->connect_to_ppu(ppu); // Ensure CPU has PPU pointer for HALT ticks
                ppu->connect_to_bus(bus);
                bus->insert_cartridge(cart);
                bus->connect_joypad(joypad);

                // 3. Setup Screen
                Screen screen{cart->get_cartridge_title(), 6};
                screen.connect_to_bus(bus);

                bus->write(0xFF40, 0x91);

                // 4. Main Loop
                bool quit = false;
                while (!quit) {
                        cpu->step();

                        if (ppu->frame_complete) {
                                ppu->frame_complete = false;

                                screen.update_screen(ppu->get_buffer());

                                // Handle Inputs
                                if (screen.handle_events()) {
                                        quit = true;
                                }
                        }}
        }
        catch(const std::exception& e){
                std::cout << e.what() << '\n';
        }

    return 0;
}
