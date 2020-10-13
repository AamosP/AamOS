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
#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

//#include <stdint.h>

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

#ifndef _TIME_T
#define _TIME_T
typedef long time_t;
#endif

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
typedef long ptrdiff_t;
#endif

#ifndef NULL
#define NULL 0
#endif

typedef int pid_t;
typedef unsigned short uid_t;
typedef unsigned char gid_t;
typedef unsigned short dev_t;
typedef unsigned short ino_t;
typedef unsigned short mode_t;
typedef unsigned short umode_t;
typedef unsigned char nlink_t;
typedef int daddr_t;
typedef unsigned int vaddr_t;
typedef long off_t;
typedef unsigned char u_char;
typedef unsigned short ushort;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;
typedef unsigned int uintptr_t;

typedef struct {
	int quot, rem;
} div_t;
typedef struct {
	long quot, rem;
} ldiv_t;

#if __WORDSIZE == 64
# ifndef __intptr_t_defined
//typedef long int                intptr_t;
//#  define __intptr_t_defined
# endif
//typedef unsigned long int        uintptr_t;
#else
# ifndef __intptr_t_defined
//typedef int                        intptr_t;
//#  define __intptr_t_defined
# endif
//typedef unsigned int                uintptr_t;
#endif

#define FALSE 0
#define TRUE (!FALSE)

struct ustat {
	daddr_t f_tfree;
	ino_t f_tinode;
	char f_fname[6];
	char f_fpack[6];
};


#endif
