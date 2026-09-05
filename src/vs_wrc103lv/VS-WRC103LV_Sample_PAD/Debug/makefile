################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: VS-WRC103LV_Sample_PAD.axf

# Tool invocations
VS-WRC103LV_Sample_PAD.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:/Users/2019228/Documents/LPCXpresso_8.2.2_650/workspace/VS-WRC103LV_Sample_PAD/lib" -Xlinker --gc-sections -Xlinker -Map=VS-WRC103LV_Sample_PAD.map -mcpu=cortex-m3 -mthumb -T "../Debug/vs-wrc103lv_Debug.ld" -o "VS-WRC103LV_Sample_PAD.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) VS-WRC103LV_Sample_PAD.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size VS-WRC103LV_Sample_PAD.axf; arm-none-eabi-size VS-WRC103LV_Sample_PAD.axf; arm-none-eabi-objcopy -O binary VS-WRC103LV_Sample_PAD.axf VS-WRC103LV_Sample_PAD.bin; checksum VS-WRC103LV_Sample_PAD.bin;
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
