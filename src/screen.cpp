#include "../include/screen.hpp"
#include "../include/bus.hpp"
#include <stdexcept>

Screen::Screen(std::string_view title){
        window_title = title.data();
        SDL_Init(SDL_INIT_VIDEO);

        window = SDL_CreateWindow(window_title.c_str(),
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  window_width*scale,
                                  window_height*scale,
                                  0);
        if(!window) throw std::runtime_error(SDL_GetError());
        renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
        if(!renderer) throw std::runtime_error(SDL_GetError());
        texture = (SDL_CreateTexture(renderer,
                                     SDL_PIXELFORMAT_ARGB8888,
                                     SDL_TEXTUREACCESS_STREAMING,
                                     window_width,
                                     window_height));
        if(!texture) throw std::runtime_error(SDL_GetError());
}

Screen::~Screen(){
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
}

void Screen::connect_to_bus(const std::shared_ptr<Bus>& bus) noexcept{
        this->bus = bus;
}

void Screen::update_window_width(unsigned int new_width) noexcept{
        window_width = new_width;
}

void Screen::update_window_height(unsigned int new_height) noexcept{
        window_height = new_height;
}

void Screen::update_window_title(std::string_view new_title) noexcept{
        window_title = new_title;
}

void Screen::update_screen(const std::vector<std::uint32_t>& video_buffer){
        void* raw_pixels{};
        int pitch{};
        if(SDL_LockTexture(texture, nullptr, &raw_pixels, &pitch) < 0){
                throw std::runtime_error(SDL_GetError());
        }

        memcpy(raw_pixels, video_buffer.data(), video_buffer.size() * sizeof(std::uint32_t));

        SDL_UnlockTexture(texture);
        if(SDL_RenderClear(renderer) < 0) throw std::runtime_error(SDL_GetError());
        if(SDL_RenderCopy(renderer, texture, nullptr, nullptr) < 0) throw std::runtime_error(SDL_GetError());
        SDL_RenderPresent(renderer);
}

bool Screen::handle_events(){
        if(!bus) throw std::runtime_error("Screen Error: Bus not connected");
        SDL_Event event{};
        while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                        return true;
                }
                else if(event.type == SDL_KEYUP){
                        switch(event.key.keysym.sym){
                                case SDL_KeyCode::SDLK_w:
                                        bus->key_up(Joypad::Keys::UP);
                                        break;
                                case SDL_KeyCode::SDLK_s:
                                        bus->key_up(Joypad::Keys::DOWN);
                                        break;
                                case SDL_KeyCode::SDLK_a:
                                        bus->key_up(Joypad::Keys::LEFT);
                                        break;
                                case SDL_KeyCode::SDLK_d:
                                        bus->key_up(Joypad::Keys::RIGHT);
                                        break;
                                case SDL_KeyCode::SDLK_1:
                                        bus->key_up(Joypad::Keys::START);
                                        break;
                                case SDL_KeyCode::SDLK_2:
                                        bus->key_up(Joypad::Keys::SELECT);
                                        break;
                                case SDL_KeyCode::SDLK_j:
                                        bus->key_up(Joypad::Keys::A);
                                        break;
                                case SDL_KeyCode::SDLK_k:
                                        bus->key_up(Joypad::Keys::B);
                                        break;
                                default:
                                        break;
                        }
                }
                else if(event.type == SDL_KEYDOWN){
                        switch(event.key.keysym.sym){
                                case SDL_KeyCode::SDLK_w:
                                        bus->key_down(Joypad::Keys::UP);
                                        break;
                                case SDL_KeyCode::SDLK_s:
                                        bus->key_down(Joypad::Keys::DOWN);
                                        break;
                                case SDL_KeyCode::SDLK_a:
                                        bus->key_down(Joypad::Keys::LEFT);
                                        break;
                                case SDL_KeyCode::SDLK_d:
                                        bus->key_down(Joypad::Keys::RIGHT);
                                        break;
                                case SDL_KeyCode::SDLK_1:
                                        bus->key_down(Joypad::Keys::START);
                                        break;
                                case SDL_KeyCode::SDLK_2:
                                        bus->key_down(Joypad::Keys::SELECT);
                                        break;
                                case SDL_KeyCode::SDLK_j:
                                        bus->key_down(Joypad::Keys::A);
                                        break;
                                case SDL_KeyCode::SDLK_k:
                                        bus->key_down(Joypad::Keys::B);
                                        break;
                                default:
                                        break;
                        }
                }
        }
        return false;
}
