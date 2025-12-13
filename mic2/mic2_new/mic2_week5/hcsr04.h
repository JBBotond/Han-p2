/*
  MIC2 Week 5. HC-SR04 driver
  Author <Student name>
  <Student number>
  Date dd/mm/yyyy
*/
#ifndef HCSR04_H

#define HCSR04_H

#include <stdint.h>

void hcsr04_init(void);

uint16_t hcsr04_read(void);

#endif // HCSR04_H
