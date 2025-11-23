################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/config/ProgramConfig.cpp \
../src/config/UmbDevice.cpp \
../src/config/UmbDevice_test.cpp 

CPP_DEPS += \
./src/config/ProgramConfig.d \
./src/config/UmbDevice.d \
./src/config/UmbDevice_test.d 

OBJS += \
./src/config/ProgramConfig.o \
./src/config/UmbDevice.o \
./src/config/UmbDevice_test.o 


# Each subdirectory must supply rules for building sources it contributes
src/config/%.o: ../src/config/%.cpp src/config/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG -I/usr/include/spdlog -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-config

clean-src-2f-config:
	-$(RM) ./src/config/ProgramConfig.d ./src/config/ProgramConfig.o ./src/config/UmbDevice.d ./src/config/UmbDevice.o ./src/config/UmbDevice_test.d ./src/config/UmbDevice_test.o

.PHONY: clean-src-2f-config

