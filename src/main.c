#include <avr/io.h>
#include <avr/interrupt.h>
#include "main.h"

char serial_buffer[BUFFER_LENGTH];
uint8_t buffer_pos = 0;

int main(void) {
	// Disable interrupts
	cli();

	// Set UART up
	UBRR0 = UBRR;
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	UCSR0B |= (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);

	// Set timer up
	TCCR0A = (1 << WGM01);
	TCCR0B |= (1 << CS02) | (1 << CS00); // Clock / 64 prescaler
	OCR0A = 250;
	TIMSK0 |= (1<<OCIE0A);

	// Set SPI up
	DDRB = (1 << PB5) | (1 << PB3) | (1 << PB2);
	SPCR = (1 << SPE) | (1 << MSTR);

	// Enable interrupts
	sei();

	// Endless loop
	//while (1);

	sendSPIchar(0b11111111);
	PORTB |= (1 << PB2);
	PORTB &= (1 << PB2);

	return 0;
}

#ifdef DEBUG
void sendUARTchar(char data) {
	UDR0 = data;
	while (!(UCSR0A & (1 << UDRE0)));
}
#endif

void sendSPIchar(char data) {
	 SPDR = data;
	 while(!(SPSR & (1 << SPIF)));
}

/*// UART reception event
ISR(USART_RX_vect) {
	serial_buffer[buffer_pos] = UDR0;
	buffer_pos++;

	// We have received a correct packet
	if (buffer_pos == BUFFER_LENGTH && serial_buffer[0] == 0x42) {
		buffer_pos = 0;

		#ifdef DEBUG
		sendUARTchar('o');
		sendUARTchar('k');
		#endif
	}
}

// 1KHz timer
ISR (TIMER0_COMPA_vect) {
	sendSPIchar(0b00000000);
	PORTB |= (1 << PB2);
	PORTB &= (1 << PB2);
}*/