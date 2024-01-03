################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdPart/FreeRTOS/portable/MemMang/heap_4.c 

OBJS += \
./ThirdPart/FreeRTOS/portable/MemMang/heap_4.o 

C_DEPS += \
./ThirdPart/FreeRTOS/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdPart/FreeRTOS/portable/MemMang/%.o: ../ThirdPart/FreeRTOS/portable/MemMang/%.c ThirdPart/FreeRTOS/portable/MemMang/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\University\Year 4\Resarch Graduation Project\Codes\RGP_Workspace\RTOS_workspace\RTOS_T1\ThirdPart\FreeRTOS\portable\GCC\ATMega323" -I"E:\University\Year 4\Resarch Graduation Project\Codes\RGP_Workspace\RTOS_workspace\RTOS_T1" -I"E:\University\Year 4\Resarch Graduation Project\Codes\RGP_Workspace\RTOS_workspace\RTOS_T1\ThirdPart\FreeRTOS\include" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


