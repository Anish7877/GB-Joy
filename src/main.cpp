#include "../include/screen.hpp"
#include "../include/bus.hpp"
#include "../include/cpu.hpp"
#include "../include/ppu.hpp"
#include "../include/apu.hpp"
#include "../include/cartridge.hpp"
#include "../include/audio.hpp"
#include <exception>
#include <iostream>
#include <memory>

void print_usage(){
        std::cout << "Usage :-" << '\n';
        std::cout << "./GBJoy <path-to-gameboy-dmg-rom>" << '\n';
        std::cout << "./GBJoy help" << '\n';
}
void help_menu(){
        std::cout << "Controls :-" << '\n';
        std::cout << "Dpad Up    - W" << '\n';
        std::cout << "Dpad Down  - S" << '\n';
        std::cout << "Dpad Left  - A" << '\n';
        std::cout << "Dpad Right - D" << '\n';
        std::cout << "Start      - 1" << '\n';
        std::cout << "Select     - 2" << '\n';
        std::cout << "A          - J" << '\n';
        std::cout << "B          - K" << '\n';
}
int main(int argc, char** argv){
        using namespace std::literals;
        try {
                if (argc < 2){
                        throw std::runtime_error("Usage :-\n./GBJoy <path-to-gameboy-rom>");
                }
                std::string arg{argv[1]};
                if(argv[1] == "help"s){
                        print_usage();
                        help_menu();
                        return 0;
                }
                static constexpr int TARGET_FPS{60};
                static constexpr int frame_delay{1000 / TARGET_FPS};
                std::uint32_t frame_start_time{0};
                int frame_time{0};
                std::shared_ptr<Bus> bus{std::make_shared<Bus>()};
                std::shared_ptr<CPU> cpu{std::make_shared<CPU>()};
                std::shared_ptr<PPU> ppu{std::make_shared<PPU>()};
                std::shared_ptr<APU> apu{std::make_shared<APU>()};
                std::shared_ptr<Joypad> joypad{std::make_shared<Joypad>()};
                std::shared_ptr<Cartridge> cart{std::make_shared<Cartridge>()};
                std::shared_ptr<Audio> audio{std::make_shared<Audio>()};
                std::shared_ptr<Screen> screen{};

                cart->load(std::string(argv[1]));
                screen = std::make_shared<Screen>(cart->get_cartridge_title(), 6);
                cpu->connect_to_bus(bus);
                cpu->connect_to_ppu(ppu);
                cpu->connect_to_apu(apu);
                ppu->connect_to_bus(bus);
                bus->connect_apu(apu);
                apu->connect_to_bus(bus);
                bus->insert_cartridge(cart);
                bus->connect_joypad(joypad);
                screen->connect_to_bus(bus);

                bus->write(0xFF40, 0x91);

                bool quit{false};
                while (!quit){
                        frame_start_time = SDL_GetTicks();

                        while (!ppu->set_frame_complete_flag()){
                                cpu->step();

                                audio->set_audio_accumulator(cpu->get_internal_audio_accumulator());
                                while(audio->get_audio_accumulator() >= Audio::cycles_per_sample){
                                        audio->set_audio_accumulator(audio->get_audio_accumulator() - cpu->get_internal_audio_accumulator());
                                        if (audio->audio_device_check()) {
                                                float sample{apu->get_sample()};
                                                audio->update_audio_device_data(sample);
                                        }
                                }
                                cpu->set_internal_audio_accumulator(audio->get_audio_accumulator());
                        }

                        ppu->unset_frame_complete_flag();
                        screen->update_screen(ppu->get_buffer());
                        if (screen->handle_events()) quit = true;

                        frame_time = SDL_GetTicks() - frame_start_time;
                        if (frame_delay > frame_time) {
                                SDL_Delay(frame_delay - frame_time);
                        }
                }

        }
        catch(const std::exception& e){
                std::cout << e.what() << '\n';
                return -1;
        }
        return 0;
}
