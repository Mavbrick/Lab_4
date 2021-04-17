/*	Author: mbaut030
 *  Partner(s) Name: Maverick
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char arr[4] = {0x04, 0x01, 0x02, 0x01};
unsigned char i = 0x00;
unsigned char tmpB = 0x00;

enum States { Start, Lock, Press, Release, Unlock } State;

void Tick() {
    switch(State) {
        case Start:
                State = Lock;
	break;

	case Lock:
		if(PINA == arr[i]) {
			State = Press;
		}
		else {
			State = Lock;
		}
	break;

	case Press:
		if(PINA == arr[i]) {
			State = Press;
		}
		else if(!PINA) {
			State = Release;
			i++;
		}
		else {
			State = Lock;
		}
	break;

	case Release:
		if(!PINA) {
			State = Release;
		}
		else if(PINA == arr[i] && i == 3) {
			if(tmpB == 0x00) {
				State = Unlock;
			}
			else {
				State = Lock;
			}
		}
		else if(PINA == arr[i] && i < 3) {
			State = Press;
		}
		else {
			State = Lock;
		}
	break;

	case Unlock:
		if(PINA == 0x80) {
			State = Lock;
		}
		else if(PINA == arr[i]) {
			State = Press;
		}
		else {
			State = Unlock;
		}
	break;

	default:
	break;
        }

    switch (State) {
        case Start:
        break;

        case Lock:
	tmpB = 0x00;
	i = 0x00;
        break;

        case Press:
        break;

        case Release:
        break;

        case Unlock:
	tmpB = 0x01;
	i = 0x00;
        break; 

	default:
	break;
    }
}

int main(void) {

    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

	State = Start;
	i = 0x00;
	tmpB = 0x00;

    while (1) {
        Tick();
	PORTB = tmpB;
    }

    return 1;
}
 
