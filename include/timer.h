#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#ifndef TIMER_H
#define TIMER_H
typedef struct {
  bool is_timer_reached;
  uint32_t timer_count;
} TimerData;
TimerData *setupTimer(uint32_t time);
#endif
