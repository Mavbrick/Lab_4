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

enum States { Start, Wait, Check, Inc, Dec, Reset } State;
unsigned char count;

void Tick() {
	switch(State) {
		case Start:
			State = Wait;
		break;

		case Wait:
			if(PINA & 0x01) {
				State = Inc;
			}
			else if(PINA & 0x02) {
				State = Dec;
			}
			else if((PINA & 0x03) == 0x03) {
				State = Reset;
			}
		break;

		case Check:
			if(PINA == 0x00) {
				State = Wait;
			}
		break;

		case Inc:
			if(PINA & 0x00) {
				State = Wait;
			}
			else if((PINA & 0x03) == 0x03) {
				State = Reset;
			}
			else {
				State = Check;
			}
		break;

		case Dec:
                        if(PINA & 0x00) {
                                State = Wait;
                        }
                        else if((PINA & 0x03) == 0x03) {
                                State = Reset;
                        }
                        else {
                                State = Check;
                        }
		break;

		case Reset:
			State = Wait;
		break;


	}

	switch(State) {
		case Start:	
		break;

		case Wait:
		break;

		case Check:
		break;

		case Inc:
		if(count < 0x09) {
			count = count + 0x01;
		}
		break;

		case Dec:
		if(count > 0x00) {
			count = count - 0x01;
		}
		break;

		case Reset:
		count = 0x00;
		break;

	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x00;
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
