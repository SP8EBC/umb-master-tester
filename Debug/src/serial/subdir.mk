################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/serial/serial.cpp 

CPP_DEPS += \
./src/serial/serial.d 

OBJS += \
./src/serial/serial.o 


# Each subdirectory must supply rules for building sources it contributes
src/serial/%.o: ../src/serial/%.cpp src/serial/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG -I/usr/include/spdlog -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-serial

clean-src-2f-serial:
	-$(RM) ./src/serial/serial.d ./src/serial/serial.o

.PHONY: clean-src-2f-serial

