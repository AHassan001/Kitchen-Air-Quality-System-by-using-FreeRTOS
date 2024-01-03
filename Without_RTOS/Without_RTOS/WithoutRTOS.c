 /******************************************************************************
 *
 * Module: Without RTOS
 *
 * File Name: WithoutRTOS.c
 *
 * Description: source file for the application without RTOS
 *
 * Author: Abdelrahman Maher
 *
 *******************************************************************************/
#define F_CPU 1000000UL

#include "adc.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "dc_motor.h"
#include "mq2_sensor.h"
#include <util/delay.h>
#include <stdlib.h>
#include "avr/io.h" /* To use the SREG Register */
#include <avr/interrupt.h>

void Timer_Init(void);

uint16 g_counter = 0;


typedef enum
{
	FAN_OFF,FAN_ON_CLK, FAN_ON_ACLK
}Fan_State;

uint8 main(void)
{
	TCNT1= 0;

	Timer_Init();
	static uint8 temp, Res[16], lpg[16], smoke[16];
	float32 Ro=10,rs_ro;

	ADC_ConfigType ADC_Configurations = {INTERNAL_VOLT,F_CPU_8};
	Fan_State Fan = FAN_OFF;

	/* Enable interrupts by setting I-bit */
	SREG  |= (1<<7);

	/* Initialize Motor driver */
	DcMotor_Init();
	/* Initialize LCD driver */
	LCD_init();
	/* Initialize ADC driver */
	ADC_init(&ADC_Configurations);
	


	Ro = SensorCalibration();                       //Please make sure the sensor is in clean air when you perform the calibration
	dtostrf(Ro, 6, 2, Res);                         // floating to string(Floating pt value ant to be converted,min. width of the output,no.of digits after the pt, store the output string)
	_delay_ms(1000);


	LCD_clearScreen();

	LCD_displayStringRowColumn(1,0,"Temp =    C");
	LCD_displayStringRowColumn(2,0,"LPG:         ppm");
	LCD_displayStringRowColumn(3,0,"SMOKE:       ppm");

    while(1)
    {

		/* Display the temperature and FAN state */
		if(Fan == FAN_OFF)
		{
			LCD_moveCursor(0,0);
			LCD_displayString("FAN is OFF");
		}
		else if(Fan == FAN_ON_CLK)
		{
			LCD_moveCursor(0,0);
			LCD_displayString("FAN is ON CLK ");
		}
		else
		{
			LCD_moveCursor(0,0);
			LCD_displayString("FAN is ON ACLK ");
		}
		
		/* Get the temperature value */
		temp = LM35_getTemperature();
		
		itoa(GetGasPercentage(ReadSensor()/Ro,LPG), lpg, 10);
		itoa(GetGasPercentage(ReadSensor()/Ro,SMOKE), smoke, 10);

		LCD_moveCursor(2,5);
		LCD_displayString(lpg);

		LCD_moveCursor(3,7);
		LCD_displayString(smoke);
		
		if(lpg >= 2000 || smoke >= 400)
		{
			Fan = FAN_ON_ACLK;
			DcMotor_Rotate(DC_MOTOR_ACW,50); /* Rotates the motor with 50% from its speed */
			break;
		}
		else if(temp >= 30)
		{
			Fan = FAN_ON_CLK;
			DcMotor_Rotate(DC_MOTOR_CW,50); /* Rotates the motor with 50% from its speed */
		}
		else
		{
			Fan = FAN_OFF;
			DcMotor_Rotate(DC_MOTOR_STOP,0); /* Stop the motor */
		}

		/* Display the temperature value every time at same position */
		LCD_moveCursor(1,7);
		if(temp >= 100)
		{
			LCD_intgerToString(temp);

		}
		else
		{
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
	
		_delay_ms(1000);


    }
}

void Timer_Init(void)
{
	TCCR1A = 0;
	
	TCCR1B  |= ( 1<< CS10);
	TIMSK |= (1 << TOIE1);
	TCNT1= 0;

}

ISR(TIMER1_OVF_vect)
{
	TCNT1= 0;
	g_counter += 1;
	TIFR |= (1 << TOV1);
}
/*
*   Program Memory Usage 	:	6032 bytes   18.7 % Full
*   Data Memory Usage 		:	128 bytes    8.0  % Full
*  		   text	     data	  bss	    dec	        hex  	    filename
*		   5904	     128	  0	        6032	    1790	    Without_RTOS.elf          
*/