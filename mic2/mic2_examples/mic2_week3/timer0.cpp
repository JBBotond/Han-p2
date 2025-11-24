/*
  MIC2 Week 3. Timers/Counters

    Author Janosi Barna-Botond
         2170302
  Date   24/11/2025
*/
#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer0.h"

static volatile uint32_t ms = 0;

void timer0_init(void) {
  ms = 0;

  // Configure Timer/counter 0 to generate an interrupt every millisecond
  //
  // TODO: Explain why the following settings configure
  //       Timer/counter 0 to generate an interrupt every millisecond.
  //  TOP - 1 = 249
  // T = 1/16 * 64 * (249 + 1)
  OCR0A = 249;    //this is output compare (what OUT will be comp to)
  TCCR0A = (1 << WGM01);  //  WGM00 AND WGM02 is 0 by default//setting CTC (clear timer on compare)
  TCCR0B = (1 << CS01) | (1 << CS00);   // choosing 64 prescaler
  TIMSK0 = (1 << OCIE0A);   //  setting this bit enables interrupt for 
}

// Interrupt Service Routine that is automatically executed as soon as
// timer/counter 0 has reached its compare value
ISR(TIMER0_COMPA_vect) {
  ms++;
}

uint32_t timer0_millis(void) {
  // ms is a 32-bit variable (uint32_t). This means that multiple accesses
  // are needed to read or write the value of ms. There is a chance that
  // in the middle of these multiple accesses, the ms value is written due
  // to the ISR being triggered. In order to make sure the value of ms is
  // not updated when reading it, disable interrupts while reading the
  // value.
  cli();
  uint32_t ret = ms;
  sei();

  return ret;
}
