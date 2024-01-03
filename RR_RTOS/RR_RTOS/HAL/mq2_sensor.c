 /******************************************************************************
 *
 * Module: MQ2 Gas Sensor
 *
 * File Name: mq2_sensor.c
 *
 * Description: source file for the gas sensor "MQ2"
 *
 * Author: Abdelrahman Maher
 *
 *******************************************************************************/

#include "mq2_sensor.h"
#include "adc.h"
#include <util/delay.h>
#include <math.h>
#include <stdio.h>


float32 LPGCurve[3] = {2.3,0.20,-0.46};   //two points from LPG curve are taken point1:(200,1.6) point2(10000,0.26)
                                          //take log of each point (lg200, lg 1.6)=(2.3,0.20)  (lg10000,lg0.26)=(4,-0.58)
                                          //find the slope using these points. take point1 as reference
                                          //data format:{ x, y, slope};
										  //(y2-y1)/(x2-x1)=(-0.58-0.2)/(4-2.3) = -0.46

float32 SmokeCurve[3] ={2.3,0.53,-0.43};  //two points from smoke curve are taken point1:(200,3.4) point2(10000,0.62)
                                        //take log of each point (lg200, lg3.4)=(2.3,0.53)  (lg10000,lg0.63)=(4,-0.20)
                                        //find the slope using these points. take point1 as reference
                                        //data format:{ x, y, slope};
										//(y2-y1)/(x2-x1)=(-0.2-0.53)/(4-2.3) = -0.43

// sensor and load resistor forms a voltage divider. so using analog value and load value
// we will find sensor resistor.

float32 ResistanceCalculation(uint16 raw_adc)
{
  return ( ((float32)RL_VALUE*(ADC_MAXIMUM_VALUE-raw_adc)/raw_adc));   // we will find sensor resistor.
}

float32 SensorCalibration()
{
  uint8 i;                                   // This function assumes that sensor is in clean air.
  float32 val=0;

  for (i=0;i<15;i++)
  {                   //take multiple samples and calculate the average value
    val += ResistanceCalculation(ADC_readChannel(0));
    _delay_ms(200);
  }

  val = val/15;
  val = val/RO_CLEAN_AIR_FACTOR;           //divided by RO_CLEAN_AIR_FACTOR yields the Ro according to the chart in the datasheet

  return val;
}

float32 ReadSensor()
{
  uint8 i;
  float32 rs=0;

  for (i=0;i<5;i++)
  {                                 // take multiple readings and average it.
    rs += ResistanceCalculation(ADC_readChannel(0));   // rs changes according to gas concentration.
    _delay_ms(50);
  }

  rs = rs/5;
  return rs;
}

uint16 GetGasPercentage(float32 rs_ro_ratio, uint16 gas_id)
{
  if ( gas_id == LPG ) {
     return GetPercentage(rs_ro_ratio,LPGCurve);
  }
  else if( gas_id == SMOKE ) {
     return GetPercentage(rs_ro_ratio,SmokeCurve);
  }
  return 0;
}

//Using slope,ratio(y2) and another point(x1,y1) on line we will find
// gas concentration(x2) using x2 = [((y2-y1)/slope)+x1]
// as in curves are on logarithmic coordinate, power of 10 is taken to convert result to non-logarithmic.

uint16  GetPercentage(float32 rs_ro_ratio, float32 *curve)
{
	uint8 x=0;
	x = ( ((log(rs_ro_ratio) - curve[1]) /curve[2]) + curve[0] );

	return pow(10,x);
}

