// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtb_top__Syms.h"


VL_ATTR_COLD void Vtb_top___024root__trace_init_sub__TOP__0(Vtb_top___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->pushNamePrefix("tb_top ");
    tracep->declBus(c+25,"clock_period", false,-1, 31,0);
    tracep->declBit(c+24,"clk", false,-1);
    tracep->declBit(c+1,"clrn", false,-1);
    tracep->declBus(c+7,"data", false,-1, 7,0);
    tracep->declBit(c+8,"ready", false,-1);
    tracep->declBit(c+9,"overflow", false,-1);
    tracep->declBit(c+2,"kbd_clk", false,-1);
    tracep->declBit(c+3,"kbd_data", false,-1);
    tracep->declBit(c+4,"nextdata_n", false,-1);
    tracep->pushNamePrefix("inst ");
    tracep->declBit(c+24,"clk", false,-1);
    tracep->declBit(c+1,"clrn", false,-1);
    tracep->declBit(c+2,"ps2_clk", false,-1);
    tracep->declBit(c+3,"ps2_data", false,-1);
    tracep->declBit(c+4,"nextdata_n", false,-1);
    tracep->declBus(c+7,"data", false,-1, 7,0);
    tracep->declBit(c+8,"ready", false,-1);
    tracep->declBit(c+9,"overflow", false,-1);
    tracep->declBus(c+10,"buffer", false,-1, 9,0);
    for (int i = 0; i < 8; ++i) {
        tracep->declBus(c+11+i*1,"fifo", true,(i+0), 7,0);
    }
    tracep->declBus(c+19,"w_ptr", false,-1, 2,0);
    tracep->declBus(c+20,"r_ptr", false,-1, 2,0);
    tracep->declBus(c+21,"count", false,-1, 3,0);
    tracep->declBus(c+22,"ps2_clk_sync", false,-1, 2,0);
    tracep->declBit(c+23,"sampling", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("model ");
    tracep->declBit(c+2,"ps2_clk", false,-1);
    tracep->declBit(c+3,"ps2_data", false,-1);
    tracep->declBus(c+26,"kbd_clk_period", false,-1, 31,0);
    tracep->declBus(c+5,"kbd_sendcode__Vstatic__i", false,-1, 31,0);
    tracep->declBus(c+6,"kbd_sendcode__Vstatic__send_buffer", false,-1, 10,0);
    tracep->popNamePrefix(2);
}

VL_ATTR_COLD void Vtb_top___024root__trace_init_top(Vtb_top___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root__trace_init_top\n"); );
    // Body
    Vtb_top___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtb_top___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtb_top___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtb_top___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtb_top___024root__trace_register(Vtb_top___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vtb_top___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vtb_top___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vtb_top___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtb_top___024root__trace_full_sub_0(Vtb_top___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtb_top___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root__trace_full_top_0\n"); );
    // Init
    Vtb_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_top___024root*>(voidSelf);
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtb_top___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtb_top___024root__trace_full_sub_0(Vtb_top___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullBit(oldp+1,(vlSelf->tb_top__DOT__clrn));
    bufp->fullBit(oldp+2,(vlSelf->tb_top__DOT__kbd_clk));
    bufp->fullBit(oldp+3,(vlSelf->tb_top__DOT__kbd_data));
    bufp->fullBit(oldp+4,(vlSelf->tb_top__DOT__nextdata_n));
    bufp->fullIData(oldp+5,(vlSelf->tb_top__DOT__model__DOT__kbd_sendcode__Vstatic__i),32);
    bufp->fullSData(oldp+6,(vlSelf->tb_top__DOT__model__DOT__kbd_sendcode__Vstatic__send_buffer),11);
    bufp->fullCData(oldp+7,(vlSelf->tb_top__DOT__inst__DOT__fifo
                            [vlSelf->tb_top__DOT__inst__DOT__r_ptr]),8);
    bufp->fullBit(oldp+8,(vlSelf->tb_top__DOT__ready));
    bufp->fullBit(oldp+9,(vlSelf->tb_top__DOT__overflow));
    bufp->fullSData(oldp+10,(vlSelf->tb_top__DOT__inst__DOT__buffer),10);
    bufp->fullCData(oldp+11,(vlSelf->tb_top__DOT__inst__DOT__fifo[0]),8);
    bufp->fullCData(oldp+12,(vlSelf->tb_top__DOT__inst__DOT__fifo[1]),8);
    bufp->fullCData(oldp+13,(vlSelf->tb_top__DOT__inst__DOT__fifo[2]),8);
    bufp->fullCData(oldp+14,(vlSelf->tb_top__DOT__inst__DOT__fifo[3]),8);
    bufp->fullCData(oldp+15,(vlSelf->tb_top__DOT__inst__DOT__fifo[4]),8);
    bufp->fullCData(oldp+16,(vlSelf->tb_top__DOT__inst__DOT__fifo[5]),8);
    bufp->fullCData(oldp+17,(vlSelf->tb_top__DOT__inst__DOT__fifo[6]),8);
    bufp->fullCData(oldp+18,(vlSelf->tb_top__DOT__inst__DOT__fifo[7]),8);
    bufp->fullCData(oldp+19,(vlSelf->tb_top__DOT__inst__DOT__w_ptr),3);
    bufp->fullCData(oldp+20,(vlSelf->tb_top__DOT__inst__DOT__r_ptr),3);
    bufp->fullCData(oldp+21,(vlSelf->tb_top__DOT__inst__DOT__count),4);
    bufp->fullCData(oldp+22,(vlSelf->tb_top__DOT__inst__DOT__ps2_clk_sync),3);
    bufp->fullBit(oldp+23,((IData)((4U == (6U & (IData)(vlSelf->tb_top__DOT__inst__DOT__ps2_clk_sync))))));
    bufp->fullBit(oldp+24,(vlSelf->tb_top__DOT__clk));
    bufp->fullIData(oldp+25,(0xaU),32);
    bufp->fullIData(oldp+26,(0x3cU),32);
}
