#ifndef APU_HPP
#define APU_HPP
#include <cstdint>
class APU{
        public:
                explicit APU() = default;
        private:
                static constexpr std::uint16_t nr_52_master_control_addr{0xFF26};
                static constexpr std::uint16_t nr_51_sound_panning_addr{0xFF25};
                static constexpr std::uint16_t nr_50_master_volume_vin_panning_addr{0xFF24};
                static constexpr std::uint16_t nr_10_channel_1_sweep_addr{0xFF10};
                static constexpr std::uint16_t nr_11_channel_1_length_duty_addr{0xFF11};
                static constexpr std::uint16_t nr_12_channel_1_volume_envelope_addr{0xFF12};
};
#endif
