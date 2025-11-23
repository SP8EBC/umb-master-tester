################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/aprs/Call.cpp \
../src/aprs/Call_test.cpp \
../src/aprs/Mappings.cpp \
../src/aprs/PacketFoundation.cpp \
../src/aprs/PacketFoundation_test.cpp \
../src/aprs/PacketWx.cpp 

CPP_DEPS += \
./src/aprs/Call.d \
./src/aprs/Call_test.d \
./src/aprs/Mappings.d \
./src/aprs/PacketFoundation.d \
./src/aprs/PacketFoundation_test.d \
./src/aprs/PacketWx.d 

OBJS += \
./src/aprs/Call.o \
./src/aprs/Call_test.o \
./src/aprs/Mappings.o \
./src/aprs/PacketFoundation.o \
./src/aprs/PacketFoundation_test.o \
./src/aprs/PacketWx.o 


# Each subdirectory must supply rules for building sources it contributes
src/aprs/%.o: ../src/aprs/%.cpp src/aprs/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG -I/usr/include/spdlog -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-aprs

clean-src-2f-aprs:
	-$(RM) ./src/aprs/Call.d ./src/aprs/Call.o ./src/aprs/Call_test.d ./src/aprs/Call_test.o ./src/aprs/Mappings.d ./src/aprs/Mappings.o ./src/aprs/PacketFoundation.d ./src/aprs/PacketFoundation.o ./src/aprs/PacketFoundation_test.d ./src/aprs/PacketFoundation_test.o ./src/aprs/PacketWx.d ./src/aprs/PacketWx.o

.PHONY: clean-src-2f-aprs

