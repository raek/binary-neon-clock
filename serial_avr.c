#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "serial.h"

void serial_init(void)
{
    uint16_t ubbr = (F_CPU / 16UL / BAUD_RATE) - 1;
    UCSR0A = ((0<<RXC0) |
              (0<<TXC0) |
              (0<<UDRE0) |
              (0<<FE0) |
              (0<<UPE0) |
              (0<<U2X0) |
              (0<<MPCM0));
    UCSR0B = ((0<<RXCIE0) |
              (0<<TXCIE0) |
              (0<<UDRIE0) |
              (1<<RXEN0) |
              (1<<TXEN0) |
              (0<<UCSZ02) |
              (0<<RXB80) |
              (0<<TXB80));
    UCSR0C = ((0<<UMSEL01) |
              (0<<UMSEL00) |
              (0<<UPM01) |
              (0<<UPM00) |
              (0<<USBS0) |
              (1<<UCSZ01) |
              (1<<UCSZ00) |
              (0<<UCPOL0));
    UBRR0H = (uint8_t) (ubbr>>8);
    UBRR0L = (uint8_t) ubbr;
}

void serial_putc(char c)
{
    UDR0 = (uint8_t) c;
    while (!(UCSR0A & (1<<TXC0))) {
    }
    UCSR0A |= (1<<TXC0);
}