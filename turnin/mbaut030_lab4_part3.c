/*	Author: mbaut030
 *  Partner(s) Name: Maverick
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { Start, Lock, Unlock_One, Wait_One, Unlock_Two, Wait_Two } State;

void Tick() {
    switch(State) {
  	 case Start:
        	State = Lock;
         break;

   	 case Lock:
        	if(PINA == 0x04) {
           		State = Unlock_One;
        	}
        	else {
            		State = Lock;
        	}
         break;

    	 case Unlock_One:
        	if(PINA == 0x04) {
           		 State = Unlock_One;
        	}
        	else if(PINA == 0x00) {
            		State = Wait_One;
       		}
        	else {
            		State = Lock;
        	}
         break;

   	 case Wait_One:
        	if(PINA == 0x00) {
            		State = Wait_One;
        	}
        	else if(PINA == 0x02) {
            		State = Unlock_Two;
        	}
        	else {
            		State = Lock;
        	}
         break;

    	 case Unlock_Two:
       		if(PINA == 0x02) {
            		State = Unlock_Two;
        	}
        	else if(PINA == 0x00) {
         	   	State = Wait_Two;
        	}
         break;

    	case Wait_Two:
        	if(PINA == 0x80) {
            		State = Lock;
        	}
        	else if(PINA == 0x00) {
            		State = Wait_Two;
        	}
         break;
    	}

    switch (State) {
    	case Start:
    	PORTB = 0x00;
        break;
    	case Lock:
        PORTB = 0x00;
        break;
    	case Unlock_One:
        break;
   	case Wait_One:
        break;
    	case Unlock_Two:
        PORTB = 0x01;
    	case Wait_Two:
        break;
    }
}

int main(void)
{

    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

State = Start;
    while (1)
    {
        Tick();
    }

    return 1;
}
