/*******************************************************************************
 * Copyright (c) 2020 IBM Corporation and others.
 *
 * This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License 2.0
 * which accompanies this distribution, and is available at
 * https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *     IBM Corporation - initial API and implementation
 *******************************************************************************/
#include <asm/io.h>
#include <asm/system.h>
#include <idt.h>
#include <aamOS/kernel.h>

static struct IDT_entry IDT[256];

/* Set the value of one IDT entry. */
static void
idt_set_gate (uint8_t num, uint32_t offset, uint16_t sel, uint8_t flags)
{
  IDT[num].offset_lo = offset & 0xFFFF;
  IDT[num].offset_hi = (offset >> 16) & 0xFFFF;

  IDT[num].selector = sel;
  IDT[num].zero = 0;
  /* We must uncomment the OR below when we get to using user-mode.
   // It sets the interrupt gate's privilege level to 3. */
  IDT[num].type_attr = flags /* | 0x60 */;
}

void
idt_init (void)
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

static char *isr_messages[32] =
  { "#DE", "#DB", "Non-maskable Interrupt", "#BP", "#OF", "#BR", "#UD", "#NM",
      "#DF", "Coprocessor Segment Overrun", "#TD", "#NP", "#SS", "#GP", "#PF",
      "Reserved", "#MF", "#AC", "#MC", "#XM", "#VE", "Reserved", "Reserved",
      "Reserved", "Reserved", "Reserved", "Reserved", "Reserved", "Reserved",
      "Reserved", "#SX", "Reserved" };

void
isr0_handler (void)
{
  write_serial_str ("#DE\n");
  iret();
}

void
isr1_handler (void)
{
  write_serial_str ("#DB\n");
  iret();
}

void
isr2_handler (void)
{
  write_serial_str ("Non-maskable Interrupt\n");
  iret();
}

void
isr3_handler (void)
{
  write_serial_str ("#BP\n");
  iret();
}

void
isr4_handler (void)
{
  write_serial_str ("#OF\n");
  iret();
}

void
isr5_handler (void)
{
  write_serial_str ("#BR\n");
  iret();
}

void
isr6_handler (void)
{
  write_serial_str ("#UD\n");
  iret();
}

void
isr7_handler (void)
{
  write_serial_str ("#NN\n");
  iret();
}

void
isr8_handler (int error)
{
  write_serial_str ("#DF(");
  char *s;
  itoa (s, 'd', error);
  write_serial_str (s);
  write_serial_str (")\n");
  iret();
}

void
isr9_handler (void)
{
  write_serial_str ("Coprocessor Segment Overrun");
  iret();
}

void
isr10_handler (int error)
{
  write_serial_str ("#TD(");
  char *s;
  itoa (s, 'd', error);
  write_serial_str (s);
  write_serial_str (")\n");
  iret();
}

void
isr11_handler (int error)
{
  write_serial_str ("#NP(");
  char *s;
  itoa (s, 'd', error);
  write_serial_str (s);
  write_serial_str (")\n");
  iret();
}

void
isr12_handler (int error)
{
  write_serial_str ("#SS(");
  char *s;
  itoa (s, 'd', error);
  write_serial_str (s);
  write_serial_str (")\n");
  iret();
}

void
isr13_handler (unsigned int error)
{
  write_serial_str ("#GP(");
  char *s;
  itoa (s, 'd', error);
  write_serial_str (s);
  write_serial_str (")\n");
  iret();
}

void
isr14_handler (int error)
{
  write_serial_str ("#PF(");
  char *s;
  itoa (s, 'd', error);
  write_serial_str (s);
  write_serial_str (")\n");
  iret();
}

void
isr15_handler (void)
{
  write_serial_str ("Reserved\n");
  iret();
}

void
isr16_handler (void)
{
  write_serial_str ("#MF\n");
  iret();
}

void
isr17_handler (void)
{
  write_serial_str ("#AC\n");
  iret();
}

void
isr18_handler (void)
{
  write_serial_str ("#MC\n");
  iret();
}

void
isr19_handler (void)
{
  write_serial_str ("#XM\n");
  iret();
}

void
isr20_handler (void)
{
  write_serial_str ("#VE\n");
  iret();
}

void
isr21_handler (void)
{
  write_serial_str ("Reserved\n");
  iret();
}

void
isr22_handler (void)
{
  write_serial_str ("Reserved\n");
  iret();
}

void
isr23_handler (void)
{
  write_serial_str ("Reserved\n");
  iret();
}

void
isr24_handler (void)
{
  write_serial_str ("Reserved\n");
  iret();
}

void
isr25_handler (void)
{
  write_serial_str ("Reserved\n");
  iret();
}

void
isr26_handler (void)
{
  write_serial_str ("Reserved\n");
  iret();
}

void
isr27_handler (void)
{
  write_serial_str ("Reserved\n");
  iret();
}

void
isr28_handler (void)
{
  write_serial_str ("Reserved\n");
  iret();
}

void
isr29_handler (void)
{
  write_serial_str ("Reserved\n");
  iret();
}

void
isr30_handler (void)
{
  write_serial_str ("#SX\n");
  iret();
}

void
isr31_handler (void)
{
  write_serial_str ("Reserved\n");
  iret();
}

void
irq0_handler (void)
{
  outb(0x20, 0x20);
}

void
irq1_handler (void)
{
  outb(0x20, 0x20);
  kb_handler (inb(0x60));
}

void
irq2_handler (void)
{
  outb(0x20, 0x20);
}

void
irq3_handler (void)
{
  outb(0x20, 0x20);
}

void
irq4_handler (void)
{
  outb(0x20, 0x20);
}

void
irq5_handler (void)
{
  outb(0x20, 0x20);
}

void
irq6_handler (void)
{
  outb(0x20, 0x20);
}

void
irq7_handler (void)
{
  outb(0x20, 0x20);
}

void
irq8_handler (void)
{
  outb(0xa0, 0x20);
  outb(0x20, 0x20);
}

void
irq9_handler (void)
{
  outb(0xa0, 0x20);
  outb(0x20, 0x20);
}

void
irq10_handler (void)
{
  outb(0xa0, 0x20);
  outb(0x20, 0x20);
}

void
irq11_handler (void)
{
  outb(0xa0, 0x20);
  outb(0x20, 0x20);
}

void
irq12_handler (void)
{
  outb(0xa0, 0x20);
  outb(0x20, 0x20);
}

void
irq13_handler (void)
{
  outb(0xa0, 0x20);
  outb(0x20, 0x20);
}

void
irq14_handler (void)
{
  outb(0xa0, 0x20);
  outb(0x20, 0x20);
}

void
irq15_handler (void)
{
  outb(0xa0, 0x20);
  outb(0x20, 0x20);
}
