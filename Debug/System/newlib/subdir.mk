################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../System/newlib/_exit.c \
../System/newlib/_sbrk.c \
../System/newlib/_startup.c \
../System/newlib/_syscalls.c \
../System/newlib/assert.c 

CPP_SRCS += \
../System/newlib/_cxx.cpp 

OBJS += \
./System/newlib/_cxx.o \
./System/newlib/_exit.o \
./System/newlib/_sbrk.o \
./System/newlib/_startup.o \
./System/newlib/_syscalls.o \
./System/newlib/assert.o 

C_DEPS += \
./System/newlib/_exit.d \
./System/newlib/_sbrk.d \
./System/newlib/_startup.d \
./System/newlib/_syscalls.d \
./System/newlib/assert.d 

CPP_DEPS += \
./System/newlib/_cxx.d 


# Each subdirectory must supply rules for building sources it contributes
System/newlib/%.o: ../System/newlib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_ITM -DSTM32F427xx -DUSE_HAL_DRIVER -DHSE_VALUE=12000000 -I"D:/workspace/junior_eclipse\Drivers\STM32F4xx_HAL_Driver\Inc" -I"D:/workspace/junior_eclipse\MDK-ARM\bsp" -I"D:/workspace/junior_eclipse\MDK-ARM\app" -I"D:/workspace/junior_eclipse\MDK-ARM\RTE\Device\STM32F427II" -I"D:/workspace/junior_eclipse\Middlewares\Third_Party\FreeRTOS\Source\CMSIS_RTOS" -I"D:/workspace/junior_eclipse\Drivers\STM32F4xx_HAL_Driver\Inc\Legacy" -I"D:/workspace/junior_eclipse\Drivers\CMSIS\Include" -I"D:/workspace/junior_eclipse\Inc" -I"D:/workspace/junior_eclipse\MDK-ARM" -I"D:/workspace/junior_eclipse\Middlewares\Third_Party\FreeRTOS\Source\include" -I"D:/workspace/junior_eclipse\Middlewares\Third_Party\FreeRTOS\Source\portable\GCC\ARM_CM4F" -I"D:/workspace/junior_eclipse\System" -I"D:/workspace/junior_eclipse\MDK-ARM\RTE\_chassis" -I"D:/workspace/junior_eclipse\System\newlib\diag" -I"D:/workspace/junior_eclipse\MDK-ARM\RTE" -I"D:/workspace/junior_eclipse\Drivers\CMSIS\Device\ST\STM32F4xx\Include" -I"D:/workspace/junior_eclipse\Debug" -I"D:/workspace/junior_eclipse\MDK-ARM\chassis" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

System/newlib/%.o: ../System/newlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_ITM -DSTM32F427xx -DUSE_HAL_DRIVER -DHSE_VALUE=12000000 -I"D:/workspace/junior_eclipse\Drivers\STM32F4xx_HAL_Driver\Inc" -I"D:/workspace/junior_eclipse\MDK-ARM\bsp" -I"D:/workspace/junior_eclipse\MDK-ARM\app" -I"D:/workspace/junior_eclipse\MDK-ARM\RTE\Device\STM32F427II" -I"D:/workspace/junior_eclipse\Middlewares\Third_Party\FreeRTOS\Source\CMSIS_RTOS" -I"D:/workspace/junior_eclipse\Drivers\STM32F4xx_HAL_Driver\Inc\Legacy" -I"D:/workspace/junior_eclipse\Drivers\CMSIS\Include" -I"D:/workspace/junior_eclipse\Inc" -I"D:/workspace/junior_eclipse\MDK-ARM" -I"D:/workspace/junior_eclipse\Middlewares\Third_Party\FreeRTOS\Source\include" -I"D:/workspace/junior_eclipse\Middlewares\Third_Party\FreeRTOS\Source\portable\GCC\ARM_CM4F" -I"D:/workspace/junior_eclipse\System" -I"D:/workspace/junior_eclipse\MDK-ARM\RTE\_chassis" -I"D:/workspace/junior_eclipse\System\newlib\diag" -I"D:/workspace/junior_eclipse\MDK-ARM\RTE" -I"D:/workspace/junior_eclipse\Drivers\CMSIS\Device\ST\STM32F4xx\Include" -I"D:/workspace/junior_eclipse\Debug" -I"D:/workspace/junior_eclipse\MDK-ARM\chassis" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


