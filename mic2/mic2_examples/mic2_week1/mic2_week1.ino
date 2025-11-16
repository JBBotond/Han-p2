/*
  MIC2 Week 1. Basics

  Author Janosi Barna-Botond
         2170302
  Date   10/11/2025
*/

//  PORTBx is just x
//  for example PORTB1 is just #define ... 1
#include <avr/io.h>
#include <util/delay.h>

int ledLit = 0;
//modifier can be -1, +1
//  it is to be added to ledLit
int modifier = 1;

int main(void) {
  //register in DDRB that all of these are outputs
  DDRB |= (1 << DDB0);
  DDRB |= (1 << DDB1);
  DDRB |= (1 << DDB2);
  DDRB |= (1 << DDB3);
  DDRB |= (1 << DDB4);
  DDRB |= (1 << DDB5);

  while (1) {
    //  turn on ledLit
    PORTB |= (1 << ledLit);
    _delay_ms(200);

    // turn off ledLit, increment
    PORTB &= ~(1 << ledLit);
    //  check for edge case here
    if(ledLit == PORTB5) {
      modifier = -1;
    }
    if(ledLit == PORTB0) {
      modifier = +1;
    }
    ledLit += modifier;
  }
}
