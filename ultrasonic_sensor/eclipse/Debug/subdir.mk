################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../eclipse.c \
../gpio.c \
../icu.c \
../lcd.c \
../ultrasonic_sensor.c 

OBJS += \
./eclipse.o \
./gpio.o \
./icu.o \
./lcd.o \
./ultrasonic_sensor.o 

C_DEPS += \
./eclipse.d \
./gpio.d \
./icu.d \
./lcd.d \
./ultrasonic_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


