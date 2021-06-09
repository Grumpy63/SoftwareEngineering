################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Liste_einlesen.c \
../Liste_einlesen_alt.c \
../Main.c \
../kategorie_waehlen.c \
../richtung.c \
../vokabelzahl_feststellen.c 

OBJS += \
./Liste_einlesen.o \
./Liste_einlesen_alt.o \
./Main.o \
./kategorie_waehlen.o \
./richtung.o \
./vokabelzahl_feststellen.o 

C_DEPS += \
./Liste_einlesen.d \
./Liste_einlesen_alt.d \
./Main.d \
./kategorie_waehlen.d \
./richtung.d \
./vokabelzahl_feststellen.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


