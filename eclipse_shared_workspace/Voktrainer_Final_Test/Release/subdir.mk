################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Liste_einlesen.c \
../Main.c \
../verzeichnis.c 

OBJS += \
./Liste_einlesen.o \
./Main.o \
./verzeichnis.o 

C_DEPS += \
./Liste_einlesen.d \
./Main.d \
./verzeichnis.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


