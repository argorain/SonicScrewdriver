#include "usart.h"

uint8_t tx_buffer_pos=0;

void USART_Init (uint16_t baud)
{
	/* Set baud rate */
	UBRR0H  = (uint8_t)((F_CPU/16/baud-1)>>8);
	UBRR0L  = (uint8_t)((F_CPU/16/baud-1)>>0);
	/* Enable receiver and transmitter */
	UCSR0B  = (1<<RXEN0)|(1<<TXEN0);

	/* Set frame format: 8data, none parity, 1 stop bit */
	UCSR0C  = (0<<UPM01)|(1<<UCSZ01)|(1<<UCSZ00);
}

uint8_t USART_Read (void)
{
	while (!(UCSR0A & (1<<RXC0)));	
	return UDR0;
}

void USART_Write (uint8_t byte)
{
	while (!( UCSR0A & (1<<UDRE0)));
	UDR0 = byte;
}

void USART_RX_Intrerrupt(uint8_t state)
{
	// RX Complete Interrupt Enable
	if (state)
	{
		UCSR0B |=  (1<<RXCIE0);
	}
	else
	{
		UCSR0B &= ~(1<<RXCIE0);
	}
}

void USART_UDRE_Intrerrupt(uint8_t state)
{
	// Data Register Empty interrupt
	if (state)
	{
		UCSR0B |=  (1<<UDRIE0);
	}
	else
	{
		UCSR0B &= ~(1<<UDRIE0);
	}
}

void USART_TX_Interrrupt(uint8_t state)
{
	if(state)
	{
		UCSR0B |=  (1<<TXCIE0);
	}
	else
	{
		UCSR0B &= ~(1<<TXCIE0);
	}
}