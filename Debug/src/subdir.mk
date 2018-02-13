################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ad9833.c \
../src/hc05.c \
../src/led.c \
../src/main.c \
../src/signals.c \
../src/spi.c \
../src/syscalls.c \
../src/system_stm32f10x.c \
../src/timer.c \
../src/uart.c 

OBJS += \
./src/ad9833.o \
./src/hc05.o \
./src/led.o \
./src/main.o \
./src/signals.o \
./src/spi.o \
./src/syscalls.o \
./src/system_stm32f10x.o \
./src/timer.o \
./src/uart.o 

C_DEPS += \
./src/ad9833.d \
./src/hc05.d \
./src/led.d \
./src/main.d \
./src/signals.d \
./src/spi.d \
./src/syscalls.d \
./src/system_stm32f10x.d \
./src/timer.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F1 -DSTM32F103RCTx -DDEBUG -DSTM32F10X_HD -DUSE_STDPERIPH_DRIVER -I"D:/Workspace/AC6/GINKGO_SPI_STM32_AC6/StdPeriph_Driver/inc" -I"D:/Workspace/AC6/GINKGO_SPI_STM32_AC6/inc" -I"D:/Workspace/AC6/GINKGO_SPI_STM32_AC6/CMSIS/device" -I"D:/Workspace/AC6/GINKGO_SPI_STM32_AC6/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


