################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/app_event.c \
../src/app_serialio.c \
../src/cr_startup_lpc13.c \
../src/gpio.c \
../src/ixbus.c \
../src/main.c \
../src/vs-wrc103.c 

OBJS += \
./src/app_event.o \
./src/app_serialio.o \
./src/cr_startup_lpc13.o \
./src/gpio.o \
./src/ixbus.o \
./src/main.o \
./src/vs-wrc103.o 

C_DEPS += \
./src/app_event.d \
./src/app_serialio.d \
./src/cr_startup_lpc13.d \
./src/gpio.d \
./src/ixbus.d \
./src/main.d \
./src/vs-wrc103.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv1p30_LPC13xx -DDEBUG -D__CODE_RED -D__REDLIB__ -I"E:/Akinao/git/arc_2026/src/vs_wrc103lv/VS-WRC103LV_Sample_UART/inc" -I"E:/Akinao/git/arc_2026/src/vs_wrc103lv/VS-WRC103LV_Sample_UART/lib" -O0 -Os -mword-relocations -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/main.o: ../src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_CMSIS=CMSISv1p30_LPC13xx -DDEBUG -D__CODE_RED -D__REDLIB__ -I"E:/Akinao/git/arc_2026/src/vs_wrc103lv/VS-WRC103LV_Sample_UART/inc" -I"E:/Akinao/git/arc_2026/src/vs_wrc103lv/VS-WRC103LV_Sample_UART/lib" -O0 -Os -mword-relocations -g1 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/main.d" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


