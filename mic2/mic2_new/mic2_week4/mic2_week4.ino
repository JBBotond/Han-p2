/*
  MIC2 Week 4. Communication

  Author <Student name>
         <Student number>
  Date   dd/mm/yyyy
*/
#include "util/delay.h"
#include "timer0.h"
#include "usart0.h"

int cnt = 0;

uint8_t buttonState = 1;
uint8_t prevButtonState = 1;

int main(void) {
  // PB0 - PB5 output, rest input
  DDRB = 0b00111111;

  // Initialize the millisecond counter
  timer0_init();
  uint32_t previousmillis = 0;
  uint32_t currentmillis = 0;
  uint32_t interval = 1000;

  // Initialize the USART
  usart0_init();

  sei();

  while (1) {
    // Get the current millis
    currentmillis = timer0_millis();

    // Has 'interval' time passed since the last time we checked?
    if ((currentmillis - previousmillis) >= interval) {
      // Yes, 'interval' time has passed
      // Save the current millis
      previousmillis = currentmillis;

      // Toggle the LED
      PORTB ^= (1 << PORTB5);

      // Print counter
      char str[32];
      sprintf(str, "cnt = %x\n", cnt);
      usart0_transmitStr(str);

      cnt++;
    }

    // ------------------------------------------------------------------------

    // Check for unread bytes in the receive buffer
    unsigned char nBytes = usart0_nUnread();

    //    handle incoming data here
    if (nBytes > 0) {
      char data = usart0_receive();

      if(data != '\n') {
        switch(data) {
          case 'x':
          case 'X':
            cnt = 0;
            usart0_transmitStr("Reset\n");
          break;

          case 's':
          case 'S':
            interval = 100;
            usart0_transmitStr("Interval set to 100ms\n");
          break;

          case 'd':
          case 'D':
            interval = 1000;
            usart0_transmitStr("Interval set to 1000ms\n");
          break;

          default:
            usart0_transmitStr("Uknown command\n");
        }
      }

    }
    // --------------------------------------
    //0 means pressed, 1 is released
    buttonState = PINB & (1 << PB7);
    //handle button stuff here
    if(buttonState != prevButtonState) {
      if(buttonState == 0) {
        usart0_transmitStr("SW0 pressed, reset\n");
        cnt = 0;
        _delay_ms(30);
      }
      prevButtonState = buttonState;
    }
  }

  return 0;
}
