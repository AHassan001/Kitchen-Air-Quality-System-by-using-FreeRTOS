################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdPart/FreeRTOS/portable/croutine.c \
../ThirdPart/FreeRTOS/portable/event_groups.c \
../ThirdPart/FreeRTOS/portable/list.c \
../ThirdPart/FreeRTOS/portable/queue.c \
../ThirdPart/FreeRTOS/portable/tasks.c \
../ThirdPart/FreeRTOS/portable/timers.c 

OBJS += \
./ThirdPart/FreeRTOS/portable/croutine.o \
./ThirdPart/FreeRTOS/portable/event_groups.o \
./ThirdPart/FreeRTOS/portable/list.o \
./ThirdPart/FreeRTOS/portable/queue.o \
./ThirdPart/FreeRTOS/portable/tasks.o \
./ThirdPart/FreeRTOS/portable/timers.o 

C_DEPS += \
./ThirdPart/FreeRTOS/portable/croutine.d \
./ThirdPart/FreeRTOS/portable/event_groups.d \
./ThirdPart/FreeRTOS/portable/list.d \
./ThirdPart/FreeRTOS/portable/queue.d \
./ThirdPart/FreeRTOS/portable/tasks.d \
./ThirdPart/FreeRTOS/portable/timers.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdPart/FreeRTOS/portable/%.o: ../ThirdPart/FreeRTOS/portable/%.c ThirdPart/FreeRTOS/portable/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\University\Year 4\Resarch Graduation Project\Codes\RGP_Workspace\RTOS_workspace\RTOS_T1\ThirdPart\FreeRTOS\portable\GCC\ATMega323" -I"E:\University\Year 4\Resarch Graduation Project\Codes\RGP_Workspace\RTOS_workspace\RTOS_T1" -I"E:\University\Year 4\Resarch Graduation Project\Codes\RGP_Workspace\RTOS_workspace\RTOS_T1\ThirdPart\FreeRTOS\include" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


