#ifndef CPU_HPP
#define CPU_HPP
#include <cstdint>
#include <functional>

class Bus;
class CPU {
        public:
                // note every ldh uses little endian address
                explicit CPU() = default;
                void nop() const;
                void load_bc();
                void load_addr_bc_a() const;
                void inc_bc();
                void inc_b();
                void dec_b();
                void load_b();
                void rlca();
                void load_addr_sp();
                void add_hl_bc();
                void load_a_addr_bc();
                void dec_bc();
                void inc_c();
                void dec_c();
                void load_c();
                void rrca();
                void stop();
                void load_de();
                void load_addr_de_a() const;
                void inc_de();
                void inc_d();
                void dec_d();
                void load_d();
                void rla();
                void jr();
                void add_hl_de();
                void load_a_addr_de();
                void dec_de();
                void inc_e();
                void dec_e();
                void load_e();
                void rra();
                void jr_nz();
                void load_hl();
                void load_addr_hl_plus_a() const;
                void inc_hl();
                void inc_h();
                void dec_h();
                void load_h();
                void daa();
                void jr_z();
                void add_hl_hl();
                void load_a_addr_hl_plus();
                void dec_hl();
                void inc_l();
                void dec_l();
                void load_l();
                void cpl();
                void jr_nc();
                void load_sp();
                void load_addr_hl_minus_a() const;
                void inc_sp();
                void inc_addr_hl() const;
                void dec_addr_hl() const;
                void load_addr_hl() const;
                void scf();
                void jr_c();
                void add_hl_sp();
                void load_a_addr_hl_minus();
                void dec_sp();
                void inc_a();
                void dec_a();
                void load_a();
                void ccf();
                void load_b_b();
                void load_b_c();
                void load_b_d();
                void load_b_e();
                void load_b_h();
                void load_b_l();
                void load_b_addr_hl();
                void load_b_a();
                void load_c_b();
                void load_c_c();
                void load_c_d();
                void load_c_e();
                void load_c_h();
                void load_c_l();
                void load_c_addr_hl();
                void load_c_a();
                void load_d_b();
                void load_d_c();
                void load_d_d();
                void load_d_e();
                void load_d_h();
                void load_d_l();
                void load_d_addr_hl();
                void load_d_a();
                void load_e_b();
                void load_e_c();
                void load_e_d();
                void load_e_e();
                void load_e_h();
                void load_e_l();
                void load_e_addr_hl();
                void load_e_a();
                void load_h_b();
                void load_h_c();
                void load_h_d();
                void load_h_e();
                void load_h_h();
                void load_h_l();
                void load_h_addr_hl();
                void load_h_a();
                void load_l_b();
                void load_l_c();
                void load_l_d();
                void load_l_e();
                void load_l_h();
                void load_l_l();
                void load_l_addr_hl();
                void load_l_a();
                void load_addr_hl_b();
                void load_addr_hl_c();
                void load_addr_hl_d();
                void load_addr_hl_e();
                void load_addr_hl_h();
                void load_addr_hl_l();
                void halt();
                void load_addr_hl_a();
                void load_a_b();
                void load_a_c();
                void load_a_d();
                void load_a_e();
                void load_a_h();
                void load_a_l();
                void load_a_addr_hl();
                void load_a_a();
                void add_a_b();
                void add_a_c();
                void add_a_d();
                void add_a_e();
                void add_a_h();
                void add_a_l();
                void add_a_addr_hl();
                void add_a_a();
                void adc_a_b();
                void adc_a_c();
                void adc_a_d();
                void adc_a_e();
                void adc_a_h();
                void adc_a_l();
                void adc_a_addr_hl();
                void adc_a_a();
                void sub_a_b();
                void sub_a_c();
                void sub_a_d();
                void sub_a_e();
                void sub_a_h();
                void sub_a_l();
                void sub_a_addr_hl();
                void sub_a_a();
                void sbc_a_b();
                void sbc_a_c();
                void sbc_a_d();
                void sbc_a_e();
                void sbc_a_h();
                void sbc_a_l();
                void sbc_a_addr_hl();
                void sbc_a_a();
                void and_a_b();
                void and_a_c();
                void and_a_d();
                void and_a_e();
                void and_a_h();
                void and_a_l();
                void and_a_addr_hl();
                void and_a_a();
                void xor_a_b();
                void xor_a_c();
                void xor_a_d();
                void xor_a_e();
                void xor_a_h();
                void xor_a_l();
                void xor_a_addr_hl();
                void xor_a_a();
                void or_a_b();
                void or_a_c();
                void or_a_d();
                void or_a_e();
                void or_a_h();
                void or_a_l();
                void or_a_addr_hl();
                void or_a_a();
                void cp_a_b();
                void cp_a_c();
                void cp_a_d();
                void cp_a_e();
                void cp_a_h();
                void cp_a_l();
                void cp_a_addr_hl();
                void cp_a_a();
                void ret_nz();
                void pop_bc();
                void jp_nz();
                void jp();
                void call_nz();
                void push_bc();
                void add_a();
                void rst_00h();
                void ret_z();
                void ret();
                void jp_z();
                void prefix();
                void call_z();
                void call();
                void adc_a();
                void rst_08h();
                void ret_nc();
                void pop_de();
                void jp_nc();
                void call_nc();
                void push_de();
                void sub_a();
                void rst_10h();
                void ret_c();
                void reti();
                void jp_c();
                void call_c();
                void sbc_a();
                void rst_18h();
                void ldh_addr_a();
                void pop_hl();
                void ldh_addr_c_a();
                void push_hl();
                void and_a();
                void rst_20h();
                void add_sp();
                void jp_hl();
                void load_addr_a();
                void xor_a();
                void rst_28h();
                void ldh_a_addr();
                void pop_af();
                void ldh_a_addr_c();
                void di();
                void push_af();
                void or_a();
                void rst_30h();
                void load_hl_sp_add();
                void load_sp_hl();
                void load_a_addr();
                void ei();
                void cp_a();
                void rst_38h();
        private :
                union {
                        struct {
                                std::uint8_t unused       : 4; // BITS 4
                                std::uint8_t carry        : 1; // BITS 1
                                std::uint8_t half_carry   : 1; // BITS 1
                                std::uint8_t n_flag       : 1; // BITS 1
                                std::uint8_t zero         : 1; // BITS 1
                                std::uint8_t a;
                        };
                        struct {
                                std::uint8_t f;
                                std::uint8_t a_reg;
                        };
                        std::uint16_t af{};
                };
                union {
                        struct {
                                std::uint8_t c;
                                std::uint8_t b;
                        };
                        std::uint16_t bc{};
                };
                union {
                        struct {
                                std::uint8_t e;
                                std::uint8_t d;
                        };
                        std::uint16_t de{};
                };
                union {
                        struct {
                                std::uint8_t l;
                                std::uint8_t h;
                        };
                        std::uint16_t hl{};
                };
                std::uint16_t pc{};
                std::uint16_t sp{};
                struct Instruction {
                        std::function<void(void)> operation{};
                };
                Instruction lookup_table[0xFF+1]{
                        {[this](void){this->nop();}},
                        {[this](void){this->load_bc();}},
                        {[this](void){this->load_addr_bc_a();}},
                        {[this](void){this->inc_bc();}},
                        {[this](void){this->inc_b();}},
                        {[this](void){this->dec_b();}},
                        {[this](void){this->load_b();}},
                        {[this](void){this->rlca();}},
                        {[this](void){this->load_addr_sp();}},
                        {[this](void){this->add_hl_bc();}},
                        {[this](void){this->load_a_addr_bc();}},
                        {[this](void){this->dec_bc();}},
                        {[this](void){this->inc_c();}},
                        {[this](void){this->dec_c();}},
                        {[this](void){this->load_c();}},
                        {[this](void){this->rrca();}},
                        {[this](void){this->stop();}},
                        {[this](void){this->load_de();}},
                        {[this](void){this->load_addr_de_a();}},
                        {[this](void){this->inc_de();}},
                        {[this](void){this->inc_d();}},
                        {[this](void){this->dec_d();}},
                        {[this](void){this->load_d();}},
                        {[this](void){this->rla();}},
                        {[this](void){this->jr();}},
                        {[this](void){this->add_hl_de();}},
                        {[this](void){this->load_a_addr_de();}},
                        {[this](void){this->dec_de();}},
                        {[this](void){this->inc_e();}},
                        {[this](void){this->dec_e();}},
                        {[this](void){this->load_e();}},
                        {[this](void){this->rra();}},
                        {[this](void){this->jr_nz();}},
                        {[this](void){this->load_hl();}},
                        {[this](void){this->load_addr_hl_plus_a();}},
                        {[this](void){this->inc_hl();}},
                        {[this](void){this->inc_h();}},
                        {[this](void){this->dec_h();}},
                        {[this](void){this->load_h();}},
                        {[this](void){this->daa();}},
                        {[this](void){this->jr_z();}},
                        {[this](void){this->add_hl_hl();}},
                        {[this](void){this->load_a_addr_hl_plus();}},
                        {[this](void){this->dec_hl();}},
                        {[this](void){this->inc_l();}},
                        {[this](void){this->dec_l();}},
                        {[this](void){this->load_l();}},
                        {[this](void){this->cpl();}},
                        {[this](void){this->jr_nc();}},
                        {[this](void){this->load_sp();}},
                        {[this](void){this->load_addr_hl_minus_a();}},
                        {[this](void){this->inc_sp();}},
                        {[this](void){this->inc_addr_hl();}},
                        {[this](void){this->dec_addr_hl();}},
                        {[this](void){this->load_addr_hl();}},
                        {[this](void){this->scf();}},
                        {[this](void){this->jr_c();}},
                        {[this](void){this->add_hl_sp();}},
                        {[this](void){this->load_a_addr_hl_minus();}},
                        {[this](void){this->dec_sp();}},
                        {[this](void){this->inc_a();}},
                        {[this](void){this->dec_a();}},
                        {[this](void){this->load_a();}},
                        {[this](void){this->ccf();}},
                        {[this](void){this->load_b_b();}},
                        {[this](void){this->load_b_c();}},
                        {[this](void){this->load_b_d();}},
                        {[this](void){this->load_b_e();}},
                        {[this](void){this->load_b_h();}},
                        {[this](void){this->load_b_l();}},
                        {[this](void){this->load_b_addr_hl();}},
                        {[this](void){this->load_b_a();}},
                        {[this](void){this->load_c_b();}},
                        {[this](void){this->load_c_c();}},
                        {[this](void){this->load_c_d();}},
                        {[this](void){this->load_c_e();}},
                        {[this](void){this->load_c_h();}},
                        {[this](void){this->load_c_l();}},
                        {[this](void){this->load_c_addr_hl();}},
                        {[this](void){this->load_c_a();}},
                        {[this](void){this->load_d_b();}},
                        {[this](void){this->load_d_c();}},
                        {[this](void){this->load_d_d();}},
                        {[this](void){this->load_d_e();}},
                        {[this](void){this->load_d_h();}},
                        {[this](void){this->load_d_l();}},
                        {[this](void){this->load_d_addr_hl();}},
                        {[this](void){this->load_d_a();}},
                        {[this](void){this->load_e_b();}},
                        {[this](void){this->load_e_c();}},
                        {[this](void){this->load_e_d();}},
                        {[this](void){this->load_e_e();}},
                        {[this](void){this->load_e_h();}},
                        {[this](void){this->load_e_l();}},
                        {[this](void){this->load_e_addr_hl();}},
                        {[this](void){this->load_e_a();}},
                        {[this](void){this->load_h_b();}},
                        {[this](void){this->load_h_c();}},
                        {[this](void){this->load_h_d();}},
                        {[this](void){this->load_h_e();}},
                        {[this](void){this->load_h_h();}},
                        {[this](void){this->load_h_l();}},
                        {[this](void){this->load_h_addr_hl();}},
                        {[this](void){this->load_h_a();}},
                        {[this](void){this->load_l_b();}},
                        {[this](void){this->load_l_c();}},
                        {[this](void){this->load_l_d();}},
                        {[this](void){this->load_l_e();}},
                        {[this](void){this->load_l_h();}},
                        {[this](void){this->load_l_l();}},
                        {[this](void){this->load_l_addr_hl();}},
                        {[this](void){this->load_l_a();}},
                        {[this](void){this->load_addr_hl_b();}},
                        {[this](void){this->load_addr_hl_c();}},
                        {[this](void){this->load_addr_hl_d();}},
                        {[this](void){this->load_addr_hl_e();}},
                        {[this](void){this->load_addr_hl_h();}},
                        {[this](void){this->load_addr_hl_l();}},
                        {[this](void){this->halt();}},
                        {[this](void){this->load_addr_hl_a();}},
                        {[this](void){this->load_a_b();}},
                        {[this](void){this->load_a_c();}},
                        {[this](void){this->load_a_d();}},
                        {[this](void){this->load_a_e();}},
                        {[this](void){this->load_a_h();}},
                        {[this](void){this->load_a_l();}},
                        {[this](void){this->load_a_addr_hl();}},
                        {[this](void){this->load_a_a();}},
                        {[this](void){this->add_a_b();}},
                        {[this](void){this->add_a_c();}},
                        {[this](void){this->add_a_d();}},
                        {[this](void){this->add_a_e();}},
                        {[this](void){this->add_a_h();}},
                        {[this](void){this->add_a_l();}},
                        {[this](void){this->add_a_addr_hl();}},
                        {[this](void){this->add_a_a();}},
                        {[this](void){this->adc_a_b();}},
                        {[this](void){this->adc_a_c();}},
                        {[this](void){this->adc_a_d();}},
                        {[this](void){this->adc_a_e();}},
                        {[this](void){this->adc_a_h();}},
                        {[this](void){this->adc_a_l();}},
                        {[this](void){this->adc_a_addr_hl();}},
                        {[this](void){this->adc_a_a();}},
                        {[this](void){this->sub_a_b();}},
                        {[this](void){this->sub_a_c();}},
                        {[this](void){this->sub_a_d();}},
                        {[this](void){this->sub_a_e();}},
                        {[this](void){this->sub_a_h();}},
                        {[this](void){this->sub_a_l();}},
                        {[this](void){this->sub_a_addr_hl();}},
                        {[this](void){this->sub_a_a();}},
                        {[this](void){this->sbc_a_b();}},
                        {[this](void){this->sbc_a_c();}},
                        {[this](void){this->sbc_a_d();}},
                        {[this](void){this->sbc_a_e();}},
                        {[this](void){this->sbc_a_h();}},
                        {[this](void){this->sbc_a_l();}},
                        {[this](void){this->sbc_a_addr_hl();}},
                        {[this](void){this->sbc_a_a();}},
                        {[this](void){this->and_a_b();}},
                        {[this](void){this->and_a_c();}},
                        {[this](void){this->and_a_d();}},
                        {[this](void){this->and_a_e();}},
                        {[this](void){this->and_a_h();}},
                        {[this](void){this->and_a_l();}},
                        {[this](void){this->and_a_addr_hl();}},
                        {[this](void){this->and_a_a();}},
                        {[this](void){this->xor_a_b();}},
                        {[this](void){this->xor_a_c();}},
                        {[this](void){this->xor_a_d();}},
                        {[this](void){this->xor_a_e();}},
                        {[this](void){this->xor_a_h();}},
                        {[this](void){this->xor_a_l();}},
                        {[this](void){this->xor_a_addr_hl();}},
                        {[this](void){this->xor_a_a();}},
                        {[this](void){this->or_a_b();}},
                        {[this](void){this->or_a_c();}},
                        {[this](void){this->or_a_d();}},
                        {[this](void){this->or_a_e();}},
                        {[this](void){this->or_a_h();}},
                        {[this](void){this->or_a_l();}},
                        {[this](void){this->or_a_addr_hl();}},
                        {[this](void){this->or_a_a();}},
                        {[this](void){this->cp_a_b();}},
                        {[this](void){this->cp_a_c();}},
                        {[this](void){this->cp_a_d();}},
                        {[this](void){this->cp_a_e();}},
                        {[this](void){this->cp_a_h();}},
                        {[this](void){this->cp_a_l();}},
                        {[this](void){this->cp_a_addr_hl();}},
                        {[this](void){this->cp_a_a();}},
                        {[this](void){this->ret_nz();}},
                        {[this](void){this->pop_bc();}},
                        {[this](void){this->jp_nz();}},
                        {[this](void){this->jp();}},
                        {[this](void){this->call_nz();}},
                        {[this](void){this->push_bc();}},
                        {[this](void){this->add_a();}},
                        {[this](void){this->rst_00h();}},
                        {[this](void){this->ret_z();}},
                        {[this](void){this->ret();}},
                        {[this](void){this->jp_z();}},
                        {[this](void){this->prefix();}},
                        {[this](void){this->call_z();}},
                        {[this](void){this->call();}},
                        {[this](void){this->adc_a();}},
                        {[this](void){this->rst_08h();}},
                        {[this](void){this->ret_nc();}},
                        {[this](void){this->pop_de();}},
                        {[this](void){this->jp_nc();}},
                        {[this](void){return;}},
                        {[this](void){this->call_nc();}},
                        {[this](void){this->push_de();}},
                        {[this](void){this->sub_a();}},
                        {[this](void){this->rst_10h();}},
                        {[this](void){this->ret_c();}},
                        {[this](void){this->reti();}},
                        {[this](void){this->jp_c();}},
                        {[this](void){return;}},
                        {[this](void){this->call_c();}},
                        {[this](void){return;}},
                        {[this](void){this->sbc_a();}},
                        {[this](void){this->rst_18h();}},
                        {[this](void){this->ldh_addr_a();}},
                        {[this](void){this->pop_hl();}},
                        {[this](void){this->ldh_addr_c_a();}},
                        {[this](void){return;}},
                        {[this](void){return;}},
                        {[this](void){this->push_hl();}},
                        {[this](void){this->and_a();}},
                        {[this](void){this->rst_20h();}},
                        {[this](void){this->add_sp();}},
                        {[this](void){this->jp_hl();}},
                        {[this](void){this->load_addr_a();}},
                        {[this](void){return;}},
                        {[this](void){return;}},
                        {[this](void){return;}},
                        {[this](void){this->xor_a();}},
                        {[this](void){this->rst_28h();}},
                        {[this](void){this->ldh_a_addr();}},
                        {[this](void){return;}},
                        {[this](void){this->pop_af();}},
                        {[this](void){this->ldh_a_addr_c();}},
                        {[this](void){this->di();}},
                        {[this](void){this->push_af();}},
                        {[this](void){this->or_a();}},
                        {[this](void){this->rst_30h();}},
                        {[this](void){this->load_hl_sp_add();}},
                        {[this](void){this->load_sp_hl();}},
                        {[this](void){this->load_a_addr();}},
                        {[this](void){this->ei();}},
                        {[this](void){return;}},
                        {[this](void){return;}},
                        {[this](void){this->cp_a();}},
                        {[this](void){this->rst_38h();}},
                };
};
class CPU {
        public:
                // note every ldh uses little endian address
                explicit CPU() = default;
                void nop() const;
                void load_bc();
                void load_addr_bc_a() const;
                void inc_bc();
                void inc_b();
                void dec_b();
                void load_b();
                void rlca();
                void load_addr_sp();
                void add_hl_bc();
                void load_a_addr_bc();
                void dec_bc();
                void inc_c();
                void dec_c();
                void load_c();
                void rrca();
                void stop();
                void load_de();
                void load_addr_de_a() const;
                void inc_de();
                void inc_d();
                void dec_d();
                void load_d();
                void rla();
                void jr();
                void add_hl_de();
                void load_a_addr_de();
                void dec_de();
                void inc_e();
                void dec_e();
                void load_e();
                void rra();
                void jr_nz();
                void load_hl();
                void load_addr_hl_plus_a() const;
                void inc_hl();
                void inc_h();
                void dec_h();
                void load_h();
                void daa();
                void jr_z();
                void add_hl_hl();
                void load_a_addr_hl_plus();
                void dec_hl();
                void inc_l();
                void dec_l();
                void load_l();
                void cpl();
                void jr_nc();
                void load_sp();
                void load_addr_hl_minus_a() const;
                void inc_sp();
                void inc_addr_hl() const;
                void dec_addr_hl() const;
                void load_addr_hl() const;
                void scf();
                void jr_c();
                void add_hl_sp();
                void load_a_addr_hl_minus();
                void dec_sp();
                void inc_a();
                void dec_a();
                void load_a();
                void ccf();
                void load_b_b();
                void load_b_c();
                void load_b_d();
                void load_b_e();
                void load_b_h();
                void load_b_l();
                void load_b_addr_hl();
                void load_b_a();
                void load_c_b();
                void load_c_c();
                void load_c_d();
                void load_c_e();
                void load_c_h();
                void load_c_l();
                void load_c_addr_hl();
                void load_c_a();
                void load_d_b();
                void load_d_c();
                void load_d_d();
                void load_d_e();
                void load_d_h();
                void load_d_l();
                void load_d_addr_hl();
                void load_d_a();
                void load_e_b();
                void load_e_c();
                void load_e_d();
                void load_e_e();
                void load_e_h();
                void load_e_l();
                void load_e_addr_hl();
                void load_e_a();
                void load_h_b();
                void load_h_c();
                void load_h_d();
                void load_h_e();
                void load_h_h();
                void load_h_l();
                void load_h_addr_hl();
                void load_h_a();
                void load_l_b();
                void load_l_c();
                void load_l_d();
                void load_l_e();
                void load_l_h();
                void load_l_l();
                void load_l_addr_hl();
                void load_l_a();
                void load_addr_hl_b();
                void load_addr_hl_c();
                void load_addr_hl_d();
                void load_addr_hl_e();
                void load_addr_hl_h();
                void load_addr_hl_l();
                void halt();
                void load_addr_hl_a();
                void load_a_b();
                void load_a_c();
                void load_a_d();
                void load_a_e();
                void load_a_h();
                void load_a_l();
                void load_a_addr_hl();
                void load_a_a();
                void add_a_b();
                void add_a_c();
                void add_a_d();
                void add_a_e();
                void add_a_h();
                void add_a_l();
                void add_a_addr_hl();
                void add_a_a();
                void adc_a_b();
                void adc_a_c();
                void adc_a_d();
                void adc_a_e();
                void adc_a_h();
                void adc_a_l();
                void adc_a_addr_hl();
                void adc_a_a();
                void sub_a_b();
                void sub_a_c();
                void sub_a_d();
                void sub_a_e();
                void sub_a_h();
                void sub_a_l();
                void sub_a_addr_hl();
                void sub_a_a();
                void sbc_a_b();
                void sbc_a_c();
                void sbc_a_d();
                void sbc_a_e();
                void sbc_a_h();
                void sbc_a_l();
                void sbc_a_addr_hl();
                void sbc_a_a();
                void and_a_b();
                void and_a_c();
                void and_a_d();
                void and_a_e();
                void and_a_h();
                void and_a_l();
                void and_a_addr_hl();
                void and_a_a();
                void xor_a_b();
                void xor_a_c();
                void xor_a_d();
                void xor_a_e();
                void xor_a_h();
                void xor_a_l();
                void xor_a_addr_hl();
                void xor_a_a();
                void or_a_b();
                void or_a_c();
                void or_a_d();
                void or_a_e();
                void or_a_h();
                void or_a_l();
                void or_a_addr_hl();
                void or_a_a();
                void cp_a_b();
                void cp_a_c();
                void cp_a_d();
                void cp_a_e();
                void cp_a_h();
                void cp_a_l();
                void cp_a_addr_hl();
                void cp_a_a();
                void ret_nz();
                void pop_bc();
                void jp_nz();
                void jp();
                void call_nz();
                void push_bc();
                void add_a();
                void rst_00h();
                void ret_z();
                void ret();
                void jp_z();
                void prefix();
                void call_z();
                void call();
                void adc_a();
                void rst_08h();
                void ret_nc();
                void pop_de();
                void jp_nc();
                void call_nc();
                void push_de();
                void sub_a();
                void rst_10h();
                void ret_c();
                void reti();
                void jp_c();
                void call_c();
                void sbc_a();
                void rst_18h();
                void ldh_addr_a();
                void pop_hl();
                void ldh_addr_c_a();
                void push_hl();
                void and_a();
                void rst_20h();
                void add_sp();
                void jp_hl();
                void load_addr_a();
                void xor_a();
                void rst_28h();
                void ldh_a_addr();
                void pop_af();
                void ldh_a_addr_c();
                void di();
                void push_af();
                void or_a();
                void rst_30h();
                void load_hl_sp_add();
                void load_sp_hl();
                void load_a_addr();
                void ei();
                void cp_a();
                void rst_38h();
        private :
                union {
                        struct {
                                std::uint8_t unused       : 4; // BITS 4
                                std::uint8_t carry        : 1; // BITS 1
                                std::uint8_t half_carry   : 1; // BITS 1
                                std::uint8_t n_flag       : 1; // BITS 1
                                std::uint8_t zero         : 1; // BITS 1
                                std::uint8_t a;
                        };
                        struct {
                                std::uint8_t f;
                                std::uint8_t a_reg;
                        };
                        std::uint16_t af{};
                };
                union {
                        struct {
                                std::uint8_t c;
                                std::uint8_t b;
                        };
                        std::uint16_t bc{};
                };
                union {
                        struct {
                                std::uint8_t e;
                                std::uint8_t d;
                        };
                        std::uint16_t de{};
                };
                union {
                        struct {
                                std::uint8_t l;
                                std::uint8_t h;
                        };
                        std::uint16_t hl{};
                };
                std::uint16_t pc{};
                std::uint16_t sp{};
                struct Instruction {
                        std::function<void(Bus& bus)> operation{};
                };
                Instruction lookup_table[0xFF+1]{
                        {[this](void){this->nop();}},
                        {[this](void){this->load_bc();}},
                        {[this](void){this->load_addr_bc_a();}},
                        {[this](void){this->inc_bc();}},
                        {[this](void){this->inc_b();}},
                        {[this](void){this->dec_b();}},
                        {[this](void){this->load_b();}},
                        {[this](void){this->rlca();}},
                        {[this](void){this->load_addr_sp();}},
                        {[this](void){this->add_hl_bc();}},
                        {[this](void){this->load_a_addr_bc();}},
                        {[this](void){this->dec_bc();}},
                        {[this](void){this->inc_c();}},
                        {[this](void){this->dec_c();}},
                        {[this](void){this->load_c();}},
                        {[this](void){this->rrca();}},
                        {[this](void){this->stop();}},
                        {[this](void){this->load_de();}},
                        {[this](void){this->load_addr_de_a();}},
                        {[this](void){this->inc_de();}},
                        {[this](void){this->inc_d();}},
                        {[this](void){this->dec_d();}},
                        {[this](void){this->load_d();}},
                        {[this](void){this->rla();}},
                        {[this](void){this->jr();}},
                        {[this](void){this->add_hl_de();}},
                        {[this](void){this->load_a_addr_de();}},
                        {[this](void){this->dec_de();}},
                        {[this](void){this->inc_e();}},
                        {[this](void){this->dec_e();}},
                        {[this](void){this->load_e();}},
                        {[this](void){this->rra();}},
                        {[this](void){this->jr_nz();}},
                        {[this](void){this->load_hl();}},
                        {[this](void){this->load_addr_hl_plus_a();}},
                        {[this](void){this->inc_hl();}},
                        {[this](void){this->inc_h();}},
                        {[this](void){this->dec_h();}},
                        {[this](void){this->load_h();}},
                        {[this](void){this->daa();}},
                        {[this](void){this->jr_z();}},
                        {[this](void){this->add_hl_hl();}},
                        {[this](void){this->load_a_addr_hl_plus();}},
                        {[this](void){this->dec_hl();}},
                        {[this](void){this->inc_l();}},
                        {[this](void){this->dec_l();}},
                        {[this](void){this->load_l();}},
                        {[this](void){this->cpl();}},
                        {[this](void){this->jr_nc();}},
                        {[this](void){this->load_sp();}},
                        {[this](void){this->load_addr_hl_minus_a();}},
                        {[this](void){this->inc_sp();}},
                        {[this](void){this->inc_addr_hl();}},
                        {[this](void){this->dec_addr_hl();}},
                        {[this](void){this->load_addr_hl();}},
                        {[this](void){this->scf();}},
                        {[this](void){this->jr_c();}},
                        {[this](void){this->add_hl_sp();}},
                        {[this](void){this->load_a_addr_hl_minus();}},
                        {[this](void){this->dec_sp();}},
                        {[this](void){this->inc_a();}},
                        {[this](void){this->dec_a();}},
                        {[this](void){this->load_a();}},
                        {[this](void){this->ccf();}},
                        {[this](void){this->load_b_b();}},
                        {[this](void){this->load_b_c();}},
                        {[this](void){this->load_b_d();}},
                        {[this](void){this->load_b_e();}},
                        {[this](void){this->load_b_h();}},
                        {[this](void){this->load_b_l();}},
                        {[this](void){this->load_b_addr_hl();}},
                        {[this](void){this->load_b_a();}},
                        {[this](void){this->load_c_b();}},
                        {[this](void){this->load_c_c();}},
                        {[this](void){this->load_c_d();}},
                        {[this](void){this->load_c_e();}},
                        {[this](void){this->load_c_h();}},
                        {[this](void){this->load_c_l();}},
                        {[this](void){this->load_c_addr_hl();}},
                        {[this](void){this->load_c_a();}},
                        {[this](void){this->load_d_b();}},
                        {[this](void){this->load_d_c();}},
                        {[this](void){this->load_d_d();}},
                        {[this](void){this->load_d_e();}},
                        {[this](void){this->load_d_h();}},
                        {[this](void){this->load_d_l();}},
                        {[this](void){this->load_d_addr_hl();}},
                        {[this](void){this->load_d_a();}},
                        {[this](void){this->load_e_b();}},
                        {[this](void){this->load_e_c();}},
                        {[this](void){this->load_e_d();}},
                        {[this](void){this->load_e_e();}},
                        {[this](void){this->load_e_h();}},
                        {[this](void){this->load_e_l();}},
                        {[this](void){this->load_e_addr_hl();}},
                        {[this](void){this->load_e_a();}},
                        {[this](void){this->load_h_b();}},
                        {[this](void){this->load_h_c();}},
                        {[this](void){this->load_h_d();}},
                        {[this](void){this->load_h_e();}},
                        {[this](void){this->load_h_h();}},
                        {[this](void){this->load_h_l();}},
                        {[this](void){this->load_h_addr_hl();}},
                        {[this](void){this->load_h_a();}},
                        {[this](void){this->load_l_b();}},
                        {[this](void){this->load_l_c();}},
                        {[this](void){this->load_l_d();}},
                        {[this](void){this->load_l_e();}},
                        {[this](void){this->load_l_h();}},
                        {[this](void){this->load_l_l();}},
                        {[this](void){this->load_l_addr_hl();}},
                        {[this](void){this->load_l_a();}},
                        {[this](void){this->load_addr_hl_b();}},
                        {[this](void){this->load_addr_hl_c();}},
                        {[this](void){this->load_addr_hl_d();}},
                        {[this](void){this->load_addr_hl_e();}},
                        {[this](void){this->load_addr_hl_h();}},
                        {[this](void){this->load_addr_hl_l();}},
                        {[this](void){this->halt();}},
                        {[this](void){this->load_addr_hl_a();}},
                        {[this](void){this->load_a_b();}},
                        {[this](void){this->load_a_c();}},
                        {[this](void){this->load_a_d();}},
                        {[this](void){this->load_a_e();}},
                        {[this](void){this->load_a_h();}},
                        {[this](void){this->load_a_l();}},
                        {[this](void){this->load_a_addr_hl();}},
                        {[this](void){this->load_a_a();}},
                        {[this](void){this->add_a_b();}},
                        {[this](void){this->add_a_c();}},
                        {[this](void){this->add_a_d();}},
                        {[this](void){this->add_a_e();}},
                        {[this](void){this->add_a_h();}},
                        {[this](void){this->add_a_l();}},
                        {[this](void){this->add_a_addr_hl();}},
                        {[this](void){this->add_a_a();}},
                        {[this](void){this->adc_a_b();}},
                        {[this](void){this->adc_a_c();}},
                        {[this](void){this->adc_a_d();}},
                        {[this](void){this->adc_a_e();}},
                        {[this](void){this->adc_a_h();}},
                        {[this](void){this->adc_a_l();}},
                        {[this](void){this->adc_a_addr_hl();}},
                        {[this](void){this->adc_a_a();}},
                        {[this](void){this->sub_a_b();}},
                        {[this](void){this->sub_a_c();}},
                        {[this](void){this->sub_a_d();}},
                        {[this](void){this->sub_a_e();}},
                        {[this](void){this->sub_a_h();}},
                        {[this](void){this->sub_a_l();}},
                        {[this](void){this->sub_a_addr_hl();}},
                        {[this](void){this->sub_a_a();}},
                        {[this](void){this->sbc_a_b();}},
                        {[this](void){this->sbc_a_c();}},
                        {[this](void){this->sbc_a_d();}},
                        {[this](void){this->sbc_a_e();}},
                        {[this](void){this->sbc_a_h();}},
                        {[this](void){this->sbc_a_l();}},
                        {[this](void){this->sbc_a_addr_hl();}},
                        {[this](void){this->sbc_a_a();}},
                        {[this](void){this->and_a_b();}},
                        {[this](void){this->and_a_c();}},
                        {[this](void){this->and_a_d();}},
                        {[this](void){this->and_a_e();}},
                        {[this](void){this->and_a_h();}},
                        {[this](void){this->and_a_l();}},
                        {[this](void){this->and_a_addr_hl();}},
                        {[this](void){this->and_a_a();}},
                        {[this](void){this->xor_a_b();}},
                        {[this](void){this->xor_a_c();}},
                        {[this](void){this->xor_a_d();}},
                        {[this](void){this->xor_a_e();}},
                        {[this](void){this->xor_a_h();}},
                        {[this](void){this->xor_a_l();}},
                        {[this](void){this->xor_a_addr_hl();}},
                        {[this](void){this->xor_a_a();}},
                        {[this](void){this->or_a_b();}},
                        {[this](void){this->or_a_c();}},
                        {[this](void){this->or_a_d();}},
                        {[this](void){this->or_a_e();}},
                        {[this](void){this->or_a_h();}},
                        {[this](void){this->or_a_l();}},
                        {[this](void){this->or_a_addr_hl();}},
                        {[this](void){this->or_a_a();}},
                        {[this](void){this->cp_a_b();}},
                        {[this](void){this->cp_a_c();}},
                        {[this](void){this->cp_a_d();}},
                        {[this](void){this->cp_a_e();}},
                        {[this](void){this->cp_a_h();}},
                        {[this](void){this->cp_a_l();}},
                        {[this](void){this->cp_a_addr_hl();}},
                        {[this](void){this->cp_a_a();}},
                        {[this](void){this->ret_nz();}},
                        {[this](void){this->pop_bc();}},
                        {[this](void){this->jp_nz();}},
                        {[this](void){this->jp();}},
                        {[this](void){this->call_nz();}},
                        {[this](void){this->push_bc();}},
                        {[this](void){this->add_a();}},
                        {[this](void){this->rst_00h();}},
                        {[this](void){this->ret_z();}},
                        {[this](void){this->ret();}},
                        {[this](void){this->jp_z();}},
                        {[this](void){this->prefix();}},
                        {[this](void){this->call_z();}},
                        {[this](void){this->call();}},
                        {[this](void){this->adc_a();}},
                        {[this](void){this->rst_08h();}},
                        {[this](void){this->ret_nc();}},
                        {[this](void){this->pop_de();}},
                        {[this](void){this->jp_nc();}},
                        {[this](void){return;}},
                        {[this](void){this->call_nc();}},
                        {[this](void){this->push_de();}},
                        {[this](void){this->sub_a();}},
                        {[this](void){this->rst_10h();}},
                        {[this](void){this->ret_c();}},
                        {[this](void){this->reti();}},
                        {[this](void){this->jp_c();}},
                        {[this](void){return;}},
                        {[this](void){this->call_c();}},
                        {[this](void){return;}},
                        {[this](void){this->sbc_a();}},
                        {[this](void){this->rst_18h();}},
                        {[this](void){this->ldh_addr_a();}},
                        {[this](void){this->pop_hl();}},
                        {[this](void){this->ldh_addr_c_a();}},
                        {[this](void){return;}},
                        {[this](void){return;}},
                        {[this](void){this->push_hl();}},
                        {[this](void){this->and_a();}},
                        {[this](void){this->rst_20h();}},
                        {[this](void){this->add_sp();}},
                        {[this](void){this->jp_hl();}},
                        {[this](void){this->load_addr_a();}},
                        {[this](void){return;}},
                        {[this](void){return;}},
                        {[this](void){return;}},
                        {[this](void){this->xor_a();}},
                        {[this](void){this->rst_28h();}},
                        {[this](void){this->ldh_a_addr();}},
                        {[this](void){return;}},
                        {[this](void){this->pop_af();}},
                        {[this](void){this->ldh_a_addr_c();}},
                        {[this](void){this->di();}},
                        {[this](void){this->push_af();}},
                        {[this](void){this->or_a();}},
                        {[this](void){this->rst_30h();}},
                        {[this](void){this->load_hl_sp_add();}},
                        {[this](void){this->load_sp_hl();}},
                        {[this](void){this->load_a_addr();}},
                        {[this](void){this->ei();}},
                        {[this](void){return;}},
                        {[this](void){return;}},
                        {[this](void){this->cp_a();}},
                        {[this](void){this->rst_38h();}},
                };
};
enum class RegisterCode8_t {
        A   = 0b111,
        B   = 0b000,
        C   = 0b001,
        D   = 0b010,
        E   = 0b011,
        H   = 0b100,
        HLI = 0b110,
        L   = 0b101
};
enum class RegisterCode16_t {
        AF = 0b11,
        BC = 0b00,
        DE = 0b01,
        HL = 0b10
};
#endif
