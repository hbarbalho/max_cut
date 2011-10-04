################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Edge.cpp \
../src/GA.cpp \
../src/Instance.cpp \
../src/Main.cpp \
../src/Solution.cpp 

C_SRCS += \
../src/bibrand.c 

OBJS += \
./src/Edge.o \
./src/GA.o \
./src/Instance.o \
./src/Main.o \
./src/Solution.o \
./src/bibrand.o 

C_DEPS += \
./src/bibrand.d 

CPP_DEPS += \
./src/Edge.d \
./src/GA.d \
./src/Instance.d \
./src/Main.d \
./src/Solution.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


