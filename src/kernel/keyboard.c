#include <keyboard.h>
#include <utils.h>
#include <font.h>
#include <stddef.h>

static unsigned char kb_data = 0;

unsigned char read_kb() {
	unsigned char c = inb(KB_PORT);
	if (c != kb_data) {
		if (c < 0x80) {
			kb_data = c;
		} else if (c > 0x80) {
			kb_data = 0;
		}
//		if (kb_data > 0x80)
//			kb_data = 0;
	}
	return kb_data;
}
