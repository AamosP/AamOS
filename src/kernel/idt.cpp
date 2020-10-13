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
#include <asm/io.h>
#include <asm/system.h>
#include <idt.h>
#include <sys/types.h>
#include <aamOS/kernel.h>
#include <stdio.h>

static struct IDT_entry IDT[256];

/* Set the value of one IDT entry. */
void idt_set_gate (uint8_t num, uint32_t offset, uint16_t sel, uint8_t flags)
{
  IDT[num].offset_lo = offset & 0xFFFF;
  IDT[num].offset_hi = (offset >> 16) & 0xFFFF;

  IDT[num].selector = sel;
  IDT[num].zero = 0;
  /* We must uncomment the OR below when we get to using user-mode.
   // It sets the interrupt gate's privilege level to 3. */
  IDT[num].type_attr = flags /* | 0x60 */;
}

extern "C" void idt_init (void)
{
  extern int
  loadIdt (unsigned long*);
  extern int
  irq0 (void);
  extern int
  irq1 (void);
  extern int
  irq2 (void);
  extern int
  irq3 (void);
  extern int
  irq4 (void);
  extern int
  irq5 (void);
  extern int
  irq6 (void);
  extern int
  irq7 (void);
  extern int
  irq8 (void);
  extern int
  irq9 (void);
  extern int
  irq10 (void);
  extern int
  irq11 (void);
  extern int
  irq12 (void);
  extern int
  irq13 (void);
  extern int
  irq14 (void);
  extern int
  irq15 (void);

  extern int
  isr0 (void);
  extern int
  isr1 (void);
  extern int
  isr2 (void);
  extern int
  isr3 (void);
  extern int
  isr4 (void);
  extern int
  isr5 (void);
  extern int
  isr6 (void);
  extern int
  isr7 (void);
  extern int
  isr8 (void);
  extern int
  isr9 (void);
  extern int
  isr10 (void);
  extern int
  isr11 (void);
  extern int
  isr12 (void);
  extern int
  isr13 (void);
  extern int
  isr14 (void);
  extern int
  isr15 (void);
  extern int
  isr16 (void);
  extern int
  isr17 (void);
  extern int
  isr18 (void);
  extern int
  isr19 (void);
  extern int
  isr20 (void);
  extern int
  isr21 (void);
  extern int
  isr22 (void);
  extern int
  isr23 (void);
  extern int
  isr24 (void);
  extern int
  isr25 (void);
  extern int
  isr26 (void);
  extern int
  isr27 (void);
  extern int
  isr28 (void);
  extern int
  isr29 (void);
  extern int
  isr30 (void);
  extern int
  isr31 (void);

  unsigned long idt_address;
  unsigned long idt_ptr[2];

  /* remapping the PIC */
  outb(0x20, 0x11);
  outb(0xA0, 0x11);
  outb(0x21, 0x20);
  outb(0xA1, 40);
  outb(0x21, 0x04);
  outb(0xA1, 0x02);
  outb(0x21, 0x01);
  outb(0xA1, 0x01);
  outb(0x21, 0x0);
  outb(0xA1, 0x0);

  idt_set_gate (0, (uint32_t) isr0, 0x08, 0x8e);
  idt_set_gate (1, (uint32_t) isr1, 0x08, 0x8e);
  idt_set_gate (2, (uint32_t) isr2, 0x08, 0x8e);
  idt_set_gate (3, (uint32_t) isr3, 0x08, 0x8e);
  idt_set_gate (4, (uint32_t) isr4, 0x08, 0x8e);
  idt_set_gate (5, (uint32_t) isr5, 0x08, 0x8e);
  idt_set_gate (6, (uint32_t) isr6, 0x08, 0x8e);
  idt_set_gate (7, (uint32_t) isr7, 0x08, 0x8e);
  idt_set_gate (8, (uint32_t) isr8, 0x08, 0x8e);
  idt_set_gate (9, (uint32_t) isr9, 0x08, 0x8e);
  idt_set_gate (10, (uint32_t) isr10, 0x08, 0x8e);
  idt_set_gate (11, (uint32_t) isr11, 0x08, 0x8e);
  idt_set_gate (12, (uint32_t) isr12, 0x08, 0x8e);
  idt_set_gate (13, (uint32_t) isr13, 0x08, 0x8e);
  idt_set_gate (14, (uint32_t) isr14, 0x08, 0x8e);
  idt_set_gate (15, (uint32_t) isr15, 0x08, 0x8e);
  idt_set_gate (16, (uint32_t) isr16, 0x08, 0x8e);
  idt_set_gate (17, (uint32_t) isr17, 0x08, 0x8e);
  idt_set_gate (18, (uint32_t) isr18, 0x08, 0x8e);
  idt_set_gate (19, (uint32_t) isr19, 0x08, 0x8e);
  idt_set_gate (20, (uint32_t) isr20, 0x08, 0x8e);
  idt_set_gate (21, (uint32_t) isr21, 0x08, 0x8e);
  idt_set_gate (22, (uint32_t) isr22, 0x08, 0x8e);
  idt_set_gate (23, (uint32_t) isr23, 0x08, 0x8e);
  idt_set_gate (24, (uint32_t) isr24, 0x08, 0x8e);
  idt_set_gate (25, (uint32_t) isr25, 0x08, 0x8e);
  idt_set_gate (26, (uint32_t) isr26, 0x08, 0x8e);
  idt_set_gate (27, (uint32_t) isr27, 0x08, 0x8e);
  idt_set_gate (28, (uint32_t) isr28, 0x08, 0x8e);
  idt_set_gate (29, (uint32_t) isr29, 0x08, 0x8e);
  idt_set_gate (30, (uint32_t) isr30, 0x08, 0x8e);
  idt_set_gate (31, (uint32_t) isr31, 0x08, 0x8e);

  idt_set_gate (32, (uint32_t) irq0, 0x08, 0x8e);
  idt_set_gate (33, (uint32_t) irq1, 0x08, 0x8e);
  idt_set_gate (34, (uint32_t) irq2, 0x08, 0x8e);
  idt_set_gate (35, (uint32_t) irq3, 0x08, 0x8e);
  idt_set_gate (36, (uint32_t) irq4, 0x08, 0x8e);
  idt_set_gate (37, (uint32_t) irq5, 0x08, 0x8e);
  idt_set_gate (38, (uint32_t) irq6, 0x08, 0x8e);
  idt_set_gate (39, (uint32_t) irq7, 0x08, 0x8e);
  idt_set_gate (40, (uint32_t) irq8, 0x08, 0x8e);
  idt_set_gate (41, (uint32_t) irq9, 0x08, 0x8e);
  idt_set_gate (42, (uint32_t) irq10, 0x08, 0x8e);
  idt_set_gate (43, (uint32_t) irq11, 0x08, 0x8e);
  idt_set_gate (44, (uint32_t) irq12, 0x08, 0x8e);
  idt_set_gate (45, (uint32_t) irq13, 0x08, 0x8e);
  idt_set_gate (46, (uint32_t) irq14, 0x08, 0x8e);
  idt_set_gate (47, (uint32_t) irq15, 0x08, 0x8e);

  /* fill the IDT descriptor */
  idt_address = (unsigned long) IDT;
  idt_ptr[0] = (sizeof(struct IDT_entry) * 256)
      + ((idt_address & 0xffff) << 16);
  idt_ptr[1] = idt_address >> 16;

  loadIdt (idt_ptr);

}

//static char *isr_messages[32] =
//  { "#DE", "#DB", "Non-maskable Interrupt", "#BP", "#OF", "#BR", "#UD", "#NM",
//      "#DF", "Coprocessor Segment Overrun", "#TD", "#NP", "#SS", "#GP", "#PF",
//      "Reserved", "#MF", "#AC", "#MC", "#XM", "#VE", "Reserved", "Reserved",
//      "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved",
//      "Reserved", "#SX", "Reserved" };

void
isr0_handler (void)
{
  printf("#DE\n");
  iret();
}

void
isr1_handler (void)
{
  printf("#DB\n");
  iret();
}

void
isr2_handler (void)
{
  printf("Non-maskable Interrupt\n");
  iret();
}

void
isr3_handler (void)
{
  printf("#BP\n");
  iret();
}

void
isr4_handler (void)
{
  printf("#OF\n");
  iret();
}

void
isr5_handler (void)
{
  printf("#BR\n");
  iret();
}

void
isr6_handler (void)
{
  printf("#UD\n");
  iret();
}

void
isr7_handler (void)
{
  printf("#NN\n");
  iret();
}

void
isr8_handler (int error)
{
  printf("#DF(%i)/n", error);
  iret();
}

void
isr9_handler (void)
{
  printf("Coprocessor Segment Overrun");
  iret();
}

void
isr10_handler (int error)
{
  printf("#TD(%i)/n", error);
  iret();
}

void
isr11_handler (int error)
{
  printf("#NP(%i)/n", error);
  iret();
}

void
isr12_handler (int error)
{
  printf("#SS(%i)/n", error);
  iret();
}

void
isr13_handler (unsigned int error)
{
  printf("#GP(%i)/n", error);
  iret();
}

void
isr14_handler (int error)
{
  printf("#PF(%i)/n", error);
  iret();
}

void
isr15_handler (void)
{
  printf("Reserved\n");
  iret();
}

void
isr16_handler (void)
{
  printf("#MF\n");
  iret();
}

void
isr17_handler (void)
{
  printf("#AC\n");
  iret();
}

void
isr18_handler (void)
{
  printf("#MC\n");
  iret();
}

void
isr19_handler (void)
{
  printf("#XM\n");
  iret();
}

void
isr20_handler (void)
{
  printf("#VE\n");
  iret();
}

void
isr21_handler (void)
{
  printf("Reserved\n");
  iret();
}

void
isr22_handler (void)
{
  printf("Reserved\n");
  iret();
}

void
isr23_handler (void)
{
  printf("Reserved\n");
  iret();
}

void
isr24_handler (void)
{
  printf("Reserved\n");
  iret();
}

void
isr25_handler (void)
{
  printf("Reserved\n");
  iret();
}

void
isr26_handler (void)
{
  printf("Reserved\n");
  iret();
}

void
isr27_handler (void)
{
  printf("Reserved\n");
  iret();
}

void
isr28_handler (void)
{
  printf("Reserved\n");
  iret();
}

void
isr29_handler (void)
{
  printf("Reserved\n");
  iret();
}

void
isr30_handler (void)
{
  printf("#SX\n");
  iret();
}

void
isr31_handler (void)
{
  printf("Reserved\n");
  iret();
}
