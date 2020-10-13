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
#include <string.h>
#include <sys/types.h>
#include <pointer-arith.h>
#define likely(x)	__builtin_expect(!!(x), 1)
#define unlikely(x)	__builtin_expect(!!(x), 0)

int strcmp(char *str1, char *str2) {
	if (strlen(str1) != strlen(str2))
		return -1;

	size_t end = strlen(str1);
	unsigned int i;
	for (i = 0; i < end; i++)
		if (str1[i] != str2[i])
			return -1;

	return 0;
}

size_t strlen(const char *str) {
	const char *char_ptr;
	const unsigned long int *longword_ptr;
	unsigned long int longword, himagic, lomagic;

	/* Handle the first few characters by reading one character at a time.
	 Do this until CHAR_PTR is aligned on a longword boundary.  */
	for (char_ptr = str;
			((unsigned long int) char_ptr & (sizeof(longword) - 1)) != 0;
			++char_ptr)
		if (*char_ptr == '\0')
			return char_ptr - str;

	/* All these elucidatory comments refer to 4-byte longwords,
	 but the theory applies equally well to 8-byte longwords.  */

	longword_ptr = (unsigned long int*) char_ptr;

	/* Bits 31, 24, 16, and 8 of this number are zero.  Call these bits
	 the "holes."  Note that there is a hole just to the left of
	 each byte, with an extra at the end:

	 bits:  01111110 11111110 11111110 11111111
	 bytes: AAAAAAAA BBBBBBBB CCCCCCCC DDDDDDDD

	 The 1-bits make sure that carries propagate to the next 0-bit.
	 The 0-bits provide holes for carries to fall into.  */
	himagic = 0x80808080L;
	lomagic = 0x01010101L;
	if (sizeof(longword) > 4) {
		/* 64-bit version of the magic.  */
		/* Do the shift in two steps to avoid a warning if long has 32 bits.  */
		himagic = ((himagic << 16) << 16) | himagic;
		lomagic = ((lomagic << 16) << 16) | lomagic;
	}
	if (sizeof(longword) > 8)
		//abort ();
		return -1;
	/* Instead of the traditional loop which tests each character,
	 we will test a longword at a time.  The tricky part is testing
	 if *any of the four* bytes in the longword in question are zero.  */
	for (;;) {
		longword = *longword_ptr++;

		if (((longword - lomagic) & ~longword & himagic) != 0) {
			/* Which of the bytes was the zero?  If none of them were, it was
			 a misfire; continue the search.  */

			const char *cp = (const char*) (longword_ptr - 1);

			if (cp[0] == 0)
				return cp - str;
			if (cp[1] == 0)
				return cp - str + 1;
			if (cp[2] == 0)
				return cp - str + 2;
			if (cp[3] == 0)
				return cp - str + 3;
			if (sizeof(longword) > 4) {
				if (cp[4] == 0)
					return cp - str + 4;
				if (cp[5] == 0)
					return cp - str + 5;
				if (cp[6] == 0)
					return cp - str + 6;
				if (cp[7] == 0)
					return cp - str + 7;
			}
		}
	}
	return 0;
}

/* Return the length of the maximum initial segment
 of S which contains only characters in ACCEPT.  */
size_t strspn(const char *str, const char *accept) {
	if (accept[0] == '\0')
		return 0;
	if (unlikely(accept[1] == '\0')) {
		const char *a = str;
		for (; *str == *accept; str++)
			;
		return str - a;
	}
	/* Use multiple small memsets to enable inlining on most targets.  */
	unsigned char table[256];
	unsigned char *p = (uint8_t*) memset(table, 0, 64);
	memset(p + 64, 0, 64);
	memset(p + 128, 0, 64);
	memset(p + 192, 0, 64);
	unsigned char *s = (unsigned char*) accept;
	/* Different from strcspn it does not add the NULL on the table
	 so can avoid check if str[i] is NULL, since table['\0'] will
	 be 0 and thus stopping the loop check.  */
	do
		p[*s++] = 1;
	while (*s);
	s = (unsigned char*) str;
	if (!p[s[0]])
		return 0;
	if (!p[s[1]])
		return 1;
	if (!p[s[2]])
		return 2;
	if (!p[s[3]])
		return 3;
	s = (unsigned char*) PTR_ALIGN_DOWN(s, 4);
	unsigned int c0, c1, c2, c3;
	do {
		s += 4;
		c0 = p[s[0]];
		c1 = p[s[1]];
		c2 = p[s[2]];
		c3 = p[s[3]];
	} while ((c0 & c1 & c2 & c3) != 0);
	size_t count = s - (unsigned char*) str;
	return (c0 & c1) == 0 ? count + c0 : count + c2 + 2;
}

char* strchrnul(const char *s, int c_in) {
	const unsigned char *char_ptr;
	const unsigned long int *longword_ptr;
	unsigned long int longword, magic_bits, charmask;
	unsigned char c;
	c = (unsigned char) c_in;
	/* Handle the first few characters by reading one character at a time.
	 Do this until CHAR_PTR is aligned on a longword boundary.  */
	for (char_ptr = (const unsigned char*) s;
			((unsigned long int) char_ptr & (sizeof(longword) - 1)) != 0;
			++char_ptr)
		if (*char_ptr == c || *char_ptr == '\0')
			return (char*) char_ptr;
	/* All these elucidatory comments refer to 4-byte longwords,
	 but the theory applies equally well to 8-byte longwords.  */
	longword_ptr = (unsigned long int*) char_ptr;
	/* Bits 31, 24, 16, and 8 of this number are zero.  Call these bits
	 the "holes."  Note that there is a hole just to the left of
	 each byte, with an extra at the end:
	 bits:  01111110 11111110 11111110 11111111
	 bytes: AAAAAAAA BBBBBBBB CCCCCCCC DDDDDDDD
	 The 1-bits make sure that carries propagate to the next 0-bit.
	 The 0-bits provide holes for carries to fall into.  */
	magic_bits = -1;
	magic_bits = magic_bits / 0xff * 0xfe << 1 >> 1 | 1;
	/* Set up a longword, each of whose bytes is C.  */
	charmask = c | (c << 8);
	charmask |= charmask << 16;
	if (sizeof(longword) > 4)
		/* Do the shift in two steps to avoid a warning if long has 32 bits.  */
		charmask |= (charmask << 16) << 16;
	if (sizeof(longword) > 8)
		return (char*) NULL;
	//abort ();
	/* Instead of the traditional loop which tests each character,
	 we will test a longword at a time.  The tricky part is testing
	 if *any of the four* bytes in the longword in question are zero.  */
	for (;;) {
		/* We tentatively exit the loop if adding MAGIC_BITS to
		 LONGWORD fails to change any of the hole bits of LONGWORD.
		 1) Is this safe?  Will it catch all the zero bytes?
		 Suppose there is a byte with all zeros.  Any carry bits
		 propagating from its left will fall into the hole at its
		 least significant bit and stop.  Since there will be no
		 carry from its most significant bit, the LSB of the
		 byte to the left will be unchanged, and the zero will be
		 detected.
		 2) Is this worthwhile?  Will it ignore everything except
		 zero bytes?  Suppose every byte of LONGWORD has a bit set
		 somewhere.  There will be a carry into bit 8.  If bit 8
		 is set, this will carry into bit 16.  If bit 8 is clear,
		 one of bits 9-15 must be set, so there will be a carry
		 into bit 16.  Similarly, there will be a carry into bit
		 24.  If one of bits 24-30 is set, there will be a carry
		 into bit 31, so all of the hole bits will be changed.
		 The one misfire occurs when bits 24-30 are clear and bit
		 31 is set; in this case, the hole at bit 31 is not
		 changed.  If we had access to the processor carry flag,
		 we could close this loophole by putting the fourth hole
		 at bit 32!
		 So it ignores everything except 128's, when they're aligned
		 properly.
		 3) But wait!  Aren't we looking for C as well as zero?
		 Good point.  So what we do is XOR LONGWORD with a longword,
		 each of whose bytes is C.  This turns each byte that is C
		 into a zero.  */
		longword = *longword_ptr++;
		/* Add MAGIC_BITS to LONGWORD.  */
		if ((((longword + magic_bits)
		/* Set those bits that were unchanged by the addition.  */
		^ ~longword)
		/* Look at only the hole bits.  If any of the hole bits
		 are unchanged, most likely one of the bytes was a
		 zero.  */
		& ~magic_bits) != 0
				/* That caught zeroes.  Now test for C.  */
				|| ((((longword ^ charmask) + magic_bits)
						^ ~(longword ^ charmask)) & ~magic_bits) != 0) {
			/* Which of the bytes was C or zero?
			 If none of them were, it was a misfire; continue the search.  */
			const unsigned char *cp = (const unsigned char*) (longword_ptr - 1);
			if (*cp == c || *cp == '\0')
				return (char*) cp;
			if (*++cp == c || *cp == '\0')
				return (char*) cp;
			if (*++cp == c || *cp == '\0')
				return (char*) cp;
			if (*++cp == c || *cp == '\0')
				return (char*) cp;
			if (sizeof(longword) > 4) {
				if (*++cp == c || *cp == '\0')
					return (char*) cp;
				if (*++cp == c || *cp == '\0')
					return (char*) cp;
				if (*++cp == c || *cp == '\0')
					return (char*) cp;
				if (*++cp == c || *cp == '\0')
					return (char*) cp;
			}
		}
	}
	/* This should never happen.  */
	return (char*) NULL;
}

size_t strcspn(const char *str, const char *reject) {
	if (unlikely (reject[0] == '\0') || unlikely(reject[1] == '\0'))
		return strchrnul(str, reject[0]) - str;
	/* Use multiple small memsets to enable inlining on most targets.  */
	unsigned char table[256];
	unsigned char *p = (uint8_t*) memset(table, 0, 64);
	memset(p + 64, 0, 64);
	memset(p + 128, 0, 64);
	memset(p + 192, 0, 64);
	unsigned char *s = (unsigned char*) reject;
	unsigned char tmp;
	do
		p[tmp = *s++] = 1;
	while (tmp);
	s = (unsigned char*) str;
	if (p[s[0]])
		return 0;
	if (p[s[1]])
		return 1;
	if (p[s[2]])
		return 2;
	if (p[s[3]])
		return 3;
	s = PTR_ALIGN_DOWN(s, 4);
	unsigned int c0, c1, c2, c3;
	do {
		s += 4;
		c0 = p[s[0]];
		c1 = p[s[1]];
		c2 = p[s[2]];
		c3 = p[s[3]];
	} while ((c0 | c1 | c2 | c3) == 0);
	size_t count = s - (unsigned char*) str;
	return (c0 | c1) != 0 ? count - c0 + 1 : count - c2 + 3;
}


/* Parse S into tokens separated by characters in DELIM.
   If S is NULL, the saved pointer in SAVE_PTR is used as
   the next starting point.  For example:
        char s[] = "-abc-=-def";
        char *sp;
        x = strtok_r(s, "-", &sp);        // x = "abc", sp = "=-def"
        x = strtok_r(NULL, "-=", &sp);        // x = "def", sp = NULL
        x = strtok_r(NULL, "=", &sp);        // x = NULL
                // s = "abc\0-def\0"
*/
char* __strtok_r(char *s, const char *delim, char **save_ptr) {
	char *end;
	if (s == NULL)
		s = *save_ptr;
	if (*s == '\0') {
		*save_ptr = s;
		return (char*) NULL;
	}
	/* Scan leading delimiters.  */
	s += strspn(s, delim);
	if (*s == '\0') {
		*save_ptr = s;
		return (char*) NULL;
	}
	/* Find the end of the token.  */
	end = s + strcspn(s, delim);
	if (*end == '\0') {
		*save_ptr = end;
		return s;
	}
	/* Terminate the token and make *SAVE_PTR point past it.  */
	*end = '\0';
	*save_ptr = end + 1;
	return s;
}

/* Parse S into tokens separated by characters in DELIM.
 If S is NULL, the last string strtok() was called with is
 used.  For example:
 char s[] = "-abc-=-def";
 x = strtok(s, "-");                // x = "abc"
 x = strtok(NULL, "-=");                // x = "def"
 x = strtok(NULL, "=");                // x = NULL
 // s = "abc\0=-def\0"
 */
char* strtok(char *s, const char *delim) {
	static char *olds;
	return __strtok_r(s, delim, &olds);
}
