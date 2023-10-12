/*
 * ultrasonic_sensor.h
 *
 *  Created on: Oct 11, 2023
 *      Author: bassant
 */
#include"std_types.h"/*to use declarations as uint16*/
#include"gpio.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
#define TRIGGER_PORT  PORTB_ID
#define TRIGGER_PIN   PIN5_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description:
 * function to init the ultrasonic module
 * 1-we initiale the icu by sending it the structure containing the required prescaler and the intial edge
 * 2-we set the call back function
 * 3-set the trigger pin as output pin
 */
void Ultrasonic_init(void);
/*
 * Decription:
 * we set the trigger pin to high and delay till we get the high time value
 */
void Ultrasonic_Trigger(void);
/*
 * Description:
 * we start the timer after sending the pulse trigger and after we get the high time value
  we set the trigger pin to low
 */
uint16 Ultrasonic_readDistance(void);
/*
 * Description:
 * function to get the hight time value
 */
void Ultrasonic_edgeProcessing(void);
