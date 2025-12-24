#include "../include/cpu.hpp"
#include "../include/bus.hpp"
#include "../include/cartridge.hpp"
#include <memory>

int main(void){
        std::shared_ptr<Cartridge> cartridge{std::make_shared<Cartridge>()};
        std::shared_ptr<Bus> bus{std::make_shared<Bus>()};
        CPU cpu{};
        cartridge->load("/home/anish/Downloads/gameboy/Super Mario Land (World) (Rev 1).gb");
        bus->insert_cartridge(cartridge);
        cpu.connect_to_bus(bus);
        while(true){
                cpu.step();
        }
        return 0;
}
