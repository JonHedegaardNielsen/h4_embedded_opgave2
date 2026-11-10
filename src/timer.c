#include "../include/ProjectDefines.h"
#include "../include/uart.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>
// koden der kører når tiden løber ud
uint32_t count = 0;
ISR(TIMER1_COMPA_vect) {
  count++;
  // PORTB ^= (1 << PB0);
  char buffer[128];
  snprintf(buffer, sizeof(buffer), "Sekunder efter opstart: %d\r\n", count);
  uart_puts(buffer);
  uart1_puts(buffer);
}

void setupTimer(uint32_t time) {
  // CTC mode
  TCCR1B |= (1 << WGM12);
  // 16MHz / 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // tid
  OCR1A = time;
  // Interrupt når OCR1A nås
  TIMSK1 |= (1 << OCIE1A);
  sei();
}
