// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    // Body
    if (vlSelf->rstn) {
        vlSelf->top__DOT__u_barrel_shifter__DOT__i = 8U;
        vlSelf->dout = ((0xfeU & (IData)(vlSelf->dout)) 
                        | (1U & ((IData)(vlSelf->lr)
                                  ? ((0U >= (IData)(vlSelf->shamt)) 
                                     & ((IData)(vlSelf->din) 
                                        >> (7U & (- (IData)(vlSelf->shamt)))))
                                  : ((0U < ((IData)(8U) 
                                            - (IData)(vlSelf->shamt)))
                                      ? ((IData)(vlSelf->din) 
                                         >> (IData)(vlSelf->shamt))
                                      : ((IData)(vlSelf->al) 
                                         & ((IData)(vlSelf->din) 
                                            >> 7U))))));
        vlSelf->dout = ((0xfdU & (IData)(vlSelf->dout)) 
                        | (2U & (((IData)(vlSelf->lr)
                                   ? ((1U >= (IData)(vlSelf->shamt)) 
                                      & ((IData)(vlSelf->din) 
                                         >> (7U & ((IData)(1U) 
                                                   - (IData)(vlSelf->shamt)))))
                                   : ((1U < ((IData)(8U) 
                                             - (IData)(vlSelf->shamt)))
                                       ? ((IData)(vlSelf->din) 
                                          >> (7U & 
                                              ((IData)(1U) 
                                               + (IData)(vlSelf->shamt))))
                                       : ((IData)(vlSelf->al) 
                                          & ((IData)(vlSelf->din) 
                                             >> 7U)))) 
                                 << 1U)));
        vlSelf->dout = ((0xfbU & (IData)(vlSelf->dout)) 
                        | (4U & (((IData)(vlSelf->lr)
                                   ? ((2U >= (IData)(vlSelf->shamt)) 
                                      & ((IData)(vlSelf->din) 
                                         >> (7U & ((IData)(2U) 
                                                   - (IData)(vlSelf->shamt)))))
                                   : ((2U < ((IData)(8U) 
                                             - (IData)(vlSelf->shamt)))
                                       ? ((IData)(vlSelf->din) 
                                          >> (7U & 
                                              ((IData)(2U) 
                                               + (IData)(vlSelf->shamt))))
                                       : ((IData)(vlSelf->al) 
                                          & ((IData)(vlSelf->din) 
                                             >> 7U)))) 
                                 << 2U)));
        vlSelf->dout = ((0xf7U & (IData)(vlSelf->dout)) 
                        | (8U & (((IData)(vlSelf->lr)
                                   ? ((3U >= (IData)(vlSelf->shamt)) 
                                      & ((IData)(vlSelf->din) 
                                         >> (7U & ((IData)(3U) 
                                                   - (IData)(vlSelf->shamt)))))
                                   : ((3U < ((IData)(8U) 
                                             - (IData)(vlSelf->shamt)))
                                       ? ((IData)(vlSelf->din) 
                                          >> (7U & 
                                              ((IData)(3U) 
                                               + (IData)(vlSelf->shamt))))
                                       : ((IData)(vlSelf->al) 
                                          & ((IData)(vlSelf->din) 
                                             >> 7U)))) 
                                 << 3U)));
        vlSelf->dout = ((0xefU & (IData)(vlSelf->dout)) 
                        | (0x10U & (((IData)(vlSelf->lr)
                                      ? ((4U >= (IData)(vlSelf->shamt)) 
                                         & ((IData)(vlSelf->din) 
                                            >> (7U 
                                                & ((IData)(4U) 
                                                   - (IData)(vlSelf->shamt)))))
                                      : ((4U < ((IData)(8U) 
                                                - (IData)(vlSelf->shamt)))
                                          ? ((IData)(vlSelf->din) 
                                             >> (7U 
                                                 & ((IData)(4U) 
                                                    + (IData)(vlSelf->shamt))))
                                          : ((IData)(vlSelf->al) 
                                             & ((IData)(vlSelf->din) 
                                                >> 7U)))) 
                                    << 4U)));
        vlSelf->dout = ((0xdfU & (IData)(vlSelf->dout)) 
                        | (0x20U & (((IData)(vlSelf->lr)
                                      ? ((5U >= (IData)(vlSelf->shamt)) 
                                         & ((IData)(vlSelf->din) 
                                            >> (7U 
                                                & ((IData)(5U) 
                                                   - (IData)(vlSelf->shamt)))))
                                      : ((5U < ((IData)(8U) 
                                                - (IData)(vlSelf->shamt)))
                                          ? ((IData)(vlSelf->din) 
                                             >> (7U 
                                                 & ((IData)(5U) 
                                                    + (IData)(vlSelf->shamt))))
                                          : ((IData)(vlSelf->al) 
                                             & ((IData)(vlSelf->din) 
                                                >> 7U)))) 
                                    << 5U)));
        vlSelf->dout = ((0xbfU & (IData)(vlSelf->dout)) 
                        | (0x40U & (((IData)(vlSelf->lr)
                                      ? ((6U >= (IData)(vlSelf->shamt)) 
                                         & ((IData)(vlSelf->din) 
                                            >> (7U 
                                                & ((IData)(6U) 
                                                   - (IData)(vlSelf->shamt)))))
                                      : ((6U < ((IData)(8U) 
                                                - (IData)(vlSelf->shamt)))
                                          ? ((IData)(vlSelf->din) 
                                             >> (7U 
                                                 & ((IData)(6U) 
                                                    + (IData)(vlSelf->shamt))))
                                          : ((IData)(vlSelf->al) 
                                             & ((IData)(vlSelf->din) 
                                                >> 7U)))) 
                                    << 6U)));
        vlSelf->dout = ((0x7fU & (IData)(vlSelf->dout)) 
                        | (0x80U & (((IData)(vlSelf->lr)
                                      ? ((IData)(vlSelf->al) 
                                         & ((IData)(vlSelf->din) 
                                            >> 7U))
                                      : ((7U < ((IData)(8U) 
                                                - (IData)(vlSelf->shamt)))
                                          ? ((IData)(vlSelf->din) 
                                             >> (7U 
                                                 & ((IData)(7U) 
                                                    + (IData)(vlSelf->shamt))))
                                          : ((IData)(vlSelf->al) 
                                             & ((IData)(vlSelf->din) 
                                                >> 7U)))) 
                                    << 7U)));
    } else {
        vlSelf->dout = 0U;
    }
}

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    // Body
    if (vlSelf->__VnbaTriggered.at(0U)) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        __VnbaContinue = 0U;
        vlSelf->__VnbaTriggered.clear();
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            vlSelf->__VactContinue = 0U;
            Vtop___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    Vtop___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("/home/zhu/workspace/ysyx-workbench/npc/ex6/vsrc/top.v", 1, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                Vtop___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("/home/zhu/workspace/ysyx-workbench/npc/ex6/vsrc/top.v", 1, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            Vtop___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rstn & 0xfeU))) {
        Verilated::overWidthError("rstn");}
    if (VL_UNLIKELY((vlSelf->shamt & 0xf8U))) {
        Verilated::overWidthError("shamt");}
    if (VL_UNLIKELY((vlSelf->lr & 0xfeU))) {
        Verilated::overWidthError("lr");}
    if (VL_UNLIKELY((vlSelf->al & 0xfeU))) {
        Verilated::overWidthError("al");}
}
#endif  // VL_DEBUG