################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/types/ChannelValueFoundation.cpp \
../src/types/DeviceChannel.cpp \
../src/types/DeviceChannel_test.cpp \
../src/types/Float.cpp \
../src/types/Float_test.cpp \
../src/types/Integer.cpp \
../src/types/OutputValues.cpp \
../src/types/UnsignedInteger.cpp 

CPP_DEPS += \
./src/types/ChannelValueFoundation.d \
./src/types/DeviceChannel.d \
./src/types/DeviceChannel_test.d \
./src/types/Float.d \
./src/types/Float_test.d \
./src/types/Integer.d \
./src/types/OutputValues.d \
./src/types/UnsignedInteger.d 

OBJS += \
./src/types/ChannelValueFoundation.o \
./src/types/DeviceChannel.o \
./src/types/DeviceChannel_test.o \
./src/types/Float.o \
./src/types/Float_test.o \
./src/types/Integer.o \
./src/types/OutputValues.o \
./src/types/UnsignedInteger.o 


# Each subdirectory must supply rules for building sources it contributes
src/types/%.o: ../src/types/%.cpp src/types/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG -I/usr/include/spdlog -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-types

clean-src-2f-types:
	-$(RM) ./src/types/ChannelValueFoundation.d ./src/types/ChannelValueFoundation.o ./src/types/DeviceChannel.d ./src/types/DeviceChannel.o ./src/types/DeviceChannel_test.d ./src/types/DeviceChannel_test.o ./src/types/Float.d ./src/types/Float.o ./src/types/Float_test.d ./src/types/Float_test.o ./src/types/Integer.d ./src/types/Integer.o ./src/types/OutputValues.d ./src/types/OutputValues.o ./src/types/UnsignedInteger.d ./src/types/UnsignedInteger.o

.PHONY: clean-src-2f-types

