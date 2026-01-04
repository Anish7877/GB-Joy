#ifndef SCREEN_HPP
#define SCREEN_HPP
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
class Bus;
class Screen{
        public:
                explicit Screen(std::string_view title, unsigned int scale);
                ~Screen();
                void connect_to_bus(const std::shared_ptr<Bus>& bus) noexcept;
                void update_screen(const std::vector<std::uint32_t>& video_buffer);
                bool handle_events();
        private:
                static constexpr unsigned int window_width{160};
                static constexpr unsigned int window_height{144};
                unsigned int scale{8};
                std::string window_title{};
                SDL_Window* window{};
                SDL_Renderer* renderer{};
                SDL_Texture* texture{};
                SDL_Texture* debug_texture{};
                std::shared_ptr<Bus> bus{};
};
#endif
