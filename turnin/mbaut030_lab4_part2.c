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

enum States { Start, Inc, Dec, Reset, Wait} State;
unsigned char count = 0x00;
unsigned char prevState = 0x00;

void Tick() {
	switch(State) {
		
		case Start:
			if(PINA == 0x03) {
				State = Reset;
			}
			else if(PINA == 0x02) {
				State = Dec;
			}
			else if(PINA == 0x01) {
				State = Inc;
			}
			else {
				State = Start;
			}
		break;

		case Inc:
			if(PINA == 0x00) {
				State = Start;
			}
			else if(PINA == 0x02) {
				State = Dec;
			}
			else if(PINA == 0x03) {
				State = Reset;
			}
			else {
				State = Wait;
			}
		break;

		case Dec:
                        if(PINA == 0x00) {
                                State = Start;
                        }
                        else if(PINA == 0x01) {
                                State = Inc;
                        }
			else if(PINA == 0x03) {
				State = Reset;
			}
			else {
				State = Wait;
			}
		break;

		case Reset:
			if(PINA == 0x00) {
				State = Start;
			}
			else if(PINA == 0x01) {
				State = Inc;
			}
			else if(PINA == 0x02) {
				State = Dec;
			}
			else {
				State = Wait;
			}
		break;

                case Wait:
                        if(PINA == 0x03) {
                                State = Reset;
                        }
                        else if(PINA == 0x00) {
                                State = Start;
                        }
                        else if(PINA == 0x01 && prevState == 0x02) {
                                State = Inc;
                        }
                        else if(PINA == 0x02 && prevState == 0x01) {
                                State = Dec;
                        }
                        else {
                                State = Wait;
                        }
                break;

		default:
		break;		

	}

	switch(State) {
		case Start:	
		break;

		case Inc:
		if(count < 9) {
			count = count + 0x01;
		}
		prevState = 0x01;
		break;

		case Dec:
		if(count > 0) {
			count = count - 0x01;
		}
		prevState = 0x02;
		break;

		case Reset:
		count = 0x00;
		prevState = 0x00;
		break;

		case Wait:
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
