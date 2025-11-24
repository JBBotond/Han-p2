/*
  MIC2 Week 3. Timers/Counters

  Author Janosi Barna-Botond
         2170302
  Date   24/11/2025
*/

#include <avr/io.h>
#include <util/delay.h>

#include "timer0.h"

int main(void) {
  // PB5-PB0 output
  DDRB |= 0b00111111;

  // PB7 input
  // PB7 is the button
  DDRB &= ~(1 << DDB7);

  // Initialize the millisecond counter
  timer0_init();

  // Global interrupt enable
  //  !!  this is important !!
  sei();

  uint32_t previousmillis = 0;
  uint32_t currentmillis = 0;
  uint32_t interval = 200;

  //port to be toggled for chaser
  int portToggle = 0;
  //  modifier to be added to portToggle
  //  modifier indicate direction
  int modifier = 1;

  while (1) {
    // Get the current millis
    currentmillis = timer0_millis();

      if ((PINB & (1 << PINB7)) == 0) {
        switch(modifier) {
          case 1:
            modifier = -1;
            break;
          case -1:
            modifier = 1;
            break;
        }
        //_delay_ms(30);
      }
    // Has 'interval' time passed since the last time we checked?
    if ((currentmillis - previousmillis) >= interval) {
      //read button input

      // Yes, 'interval' time has passed
      // Save the current millis
      previousmillis = currentmillis;

      // Toggle the LED
      //PORTB is initialized as 0b00000000
      PORTB = 0b00000000;
      PORTB |= (1 << portToggle);
      portToggle += modifier;
      if(portToggle > PORTB5)
        portToggle = PORTB0;
      if(portToggle < PORTB0)
        portToggle = PORTB5;
    }
  }
}
