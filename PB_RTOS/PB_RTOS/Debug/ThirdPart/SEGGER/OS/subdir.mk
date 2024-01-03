################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdPart/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.c 

OBJS += \
./ThirdPart/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.o 

C_DEPS += \
./ThirdPart/SEGGER/OS/SEGGER_SYSVIEW_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdPart/SEGGER/OS/%.o: ../ThirdPart/SEGGER/OS/%.c ThirdPart/SEGGER/OS/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\University\Year 4\Resarch Graduation Project\Codes\RGP_Workspace\RTOS_workspace\RTOS_T1\ThirdPart\FreeRTOS\portable\GCC\ATMega323" -I"E:\University\Year 4\Resarch Graduation Project\Codes\RGP_Workspace\RTOS_workspace\RTOS_T1" -I"E:\University\Year 4\Resarch Graduation Project\Codes\RGP_Workspace\RTOS_workspace\RTOS_T1\ThirdPart\FreeRTOS\include" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


