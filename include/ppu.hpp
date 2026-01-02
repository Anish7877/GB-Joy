#ifndef PPU_HPP
#define PPU_HPP
#include <cstdint>
#include <memory>
#include <vector>
class Bus;
class PPU{
        public:
                explicit PPU() = default;
                void connect_to_bus(const std::shared_ptr<Bus>& bus) noexcept;
                void tick(unsigned int cycles);
                std::uint8_t get_lcdc() const noexcept;
                std::uint8_t get_stat() const noexcept;
                std::uint8_t get_scx() const noexcept;
                std::uint8_t get_scy() const noexcept;
                std::uint8_t get_ly() const noexcept;
                std::uint8_t get_lyc() const noexcept;
                std::uint8_t get_bgp() const noexcept;
                std::uint8_t get_wx() const noexcept;
                std::uint8_t get_wy() const noexcept;
                std::vector<std::uint32_t> get_buffer() const noexcept {return video_buffer;}
                bool frame_complete{false};
        private:
                struct ObjectAttribute{
                        std::uint8_t y{};
                        std::uint8_t x{};
                        std::uint8_t tile_index{};
                        std::uint8_t flags{};
                };
                std::vector<ObjectAttribute> sprite_buffer{};
                std::vector<std::uint32_t> video_buffer{std::vector<std::uint32_t>(160 * 144, 0xFFFFFFFF)};
                const std::uint32_t colors[4] = {0xFFFFFFFF, 0xFFD3D3D3, 0xFF888888, 0xFF000000};
                std::uint16_t internal_cycles{0};
                std::uint8_t current_mode{2};
                std::shared_ptr<Bus> bus{};
                const std::uint16_t lcdc_addr{0xFF40};
                const std::uint16_t stat_addr{0xFF41};
                const std::uint16_t scx_addr{0xFF42};
                const std::uint16_t scy_addr{0xFF43};
                const std::uint16_t ly_addr{0xFF44};
                const std::uint16_t lyc_addr{0xFF45};
                const std::uint16_t bgp_addr{0xFF47};
                const std::uint16_t wx_addr{0xFF4A};
                const std::uint16_t wy_addr{0xFF4B};

                void update_stat_mode(std::uint8_t mode) noexcept;
                void compare_ly_lyc() noexcept;
                void render_scanline();
};
#endif
