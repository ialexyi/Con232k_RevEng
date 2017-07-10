################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../IoSupport.c \
../Main.c \
../Ps2.c \
../Ps2IntSupport.c \
../ScanCode.c \
../USART2.c 

OBJS += \
./IoSupport.o \
./Main.o \
./Ps2.o \
./Ps2IntSupport.o \
./ScanCode.o \
./USART2.o 

C_DEPS += \
./IoSupport.d \
./Main.d \
./Ps2.d \
./Ps2IntSupport.d \
./ScanCode.d \
./USART2.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega88pa -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


