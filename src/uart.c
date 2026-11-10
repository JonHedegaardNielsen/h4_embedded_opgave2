#include <avr/interrupt.h>
#include <stdint.h>
#include <string.h>
#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)
#include <avr/io.h>
#include <util/delay.h>
#include "../include/ProjectDefines.h"
#define UBRR1_VALUE ((F_CPU / (16UL * BAUD)) - 1)

static Function_Pointer_With_One_CharPointer_Parameter Callback_Function_Pointer = NULL;
 
void SetupUARTFunctionCallbackPointer(Function_Pointer_With_One_CharPointer_Parameter 
                                      Function_To_Callback)
{
	Callback_Function_Pointer = Function_To_Callback;
}
void uart1_init(void)
{
    UBRR1H = (uint8_t)(UBRR1_VALUE >> 8);
    UBRR1L = (uint8_t)UBRR1_VALUE;

    UCSR1B = (1 << RXEN1) | (1 << TXEN1);
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10); // 8N1
}

void uart1_putchar(char c)
{
    while (!(UCSR1A & (1 << UDRE1)));
    UDR1 = c;
}

void uart1_puts(const char *s) {
  while (*s)
    uart1_putchar(*s++);
}

void uart_init(void) {
  UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
  UBRR0L = (uint8_t)UBRR_VALUE;

  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_putchar(char c) {
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  UDR0 = c;
}

void uart_puts(const char *s) {
  while (*s)
    uart_putchar(*s++);
}

char uart_getchar(void) {
  // interrupt når nogen skriver
  if ((UCSR0A & (1 << RXC0))) {
    return UDR0;
  }
  return 0;
}
