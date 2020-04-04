#ifndef CONSOLE_H
#define CONSOLE_H

#include <multiboot2.h>
#include <utils.h>

void console_init(struct multiboot_tag_framebuffer *tag, uint32_t fg, uint32_t bg);
void console_clear(void);
void console_putchar(char c);
void console_print(char* s);

#endif
