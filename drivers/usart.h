#ifndef __USART_H__
#define __USART_H__

#include <avr/io.h> 		

/// Enable UART Transmitter macro
#define EnableUartTransmitter()     (UCSR0B |=  ((1 << UDRIE0) | ( 1 << TXEN0)))
/// Disable UART Transmitter macro
#define DisableUartTransmitter()    (UCSR0B &= ~((1 << UDRIE0) | ( 1 << TXEN0)))
/// Enable UART Receiver macro
#define EnableUartReceiver()        (UCSR0B |=  ((1 << RXCIE0) | ( 1 << RXEN0)))
/// Disable UART Receiver macro
#define DisableUartReceiver()       (UCSR0B &= ~((1 << RXCIE0) | ( 1 << RXEN0)))
/// Test for Transmitter enabled
#define IsUartTransmitterEnabled()  (UCSR0B &   (1 << TXEN0))
/// Test for Receiver enabled
#define IsUartReceiverEnabled()     (UCSR0B &   (1 << RXEN0))
/// Test for Transmit completed
#define UartTransmitIsComplete()    ((UCSR0A &  (1 << TXC0)) != 0)
/// Test if UART completed transmission
#define UartClearTransmitComplete() (UCSR0A |=  (1 << TXC0))
/// Check for RX errors
#define UartRxErrorsMask            ( (1 << FE0) | (1 << DOR0) | ( 1 << UPE0) )


void USART_Init(uint16_t baud);
uint8_t USART_Read(void);
void USART_Write(uint8_t byte);
void USART_RX_Intrerrupt(uint8_t state);
void USART_UDRE_Intrerrupt(uint8_t state);
void USART_TX_Interrrupt(uint8_t state);

#endif

