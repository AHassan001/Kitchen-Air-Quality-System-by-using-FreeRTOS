 /******************************************************************************
 *
 * Module: Main Functions
 *
 * File Name: main.c
 *
 * Description: source file for Temperature checker by using FreeRTOS Priority Based Scheduling algorithm
 *
 * Author: Abdelrahman Maher
 *
 *******************************************************************************/

/************************************************************************/
/*	       	                   Includes                                 */
/************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
//#include "queue.h"
//#include "semphr.h"
#include "./MCAL/adc.h"
#include "./HAL/lcd.h"
#include "./HAL/lm35_sensor.h"
#include "./HAL/mq2_sensor.h"
#include "./HAL/dc_motor.h"
//#include <stdio.h>
#include "./MCAL/gpio.h"
#include <stdio.h>
#include <avr/interrupt.h>


#define F_CPU				 1000000UL

#define LCD_Priority 		 1
#define MOTOR_LED_Priority	 2
#define TEMP_Priority		 3  
#define Gas_Priority		 4		/* Highest Priority to not miss any reading*/


void vLcd_Task(void *pvparamters);
void vTemp_Task(void *pvparamters);
void vMotor_LED_Task(void *pvparamters);
void vGas_Task (void *pvparamters);
void Timer_Init(void);

/************************************************************************/
/*                          Global variables                            */
/************************************************************************/
typedef enum
{
	FAN_OFF,FAN_ON_CLK, FAN_ON_ACLK
}Fan_State;

uint16 g_counter = 0;


uint16 g_Task1_duartion=0;
uint16 g_Task2_duartion=0;
uint16 g_Task3_duartion=0;
uint16 g_Task4_duartion=0;

uint16 g_start_t1=0;
uint16 g_end_t1 =0;

uint16 g_start_t2=0;
uint16 g_end_t2=0;

uint16 g_start_t3=0;
uint16 g_end_t3=0;


uint16 g_start_t4=0;
uint16 g_end_t4=0;


TaskHandle_t Temp_Sensor_Handeler, Gas_Sensor_Handeler, Dc_motor_Handler, Lcd_Handler;

static uint8 G_temp = 0;
static uint8 G_lpg[16];
static uint8 G_smoke[16] ;

Fan_State Fan = FAN_OFF;


void main(void)
{
	
	g_counter=0;
	Timer_Init();
		
	BaseType_t status;

	ADC_ConfigType ADC_Configurations = {INTERNAL_VOLT,F_CPU_8};

	LCD_init();  									/* Initialize LCD */
	DcMotor_Init();									/* Initialize DC Motor */
	ADC_init(&ADC_Configurations);					/* Initialize ADC driver */

	/* Enable interrupts by setting I-bit */
	SREG  |= (1<<7);
	

 	GPIO_setupPinDirection(PORTC_ID,PIN4_ID,PIN_OUTPUT);			// for Proteus config only
 	GPIO_setupPinDirection(PORTC_ID,PIN5_ID,PIN_OUTPUT);			// for Proteus config only
    GPIO_setupPinDirection(PORTC_ID,PIN6_ID,PIN_OUTPUT);			// for Proteus config only
 	GPIO_setupPinDirection(PORTC_ID,PIN7_ID,PIN_OUTPUT);			// for Proteus config only


	status = xTaskCreate(vLcd_Task, "Lcd_Task", 100, NULL, LCD_Priority, &Lcd_Handler); //180
	configASSERT(status == pdPASS);								// if status=0 enter infinity loop

	status = xTaskCreate(vTemp_Task, "Temp_Task", 100, NULL, TEMP_Priority, &Temp_Sensor_Handeler);
	configASSERT(status == pdPASS);								// if status=0 enter infinity loop

	status = xTaskCreate(vMotor_LED_Task, "Motor_LED_Task", 100, NULL,MOTOR_LED_Priority, &Dc_motor_Handler);
	configASSERT(status == pdPASS); 							// if status=0 enter infinity loop


	status = xTaskCreate(vGas_Task, "Gas_Task", 100, NULL, Gas_Priority, &Gas_Sensor_Handeler);
	configASSERT(status == pdPASS);								// if status=0 enter infinity loop

	vTaskStartScheduler();

}

void vLcd_Task(void *pvparamters)
{
	
	GPIO_writePin(PORTC_ID, PIN4_ID , LOGIC_HIGH);			// for Proteus config only
	
	
	LCD_clearScreen();

	while(1)
	{
		g_start_t1 = xTaskGetTickCount();
		
		 
		g_counter=0;
		Timer_Init();
		
		 
		if(Fan == FAN_OFF)
		{
			LCD_moveCursor(0,0);
			LCD_displayString("FAN is OFF");
		}
		else if(Fan == FAN_ON_CLK)
		{
			LCD_moveCursor(0,0);
			LCD_displayString("FAN is ON (CLK) ");
		}
		else
		{
			LCD_moveCursor(0,0);
			LCD_displayString("FAN is ON (ACLK) ");		 
		}

		LCD_moveCursor(1,0);
		LCD_displayString("Temp =    C");

		LCD_moveCursor(1,7);
		if(G_temp >= 100)
		{
			LCD_intgerToString(G_temp);
		}
		else
		{
			LCD_intgerToString(G_temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');

		}
		
		LCD_displayStringRowColumn(2,0,"LPG:         ppm");
		LCD_moveCursor(2,5);
		LCD_displayString(G_lpg);

		LCD_displayStringRowColumn(3,0,"SMOKE:       ppm");
		LCD_moveCursor(3,7);
		LCD_displayString(G_smoke);

		GPIO_writePin(PORTC_ID, PIN4_ID , LOGIC_LOW);					// for Proteus config only

		g_end_t1 = xTaskGetTickCount();
		
		g_Task1_duartion = g_end_t1 - g_start_t1 ;

		vTaskDelay(pdMS_TO_TICKS(2000));
	}
}

void vTemp_Task(void *pvparamters)
{
	/*
	
	*/

	while(1)
	{
		g_start_t2 = xTaskGetTickCount();
		
		g_counter=0;
		Timer_Init();
		
		GPIO_writePin(PORTC_ID, PIN5_ID , LOGIC_HIGH);					// for Proteus config only

		G_temp = 0 ;
		G_temp = LM35_getTemperature();


		GPIO_writePin(PORTC_ID, PIN5_ID , LOGIC_LOW);					// for Proteus config only

		g_end_t2 = xTaskGetTickCount();

		g_Task2_duartion = g_end_t2 - g_start_t2 ;		

		vTaskDelay(pdMS_TO_TICKS(1000));
		
	}
}

void vMotor_LED_Task(void *pvparamters)
{
	/*

	*/
	
	while(1)
	{
		g_start_t3 = xTaskGetTickCount();
		
		g_counter=0;
		Timer_Init();
		
		GPIO_writePin(PORTC_ID, PIN6_ID , LOGIC_HIGH);					// for Proteus config only
		
		if(G_lpg >= 2000 || G_smoke >= 400)
		{
			Fan = FAN_ON_ACLK;
			DcMotor_Rotate(DC_MOTOR_ACW,50); /* Rotates the motor with 50% from its speed */
			break;
		}
		else if(G_temp >= 30)
		{
			Fan = FAN_ON_CLK;
			DcMotor_Rotate(DC_MOTOR_CW,50); /* Rotates the motor with 50% from its speed */
		}
		else
		{
			Fan = FAN_OFF;
			DcMotor_Rotate(DC_MOTOR_STOP,0); /* Stop the motor */
		}
		
		
		GPIO_writePin(PORTC_ID, PIN6_ID, LOGIC_LOW);					// for Proteus config only

	    g_end_t3 = xTaskGetTickCount();
		
		g_Task3_duartion = g_end_t3 - g_start_t3 ;

		vTaskDelay(pdMS_TO_TICKS(250));

	}
}

void vGas_Task (void *pvparamters)
{
	
	g_counter=0;
	Timer_Init();
	
	
	g_start_t4 = xTaskGetTickCount();

	GPIO_writePin(PORTC_ID, PIN7_ID , LOGIC_HIGH);					// for Proteus config only	
	uint8 Res[16];
	float32 Ro=10,rs_ro;
	
	Ro = SensorCalibration();                       //Please make sure the sensor is in clean air when you perform the calibration
	//Ro = 500;
	dtostrf(Ro, 6, 2, Res);                         // floating to string(Floating pt value and to be converted,min. width of the output,no.of digits after the pt, store the output string)
	
	
	while(1)
	{
		itoa(GetGasPercentage(ReadSensor()/Ro,LPG), G_lpg, 10);
		itoa(GetGasPercentage(ReadSensor()/Ro,SMOKE), G_smoke, 10);
		
		GPIO_writePin(PORTC_ID, PIN7_ID , LOGIC_LOW);					// for Proteus config only

		g_end_t4 = xTaskGetTickCount();

		g_Task4_duartion = g_end_t4 - g_start_t4 ;

		vTaskDelay(pdMS_TO_TICKS(500));
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
 * 1st Run Data:
 *
 * Program:   9982 bytes (30.5% Full)
 *			  (.text + .data + .bootloader)
 *
 * Data:      1817 bytes (88.7% Full)
 *            (.data + .bss + .noinit)
 *
 *  Build Finished. 0 errors, 7 warnings. 
 *
 * */
