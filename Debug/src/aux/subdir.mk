################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/aux/UnitsConversionMatrix.cpp 

CPP_DEPS += \
./src/aux/UnitsConversionMatrix.d 

OBJS += \
./src/aux/UnitsConversionMatrix.o 


# Each subdirectory must supply rules for building sources it contributes
src/aux/%.o: ../src/aux/%.cpp src/aux/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG -I/usr/include/spdlog -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-aux

clean-src-2f-aux:
	-$(RM) ./src/aux/UnitsConversionMatrix.d ./src/aux/UnitsConversionMatrix.o

.PHONY: clean-src-2f-aux

