################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Tasks/subdir.mk
-include MCAL/UART/subdir.mk
-include MCAL/GIE/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/LCD/subdir.mk
-include FreeRTOS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Irrigation_System.lss \

FLASH_IMAGE += \
Irrigation_System.hex \

EEPROM_IMAGE += \
Irrigation_System.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Irrigation_System.elf secondary-outputs

# Tool invocations
Irrigation_System.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Irrigation_System.map -mmcu=atmega32 -o "Irrigation_System.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Irrigation_System.lss: Irrigation_System.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Irrigation_System.elf  >"Irrigation_System.lss"
	@echo 'Finished building: $@'
	@echo ' '

Irrigation_System.hex: Irrigation_System.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Irrigation_System.elf  "Irrigation_System.hex"
	@echo 'Finished building: $@'
	@echo ' '

Irrigation_System.eep: Irrigation_System.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Irrigation_System.elf  "Irrigation_System.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Irrigation_System.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Irrigation_System.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Irrigation_System.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
