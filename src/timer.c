#include "../include/ProjectDefines.h"
#include "../include/uart.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>
typedef struct {
  bool is_timer_reached;
  uint32_t timer_count;
} TimerData;
// koden der kører når tiden løber ud
TimerData *current_timer_data;
ISR(TIMER1_COMPA_vect) {
  current_timer_data->timer_count++;
  current_timer_data->is_timer_reached = true;
  PORTB ^= (1 << PB0);
}

TimerData *setupTimer(uint32_t time) {
  TimerData *timer_data = malloc(sizeof(TimerData));
  if (timer_data == NULL) {
    return NULL;
  }
  timer_data->is_timer_reached = false;
  timer_data->timer_count = 0;
  current_timer_data = timer_data;
  DDRB |= (1 << PB0);
  // CTC mode
  TCCR1B |= (1 << WGM12);
  // 16MHz / 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // tid
  OCR1A = time;
  // Interrupt når OCR1A nås
  TIMSK1 |= (1 << OCIE1A);

  sei();
  return timer_data;
}
