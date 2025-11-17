/*
  MIC2 Week 2. Digital

  Author Janosi Barna-Botond
         2170302
  Date   17/11/2025
*/
#include <avr/io.h>
#include <util/delay.h>



int main(void) {
  // Configure PB5 so it will be an output pin
  DDRB |= (1 << DDB0);
  DDRB |= (1 << DDB1);
  DDRB |= (1 << DDB2);
  DDRB |= (1 << DDB3);
  DDRB |= (1 << DDB4);
  DDRB |= (1 << DDB5);
  //DDRB |= 0b00111111

  // Configure PB7 so it will be an input pin
  // Notice that strictly speaking this instruction is redundant,
  // because after a reset, the initial value of this bit is already
  // logic 0.
  DDRB &= ~(1 << DDB7);
  //check for assignements sake
  //PB7 is surely an input pin
  DDRD &= ~(1 << DDD7);
  PORTD |= (1 << PORTD7);
  if((DDRB & (1 << DDB7)) == 0) {
    while (1) {
      //put chaser here
    }
  }
}

/*
      // Read the content from the PINB register and perform a bitwise-and
      // operation using the mask (1<<PINB7). Only if bit number 7 in the
      // PINB register is not set, the condition evaluates to True.
      //
      // Notice that when the switch is not pressed PB7 reads logic 1!
      // In other words: the condition in this if-statement is true when the
      // switch is pressed.
      if ((PINB & (1 << PINB7)) == 0) {
        // LED connected to PB5 on
        PORTB |= (1 << PORTB5);
      } else {
        // LED connected to PB5 off
        PORTB &= ~(1 << PORTB5);
      }
*/