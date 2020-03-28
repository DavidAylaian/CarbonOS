/**
 *
 * Copyright 2020 David Aylaian
 * https://github.com/DavidAylaian/Carbon/
 *
 * Based off of code by Brandon F. that can be found at
 * http://www.osdever.net/bkerndev/Docs/irqs.htm
 *
 */

#include <kernel/hal.h>
#include <stdio.h>
#include "regs.h"

// see wrappers.asm
extern void irq_wrapper_0();
extern void irq_wrapper_1();
extern void irq_wrapper_2();
extern void irq_wrapper_3();
extern void irq_wrapper_4();
extern void irq_wrapper_5();
extern void irq_wrapper_6();
extern void irq_wrapper_7();
extern void irq_wrapper_8();
extern void irq_wrapper_9();
extern void irq_wrapper_10();
extern void irq_wrapper_11();
extern void irq_wrapper_12();
extern void irq_wrapper_13();
extern void irq_wrapper_14();
extern void irq_wrapper_15();

// install irqs into their corresponding slots in the idt
void irq_install()
{
	setvect(32, (unsigned) irq_wrapper_0);
	setvect(33, (unsigned) irq_wrapper_1);
	setvect(34, (unsigned) irq_wrapper_2);
	setvect(35, (unsigned) irq_wrapper_3);
	setvect(36, (unsigned) irq_wrapper_4);
	setvect(37, (unsigned) irq_wrapper_5);
	setvect(38, (unsigned) irq_wrapper_6);
	setvect(39, (unsigned) irq_wrapper_7);
	setvect(40, (unsigned) irq_wrapper_8);
	setvect(41, (unsigned) irq_wrapper_9);
	setvect(42, (unsigned) irq_wrapper_10);
	setvect(43, (unsigned) irq_wrapper_11);
	setvect(44, (unsigned) irq_wrapper_12);
	setvect(45, (unsigned) irq_wrapper_13);
	setvect(46, (unsigned) irq_wrapper_14);
	setvect(47, (unsigned) irq_wrapper_15);
}

// function pointers to irq handlers
static void *irq_handlers[16] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

// install an irq handler
void irq_handler_install(uint8_t irq, void(*handler)())
{
	irq_handlers[irq] = handler;
}

// send end of interrupt
static void irq_send_eoi(int intn)
{
	if (intn > 39)
	{
		outb(0xA0, 0x20);
	}

	outb(0x20, 0x20);
}

// handles an irq
void irq_handler(struct hal_registers *regs)
{
	void(*handler)();
	handler = irq_handlers[regs->intn - 32];

	if (handler)
	{
		handler();
	}
	else
	{
		printf("Received irq %d\n", regs->intn - 32);
	}

	irq_send_eoi(regs->intn);
}
