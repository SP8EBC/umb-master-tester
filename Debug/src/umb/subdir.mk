################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/umb/Routine23AnswerCbk.cpp \
../src/umb/Routine23Query.cpp \
../src/umb/Routine23Query_test.cpp \
../src/umb/Routine26AnswerCbk.cpp \
../src/umb/Routine26Query.cpp \
../src/umb/Routine26Query_test.cpp \
../src/umb/UmbHandling.cpp \
../src/umb/UmbThread.cpp 

CPP_DEPS += \
./src/umb/Routine23AnswerCbk.d \
./src/umb/Routine23Query.d \
./src/umb/Routine23Query_test.d \
./src/umb/Routine26AnswerCbk.d \
./src/umb/Routine26Query.d \
./src/umb/Routine26Query_test.d \
./src/umb/UmbHandling.d \
./src/umb/UmbThread.d 

OBJS += \
./src/umb/Routine23AnswerCbk.o \
./src/umb/Routine23Query.o \
./src/umb/Routine23Query_test.o \
./src/umb/Routine26AnswerCbk.o \
./src/umb/Routine26Query.o \
./src/umb/Routine26Query_test.o \
./src/umb/UmbHandling.o \
./src/umb/UmbThread.o 


# Each subdirectory must supply rules for building sources it contributes
src/umb/%.o: ../src/umb/%.cpp src/umb/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG -I/usr/include/spdlog -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-umb

clean-src-2f-umb:
	-$(RM) ./src/umb/Routine23AnswerCbk.d ./src/umb/Routine23AnswerCbk.o ./src/umb/Routine23Query.d ./src/umb/Routine23Query.o ./src/umb/Routine23Query_test.d ./src/umb/Routine23Query_test.o ./src/umb/Routine26AnswerCbk.d ./src/umb/Routine26AnswerCbk.o ./src/umb/Routine26Query.d ./src/umb/Routine26Query.o ./src/umb/Routine26Query_test.d ./src/umb/Routine26Query_test.o ./src/umb/UmbHandling.d ./src/umb/UmbHandling.o ./src/umb/UmbThread.d ./src/umb/UmbThread.o

.PHONY: clean-src-2f-umb

