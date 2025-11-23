################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/exceptions/NullPointerE.cpp \
../src/exceptions/NullPointerE_test.cpp \
../src/exceptions/StartOfHeaderTimeoutEx.cpp \
../src/exceptions/StartOfHeaderTimeoutEx_test.cpp \
../src/exceptions/TimeoutE.cpp \
../src/exceptions/TimeoutE_test.cpp \
../src/exceptions/UsageParseError.cpp 

CPP_DEPS += \
./src/exceptions/NullPointerE.d \
./src/exceptions/NullPointerE_test.d \
./src/exceptions/StartOfHeaderTimeoutEx.d \
./src/exceptions/StartOfHeaderTimeoutEx_test.d \
./src/exceptions/TimeoutE.d \
./src/exceptions/TimeoutE_test.d \
./src/exceptions/UsageParseError.d 

OBJS += \
./src/exceptions/NullPointerE.o \
./src/exceptions/NullPointerE_test.o \
./src/exceptions/StartOfHeaderTimeoutEx.o \
./src/exceptions/StartOfHeaderTimeoutEx_test.o \
./src/exceptions/TimeoutE.o \
./src/exceptions/TimeoutE_test.o \
./src/exceptions/UsageParseError.o 


# Each subdirectory must supply rules for building sources it contributes
src/exceptions/%.o: ../src/exceptions/%.cpp src/exceptions/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG -I/usr/include/spdlog -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-exceptions

clean-src-2f-exceptions:
	-$(RM) ./src/exceptions/NullPointerE.d ./src/exceptions/NullPointerE.o ./src/exceptions/NullPointerE_test.d ./src/exceptions/NullPointerE_test.o ./src/exceptions/StartOfHeaderTimeoutEx.d ./src/exceptions/StartOfHeaderTimeoutEx.o ./src/exceptions/StartOfHeaderTimeoutEx_test.d ./src/exceptions/StartOfHeaderTimeoutEx_test.o ./src/exceptions/TimeoutE.d ./src/exceptions/TimeoutE.o ./src/exceptions/TimeoutE_test.d ./src/exceptions/TimeoutE_test.o ./src/exceptions/UsageParseError.d ./src/exceptions/UsageParseError.o

.PHONY: clean-src-2f-exceptions

