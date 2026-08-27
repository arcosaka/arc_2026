################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: VS-WRC103LV_Sample_LED.axf

# Tool invocations
VS-WRC103LV_Sample_LED.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:/Users/yokoyama_S9/Documents/lpcxpresso_3.5/workspace/VS-WRC103LV_Sample_LED/lib" -Xlinker --gc-sections -Xlinker -Map=VS-WRC103LV_Sample_LED.map -mcpu=cortex-m3 -mthumb -T "../Release/vs-wrc103lv_Release.ld" -o"VS-WRC103LV_Sample_LED.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) VS-WRC103LV_Sample_LED.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size VS-WRC103LV_Sample_LED.axf; arm-none-eabi-size VS-WRC103LV_Sample_LED.axf; arm-none-eabi-objcopy -O binary VS-WRC103LV_Sample_LED.axf VS-WRC103LV_Sample_LED.bin; checksum VS-WRC103LV_Sample_LED.bin;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
