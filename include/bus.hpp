#ifndef BUS_HPP
#define BUS_HPP
#include <cstdint>
#include <memory>
constexpr std::size_t VRAM_SIZE{8192};
constexpr std::size_t WRAM_SIZE{8192};
constexpr std::size_t OAM_SIZE{160};
constexpr std::size_t IO_SIZE{128};
constexpr std::size_t HRAM_SIZE{127};

class Cartridge;
class Bus {
        public:
                explicit Bus() = default;
                std::uint8_t read(std::uint16_t addr);
                bool write(std::uint16_t addr, std::uint8_t data);
                void insert_cartridge(const std::shared_ptr<Cartridge>& cart);
        private:
                std::shared_ptr<Cartridge> cartridge{};
                std::uint8_t vram[VRAM_SIZE]{0};
                std::uint8_t wram[WRAM_SIZE]{0};
                std::uint8_t oam[OAM_SIZE]{0};
                std::uint8_t io_registers[IO_SIZE]{0};
                std::uint8_t hram[HRAM_SIZE]{0};
                std::uint8_t interrupt_enable_register{0};
};
#endif
