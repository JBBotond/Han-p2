#include <avr/io.h>
#include <avr/interrupt.h>
#include "hcsr04.h"

static volatile uint16_t hcsr04_distance_cm = 0;

// Interrupt handler
ISR(PCINT0_vect) {
  static uint16_t timer_start = 0;
  static uint16_t timer_stop = 0;
  // To be implemented …
}
void hcsr04_init(void) {
  //set PB1 as output, PB0 is already input
  DDRB = 0b00000010;
  
  //pulse of 10uS here
  // - WGM1[3:0] = 1110 : waveform generation mode is Fast PWM with TOP in ICR1
  // - CS1[2:0] = 011 : 64 prescaler
  //
  // TOP = (F_CPU / (F_PWM * N)) - 1
  // = (16 MHz / (10 Hz * 64)) - 1
  // = 24999
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10);
  ICR1 = 24999;
}
uint16_t hcsr04_read(void) {
  return hcsr04_distance_cm;
}
