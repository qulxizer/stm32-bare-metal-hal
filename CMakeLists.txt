cmake_minimum_required(VERSION 3.20)

project(blink C ASM)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m0plus)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

set(CMAKE_C_FLAGS
    "-mcpu=cortex-m0plus -mthumb -g -Og"
)

set(LINKER_SCRIPT
    ${CMAKE_SOURCE_DIR}/stm32g030f6.ld
)

add_executable(firmware
    startup.c
    main.c

    cmsis-device-g0/Source/Templates/system_stm32g0xx.c
    stm32g0xx-hal-driver/Src/stm32g0xx_hal.c
    stm32g0xx-hal-driver/Src/stm32g0xx_hal_cortex.c
    stm32g0xx-hal-driver/Src/stm32g0xx_hal_gpio.c
)

target_compile_definitions(firmware PRIVATE
    STM32G030xx
)

target_include_directories(firmware PRIVATE
    includes
    CMSIS_6/CMSIS/Core/Include
    cmsis-device-g0/Include
    stm32g0xx-hal-driver/Inc
)

target_link_options(firmware PRIVATE
    "-T${LINKER_SCRIPT}"
    "--specs=nosys.specs"
    "-Wl,-Map=${CMAKE_BINARY_DIR}/firmware.map"
)

set_target_properties(firmware PROPERTIES
    OUTPUT_NAME firmware
    SUFFIX ".elf"
)

add_custom_command(TARGET firmware POST_BUILD
    COMMAND arm-none-eabi-objcopy
            -O binary
            $<TARGET_FILE:firmware>
            ${CMAKE_BINARY_DIR}/firmware.bin
)
