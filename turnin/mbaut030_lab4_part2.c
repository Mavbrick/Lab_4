/*	Author: mbaut030
 *  Partner(s) Name: Maverick
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { Start, Wait, Inc, Dec, Reset } State;
unsigned char count = 0x00;

void Tick() {
	switch(State) {
		case Start:
			State = Wait;
		break;

		case Wait:
			if((PINA & 0x03) == 0x01) {
				State = Inc;
			}
			else if((PINA & 0x03) == 0x02) {
				State = Dec;
			}
			else if((PINA & 0x03) == 0x03) {
				State = Reset;
			}
			else {
				State = Wait;
			}
		break;

		case Inc:
			State = Wait;
		break;

		case Dec:
			State = Wait;
		break;

		case Reset:
			if((PINA & 0x03) == 0x03) {
				State = Reset;
			}
			else {
				State = Wait;
			}
		break;
			
		default:
		break;


	}

	switch(State) {
		case Wait:	
		break;

		case Inc:
		if(count >= 0x09) {
			count = 0x09;
		}
		else {
			count = count + 0x01;
		}
		break;

		case Dec:
		if(count <= 0x00) {
			count = 0x00;
		}
		else {
			count = count - 0x01;
		}
		break;

		case Reset:
		count = 0x00;
		break;

		default:
		break;
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */

    State = Start;
    count = 0x07;    

    while (1) {
	Tick();
	PORTC = count;
    }
    return 1;
}
