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
    tracep->declBus(c+1,"a", false,-1, 3,0);
    tracep->declBus(c+2,"b", false,-1, 3,0);
    tracep->declBus(c+3,"op", false,-1, 2,0);
    tracep->declBus(c+4,"y", false,-1, 3,0);
    tracep->declBit(c+5,"c", false,-1);
    tracep->declBit(c+6,"z", false,-1);
    tracep->declBit(c+7,"of", false,-1);
    tracep->pushNamePrefix("top ");
    tracep->declBus(c+1,"a", false,-1, 3,0);
    tracep->declBus(c+2,"b", false,-1, 3,0);
    tracep->declBus(c+3,"op", false,-1, 2,0);
    tracep->declBus(c+4,"y", false,-1, 3,0);
    tracep->declBit(c+5,"c", false,-1);
    tracep->declBit(c+6,"z", false,-1);
    tracep->declBit(c+7,"of", false,-1);
    tracep->pushNamePrefix("u_alu ");
    tracep->declBus(c+1,"a", false,-1, 3,0);
    tracep->declBus(c+2,"b", false,-1, 3,0);
    tracep->declBus(c+3,"op", false,-1, 2,0);
    tracep->declBus(c+4,"y", false,-1, 3,0);
    tracep->declBit(c+5,"c", false,-1);
    tracep->declBit(c+6,"z", false,-1);
    tracep->declBit(c+7,"of", false,-1);
    tracep->declBus(c+8,"tmp", false,-1, 4,0);
    tracep->declBus(c+9,"nb_nocin", false,-1, 3,0);
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
    bufp->fullCData(oldp+1,(vlSelf->a),4);
    bufp->fullCData(oldp+2,(vlSelf->b),4);
    bufp->fullCData(oldp+3,(vlSelf->op),3);
    bufp->fullCData(oldp+4,(vlSelf->y),4);
    bufp->fullBit(oldp+5,(vlSelf->c));
    bufp->fullBit(oldp+6,(vlSelf->z));
    bufp->fullBit(oldp+7,(vlSelf->of));
    bufp->fullCData(oldp+8,(vlSelf->top__DOT__u_alu__DOT__tmp),5);
    bufp->fullCData(oldp+9,(vlSelf->top__DOT__u_alu__DOT__nb_nocin),4);
}
