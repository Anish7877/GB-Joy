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
                explicit Screen(std::string_view title);
                ~Screen();
                void connect_to_bus(const std::shared_ptr<Bus>& bus) noexcept;
                void update_window_width(unsigned int new_width) noexcept;
                void update_window_height(unsigned int new_height) noexcept;
                void update_window_title(std::string_view new_title) noexcept;
                void update_screen(const std::vector<std::uint32_t>& video_buffer);
                bool handle_events();
        private:
                unsigned int window_width{160};
                unsigned int window_height{144};
                unsigned int scale{4};
                std::string window_title{};
                SDL_Window* window{};
                SDL_Renderer* renderer{};
                SDL_Texture* texture{};
                SDL_Texture* debug_texture{};
                std::shared_ptr<Bus> bus{};
};
#endif
