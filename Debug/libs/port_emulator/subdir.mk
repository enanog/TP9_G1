################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libs/port_emulator/port_emulator.c 

C_DEPS += \
./libs/port_emulator/port_emulator.d 

OBJS += \
./libs/port_emulator/port_emulator.o 


# Each subdirectory must supply rules for building sources it contributes
libs/port_emulator/%.o: ../libs/port_emulator/%.c libs/port_emulator/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-libs-2f-port_emulator

clean-libs-2f-port_emulator:
	-$(RM) ./libs/port_emulator/port_emulator.d ./libs/port_emulator/port_emulator.o

.PHONY: clean-libs-2f-port_emulator

