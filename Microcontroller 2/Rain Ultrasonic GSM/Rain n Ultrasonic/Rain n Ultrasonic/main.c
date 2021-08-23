/*
 * Rain n Ultrasonic.c
 *
 * Created: 1/20/2020 8:59:26 PM
 * Author : bad
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "USART.h"
#define  Trigger_pin	PA0	/* Trigger pin */
//Echo PD6


unsigned char At[] = {"AT\n"};				   // AT to check GSM
unsigned char Meg_Mode[] = {"AT+CMGF=1\n"};	// Active message mode
unsigned char Meg_cmd1[] = {"AT+CMGS="};	   // message command
unsigned char Re_num[] = {"\"+94724262922\""}; // receivers number
	
unsigned char Gps_on[] = {"AT+CGNSPWR=1\n"};		 // Gps power on
unsigned char Get_Gps_location[] = {"AT+CGNSINF\n"}; // get location CGNSINF

char gsm_data_receive[20], emergency[50] = {"Water level low or Storage full ..."}, gps_data_recive[100], water[50] = {"Water Level Low ..."}, storage[50] = {"Storage Full ..."};
char longitude[15], latitude[15];
void Send_msg(void);


int TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;	/* Increment Timer Overflow count */
}

int main(void)
{
	//////////////////////////GSM//////////////////////////////////////////////
	
	usart_init(); // initialize USART (serial communication)
	
	int a;

	for (a = 0; Gps_on[a] != '\0'; a++) // GPS power on

	{
		usart_data_transmit(Gps_on[a]);
		_delay_ms(50);
	}
	
	for (a = 0; Get_Gps_location[a] != '\0'; a++) // get location CGNSINF

	{
		usart_data_transmit(Get_Gps_location[a]);
		//_delay_ms(10);
	}

	for (int q = 0; q < 68; q++)
	{
		gps_data_recive[q] = usart_data_receive();
	}
	
	for (int q = 48; q < 56; q++)
	{
		longitude[q-48] = gps_data_recive[q];
	}
	
	for (int q = 57; q < 66; q++)
	{
		latitude[q-57] = gps_data_recive[q];
	}
	
	bool b = 0;
	//DDRA=0x00;
	
	///////////////////////////////////////////////////////////////////////////
	
	
	//////////////////////////Ultrasonic///////////////////////////////////////
	long count;
	double distance;
	DDRA = 0x01;		/* Make trigger pin as output */
	PORTD = 0b01000000;		/* Turn on Pull-up */
	sei();			/* Enable global interrupt */
	TIMSK = (1 << TOIE1);	/* Enable Timer1 overflow interrupts */
	TCCR1A = 0;		/* Set all bit to zero Normal operation */
	
	///////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////Rain///////////////////////////////////
	DDRD = 0x00;
	DDRB = 0b00000011;

	PORTD &= ~(1 << PD4); // Pin n goes low

	//////////////////////////////////////////////////////////////////////
	
	
	while (1)
	{
		
		
		//////////////////////////Ultrasonic///////////////////////////////////////
		PORTA |= (1 << Trigger_pin);
		_delay_us(10);
		PORTA &= (~(1 << Trigger_pin));
		
		TCNT1 = 0;	/* Clear Timer counter */
		TCCR1B = 0x41;	/* Capture on rising edge, No prescaler*/
		TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
		TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */

		/*Calculate width of Echo by Input Capture (ICP) */
		
		while ((TIFR & (1 << ICF1)) == 0);/* Wait for rising edge */
		TCNT1 = 0;	/* Clear Timer counter */
		TCCR1B = 0x01;	/* Capture on falling edge, No prescaler */
		TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
		TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */
		TimerOverflow = 0;/* Clear Timer overflow count */

		while ((TIFR & (1 << ICF1)) == 0);/* Wait for falling edge */
		count = ICR1 + (65535 * TimerOverflow);	/* Take count */
		/* 8MHz Timer freq, sound speed =343 m/s */
		distance = (double)count / 466.47;
		if(distance<=10)
		{
			
			PORTB=0b00000010;
			if(b == 0)
			{
				//b = 1;
				_delay_ms(5000);
				strcat(emergency, longitude);
				strcat(emergency, latitude);
				Send_msg();
				_delay_ms(5000);
			}

		}
		
		else{
		
			PORTB=0b00000000;
		}
		
		///////////////////////////////////////////////////////////////////////////
		
		////////////////////////////Rain///////////////////////////////////////////
		
		if (PIND & (1<<PD4))
		{
			PORTB = 0b00000000;
		}
		else
		{
			PORTB = 0b00000001;
			if(b == 0)
			{
				//b = 1;
				_delay_ms(5000);
				strcat(emergency, longitude);
				strcat(emergency, latitude);
				Send_msg();
				_delay_ms(5000);
			}

		}
		
		///////////////////////////////////////////////////////////////////////////
		
		/////////////////////////////GSM///////////////////////////////////////////
		
// 		if(b == 0)
// 		{
// 			b = 1;
// 			_delay_ms(5000);
// 			strcat(emergency, longitude);
// 			strcat(emergency, latitude);
// 			Send_msg();
// 			_delay_ms(5000);
// 		}
		
		///////////////////////////////////////////////////////////////////////////
	}
}

/////////////////////////////GSM///////////////////////////////////////////

void Send_msg(void)
{
	int a;
	for (a = 0; At[a] != '\0'; a++)

	{
		usart_data_transmit(At[a]);
		//_delay_ms(10);
	}
	_delay_ms(100);

	for (a = 0; Meg_Mode[a] != '\0'; a++)
	{
		usart_data_transmit(Meg_Mode[a]);
		//_delay_ms(10);
	}
	_delay_ms(100);

	for (a = 0; Meg_cmd1[a] != '\0'; a++)
	{
		usart_data_transmit(Meg_cmd1[a]);
		//_delay_ms(1);
	}
	_delay_ms(100);

	for (a = 0; Re_num[a] != '\0'; a++)
	{
		usart_data_transmit(Re_num[a]);
		//_delay_ms(10);
	}
	usart_data_transmit(13); //UDR=(13);    //  <CR> character
	_delay_ms(100);

	for (a = 0; emergency[a] != '\0'; a++)
	{
		usart_data_transmit(emergency[a]);
		//_delay_ms(10);
	}
	usart_data_transmit(26);
	_delay_ms(100);
	
}

///////////////////////////////////////////////////////////////////////////