#ifndef _INT_H_
#define _INT_H_

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */
};

void irq_handler(struct regs *r);
void irq_install();
void irq_remap(void);
void irq_uninstall_handler(int irq);
void irq_install_handler(int irq, void (*handler)(struct regs *r));
void isrs_install();
void fault_handler(struct regs *r);
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
void gdt_install();
void idt_install();
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void timer_handler(struct regs *r);
void timer_install();
void timer_wait(int ticks);

#endif
