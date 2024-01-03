 /******************************************************************************
 *
 * Module: Without RTOS
 *
 * File Name: mq2_sensor.h
 *
 * Description: header file for the gas sensor "MQ2"
 *
 * Author: Abdelrahman Maher
 *
 *******************************************************************************/


#ifndef MQ2_SENSOR_H_
#define MQ2_SENSOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define RL_VALUE 				10     	//define the load resistance on the board, in kilo ohms
#define RO_CLEAN_AIR_FACTOR 	9.83    //(Sensor resistance in clean air)/RO,which is derived from the chart in datasheet
#define LPG 					0       // Gas identity no. of LPG
#define SMOKE 					1		// Gas identity no. of Smoke


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
uint16  GetPercentage(float32, float32 *);
uint16  GetGasPercentage(float32 , uint16);
float32 ReadSensor();
float32 ResistanceCalculation(uint16);
float32 SensorCalibration();


#endif /* MQ2_SENSOR_H_ */
