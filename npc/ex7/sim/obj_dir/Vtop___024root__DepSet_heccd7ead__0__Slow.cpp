// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial__TOP\n"); );
    // Body
    vlSelf->top__DOT__u_keyboard_sim__DOT__kbd_clk = 1U;
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VactTriggered.at(0U)) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge top.u_keyboard_sim.clk)\n");
    }
    if (vlSelf->__VactTriggered.at(1U)) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VnbaTriggered.at(0U)) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge top.u_keyboard_sim.clk)\n");
    }
    if (vlSelf->__VnbaTriggered.at(1U)) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->top__DOT__u_keyboard_sim__DOT__clk = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_keyboard_sim__DOT__clrn = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_keyboard_sim__DOT__ready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_keyboard_sim__DOT__overflow = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_keyboard_sim__DOT__kbd_clk = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_keyboard_sim__DOT__kbd_data = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_keyboard_sim__DOT__nextdata_n = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_keyboard_sim__DOT__model__DOT__kbd_sendcode__Vstatic__i = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__u_keyboard_sim__DOT__model__DOT__kbd_sendcode__Vstatic__send_buffer = VL_RAND_RESET_I(11);
    vlSelf->top__DOT__u_keyboard_sim__DOT__inst__DOT__buffer = VL_RAND_RESET_I(10);
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->top__DOT__u_keyboard_sim__DOT__inst__DOT__fifo[__Vi0] = VL_RAND_RESET_I(8);
    }
    vlSelf->top__DOT__u_keyboard_sim__DOT__inst__DOT__w_ptr = VL_RAND_RESET_I(3);
    vlSelf->top__DOT__u_keyboard_sim__DOT__inst__DOT__r_ptr = VL_RAND_RESET_I(3);
    vlSelf->top__DOT__u_keyboard_sim__DOT__inst__DOT__count = VL_RAND_RESET_I(4);
    vlSelf->top__DOT__u_keyboard_sim__DOT__inst__DOT__ps2_clk_sync = VL_RAND_RESET_I(3);
    vlSelf->top__DOT__u_keyboard_sim__DOT__inst__DOT____Vlvbound_h1a91ade8__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigrprev__TOP__top__DOT__u_keyboard_sim__DOT__clk = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}