################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
NEW_CON232K.lss \

FLASH_IMAGE += \
NEW_CON232K.hex \

EEPROM_IMAGE += \
NEW_CON232K.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: NEW_CON232K.elf secondary-outputs

# Tool invocations
NEW_CON232K.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,NEW_CON232K.map -mmcu=atmega88pa -o "NEW_CON232K.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

NEW_CON232K.lss: NEW_CON232K.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S NEW_CON232K.elf  >"NEW_CON232K.lss"
	@echo 'Finished building: $@'
	@echo ' '

NEW_CON232K.hex: NEW_CON232K.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex NEW_CON232K.elf  "NEW_CON232K.hex"
	@echo 'Finished building: $@'
	@echo ' '

NEW_CON232K.eep: NEW_CON232K.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex NEW_CON232K.elf  "NEW_CON232K.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: NEW_CON232K.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega88pa NEW_CON232K.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) NEW_CON232K.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
