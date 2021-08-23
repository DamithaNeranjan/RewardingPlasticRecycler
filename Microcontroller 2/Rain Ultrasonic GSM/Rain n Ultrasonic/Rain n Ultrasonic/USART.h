#ifndef USART
#define USART

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000UL
#define BAUD 9600
#define MYUBRR  F_CPU/1UL/BAUD-1


void usart_init();
void usart_string_transmit(char *string);
void usart_data_transmit(unsigned char data );
unsigned char usart_data_receive( void );

void usart_init()
{
	UBRRH = 0;
	UBRRL =51;                                        // MYUBRR
	UCSRB|= (1<<RXEN)|(1<<TXEN);       // Enable Rx & Tx pin
	UCSRC |=(1 << URSEL)|(3<<UCSZ0); // 8 bit data  
	
}

void usart_data_transmit(unsigned char data )
{
	while ( !( UCSRA & (1<<UDRE)))
	;
	UDR = data;
	_delay_ms(1);
}

void usart_string_transmit(char *string)
{
	while(*string)
	{
		usart_data_transmit(*string++);
	}
}

unsigned char usart_data_receive( void )
{
	while ( !(UCSRA & (1<<RXC)) )        // ((UCSRA & (1 << RXC)) == 0)
	;
	return UDR;
}


#endif