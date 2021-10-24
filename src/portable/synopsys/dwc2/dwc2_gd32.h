/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2021, Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */


#ifndef DWC2_GD32_H_
#define DWC2_GD32_H_

// for remote wakeup delay
#define __NOP()   __asm volatile ("nop")

// These numbers are the same for the whole GD32VF103 family.
#define DWC2_REG_BASE   0x50000000UL
#define EP_MAX          4
#define EP_FIFO_SIZE    1280
#define RHPORT_IRQn     86

// The GD32VF103 is a RISC-V MCU, which implements the ECLIC Core-Local
// Interrupt Controller by Nuclei. It is nearly API compatible to the
// NVIC used by ARM MCUs.
#define ECLIC_INTERRUPT_ENABLE_BASE 0xD2001001UL

TU_ATTR_ALWAYS_INLINE
static inline void __eclic_enable_interrupt (uint32_t irq) {
  *(volatile uint8_t*)(ECLIC_INTERRUPT_ENABLE_BASE + (irq * 4)) = 1;
}

TU_ATTR_ALWAYS_INLINE
static inline void __eclic_disable_interrupt (uint32_t irq){
  *(volatile uint8_t*)(ECLIC_INTERRUPT_ENABLE_BASE + (irq * 4)) = 0;
}

TU_ATTR_ALWAYS_INLINE
static inline void dcd_dwc2_int_enable(uint8_t rhport)
{
  (void) rhport;
  __eclic_enable_interrupt(RHPORT_IRQn);
}

TU_ATTR_ALWAYS_INLINE
static inline void dcd_dwc2_int_disable (uint8_t rhport)
{
  (void) rhport;
  __eclic_disable_interrupt(RHPORT_IRQn);
}

#endif /* DWC2_GD32_H_ */
