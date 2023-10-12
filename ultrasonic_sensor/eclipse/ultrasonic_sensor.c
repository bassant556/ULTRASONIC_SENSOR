/*
 * ultrasonic_sensor.c
 *
 *  Created on: Oct 11, 2023
 *      Author: bassant
 */
#include"icu.h"/*for icu prototypes*/
#include"gpio.h"/*for using gpio prototypes*/
#include"ultrasonic_sensor.h"
#include<util/delay.h>/*for using _delay_us*/
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
ICU_ConfigType ICU_Configurations = {F_CPU_8,RAISING};/*here we define the prescaler and the initial edge we want to start from*/
uint8 g_edgeCount = 0;/*for counting the edges to check of we are in the rising or the falling edge*/
uint16 g_timeHigh = 0;/*to capture the high time value*/

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description:
 * function to get the hight time value
 */
void Ultrasonic_edgeProcessing(void){
	g_edgeCount++;
	/*increment this counter to check if its ==1 so we are in the rising edge
	 * so we intialize the timer by zero to start counting from this rising edge
	 * if its ==2 so we capture the the high time value and set this counter to 0 for the coming ISR */
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */

		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);/* Detect falling edge */
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = ICU_getInputCaptureValue();
		g_edgeCount=0;
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(RAISING);


	}
}

/*
 * Description:
 * function to init the ultrasonic module
 * 1-we initiale the icu by sending it the structure containing the required prescaler and the intial edge
 * 2-we set the call back function
 * 3-set the trigger pin as output pin
 */
void Ultrasonic_init(void){

	ICU_init(&ICU_Configurations);
	/*we give this structure to this function
	 *to set the bits responsible for the prescaler and
	 *the the edge according to this structure
	 */
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	/*here we give the address of Ultrasonic_edgeProcessing to ICU_setCallBack to call
	 * edge_processing function on ISR routine
	 */
	GPIO_setupPinDirection(TRIGGER_PORT,TRIGGER_PIN,PIN_OUTPUT);/*set the trigger pin as an output pin*/
}

/*
 * Decription:
 * we set the trigger pin to high and delay till we get the high time value
 */
void Ultrasonic_Trigger(void){
	GPIO_writePin(TRIGGER_PORT,TRIGGER_PIN , LOGIC_HIGH);
	_delay_us(10);
	/*here we make the trigger pin high and make a delay for 10 micro seconds
	 * after setting it to high ultrasound waves is generated with frequency 40khz
	 *echo pin remains high until it does not get the echo sound back.
	 *So the width of echo pin will be the time for sound to travel to the object and return back
	 */
}

/*
 * Description:
 * we start the timer after sending the pulse trigger and after we get the high time value
  we set the trigger pin to low
 */
uint16 Ultrasonic_readDistance(void){
	uint16 UTRRASONIC_distance=0;
	Ultrasonic_Trigger();
	/*here we send trigger pulse to the ultrasonic module after that
     ultrasound waves will be generated toward the required object
     that we want to measure the distance from it
	 */

	GPIO_writePin(PORTB_ID,PIN5_ID , LOGIC_LOW);/*we set it to low after we get the high time value*/
	UTRRASONIC_distance=g_timeHigh/58+1;/*here is some calculations to get the distance in cm*/
	return UTRRASONIC_distance;/*return the distance to read it from the lcd*/
}


