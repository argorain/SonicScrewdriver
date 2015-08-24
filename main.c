#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
    DDRB = (1 << DDB5);
    while(1)
    {
        // LED on
        PORTB = (1 << DDB5);
        _delay_ms(500);
        // LED off
        PORTB = 0;
        _delay_ms(100);
    }
}