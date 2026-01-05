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
                bool set_frame_complete_flag() const noexcept {return frame_complete;};
                void unset_frame_complete_flag() noexcept {frame_complete = false;}
        private:
                static constexpr std::uint32_t colors[4]{0xFFE0F8D0, 0xFF88C070, 0xFF346856, 0xFF081820};
                bool frame_complete{false};
                struct ObjectAttribute{
                        std::uint8_t y{};
                        std::uint8_t x{};
                        std::uint8_t tile_index{};
                        std::uint8_t flags{};
                        std::uint8_t oam_index{};
                };
                std::vector<ObjectAttribute> sprite_buffer{};
                std::vector<std::uint32_t> video_buffer{std::vector<std::uint32_t>(160 * 144, colors[0])};
                std::uint16_t internal_cycles{0};
                std::uint8_t current_mode{2};
                std::uint8_t window_line_counter{};
                std::shared_ptr<Bus> bus{};

                static constexpr std::uint16_t lcdc_addr{0xFF40};
                static constexpr std::uint16_t stat_addr{0xFF41};
                static constexpr std::uint16_t scx_addr{0xFF43};
                static constexpr std::uint16_t scy_addr{0xFF42};
                static constexpr std::uint16_t ly_addr{0xFF44};
                static constexpr std::uint16_t lyc_addr{0xFF45};
                static constexpr std::uint16_t bgp_addr{0xFF47};
                static constexpr std::uint16_t obp0_addr{0xFF48};
                static constexpr std::uint16_t obp1_addr{0xFF49};
                static constexpr std::uint16_t wy_addr{0xFF4A};
                static constexpr std::uint16_t wx_addr{0xFF4B};

                void update_stat_mode(std::uint8_t mode) noexcept;
                void compare_ly_lyc() noexcept;
                void run_oam_search();
                void render_scanline();
};
#endif
