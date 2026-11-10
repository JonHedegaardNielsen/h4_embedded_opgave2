#include "include/ProjectDefines.h"
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)
#include "include/uart.h"
#include <avr/io.h>
#include <util/delay.h>

#include "include/timer.h"

int main(void) {
  // 1 sekund timer
  TimerData *timer_data = setupTimer(15624);
  uart_init();
  uart1_init();

  while (1) {
    char c = uart_getchar();
    // c = c ^ 0x20;
    if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
      c ^= 0x20;
    }
    if (c) {
      uart_puts(&c);
      uart1_putchar(c);
    }
    if (timer_data->is_timer_reached) {
      char buffer[128];
      snprintf(buffer, sizeof(buffer), "Sekunder efter opstart: %d\r\n", timer_data->timer_count);
      uart_puts(buffer);
      uart1_puts(buffer);
      timer_data->is_timer_reached = false;
    }
  }
  free(timer_data);
}
