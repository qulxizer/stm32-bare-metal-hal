#include "stm32g0xx_hal.h"

int main(void) {
  HAL_Init();

  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitTypeDef gpio = {
      .Pin = GPIO_PIN_8,
      .Mode = GPIO_MODE_OUTPUT_PP,
      .Pull = GPIO_NOPULL,
      .Speed = GPIO_SPEED_FREQ_LOW,
  };

  HAL_GPIO_Init(GPIOA, &gpio);

  while (1) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
    HAL_Delay(100);
  }
}
