################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Liste_einlesen.c \
../abfrage.c \
../abfrage1.c \
../abfrage2new.c \
../abfrage3.c \
../highscorce.c \
../kategorie_waehlen.c \
../main.c \
../richtung.c \
../usernames.c \
../vokabelzahl_feststellen.c 

OBJS += \
./Liste_einlesen.o \
./abfrage.o \
./abfrage1.o \
./abfrage2new.o \
./abfrage3.o \
./highscorce.o \
./kategorie_waehlen.o \
./main.o \
./richtung.o \
./usernames.o \
./vokabelzahl_feststellen.o 

C_DEPS += \
./Liste_einlesen.d \
./abfrage.d \
./abfrage1.d \
./abfrage2new.d \
./abfrage3.d \
./highscorce.d \
./kategorie_waehlen.d \
./main.d \
./richtung.d \
./usernames.d \
./vokabelzahl_feststellen.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


