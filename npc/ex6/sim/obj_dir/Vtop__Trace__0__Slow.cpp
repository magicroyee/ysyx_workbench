// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+1,"clk", false,-1);
    tracep->declBit(c+2,"rstn", false,-1);
    tracep->declBus(c+3,"din", false,-1, 7,0);
    tracep->declBus(c+4,"shamt", false,-1, 2,0);
    tracep->declBit(c+5,"lr", false,-1);
    tracep->declBit(c+6,"al", false,-1);
    tracep->declBus(c+7,"dout", false,-1, 7,0);
    tracep->pushNamePrefix("top ");
    tracep->declBit(c+1,"clk", false,-1);
    tracep->declBit(c+2,"rstn", false,-1);
    tracep->declBus(c+3,"din", false,-1, 7,0);
    tracep->declBus(c+4,"shamt", false,-1, 2,0);
    tracep->declBit(c+5,"lr", false,-1);
    tracep->declBit(c+6,"al", false,-1);
    tracep->declBus(c+7,"dout", false,-1, 7,0);
    tracep->pushNamePrefix("u_barrel_shifter ");
    tracep->declBit(c+1,"clk", false,-1);
    tracep->declBit(c+2,"rstn", false,-1);
    tracep->declBus(c+3,"din", false,-1, 7,0);
    tracep->declBus(c+4,"shamt", false,-1, 2,0);
    tracep->declBit(c+5,"lr", false,-1);
    tracep->declBit(c+6,"al", false,-1);
    tracep->declBus(c+7,"dout", false,-1, 7,0);
    tracep->declBus(c+8,"shift", false,-1, 31,0);
    tracep->declBus(c+9,"i", false,-1, 31,0);
    tracep->popNamePrefix(2);
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vtop___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullBit(oldp+1,(vlSelf->clk));
    bufp->fullBit(oldp+2,(vlSelf->rstn));
    bufp->fullCData(oldp+3,(vlSelf->din),8);
    bufp->fullCData(oldp+4,(vlSelf->shamt),3);
    bufp->fullBit(oldp+5,(vlSelf->lr));
    bufp->fullBit(oldp+6,(vlSelf->al));
    bufp->fullCData(oldp+7,(vlSelf->dout),8);
    bufp->fullIData(oldp+8,(vlSelf->shamt),32);
    bufp->fullIData(oldp+9,(vlSelf->top__DOT__u_barrel_shifter__DOT__i),32);
}
