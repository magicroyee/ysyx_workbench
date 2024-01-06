// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtb_top__Syms.h"


void Vtb_top___024root__trace_chg_sub_0(Vtb_top___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtb_top___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root__trace_chg_top_0\n"); );
    // Init
    Vtb_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_top___024root*>(voidSelf);
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtb_top___024root__trace_chg_sub_0((&vlSymsp->TOP), bufp);
}

void Vtb_top___024root__trace_chg_sub_0(Vtb_top___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root__trace_chg_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY((vlSelf->__Vm_traceActivity[1U] 
                     | vlSelf->__Vm_traceActivity[2U]))) {
        bufp->chgBit(oldp+0,(vlSelf->tb_top__DOT__clrn));
        bufp->chgBit(oldp+1,(vlSelf->tb_top__DOT__kbd_clk));
        bufp->chgBit(oldp+2,(vlSelf->tb_top__DOT__kbd_data));
        bufp->chgBit(oldp+3,(vlSelf->tb_top__DOT__nextdata_n));
        bufp->chgIData(oldp+4,(vlSelf->tb_top__DOT__model__DOT__kbd_sendcode__Vstatic__i),32);
        bufp->chgSData(oldp+5,(vlSelf->tb_top__DOT__model__DOT__kbd_sendcode__Vstatic__send_buffer),11);
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[3U])) {
        bufp->chgCData(oldp+6,(vlSelf->tb_top__DOT__inst__DOT__fifo
                               [vlSelf->tb_top__DOT__inst__DOT__r_ptr]),8);
        bufp->chgBit(oldp+7,(vlSelf->tb_top__DOT__ready));
        bufp->chgBit(oldp+8,(vlSelf->tb_top__DOT__overflow));
        bufp->chgSData(oldp+9,(vlSelf->tb_top__DOT__inst__DOT__buffer),10);
        bufp->chgCData(oldp+10,(vlSelf->tb_top__DOT__inst__DOT__fifo[0]),8);
        bufp->chgCData(oldp+11,(vlSelf->tb_top__DOT__inst__DOT__fifo[1]),8);
        bufp->chgCData(oldp+12,(vlSelf->tb_top__DOT__inst__DOT__fifo[2]),8);
        bufp->chgCData(oldp+13,(vlSelf->tb_top__DOT__inst__DOT__fifo[3]),8);
        bufp->chgCData(oldp+14,(vlSelf->tb_top__DOT__inst__DOT__fifo[4]),8);
        bufp->chgCData(oldp+15,(vlSelf->tb_top__DOT__inst__DOT__fifo[5]),8);
        bufp->chgCData(oldp+16,(vlSelf->tb_top__DOT__inst__DOT__fifo[6]),8);
        bufp->chgCData(oldp+17,(vlSelf->tb_top__DOT__inst__DOT__fifo[7]),8);
        bufp->chgCData(oldp+18,(vlSelf->tb_top__DOT__inst__DOT__w_ptr),3);
        bufp->chgCData(oldp+19,(vlSelf->tb_top__DOT__inst__DOT__r_ptr),3);
        bufp->chgCData(oldp+20,(vlSelf->tb_top__DOT__inst__DOT__count),4);
        bufp->chgCData(oldp+21,(vlSelf->tb_top__DOT__inst__DOT__ps2_clk_sync),3);
        bufp->chgBit(oldp+22,((IData)((4U == (6U & (IData)(vlSelf->tb_top__DOT__inst__DOT__ps2_clk_sync))))));
    }
    bufp->chgBit(oldp+23,(vlSelf->tb_top__DOT__clk));
}

void Vtb_top___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtb_top___024root__trace_cleanup\n"); );
    // Init
    Vtb_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtb_top___024root*>(voidSelf);
    Vtb_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
}
