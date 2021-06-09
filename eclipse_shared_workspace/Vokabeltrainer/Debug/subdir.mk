################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Liste_einlesen.c \
../abfrage.c \
../abfrage1.c \
../abfrage2.c \
../abfrage3.c \
../kategorie_waehlen.c \
../main.c \
../richtung.c \
../usernames.c \
../vokabelzahl_feststellen.c 

OBJS += \
./Liste_einlesen.o \
./abfrage.o \
./abfrage1.o \
./abfrage2.o \
./abfrage3.o \
./kategorie_waehlen.o \
./main.o \
./richtung.o \
./usernames.o \
./vokabelzahl_feststellen.o 

C_DEPS += \
./Liste_einlesen.d \
./abfrage.d \
./abfrage1.d \
./abfrage2.d \
./abfrage3.d \
./kategorie_waehlen.d \
./main.d \
./richtung.d \
./usernames.d \
./vokabelzahl_feststellen.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


