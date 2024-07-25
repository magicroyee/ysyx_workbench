#include <am.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  static uint32_t key = 0;
  key = inl(KBD_ADDR);
  kbd->keydown = (key & KEYDOWN_MASK);
  kbd->keycode = key & ~KEYDOWN_MASK;
}
