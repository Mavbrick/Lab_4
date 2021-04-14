/*	Author: mbaut030
 *  Partner(s) Name: Maverick
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { Start, Release_Zero, Press_One, Release_One, Press_Zero } State;

void Tick() {
	switch(State) {
		case Start:
			State = Release_Zero;
		break;

		case Release_Zero:
			if (PINA == 0x00) {
				State = Release_Zero;	
			}
			if (PINA == 0x01) {
				State = Press_One;
			}
		break;

		case Press_One:
			if (PINA == 0x01) {
				State = Press_One;
			}
			if (PINA == 0x00) {
				State = Release_One;
			}
		break;

		case Release_One:
			if (PINA == 0x00) {
				State = Release_One;
			}
			if (PINA == 0x01) {
				State = Press_Zero;
			}
		break;

		case Press_Zero:
			if (PINA == 0x01) {
				State = Press_Zero;
			}
			if (PINA == 0x00) {
				State =	Release_Zero;
			}
		break;
		
		default:
			State = Start;
		break;


	}

	switch(State) {
		case Start:
			PORTB = 0x01;
		break;

		case Release_Zero:
			PORTB = 0x01;
		break;

		case Press_One:
			PORTB = 0x02;
		break;
		
		case Release_One:
			PORTB = 0x02;
		break;

		case Press_Zero:
			PORTB = 0x01;
		break;

		default:
		break;
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */

    State = Release_Zero;
	
    while (1) {
	Tick();
    }
    return 1;
}
