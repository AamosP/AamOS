/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#include <aamOS/kernel.h>
#include <multiboot2.h>
#include <sys/types.h>
#include <stdio.h>
#include <asm/system.h>
#include <asm/io.h>
#include <memory.h>

extern void
idt_init (void);
extern void
loadGdt (void);
struct multiboot_tag*
get_tag (uint32_t tag_type, unsigned long addr);
void
kernel_main (unsigned long magic, unsigned long addr);

void
kernel_main (unsigned long magic, unsigned long addr)
{
  init_serial (COM1);
  struct multiboot_tag *tag;
  tag = get_tag (MULTIBOOT_TAG_TYPE_FRAMEBUFFER, addr);
  VGA_init ((struct multiboot_tag_framebuffer*) tag);
  console_init ((struct multiboot_tag_framebuffer*) tag, WHITE, BLACK);
  loadGdt ();
  idt_init ();
  sti();
  kb_init();
  printf ("Helllooooo!!");
  //write_serial_str("Hi");
}

struct multiboot_tag*
get_tag (uint32_t tag_type, unsigned long addr)
{
  struct multiboot_tag *tag;
  for (tag = (struct multiboot_tag*) (addr + 8);
      tag->type != MULTIBOOT_TAG_TYPE_END;
      tag = (struct multiboot_tag*) ((multiboot_uint8_t*) tag
	  + ((tag->size + 7) & ~7)))
    {
      if (tag->type == tag_type)
	{
	  break;
	}
    }
  return tag;
}
