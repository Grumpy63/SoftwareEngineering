################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../alt_vokabel_abfrage.c \
../main.c \
../usernames.c 

OBJS += \
./alt_vokabel_abfrage.o \
./main.o \
./usernames.o 

C_DEPS += \
./alt_vokabel_abfrage.d \
./main.d \
./usernames.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


