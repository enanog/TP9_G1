################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libs/leds_emulator/leds_emulator.c 

C_DEPS += \
./libs/leds_emulator/leds_emulator.d 

OBJS += \
./libs/leds_emulator/leds_emulator.o 


# Each subdirectory must supply rules for building sources it contributes
libs/leds_emulator/%.o: ../libs/leds_emulator/%.c libs/leds_emulator/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-libs-2f-leds_emulator

clean-libs-2f-leds_emulator:
	-$(RM) ./libs/leds_emulator/leds_emulator.d ./libs/leds_emulator/leds_emulator.o

.PHONY: clean-libs-2f-leds_emulator

