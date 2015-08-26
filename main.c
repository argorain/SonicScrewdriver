#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "drivers/usart.h"

int main(void)
{
    DDRB = (1 << DDB5);

    USART_Init(9600);
    USART_RX_Intrerrupt(1);
    sei();
    


    while(1)
    {
        // LED on
        PORTB = (1 << DDB5);
        _delay_ms(500);
        // LED off
        PORTB = 0;
        _delay_ms(500);
    }
}

ISR (USART_RX_vect)
{
    char data = USART_Read();
    USART_Write(data);
}

