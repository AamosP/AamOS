/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#include <aamOS/kernel.h>
#include <asm/io.h>

char keymap[0x59] =
  { 0, 0x01/* esc */, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '+',
      '´', '\b'/* backspace */, '\t'/* tab */, 'q', 'w', 'e', 'r', 't', 'y',
      'u', 'i', 'o', 'p', 0xe5, 0xa8, '\r', 0x1d/* ctrl */, 'a', 's', 'd', 'f',
      'g', 'h', 'j', 'k', 'l', 0xf6, 0xe4, '§', 0x2a/* shift */, '\'', 'z', 'x',
      'c', 'v', 'b', 'n', 'm', ',', '.', '-', 0x36 /* rshift */, '*',
      0x38/* alt */, ' ', 0x3a/* caps lock */, 0x3b/* F1 */, 0x3c/* F2 */,
      0x3d/* F3 */, 0x3e/* F4 */, 0x3f/* F5 */, 0x40/* F6 */, 0x41/* F7 */,
      0x42/* F8 */, 0x43/* F9 */, 0x44/* F10 */, 0x45 /* num lock */,
      0x46/* scroll lock */, 0x47/* N7 */, 0x48/* N8 */, 0x49/* N9 */, '-',
      0x4b/* N4 */, 0x4c/* N5 */, 0x4d/* N6 */, '+', 0x4f/* N1 */, 0x50/* N2 */,
      0x51/* N3 */, 0x52/* N0 */, 0x53/* N, */, 0x54 /* sysrq */, 0, '<',
      0x57/* F11 */, 0x58 /* F12 */};

static int e0 = 0;

void
kb_init ()
{
  outb(0x60, 0xf5);
  outb(0x60, 0xf0);
  outb(0x60, 0x02);
  outb(0x60, 0xf4);
}

void
kb_handler (int scancode)
{
  printf("%c", keymap[scancode]);
}
