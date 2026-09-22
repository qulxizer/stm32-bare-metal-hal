#include "stm32g0xx_hal.h"
#include <stdint.h>
extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern int main(void);

void Reset_Handler(void);
void Default_Handler(void);
void SysTick_Handler(void);

__attribute__((section(".isr_vector"))) const uintptr_t vector_table[] = {
    (uintptr_t)&_estack,
    (uintptr_t)Reset_Handler,
    (uintptr_t)Default_Handler, // NMI
    (uintptr_t)Default_Handler, // HardFault

    0, // MemManage
    0, // BusFault
    0, // UsageFault
    0, // Reserved
    0, // Reserved
    0, // Reserved
    0, // Reserved

    (uintptr_t)Default_Handler, // SVCall
    0,                          // DebugMonitor
    0,                          // Reserved
    (uintptr_t)Default_Handler, // PendSV
    (uintptr_t)SysTick_Handler,

    // External interrupts
    (uintptr_t)Default_Handler, // WWDG
    (uintptr_t)Default_Handler,
    (uintptr_t)Default_Handler,
    (uintptr_t)Default_Handler,
    (uintptr_t)Default_Handler,
    (uintptr_t)Default_Handler,
    (uintptr_t)Default_Handler,
    (uintptr_t)Default_Handler,
    (uintptr_t)Default_Handler,
    (uintptr_t)Default_Handler,
    (uintptr_t)Default_Handler,
    (uintptr_t)Default_Handler,
    (uintptr_t)Default_Handler,
    (uintptr_t)Default_Handler,
    (uintptr_t)Default_Handler,
    (uintptr_t)Default_Handler,
};

void Reset_Handler(void) {
  uint32_t *src = &_sidata;
  uint32_t *dst = &_sdata;

  while (dst < &_edata)
    *dst++ = *src++;

  dst = &_sbss;

  while (dst < &_ebss)
    *dst++ = 0;

  main();

  while (1)
    ;
}

void SysTick_Handler(void) { HAL_IncTick(); }

void Default_Handler(void) {
  while (1)
    ;
}
