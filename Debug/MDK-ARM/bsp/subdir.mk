################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MDK-ARM/bsp/ITM_printf.c \
../MDK-ARM/bsp/bsp_can.c \
../MDK-ARM/bsp/bsp_flash.c \
../MDK-ARM/bsp/bsp_uart.c \
../MDK-ARM/bsp/calibrate.c \
../MDK-ARM/bsp/fifo.c \
../MDK-ARM/bsp/judge_sys.c \
../MDK-ARM/bsp/keyboard.c \
../MDK-ARM/bsp/led.c \
../MDK-ARM/bsp/mpu.c \
../MDK-ARM/bsp/myiic.c \
../MDK-ARM/bsp/pid.c 

OBJS += \
./MDK-ARM/bsp/ITM_printf.o \
./MDK-ARM/bsp/bsp_can.o \
./MDK-ARM/bsp/bsp_flash.o \
./MDK-ARM/bsp/bsp_uart.o \
./MDK-ARM/bsp/calibrate.o \
./MDK-ARM/bsp/fifo.o \
./MDK-ARM/bsp/judge_sys.o \
./MDK-ARM/bsp/keyboard.o \
./MDK-ARM/bsp/led.o \
./MDK-ARM/bsp/mpu.o \
./MDK-ARM/bsp/myiic.o \
./MDK-ARM/bsp/pid.o 

C_DEPS += \
./MDK-ARM/bsp/ITM_printf.d \
./MDK-ARM/bsp/bsp_can.d \
./MDK-ARM/bsp/bsp_flash.d \
./MDK-ARM/bsp/bsp_uart.d \
./MDK-ARM/bsp/calibrate.d \
./MDK-ARM/bsp/fifo.d \
./MDK-ARM/bsp/judge_sys.d \
./MDK-ARM/bsp/keyboard.d \
./MDK-ARM/bsp/led.d \
./MDK-ARM/bsp/mpu.d \
./MDK-ARM/bsp/myiic.d \
./MDK-ARM/bsp/pid.d 


# Each subdirectory must supply rules for building sources it contributes
MDK-ARM/bsp/%.o: ../MDK-ARM/bsp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_ITM -DSTM32F427xx -DUSE_HAL_DRIVER -DHSE_VALUE=12000000 -I"D:/workspace/junior_eclipse\Drivers\STM32F4xx_HAL_Driver\Inc" -I"D:/workspace/junior_eclipse\MDK-ARM\bsp" -I"D:/workspace/junior_eclipse\MDK-ARM\app" -I"D:/workspace/junior_eclipse\MDK-ARM\RTE\Device\STM32F427II" -I"D:/workspace/junior_eclipse\Middlewares\Third_Party\FreeRTOS\Source\CMSIS_RTOS" -I"D:/workspace/junior_eclipse\Drivers\STM32F4xx_HAL_Driver\Inc\Legacy" -I"D:/workspace/junior_eclipse\Drivers\CMSIS\Include" -I"D:/workspace/junior_eclipse\Inc" -I"D:/workspace/junior_eclipse\MDK-ARM" -I"D:/workspace/junior_eclipse\Middlewares\Third_Party\FreeRTOS\Source\include" -I"D:/workspace/junior_eclipse\Middlewares\Third_Party\FreeRTOS\Source\portable\GCC\ARM_CM4F" -I"D:/workspace/junior_eclipse\System" -I"D:/workspace/junior_eclipse\MDK-ARM\RTE\_chassis" -I"D:/workspace/junior_eclipse\System\newlib\diag" -I"D:/workspace/junior_eclipse\MDK-ARM\RTE" -I"D:/workspace/junior_eclipse\Drivers\CMSIS\Device\ST\STM32F4xx\Include" -I"D:/workspace/junior_eclipse\Debug" -I"D:/workspace/junior_eclipse\MDK-ARM\chassis" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


