#include "../include/cpu.hpp"
#include "../include/bus.hpp"

CPU::CPU(){
        lookup_table.resize(256);
        lookup_table = {
                {[this](){this->nop();}},
                {[this](){this->load_bc();}},
                {[this](){this->load_addr_bc_a();}},
                {[this](){this->inc_bc();}},
                {[this](){this->inc_b();}},
                {[this](){this->dec_b();}},
                {[this](){this->load_b();}},
                {[this](){this->rlca();}},
                {[this](){this->load_addr_sp();}},
                {[this](){this->add_hl_bc();}},
                {[this](){this->load_a_addr_bc();}},
                {[this](){this->dec_bc();}},
                {[this](){this->inc_c();}},
                {[this](){this->dec_c();}},
                {[this](){this->load_c();}},
                {[this](){this->rrca();}},
                {[this](){this->stop();}},
                {[this](){this->load_de();}},
                {[this](){this->load_addr_de_a();}},
                {[this](){this->inc_de();}},
                {[this](){this->inc_d();}},
                {[this](){this->dec_d();}},
                {[this](){this->load_d();}},
                {[this](){this->rla();}},
                {[this](){this->jr();}},
                {[this](){this->add_hl_de();}},
                {[this](){this->load_a_addr_de();}},
                {[this](){this->dec_de();}},
                {[this](){this->inc_e();}},
                {[this](){this->dec_e();}},
                {[this](){this->load_e();}},
                {[this](){this->rra();}},
                {[this](){this->jr_nz();}},
                {[this](){this->load_hl();}},
                {[this](){this->load_addr_hl_plus_a();}},
                {[this](){this->inc_hl();}},
                {[this](){this->inc_h();}},
                {[this](){this->dec_h();}},
                {[this](){this->load_h();}},
                {[this](){this->daa();}},
                {[this](){this->jr_z();}},
                {[this](){this->add_hl_hl();}},
                {[this](){this->load_a_addr_hl_plus();}},
                {[this](){this->dec_hl();}},
                {[this](){this->inc_l();}},
                {[this](){this->dec_l();}},
                {[this](){this->load_l();}},
                {[this](){this->cpl();}},
                {[this](){this->jr_nc();}},
                {[this](){this->load_sp();}},
                {[this](){this->load_addr_hl_minus_a();}},
                {[this](){this->inc_sp();}},
                {[this](){this->inc_addr_hl();}},
                {[this](){this->dec_addr_hl();}},
                {[this](){this->load_addr_hl();}},
                {[this](){this->scf();}},
                {[this](){this->jr_c();}},
                {[this](){this->add_hl_sp();}},
                {[this](){this->load_a_addr_hl_minus();}},
                {[this](){this->dec_sp();}},
                {[this](){this->inc_a();}},
                {[this](){this->dec_a();}},
                {[this](){this->load_a();}},
                {[this](){this->ccf();}},
                {[this](){this->load_b_b();}},
                {[this](){this->load_b_c();}},
                {[this](){this->load_b_d();}},
                {[this](){this->load_b_e();}},
                {[this](){this->load_b_h();}},
                {[this](){this->load_b_l();}},
                {[this](){this->load_b_addr_hl();}},
                {[this](){this->load_b_a();}},
                {[this](){this->load_c_b();}},
                {[this](){this->load_c_c();}},
                {[this](){this->load_c_d();}},
                {[this](){this->load_c_e();}},
                {[this](){this->load_c_h();}},
                {[this](){this->load_c_l();}},
                {[this](){this->load_c_addr_hl();}},
                {[this](){this->load_c_a();}},
                {[this](){this->load_d_b();}},
                {[this](){this->load_d_c();}},
                {[this](){this->load_d_d();}},
                {[this](){this->load_d_e();}},
                {[this](){this->load_d_h();}},
                {[this](){this->load_d_l();}},
                {[this](){this->load_d_addr_hl();}},
                {[this](){this->load_d_a();}},
                {[this](){this->load_e_b();}},
                {[this](){this->load_e_c();}},
                {[this](){this->load_e_d();}},
                {[this](){this->load_e_e();}},
                {[this](){this->load_e_h();}},
                {[this](){this->load_e_l();}},
                {[this](){this->load_e_addr_hl();}},
                {[this](){this->load_e_a();}},
                {[this](){this->load_h_b();}},
                {[this](){this->load_h_c();}},
                {[this](){this->load_h_d();}},
                {[this](){this->load_h_e();}},
                {[this](){this->load_h_h();}},
                {[this](){this->load_h_l();}},
                {[this](){this->load_h_addr_hl();}},
                {[this](){this->load_h_a();}},
                {[this](){this->load_l_b();}},
                {[this](){this->load_l_c();}},
                {[this](){this->load_l_d();}},
                {[this](){this->load_l_e();}},
                {[this](){this->load_l_h();}},
                {[this](){this->load_l_l();}},
                {[this](){this->load_l_addr_hl();}},
                {[this](){this->load_l_a();}},
                {[this](){this->load_addr_hl_b();}},
                {[this](){this->load_addr_hl_c();}},
                {[this](){this->load_addr_hl_d();}},
                {[this](){this->load_addr_hl_e();}},
                {[this](){this->load_addr_hl_h();}},
                {[this](){this->load_addr_hl_l();}},
                {[this](){this->halt();}},
                {[this](){this->load_addr_hl_a();}},
                {[this](){this->load_a_b();}},
                {[this](){this->load_a_c();}},
                {[this](){this->load_a_d();}},
                {[this](){this->load_a_e();}},
                {[this](){this->load_a_h();}},
                {[this](){this->load_a_l();}},
                {[this](){this->load_a_addr_hl();}},
                {[this](){this->load_a_a();}},
                {[this](){this->add_a_b();}},
                {[this](){this->add_a_c();}},
                {[this](){this->add_a_d();}},
                {[this](){this->add_a_e();}},
                {[this](){this->add_a_h();}},
                {[this](){this->add_a_l();}},
                {[this](){this->add_a_addr_hl();}},
                {[this](){this->add_a_a();}},
                {[this](){this->adc_a_b();}},
                {[this](){this->adc_a_c();}},
                {[this](){this->adc_a_d();}},
                {[this](){this->adc_a_e();}},
                {[this](){this->adc_a_h();}},
                {[this](){this->adc_a_l();}},
                {[this](){this->adc_a_addr_hl();}},
                {[this](){this->adc_a_a();}},
                {[this](){this->sub_a_b();}},
                {[this](){this->sub_a_c();}},
                {[this](){this->sub_a_d();}},
                {[this](){this->sub_a_e();}},
                {[this](){this->sub_a_h();}},
                {[this](){this->sub_a_l();}},
                {[this](){this->sub_a_addr_hl();}},
                {[this](){this->sub_a_a();}},
                {[this](){this->sbc_a_b();}},
                {[this](){this->sbc_a_c();}},
                {[this](){this->sbc_a_d();}},
                {[this](){this->sbc_a_e();}},
                {[this](){this->sbc_a_h();}},
                {[this](){this->sbc_a_l();}},
                {[this](){this->sbc_a_addr_hl();}},
                {[this](){this->sbc_a_a();}},
                {[this](){this->and_a_b();}},
                {[this](){this->and_a_c();}},
                {[this](){this->and_a_d();}},
                {[this](){this->and_a_e();}},
                {[this](){this->and_a_h();}},
                {[this](){this->and_a_l();}},
                {[this](){this->and_a_addr_hl();}},
                {[this](){this->and_a_a();}},
                {[this](){this->xor_a_b();}},
                {[this](){this->xor_a_c();}},
                {[this](){this->xor_a_d();}},
                {[this](){this->xor_a_e();}},
                {[this](){this->xor_a_h();}},
                {[this](){this->xor_a_l();}},
                {[this](){this->xor_a_addr_hl();}},
                {[this](){this->xor_a_a();}},
                {[this](){this->or_a_b();}},
                {[this](){this->or_a_c();}},
                {[this](){this->or_a_d();}},
                {[this](){this->or_a_e();}},
                {[this](){this->or_a_h();}},
                {[this](){this->or_a_l();}},
                {[this](){this->or_a_addr_hl();}},
                {[this](){this->or_a_a();}},
                {[this](){this->cp_a_b();}},
                {[this](){this->cp_a_c();}},
                {[this](){this->cp_a_d();}},
                {[this](){this->cp_a_e();}},
                {[this](){this->cp_a_h();}},
                {[this](){this->cp_a_l();}},
                {[this](){this->cp_a_addr_hl();}},
                {[this](){this->cp_a_a();}},
                {[this](){this->ret_nz();}},
                {[this](){this->pop_bc();}},
                {[this](){this->jp_nz();}},
                {[this](){this->jp();}},
                {[this](){this->call_nz();}},
                {[this](){this->push_bc();}},
                {[this](){this->add_a();}},
                {[this](){this->rst_00h();}},
                {[this](){this->ret_z();}},
                {[this](){this->ret();}},
                {[this](){this->jp_z();}},
                {[this](){this->prefix();}},
                {[this](){this->call_z();}},
                {[this](){this->call();}},
                {[this](){this->adc_a();}},
                {[this](){this->rst_08h();}},
                {[this](){this->ret_nc();}},
                {[this](){this->pop_de();}},
                {[this](){this->jp_nc();}},
                {[this](){return;}},
                {[this](){this->call_nc();}},
                {[this](){this->push_de();}},
                {[this](){this->sub_a();}},
                {[this](){this->rst_10h();}},
                {[this](){this->ret_c();}},
                {[this](){this->reti();}},
                {[this](){this->jp_c();}},
                {[this](){return;}},
                {[this](){this->call_c();}},
                {[this](){return;}},
                {[this](){this->sbc_a();}},
                {[this](){this->rst_18h();}},
                {[this](){this->ldh_addr_a();}},
                {[this](){this->pop_hl();}},
                {[this](){this->ldh_addr_c_a();}},
                {[this](){return;}},
                {[this](){return;}},
                {[this](){this->push_hl();}},
                {[this](){this->and_a();}},
                {[this](){this->rst_20h();}},
                {[this](){this->add_sp();}},
                {[this](){this->jp_hl();}},
                {[this](){this->load_addr_a();}},
                {[this](){return;}},
                {[this](){return;}},
                {[this](){return;}},
                {[this](){this->xor_a();}},
                {[this](){this->rst_28h();}},
                {[this](){this->ldh_a_addr();}},
                {[this](){return;}},
                {[this](){this->pop_af();}},
                {[this](){this->ldh_a_addr_c();}},
                {[this](){this->di();}},
                {[this](){this->push_af();}},
                {[this](){this->or_a();}},
                {[this](){this->rst_30h();}},
                {[this](){this->load_hl_sp_add();}},
                {[this](){this->load_sp_hl();}},
                {[this](){this->load_a_addr();}},
                {[this](){this->ei();}},
                {[this](){return;}},
                {[this](){return;}},
                {[this](){this->cp_a();}},
                {[this](){this->rst_38h();}}
        };
}
void CPU::connect_to_bus(const std::shared_ptr<Bus>& bus){
        this->bus = bus;
}

std::uint8_t CPU::fetch_byte(){
        std::uint8_t byte{bus->read(pc)};
        pc++;
        return byte;
}

std::uint16_t CPU::fetch_word(){
        std::uint8_t low{fetch_byte()};
        std::uint8_t high{fetch_byte()};
        return (high<<8) | low;
}

void CPU::nop(){
        bus->read(pc);
        pc++;
}

void CPU::load_bc(){
        bc = fetch_word();
}

void CPU::load_addr_bc_a(){
        bus->write(bc, a);
}

void CPU::inc_bc(){
        bc++;
}

void CPU::inc_b(){
        half_carry = ((b&0x0F) == 0x0F);
        b++;
        zero = (b==0);
        n_flag = 0;
}

void CPU::dec_b(){
        half_carry = ((b&0x0F) == 0x00);
        b--;
        zero = (b==0);
        n_flag = 1;
}

void CPU::load_b(){
        b = fetch_byte();
}

void CPU::rlca(){
        std::uint8_t bit7{static_cast<std::uint8_t>((a>>7)&1)};
        a <<= 1;
        a = bit7 ? a | 1 : a;
        zero = 0;
        n_flag = 0;
        half_carry = 0;
        carry = bit7;
}

void CPU::load_addr_sp(){
        std::uint16_t addr{fetch_word()};
        std::uint8_t sp_low{static_cast<std::uint8_t>(sp&0x00FF)};
        std::uint8_t sp_high{static_cast<std::uint8_t>(sp>>8)};
        bus->write(addr, sp_low);
        bus->write(addr+1, sp_high);
}

void CPU::add_hl_bc(){
        std::uint32_t res{static_cast<std::uint32_t>(hl)+static_cast<std::uint32_t>(bc)};
        half_carry = ((hl&0x0FFF)+(bc&0x0FFF) > 0x0FFF);
        carry = (res > 0xFFFF);
        hl = static_cast<std::uint16_t>(res);
        n_flag = 0;
}

void CPU::load_a_addr_bc(){
        a = bus->read(bc);
}

void CPU::dec_bc(){
        bc--;
}

void CPU::inc_c(){
        half_carry = ((c&0x0F) == 0x0F);
        c++;
        zero = (c==0);
        n_flag = 0;
}

void CPU::dec_c(){
        half_carry = ((c&0x0F) == 0x00);
        c--;
        zero = (c==0);
        n_flag = 1;
}

void CPU::load_c(){
        c = fetch_byte();
}

void CPU::rrca(){
        std::uint8_t bit0{static_cast<std::uint8_t>((a)&1)};
        a >>= 1;
        a = bit0 ? a | 0x80 : a;
        zero = 0;
        n_flag = 0;
        half_carry = 0;
        carry = bit0;
}

void CPU::stop(){
        fetch_byte();
        // 2. TODO: Pause the CPU (Implement later!)
        // For now, do nothing. Just let the CPU keep running.
        // If we pause here without working interrupts, the emulator dies.

        // 3. TODO: Handle GBC Speed Switch (Implement much later)
}

void CPU::load_de(){
        de = fetch_word();
}

void CPU::load_addr_de_a(){
        a = bus->read(de);
}

void CPU::inc_de(){
        de++;
}

void CPU::inc_d(){
        half_carry = ((d&0x0F) == 0x0F);
        d++;
        zero = (d==0);
        n_flag = 0;
}

void CPU::dec_d(){
        half_carry = ((d&0x0F) == 0x00);
        d--;
        zero = (d==0);
        n_flag = 1;
}

void CPU::load_d(){
        d = fetch_byte();
}

void CPU::rla(){
        std::uint8_t bit7{static_cast<std::uint8_t>((a>>7)&1)};
        a <<= 1;
        a |= carry;
        zero = 0;
        n_flag = 0;
        half_carry = 0;
        carry = bit7;
}

void CPU::jr(){
        std::int8_t offset{static_cast<std::int8_t>(fetch_byte())};
        pc += offset;
}

void CPU::add_hl_de(){
        std::uint32_t res{static_cast<std::uint32_t>(hl)+static_cast<std::uint32_t>(de)};
        half_carry = (((hl&0x0FFF)+(de&0x0FFF)) > 0x0FFF);
        carry = (res > 0XFFFF);
        hl = static_cast<std::uint16_t>(res);
        n_flag = 0;
}

void CPU::load_a_addr_de(){
        a = bus->read(de);
}

void CPU::dec_de(){
        de--;
}

void CPU::inc_e(){
        half_carry = ((e&0x0f) == 0x0f);
        e++;
        zero = (e==0);
        n_flag = 0;
}

void CPU::dec_e(){
        half_carry = ((e&0x0F) == 0x00);
        e--;
        zero = (e==0);
        n_flag = 1;
}

void CPU::load_e(){
        e = fetch_byte();
}

void CPU::rra(){
        std::uint8_t bit0{static_cast<std::uint8_t>((a)&1)};
        a >>= 1;
        a |= (carry<<7);
        zero = 0;
        n_flag = 0;
        half_carry = 0;
        carry = bit0;
}

void CPU::jr_nz(){
        std::int8_t offset{static_cast<std::int8_t>(fetch_byte())};
        if(!zero){
                pc += offset;
        }
}

void CPU::load_hl(){
        hl = fetch_word();
}

void CPU::load_addr_hl_plus_a(){
        bus->write(hl,a);
        hl++;
}

void CPU::inc_hl(){
        hl++;
}

void CPU::inc_h(){
        half_carry = ((h&0x0f) == 0x0f);
        h++;
        zero = (h==0);
        n_flag = 0;
}

void CPU::dec_h(){
        half_carry = ((h&0x0F) == 0x00);
        h--;
        zero = (h==0);
        n_flag = 1;
}

void CPU::load_h(){
        h = fetch_byte();
}

void CPU::daa(){
        std::uint8_t correction{};
        std::uint8_t set_carry{0};
        if(!n_flag){
                if(half_carry || (a&0x0F) > 0x09){
                        correction |= 0x06;
                }
                if(carry || a > 0x99){
                        correction |= 0x60;
                        set_carry = 1;
                }
                a += correction;
        }
        else{
                if(half_carry){
                        correction |= 0x06;
                }
                if(carry){
                        correction |= 0x60;
                        set_carry = 1;
                }
                a -= correction;
        }
        zero = (a==0);
        half_carry = 0;
        carry = set_carry;
}

void CPU::jr_z(){
        std::int8_t offset{static_cast<std::int8_t>(fetch_byte())};
        if(zero){
                pc += offset;
        }
}

void CPU::add_hl_hl(){
        std::uint32_t res{static_cast<std::uint32_t>(hl) + static_cast<std::uint32_t>(hl)};
        half_carry = ((hl&0x0FFF)+(hl&0x0FFF) > 0x0FFF);
        carry = (res > 0xFFFF);
        hl = static_cast<std::uint16_t>(res);
        n_flag = 0;
}

void CPU::load_a_addr_hl_plus(){
        a = bus->read(hl);
        hl++;
}

void CPU::dec_hl(){
        hl--;
}

void CPU::inc_l(){
        half_carry = ((l&0x0F) == 0x0F);
        l++;
        zero = (l==0);
        n_flag = 0;
}

void CPU::dec_l(){
        half_carry = ((l&0x0F) == 0x00);
        l--;
        zero = (l==0);
        n_flag = 1;
}

void CPU::load_l(){
        l = fetch_byte();
}

void CPU::cpl(){
        a = ~a;
        n_flag = 1;
        half_carry = 1;
}

void CPU::jr_nc(){
        std::int8_t offset{static_cast<std::int8_t>(fetch_byte())};
        if(!carry){
                pc += offset;
        }
}

void CPU::load_sp(){
        sp = fetch_word();
}

void CPU::load_addr_hl_minus_a(){
        bus->write(hl, a);
        hl--;
}

void CPU::inc_sp(){
        sp++;
}

void CPU::inc_addr_hl(){
        std::uint8_t val{bus->read(hl)};
        half_carry = ((val&0x0F) == 0x0F);
        val++;
        zero = (val==0);
        n_flag = 0;
        bus->write(hl, val);
}

void CPU::dec_addr_hl(){
        std::uint8_t val{bus->read(hl)};
        half_carry = ((val&0x0F) == 0x00);
        val--;
        zero = (val==0);
        n_flag = 1;
        bus->write(hl, val);
}

void CPU::load_addr_hl(){
        bus->write(hl, fetch_byte());
}

void CPU::scf(){
        n_flag = 0;
        half_carry = 0;
        carry = 1;
}

void CPU::jr_c(){
        std::int8_t offset{static_cast<int8_t>(fetch_byte())};
        if(carry){
                pc += offset;
        }
}

void CPU::add_hl_sp(){
        std::uint32_t res{static_cast<std::uint32_t>(hl) + static_cast<std::uint32_t>(sp)};
        half_carry = ((hl&0x0FFF)+(sp&0x0FFF) > 0x0FFF);
        carry = (res > 0xFFFF);
        hl = static_cast<std::uint16_t>(res);
        n_flag = 0;
}

void CPU::load_a_addr_hl_minus(){
        a = bus->read(hl);
        hl--;
}

void CPU::dec_sp(){
        sp--;
}

void CPU::inc_a(){
        half_carry = ((a&0x0F) == 0x0F);
        a++;
        zero = (a==0);
        n_flag = 0;
}

void CPU::dec_a(){
        half_carry = ((a&0x0F) == 0x00);
        a--;
        zero = (a==0);
        n_flag = 1;
}

void CPU::load_a(){
        a = fetch_byte();
}

void CPU::ccf(){
        n_flag = 0;
        half_carry = 0;
        carry = ~carry;
}

void CPU::load_b_b(){}

void CPU::load_b_c(){
        b = c;
}

void CPU::load_b_d(){
        b = d;
}

void CPU::load_b_e(){
        b = e;
}

void CPU::load_b_h(){
        b = h;
}

void CPU::load_b_l(){
        b = l;
}

void CPU::load_b_addr_hl(){
        b = bus->read(hl);
}

void CPU::load_b_a(){
        b = a;
}

void CPU::load_c_b(){
        c = b;
}

void CPU::load_c_c(){}

void CPU::load_c_d(){
        c = d;
}

void CPU::load_c_e(){
        c = e;
}

void CPU::load_c_h(){
        c = h;
}

void CPU::load_c_l(){
        c = l;
}

void CPU::load_c_addr_hl(){
        c = bus->read(hl);
}

void CPU::load_c_a(){
        c = a;
}

void CPU::load_d_b(){
        d = b;
}

void CPU::load_d_c(){
        d = c;
}

void CPU::load_d_d(){}

void CPU::load_d_e(){
        d = e;
}

void CPU::load_d_h(){
        d = h;
}

void CPU::load_d_l(){
        d = l;
}

void CPU::load_d_addr_hl(){
        d = bus->read(hl);
}

void CPU::load_d_a(){
        d = a;
}

void CPU::load_e_b(){
        e = b;
}

void CPU::load_e_c(){
        e = c;
}

void CPU::load_e_d(){
        e = d;
}

void CPU::load_e_e(){}

void CPU::load_e_h(){
        e = h;
}

void CPU::load_e_l(){
        e = l;
}

void CPU::load_e_addr_hl(){
        e = bus->read(hl);
}

void CPU::load_e_a(){
        e = a;
}

void CPU::load_h_b(){
        h = b;
}

void CPU::load_h_c(){
        h = c;
}

void CPU::load_h_d(){
        h = d;
}

void CPU::load_h_e(){
        h = e;
}

void CPU::load_h_h(){}

void CPU::load_h_l(){
        h = l;
}

void CPU::load_h_addr_hl(){
        h = bus->read(hl);
}

void CPU::load_h_a(){
        h = a;
}

void CPU::load_l_b(){
        l = b;
}

void CPU::load_l_c(){
        l = c;
}

void CPU::load_l_d(){
        l = d;
}

void CPU::load_l_e(){
        l = e;
}

void CPU::load_l_h(){
        l = h;
}

void CPU::load_l_l(){}

void CPU::load_l_addr_hl(){
        l = bus->read(hl);
}

void CPU::load_l_a(){
        l = a;
}

void CPU::load_addr_hl_b(){
        bus->write(hl, b);
}

void CPU::load_addr_hl_c(){
        bus->write(hl, c);
}

void CPU::load_addr_hl_d(){
        bus->write(hl, d);
}

void CPU::load_addr_hl_e(){
        bus->write(hl, e);
}

void CPU::load_addr_hl_h(){
        bus->write(hl, h);
}

void CPU::load_addr_hl_l(){
        bus->write(hl, l);
}

void CPU::halt(){
        // TO DO implement interrupt enable register and iem
}

void CPU::load_addr_hl_a(){
        bus->write(hl, a);
}

void CPU::load_a_b(){
        a = b;
}

void CPU::load_a_c(){
        a = c;
}

void CPU::load_a_d(){
        a = d;
}

void CPU::load_a_e(){
        a = e;
}

void CPU::load_a_h(){
        a = h;
}

void CPU::load_a_l(){
        a = l;
}

void CPU::load_a_addr_hl(){
        a = bus->read(hl);
}

void CPU::load_a_a(){}

void CPU::add_a_b(){
        std::uint16_t res{static_cast<std::uint16_t>(static_cast<std::uint16_t>(a)+static_cast<std::uint16_t>(b))};
        half_carry = (((a&0x0F)+(b&0xF)) > 0x0F);
        carry = (res > 0xFF);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 0;
}

void CPU::add_a_c(){
        std::uint16_t res{static_cast<std::uint16_t>(static_cast<std::uint16_t>(a)+static_cast<std::uint16_t>(c))};
        half_carry = (((a&0x0F)+(c&0xF)) > 0x0F);
        carry = (res > 0xFF);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 0;
}

void CPU::add_a_d(){
        std::uint16_t res{static_cast<std::uint16_t>(static_cast<std::uint16_t>(a)+static_cast<std::uint16_t>(d))};
        half_carry = (((a&0x0F)+(d&0xF)) > 0x0F);
        carry = (res > 0xFF);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 0;
}

void CPU::add_a_e(){
        std::uint16_t res{static_cast<std::uint16_t>(static_cast<std::uint16_t>(a)+static_cast<std::uint16_t>(e))};
        half_carry = (((a&0x0F)+(e&0xF)) > 0x0F);
        carry = (res > 0xFF);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 0;
}

void CPU::add_a_h(){
        std::uint16_t res{static_cast<std::uint16_t>(static_cast<std::uint16_t>(a)+static_cast<std::uint16_t>(h))};
        half_carry = (((a&0x0F)+(h&0xF)) > 0x0F);
        carry = (res > 0xFF);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 0;
}

void CPU::add_a_l(){
        std::uint16_t res{static_cast<std::uint16_t>(static_cast<std::uint16_t>(a)+static_cast<std::uint16_t>(l))};
        half_carry = (((a&0x0F)+(l&0xF)) > 0x0F);
        carry = (res > 0xFF);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 0;
}

void CPU::add_a_addr_hl(){
        std::uint16_t res{static_cast<std::uint16_t>(static_cast<std::uint16_t>(a)+static_cast<std::uint16_t>(bus->read(hl)))};
        half_carry = (((a&0x0F)+(bus->read(hl)&0xF)) > 0x0F);
        carry = (res > 0xFF);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 0;
}

void CPU::add_a_a(){
        std::uint16_t res{static_cast<std::uint16_t>(static_cast<std::uint16_t>(a)+static_cast<std::uint16_t>(a))};
        half_carry = (((a&0x0F)+(a&0xF)) > 0x0F);
        carry = (res > 0xFF);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 0;
}

void CPU::adc_a_b(){
        std::uint16_t res{static_cast<std::uint16_t>(static_cast<std::uint16_t>(a)+
                                                     static_cast<std::uint16_t>(b)+
                                                     static_cast<std::uint16_t>(carry))};
        half_carry = (((a&0x0F)+(b&0xF)+carry) > 0x0F);
        carry = (res > 0xFF);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 0;
}

void CPU::adc_a_c(){
        std::uint16_t res{static_cast<std::uint16_t>(static_cast<std::uint16_t>(a)+
                                                     static_cast<std::uint16_t>(c)+
                                                     static_cast<std::uint16_t>(carry))};
        half_carry = (((a&0x0F)+(c&0xF)+carry) > 0x0F);
        carry = (res > 0xFF);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 0;
}

void CPU::adc_a_d(){
        std::uint16_t res{static_cast<std::uint16_t>(static_cast<std::uint16_t>(a)+
                                                     static_cast<std::uint16_t>(d)+
                                                     static_cast<std::uint16_t>(carry))};
        half_carry = (((a&0x0F)+(d&0xF)+carry) > 0x0F);
        carry = (res > 0xFF);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 0;
}

void CPU::adc_a_e(){
        std::uint16_t res{static_cast<std::uint16_t>(static_cast<std::uint16_t>(a)+
                                                     static_cast<std::uint16_t>(e)+
                                                     static_cast<std::uint16_t>(carry))};
        half_carry = (((a&0x0F)+(e&0xF)+carry) > 0x0F);
        carry = (res > 0xFF);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 0;
}

void CPU::adc_a_h(){
        std::uint16_t res{static_cast<std::uint16_t>(static_cast<std::uint16_t>(a)+
                                                     static_cast<std::uint16_t>(h)+
                                                     static_cast<std::uint16_t>(carry))};
        half_carry = (((a&0x0F)+(h&0xF)+carry) > 0x0F);
        carry = (res > 0xFF);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 0;
}

void CPU::adc_a_l(){
        std::uint16_t res{static_cast<std::uint16_t>(static_cast<std::uint16_t>(a)+
                                                     static_cast<std::uint16_t>(l)+
                                                     static_cast<std::uint16_t>(carry))};
        half_carry = (((a&0x0F)+(l&0xF)+carry) > 0x0F);
        carry = (res > 0xFF);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 0;
}

void CPU::adc_a_addr_hl(){
        std::uint16_t res{static_cast<std::uint16_t>(static_cast<std::uint16_t>(a)+
                                                     static_cast<std::uint16_t>(bus->read(hl))+
                                                     static_cast<std::uint16_t>(carry))};
        half_carry = (((a&0x0F)+(bus->read(hl)&0xF)+carry) > 0x0F);
        carry = (res > 0xFF);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 0;
}

void CPU::adc_a_a(){
        std::uint16_t res{static_cast<std::uint16_t>(static_cast<std::uint16_t>(a)+
                                                     static_cast<std::uint16_t>(a)+
                                                     static_cast<std::uint16_t>(carry))};
        half_carry = (((a&0x0F)+(a&0xF)+carry) > 0x0F);
        carry = (res > 0xFF);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 0;
}

void CPU::sub_a_b(){
        half_carry = ((a&0x0F) < (b&0x0F));
        carry = (a < b);
        a -= b;
        zero = (a == 0);
        n_flag = 1;
}

void CPU::sub_a_c(){
        half_carry = ((a&0x0F) < (c&0x0F));
        carry = (a < c);
        a -= c;
        zero = (a == 0);
        n_flag = 1;
}

void CPU::sub_a_d(){
        half_carry = ((a&0x0F) < (d&0x0F));
        carry = (a < d);
        a -= d;
        zero = (a == 0);
        n_flag = 1;
}

void CPU::sub_a_e(){
        half_carry = ((a&0x0F) < (e&0x0F));
        carry = (a < e);
        a -= e;
        zero = (a == 0);
        n_flag = 1;
}

void CPU::sub_a_h(){
        half_carry = ((a&0x0F) < (h&0x0F));
        carry = (a < h);
        a -= h;
        zero = (a == 0);
        n_flag = 1;
}

void CPU::sub_a_l(){
        half_carry = ((a&0x0F) < (l&0x0F));
        carry = (a < l);
        a -= l;
        zero = (a == 0);
        n_flag = 1;
}

void CPU::sub_a_addr_hl(){
        half_carry = ((a&0x0F) < (bus->read(hl)&0x0F));
        carry = (a < bus->read(hl));
        a -= bus->read(hl);
        zero = (a == 0);
        n_flag = 1;
}

void CPU::sub_a_a(){
        half_carry = 0;
        carry = 0;
        a = 0;
        zero = 1;
        n_flag = 1;
}

void CPU::sbc_a_b(){
        std::int16_t res{static_cast<std::int16_t>(
                         static_cast<std::int16_t>(a)-
                         static_cast<std::int16_t>(b)-
                         static_cast<std::int16_t>(carry)
                        )};
        half_carry = (((a&0x0F) - (b&0x0F) - carry) < 0);
        carry = (res < 0);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 1;
}

void CPU::sbc_a_c(){
        std::int16_t res{static_cast<std::int16_t>(
                         static_cast<std::int16_t>(a)-
                         static_cast<std::int16_t>(c)-
                         static_cast<std::int16_t>(carry)
                        )};
        half_carry = (((a&0x0F) - (c&0x0F) - carry) < 0);
        carry = (res < 0);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 1;
}

void CPU::sbc_a_d(){
        std::int16_t res{static_cast<std::int16_t>(
                         static_cast<std::int16_t>(a)-
                         static_cast<std::int16_t>(d)-
                         static_cast<std::int16_t>(carry)
                        )};
        half_carry = (((a&0x0F) - (d&0x0F) - carry) < 0);
        carry = (res < 0);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 1;
}

void CPU::sbc_a_e(){
        std::int16_t res{static_cast<std::int16_t>(
                         static_cast<std::int16_t>(a)-
                         static_cast<std::int16_t>(e)-
                         static_cast<std::int16_t>(carry)
                        )};
        half_carry = (((a&0x0F) - (e&0x0F) - carry) < 0);
        carry = (res < 0);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 1;
}

void CPU::sbc_a_h(){
        std::int16_t res{static_cast<std::int16_t>(
                         static_cast<std::int16_t>(a)-
                         static_cast<std::int16_t>(h)-
                         static_cast<std::int16_t>(carry)
                        )};
        half_carry = (((a&0x0F) - (h&0x0F) - carry) < 0);
        carry = (res < 0);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 1;
}

void CPU::sbc_a_l(){
        std::int16_t res{static_cast<std::int16_t>(
                         static_cast<std::int16_t>(a)-
                         static_cast<std::int16_t>(l)-
                         static_cast<std::int16_t>(carry)
                        )};
        half_carry = (((a&0x0F) - (l&0x0F) - carry) < 0);
        carry = (res < 0);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 1;
}

void CPU::sbc_a_addr_hl(){
        std::int16_t res{static_cast<std::int16_t>(
                         static_cast<std::int16_t>(a)-
                         static_cast<std::int16_t>(bus->read(hl))-
                         static_cast<std::int16_t>(carry)
                        )};
        half_carry = (((a&0x0F) - (bus->read(hl)&0x0F) - carry) < 0);
        carry = (res < 0);
        a = static_cast<std::uint8_t>(res);
        zero = (a == 0);
        n_flag = 1;
}

void CPU::sbc_a_a(){
        half_carry = carry;
        a = carry ? 0xFF : 0x00;
        zero = (a == 0);
        n_flag = 1;
}

void CPU::and_a_b(){
        a &= b;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 1;
        carry = 0;
}

void CPU::and_a_c(){
        a &= c;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 1;
        carry = 0;
}

void CPU::and_a_d(){
        a &= d;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 1;
        carry = 0;
}

void CPU::and_a_e(){
        a &= e;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 1;
        carry = 0;
}

void CPU::and_a_h(){
        a &= h;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 1;
        carry = 0;
}

void CPU::and_a_l(){
        a &= l;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 1;
        carry = 0;
}

void CPU::and_a_addr_hl(){
        a &= bus->read(hl);
        zero = (a == 0);
        n_flag = 0;
        half_carry = 1;
        carry = 0;
}

void CPU::and_a_a(){
        a &= a;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 1;
        carry = 0;
}

void CPU::xor_a_b(){
        a ^= b;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 0;
        carry = 0;
}

void CPU::xor_a_c(){
        a ^= c;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 0;
        carry = 0;
}

void CPU::xor_a_d(){
        a ^= d;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 0;
        carry = 0;
}

void CPU::xor_a_e(){
        a ^= e;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 0;
        carry = 0;
}

void CPU::xor_a_h(){
        a ^= h;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 0;
        carry = 0;
}

void CPU::xor_a_l(){
        a ^= l;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 0;
        carry = 0;
}

void CPU::xor_a_addr_hl(){
        a ^= bus->read(hl);
        zero = (a == 0);
        n_flag = 0;
        half_carry = 0;
        carry = 0;
}

void CPU::xor_a_a(){
        a ^= a;
        zero = 1;
        n_flag = 0;
        half_carry = 0;
        carry = 0;
}

void CPU::or_a_b(){
        a |= b;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 0;
        carry = 0;
}

void CPU::or_a_c(){
        a |= c;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 0;
        carry = 0;
}

void CPU::or_a_d(){
        a |= d;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 0;
        carry = 0;
}

void CPU::or_a_e(){
        a |= e;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 0;
        carry = 0;
}

void CPU::or_a_h(){
        a |= h;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 0;
        carry = 0;
}

void CPU::or_a_l(){
        a |= l;
        zero = (a == 0);
        n_flag = 0;
        half_carry = 0;
        carry = 0;
}

void CPU::or_a_addr_hl(){
        a |= bus->read(hl);
        zero = (a == 0);
        n_flag = 0;
        half_carry = 0;
        carry = 0;
}

void CPU::or_a_a(){
        zero = (a == 0);
        n_flag = 0;
        half_carry = 0;
        carry = 0;
}

void CPU::cp_a_b(){
        zero = (a == b);
        n_flag = 1;
        half_carry = ((a&0x0F) < (b&0x0F));
        carry = (a < b);
}

void CPU::cp_a_c(){
        zero = (a == c);
        n_flag = 1;
        half_carry = ((a&0x0F) < (c&0x0F));
        carry = (a < c);
}

void CPU::cp_a_d(){
        zero = (a == d);
        n_flag = 1;
        half_carry = ((a&0x0F) < (d&0x0F));
        carry = (a < d);
}

void CPU::cp_a_e(){
        zero = (a == e);
        n_flag = 1;
        half_carry = ((a&0x0F) < (e&0x0F));
        carry = (a < e);
}

void CPU::cp_a_h(){
        zero = (a == h);
        n_flag = 1;
        half_carry = ((a&0x0F) < (h&0x0F));
        carry = (a < h);
}

void CPU::cp_a_l(){
        zero = (a == l);
        n_flag = 1;
        half_carry = ((a&0x0F) < (l&0x0F));
        carry = (a < l);
}

void CPU::cp_a_addr_hl(){
        zero = (a == bus->read(hl));
        n_flag = 1;
        half_carry = ((a&0x0F) < (bus->read(hl)&0x0F));
        carry = (a < bus->read(hl));
}

void CPU::cp_a_a(){
        zero = 1;
        n_flag = 1;
        half_carry = 0;
        carry = 0;
}

void CPU::ret_nz(){
}

void CPU::pop_bc(){
}

void CPU::jp_nz(){
}

void CPU::jp(){
}

void CPU::call_nz(){
}

void CPU::push_bc(){
}

void CPU::add_a(){
}

void CPU::rst_00h(){
}

void CPU::ret_z(){
}

void CPU::ret(){
}

void CPU::jp_z(){
}

void CPU::prefix(){
}

void CPU::call_z(){
}

void CPU::call(){
}

void CPU::adc_a(){
}

void CPU::rst_08h(){
}

void CPU::ret_nc(){
}

void CPU::pop_de(){
}

void CPU::jp_nc(){
}

void CPU::call_nc(){
}

void CPU::push_de(){
}

void CPU::sub_a(){
}

void CPU::rst_10h(){
}

void CPU::ret_c(){
}

void CPU::reti(){
}

void CPU::jp_c(){
}

void CPU::call_c(){
}

void CPU::sbc_a(){
}

void CPU::rst_18h(){
}

void CPU::ldh_addr_a(){
}

void CPU::pop_hl(){
}

void CPU::ldh_addr_c_a(){
}

void CPU::push_hl(){
}

void CPU::and_a(){
}

void CPU::rst_20h(){
}

void CPU::add_sp(){
}

void CPU::jp_hl(){
}

void CPU::load_addr_a(){
}

void CPU::xor_a(){
}

void CPU::rst_28h(){
}

void CPU::ldh_a_addr(){
}

void CPU::pop_af(){
}

void CPU::ldh_a_addr_c(){
}

void CPU::di(){
}

void CPU::push_af(){
}

void CPU::or_a(){
}

void CPU::rst_30h(){
}

void CPU::load_hl_sp_add(){
}

void CPU::load_sp_hl(){
}

void CPU::load_a_addr(){
}

void CPU::ei(){
}

void CPU::cp_a(){
}

void CPU::rst_38h(){
}
