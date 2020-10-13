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
#ifndef _TIMER_H_
#define _TIMER_H_

void set_timer_freq(uint32_t hz);
void timer(registers_t *regs);
void timer_init(void);
void sleep(uint32_t d);

#endif
