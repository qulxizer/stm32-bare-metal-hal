#include "stm32g0xx_hal.h"
#include <stdint.h>

extern uint32_t _estack;

int main(void);

void Reset_Handler(void);
void SysTick_Handler(void);
void Default_Handler(void);

__attribute__((section(".isr_vector"))) const uintptr_t vectors[] = {
    (uintptr_t)&_estack,
    (uintptr_t)Reset_Handler,

    (uintptr_t)Default_Handler, // NMI
    (uintptr_t)Default_Handler, // HardFault

    0,
    0,
    0,
    0,
    0,
    0,
    0,                          // reserved
    (uintptr_t)Default_Handler, // SVCall
    0,
    0,                          // DebugMonitor, reserved
    (uintptr_t)Default_Handler, // PendSV
    (uintptr_t)SysTick_Handler,

    (uintptr_t)Default_Handler, // WWDG
};

void Reset_Handler(void) {
  main();

  while (1)
    ;
}

void SysTick_Handler(void) { HAL_IncTick(); }

void Default_Handler(void) {
  while (1)
    ;
}
