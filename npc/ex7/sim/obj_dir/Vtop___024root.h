// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"

class Vtop__Syms;

class Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ top__DOT__u_keyboard_sim__DOT__clk;
    CData/*0:0*/ top__DOT__u_keyboard_sim__DOT__clrn;
    CData/*0:0*/ top__DOT__u_keyboard_sim__DOT__ready;
    CData/*0:0*/ top__DOT__u_keyboard_sim__DOT__overflow;
    CData/*0:0*/ top__DOT__u_keyboard_sim__DOT__kbd_clk;
    CData/*0:0*/ top__DOT__u_keyboard_sim__DOT__kbd_data;
    CData/*0:0*/ top__DOT__u_keyboard_sim__DOT__nextdata_n;
    CData/*2:0*/ top__DOT__u_keyboard_sim__DOT__inst__DOT__w_ptr;
    CData/*2:0*/ top__DOT__u_keyboard_sim__DOT__inst__DOT__r_ptr;
    CData/*3:0*/ top__DOT__u_keyboard_sim__DOT__inst__DOT__count;
    CData/*2:0*/ top__DOT__u_keyboard_sim__DOT__inst__DOT__ps2_clk_sync;
    CData/*0:0*/ top__DOT__u_keyboard_sim__DOT__inst__DOT____Vlvbound_h1a91ade8__0;
    CData/*0:0*/ __Vtrigrprev__TOP__top__DOT__u_keyboard_sim__DOT__clk;
    CData/*0:0*/ __VactContinue;
    SData/*10:0*/ top__DOT__u_keyboard_sim__DOT__model__DOT__kbd_sendcode__Vstatic__send_buffer;
    SData/*9:0*/ top__DOT__u_keyboard_sim__DOT__inst__DOT__buffer;
    IData/*31:0*/ top__DOT__u_keyboard_sim__DOT__model__DOT__kbd_sendcode__Vstatic__i;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<CData/*7:0*/, 8> top__DOT__u_keyboard_sim__DOT__inst__DOT__fifo;
    VlUnpacked<CData/*0:0*/, 4> __Vm_traceActivity;
    VlDelayScheduler __VdlySched;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
