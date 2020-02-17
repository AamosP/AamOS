#include <keyboard.h>
#include <utils.h>
#include <font.h>
#include <stddef.h>

unsigned char kb_data[5];

void init_kb(unsigned char scancode_set) {
//#define SCANCODE_SET scancode_set
//	outb(KB_PORT, CMD_RESET);
//	while(inb(KB_PORT) != SELF_TEST_PASSED) {
//
//	}
//	outb(KB_PORT, CMD_SCANCODE);
//	outb(KB_PORT, scancode_set);
//	while(inb(KB_PORT) != ACK) {
//
//	}
	kb_data[0] = 0;
	kb_data[1] = 0;
	kb_data[2] = 0;
	kb_data[3] = 0;
	kb_data[4] = 0;
}

void read_kb() {
	unsigned char c = inb(KB_PORT);
	unsigned int x = 0;
	for (int i = 0; i < 5; i++) {
		if ((kb_data[i] + 128) == c) {
			kb_data[i] = 0;
			x = 1;
		} else if (c == 0) {
			kb_data[i] = 0;
			x = 1;
		} else if (kb_data[i] == c) {
			x = 1;
		}
	}
	for(int i = 0; i < 5; i++) {
		if(kb_data[i] == 0 && x == 0 && (c >> 7) == 0) {
			kb_data[i] = c;
			break;
		}
	}
}
