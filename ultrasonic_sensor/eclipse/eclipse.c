/*
 * eclipse.c
 *
 *  Created on: Oct 11, 2023
 *      Author: bassant
 */

#include<avr/io.h>/*to use SREG register*/
#include"lcd.h"
#include"ultrasonic_sensor.h"
int main(){
	uint16 US_distance=0;
	Ultrasonic_init();/*we start the timer when the rising edge come to the echo pin*/
	SREG |= (1<<7);/*set I-bit for the inetrrupt*/
	LCD_init();/*intialize the lcd*/
	LCD_moveCursor(0,0);/*move the cursor to row 0 and column 0*/
	LCD_displayString("Distance=    cm");
	    while(1){
	    	LCD_moveCursor(0,10);/*move the cursor to row 0 and column 9*/
		US_distance=Ultrasonic_readDistance();/*read the distance*/

		if(US_distance>=100){
			LCD_moveCursor(0,10);/*move the cursor to row 0 and column 9*/
			LCD_intgerToString(US_distance);
		}else{
			LCD_moveCursor(0,10);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_intgerToString(US_distance);
			LCD_displayCharacter(' ');
		}




	}




}
