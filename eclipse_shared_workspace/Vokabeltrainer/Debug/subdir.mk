################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../abfrage.c \
../abfrage1.c \
../abfrage2.c \
../abfrage3.c \
../main.c \
../usernames.c 

OBJS += \
./abfrage.o \
./abfrage1.o \
./abfrage2.o \
./abfrage3.o \
./main.o \
./usernames.o 

C_DEPS += \
./abfrage.d \
./abfrage1.d \
./abfrage2.d \
./abfrage3.d \
./main.d \
./usernames.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


