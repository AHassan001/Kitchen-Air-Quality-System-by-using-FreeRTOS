################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdPart/SEGGER/SEGGER/SEGGER_RTT.c \
../ThirdPart/SEGGER/SEGGER/SEGGER_RTT_printf.c \
../ThirdPart/SEGGER/SEGGER/SEGGER_SYSVIEW.c 

S_UPPER_SRCS += \
../ThirdPart/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./ThirdPart/SEGGER/SEGGER/SEGGER_RTT.o \
./ThirdPart/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o \
./ThirdPart/SEGGER/SEGGER/SEGGER_RTT_printf.o \
./ThirdPart/SEGGER/SEGGER/SEGGER_SYSVIEW.o 

S_UPPER_DEPS += \
./ThirdPart/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.d 

C_DEPS += \
./ThirdPart/SEGGER/SEGGER/SEGGER_RTT.d \
./ThirdPart/SEGGER/SEGGER/SEGGER_RTT_printf.d \
./ThirdPart/SEGGER/SEGGER/SEGGER_SYSVIEW.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdPart/SEGGER/SEGGER/%.o: ../ThirdPart/SEGGER/SEGGER/%.c ThirdPart/SEGGER/SEGGER/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\University\Year 4\Resarch Graduation Project\Codes\RGP_Workspace\RTOS_workspace\RTOS_T1\ThirdPart\FreeRTOS\portable\GCC\ATMega323" -I"E:\University\Year 4\Resarch Graduation Project\Codes\RGP_Workspace\RTOS_workspace\RTOS_T1" -I"E:\University\Year 4\Resarch Graduation Project\Codes\RGP_Workspace\RTOS_workspace\RTOS_T1\ThirdPart\FreeRTOS\include" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ThirdPart/SEGGER/SEGGER/%.o: ../ThirdPart/SEGGER/SEGGER/%.S ThirdPart/SEGGER/SEGGER/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -g2 -gstabs -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


