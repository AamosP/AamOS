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
#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define DARK_RED 0x4
#define PURPLE 0x5
#define BROWN 0x6
#define LIGHT_GRAY 0x7
#define GRAY 0x8
#define LIGHT_BLUE 0x9
#define LIME 0xa
#define LIGHT_CYAN 0xb
#define RED 0xc
#define MAGENTA 0xd
#define YELLOW 0xe
#define WHITE 0xf

#include <sys/types.h>

void enable_cursor(uint8_t start, uint8_t end);
void disable_cursor();
void update_cursor();
void set_fg(uint8_t fg);
void set_bg(uint8_t bg);
void console_init(uint8_t fg, uint8_t bg);
void write_char(const char c);
void write_string(const char* s);

#endif
