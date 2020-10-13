/*******************************************************************************
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2020 Aamos Pernu
 * 
 * AamOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * AamOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this aamOS.  If not, see <https://www.gnu.org/licenses/>.
 ******************************************************************************/
#include <aamOS/kernel.h>
#include <asm/io.h>
#include <stdio.h>

static int mode = 0;

static uint8_t leds = 0;

static int e0 = 0;

static unsigned long functable[12] = { 0x415b5b1b, 0x425b5b1b, 0x435b5b1b,
		0x445b5b1b, 0x455b5b1b, 0x465b5b1b, 0x475b5b1b, 0x485b5b1b, 0x495b5b1b,
		0x4a5b5b1b, 0x4b5b5b1b, 0x4c5b5b1b };

static int keymap[0x61] = { 0, 0x1b, '1', '2', '3', '4', '5', '6', '7', '8',
		'9', '0', '+', 0, 127, 9, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
		'o', 'p', 0xe5, 0, 10, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
		0xf6, 0xe4, 0, 0, '\0', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-',
		0, '*', 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0,
		0, 0, '+', 0, 0, 0, 0, 0, 0, 0, '<', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static int shiftmap[0x61] = { 0, 0x1b, '!', '"', '#', 0, '%', '&', '/', '(',
		')', '=', '?', '`', 127, 9, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O',
		'P', 0xc5, '^', 10, 0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 0xd6,
		0xc4, 0, 0, '*', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ';', ':', '_', 0,
		'*', 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0,
		0, '+', 0, 0, 0, 0, 0, 0, 0, '>', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static int altmap[0x61] = { 0, 0, '\0', '@', 0, '$', '\0', '\0', '|', '[',
		']', 0, 0, '\0', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '~', 10, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, '|', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

//static const char *num_table = "789 456 1230,";
//static const char *cur_table = "HA5 DGC YB623";

static int key = 0;
static char buf[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

static void kb_wait(void) {
	int n = inb(0x64);
	while ((n << 1) == 0) {
		n = inb(0x64);
	}
}

static void set_leds(void) {
	kb_wait();
	outb(0x60, 0xed);
	kb_wait();
	outb(0x60, leds);
}

static int top = 0;
static void put_queue(char c) {
	if (top < 8) {
		buf[top] = c;
		top++;
	} else {
		for (int i = 0; i < 8; i++) {
			buf[i] = 0;
		}
		top = 0;
		buf[top] = c;
		top++;
	}
}

char get_queue() {
	char c = 0;
	if (top != 0) {
		c = buf[top - 1];
		buf[top - 1] = 0;
		top--;
	} else {
		c = buf[0];
		buf[0] = 0;
	}
	return c;
}

static void none(void) {
	return;
}

static void do_self(void) {
	int *map;
	if (mode & 0x20)
		map = altmap;
	else if (mode & 0x03)
		map = shiftmap;
	else
		map = keymap;
	key = map[key];
	if (mode & 0x40) {
		if (key >= 'a' && key <= 'z')
			key -= 0x20;
	}
	if (mode & 0x0c) {
		if (key >= 64 && key < 96)
			key -= 64;
	}
	if (mode & 0x10)
		key |= 0x80;
	key &= 0xff;
	put_queue(key);
}

static void psbrk(void) {
	return;
}

static void sysrq(void) {
	return;
}

static void ctrl(void) {
	int m = 0x04;
	if (e0 == 1)
		m *= 2;
	else if (e0 == 2) {
		m = 0;
		psbrk();
		return;
	}
	mode |= m;
}

static void lshift(void) {
	mode |= 0x01;
}

static void minus(void) {
	if (e0)
		do_self();
	else {
		put_queue('/');
	}
}

static void rshift(void) {
	mode |= 0x02;
}

static void alt(void) {
	int m = 0x10;
	if (e0)
		m *= 2;
	mode |= m;
}

static void caps(void) {
	if (mode ^ 0x80) {
		leds ^= 4;
		mode ^= 0x40;
		mode |= 0x80;
	}
	set_leds();
}

static void func(void) {
	if (!(key -= 0x3b))
		return;
	if (key <= 9) {
		put_queue(functable[key]);
	}
	key -= 18;
	if (key < 10)
		return;
	if (key > 11)
		return;
	put_queue(functable[key]);
}

static void num(void) {
	leds ^= 0x02;
	set_leds();
}

static void scroll(void) {
	leds ^= 0x01;
	set_leds();
}

static void unctrl(void) {
	int m = 0x04;
	if (e0)
		m *= 2;
	mode &= !m;
}

static void unlshift(void) {
	mode &= !1;
}

static void unrshift(void) {
	mode &= !2;
}

static void unalt(void) {
	int m = 0x10;
	if (e0)
		m *= 2;
	mode &= !m;
}

static void uncaps(void) {
	mode &= 0x7f;
	set_leds();
}

static void cursor(void) {
	return;
}

static void (*key_table[256])(void) = {none,do_self,do_self,do_self, /* 00-03 s0 esc 1 2 */
	do_self,do_self,do_self,do_self, /* 04-07 3 4 5 6 */
	do_self,do_self,do_self,do_self, /* 08-0B 7 8 9 0 */
	do_self,do_self,do_self,do_self, /* 0C-0F + ' bs tab */
	do_self,do_self,do_self,do_self, /* 10-13 q w e r */
	do_self,do_self,do_self,do_self, /* 14-17 t y u i */
	do_self,do_self,do_self,do_self, /* 18-1B o p } ^ */
	do_self,ctrl,do_self,do_self, /* 1C-1F enter ctrl a s */
	do_self,do_self,do_self,do_self, /* 20-23 d f g h */
	do_self,do_self,do_self,do_self, /* 24-27 j k l | */
	do_self,do_self,lshift,do_self, /* 28-2B { para lshift , */
	do_self,do_self,do_self,do_self, /* 2C-2F z x c v */
	do_self,do_self,do_self,do_self, /* 30-33 b n m , */
	do_self,minus,rshift,do_self, /* 34-37 . - rshift * */
	alt,do_self,caps,func, /* 38-3B alt sp caps f1 */
	func,func,func,func, /* 3C-3F f2 f3 f4 f5 */
	func,func,func,func, /* 40-43 f6 f7 f8 f9 */
	func,num,scroll,cursor, /* 44-47 f10 num scr home */
	cursor,cursor,do_self,cursor, /* 48-4B up pgup - left */
	cursor,cursor,do_self,cursor, /* 4C-4F n5 right + end */
	cursor,cursor,cursor,cursor, /* 50-53 dn pgdn ins del */
	sysrq,none,do_self,func, /* 54-57 sysreq ? < f11 */
	func,none,none,none, /* 58-5B f12 ? ? ? */
	none,none,none,none, /* 5C-5F ? ? ? ? */
	none,none,none,none, /* 60-63 ? ? ? ? */
	none,none,none,none, /* 64-67 ? ? ? ? */
	none,none,none,none, /* 68-6B ? ? ? ? */
	none,none,none,none, /* 6C-6F ? ? ? ? */
	none,none,none,none, /* 70-73 ? ? ? ? */
	none,none,none,none, /* 74-77 ? ? ? ? */
	none,none,none,none, /* 78-7B ? ? ? ? */
	none,none,none,none, /* 7C-7F ? ? ? ? */
	none,none,none,none, /* 80-83 ? br br br */
	none,none,none,none, /* 84-87 br br br br */
	none,none,none,none, /* 88-8B br br br br */
	none,none,none,none, /* 8C-8F br br br br */
	none,none,none,none, /* 90-93 br br br br */
	none,none,none,none, /* 94-97 br br br br */
	none,none,none,none, /* 98-9B br br br br */
	none,unctrl,none,none, /* 9C-9F br unctrl br br */
	none,none,none,none, /* A0-A3 br br br br */
	none,none,none,none, /* A4-A7 br br br br */
	none,none,unlshift,none, /* A8-AB br br unlshift br */
	none,none,none,none, /* AC-AF br br br br */
	none,none,none,none, /* B0-B3 br br br br */
	none,none,unrshift,none, /* B4-B7 br br unrshift br */
	unalt,none,uncaps,none, /* B8-BB unalt br uncaps br */
	none,none,none,none, /* BC-BF br br br br */
	none,none,none,none, /* C0-C3 br br br br */
	none,none,none,none, /* C4-C7 br br br br */
	none,none,none,none, /* C8-CB br br br br */
	none,none,none,none, /* CC-CF br br br br */
	none,none,none,none, /* D0-D3 br br br br */
	none,none,none,none, /* D4-D7 br br br br */
	none,none,none,none, /* D8-DB br ? ? ? */
	none,none,none,none, /* DC-DF ? ? ? ? */
	none,none,none,none, /* E0-E3 e0 e1 ? ? */
	none,none,none,none, /* E4-E7 ? ? ? ? */
	none,none,none,none, /* E8-EB ? ? ? ? */
	none,none,none,none, /* EC-EF ? ? ? ? */
	none,none,none,none, /* F0-F3 ? ? ? ? */
	none,none,none,none, /* F4-F7 ? ? ? ? */
	none,none,none,none, /* F8-FB ? ? ? ? */
	none,none,none,none /* FC-FF ? ? ? ? */};

void kb_init() {
	register_irq_handler(1, kb_handler);
	outb(0x60, 0xf5);
	inb(0x60);
	outb(0x60, 0xf0);
	inb(0x60);
	outb(0x60, 0x02);
	inb(0x60);
	outb(0x60, 0xf4);
	inb(0x60);
	//return;
	//write_serial('k');
}

void kb_handler(registers_t *regs) {
	int scancode = inb(0x60);
	key = scancode;
	void (*key_handler)(void);
	if (scancode == 0xe0) {
		e0 = 1;
	} else if (scancode == 0xe1) {
		e0 = 2;
	} else {
		key_handler = key_table[scancode];
		key_handler();
		e0 = 0;
	}
	char c = get_queue();
	write_serial(c);
	printf("%c", c);
	//const char* s = "";
	//itoa((char*)s, 'x', regs->err_code);
	//write_serial_str(s);
}
