/*
 * KeyPadTest1.c
 *
 * Created: 1/14/2020 11:36:44 PM
 * Author : bad
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>

////////////////LCD display////////////////
#include "i2c_lcd.h"
#include "i2cmaster.h"

#define BTN_1	0b00010001U
#define BTN_4	0b00010010U
#define BTN_7	0b00010100U
#define BTN_STR	0b00011000U
#define BTN_2	0b00100001U
#define BTN_5	0b00100010U
#define BTN_8	0b00100100U
#define BTN_0	0b00101000U
#define BTN_3	0b01000001U
#define BTN_6	0b01000010U
#define BTN_9	0b01000100U
#define BTN_HSH	0b01001000U
#define BTN_A	0b10000001U
#define BTN_B	0b10000010U
#define BTN_C	0b10000100U
#define BTN_D	0b10001000U
///////////////////////////////////////////


int main(void)
{
	
	char string[10];
	char string1[10];
	long count;
	int bot_count = 0;
	int x = 65;
	int charge_count = 0;
	int cnt;
	
	double distance;
	lcd_init(LCD_BACKLIGHT_ON);
	lcd_goto_xy(0, 0);
	lcd_clear();
	DDRA = 0x01;		/* Make trigger pin as output */
	PORTD = 0xFF;		/* Turn on Pull-up */

    int flag = 1;
    //lcd_init(LCD_BACKLIGHT_ON);
    
    register unsigned char keypressed_bot_count;//integer for storing matrix value
	register unsigned char keypressed;//integer for storing matrix value
    DDRA = 0xFF;

    DDRA = 0xF0;//taking column pins as input and row pins as output
    _delay_ms(1);

    PORTA = 0x0F;// powering the row ins

    _delay_ms(1);
    
    //lcd_puts("Welcome");
    while (flag == 1) 
    {
		lcd_goto_xy(0,0);
		lcd_puts("Enter number");
		lcd_goto_xy(0,1);
		 lcd_puts("of bottles");

		
		if(PINA != 0b11110000)
		{
			_delay_ms(5);
			keypressed = PINA;//taking the column value into integer
			DDRA ^= 0b11111111;//making rows as inputs and columns as output
			_delay_ms(1);
			PORTA ^= 0b11111111;//powering columns
			
			_delay_ms(1);
			
			keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
			//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
			
			if(keypressed == BTN_1)
			{
				bot_count = 1;
				
				while (flag == 1) 
				{
					//flag = 0;
					lcd_clear();
					lcd_clear();
					lcd_goto_xy(0,0);
					//lcd_puts("  ");
					lcd_puts("Press *");
					lcd_goto_xy(0,1);
					lcd_puts("when done");
					_delay_ms(500);
			
					if(PINA != 0b11110000)
					{
						_delay_ms(5);
						keypressed = PINA;//taking the column value into integer
						DDRA ^= 0b11111111;//making rows as inputs and columns as output
						_delay_ms(1);
						PORTA ^= 0b11111111;//powering columns
				
						_delay_ms(1);
				
						keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
						//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
				
						if(keypressed == BTN_STR)
						{
							lcd_clear();
							lcd_goto_xy(0,0);
							lcd_puts("");
							lcd_puts("A.Coins");
							lcd_goto_xy(0,1);
							lcd_puts("B.Water");
							lcd_puts("");
							lcd_goto_xy(-4,2);
							lcd_puts("C.Charging");
							lcd_puts("");
							lcd_goto_xy(-4,3);
							lcd_puts("D.Donate");
					
							while(flag == 1)
							{
								if(PINA != 0b11110000)
								{
									_delay_ms(5);
									keypressed = PINA;//taking the column value into integer
									DDRA ^= 0b11111111;//making rows as inputs and columns as output
									_delay_ms(1);
									PORTA ^= 0b11111111;//powering columns
							
									_delay_ms(1);
							
									keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
									//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
							
									if(keypressed == BTN_A)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Collect coins");
										
										//int cnt;
										
										for(cnt = 1; cnt <= 1; cnt++)
										{
 											OCR1A = 65;	/* Set servo shaft at -90� position */
 											_delay_ms(1000);
 											OCR1A = 300;	/* Set servo shaft at 0� position */
 											_delay_ms(1000);
										}
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_B)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Collect water");
										
										DDRD |= (1<<PD0);
										
  										PORTD &= ~(1 << PD0); //Set PD0 low
  										_delay_ms(4000);
  										PORTD |= (1 << PD0); //Set PD0 high
										
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_C)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Charge device");
										DDRD |= (1<<PD2);
										PORTD &= ~(1 << PD2); //Set PD2 low
										_delay_ms(10000);
										PORTD |= (1 << PD2); //Set PD2 high
										
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_D)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("D.Donate");
										_delay_ms(2000);
										
										flag = 0;
										bot_count = 0;
										break;
									}
								}
							}
						}
					}
				}
				flag = 1;
			}
			if(keypressed == BTN_2)
			{
				bot_count = 1;
				
				while (flag == 1)
				{
					lcd_clear();
					lcd_goto_xy(0,0);
					lcd_puts("     ");
					lcd_puts("Press * when done");
					_delay_ms(800);
					
					if(PINA != 0b11110000)
					{
						_delay_ms(5);
						keypressed = PINA;//taking the column value into integer
						DDRA ^= 0b11111111;//making rows as inputs and columns as output
						_delay_ms(1);
						PORTA ^= 0b11111111;//powering columns
						
						_delay_ms(1);
						
						keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
						//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
						
						if(keypressed == BTN_STR)
						{
							lcd_clear();
							lcd_goto_xy(0,0);
							lcd_puts("     ");
							lcd_puts("A.Coins");
							lcd_goto_xy(0,1);
							lcd_puts("B.Water");
							lcd_puts("");
							lcd_goto_xy(-4,2);
							lcd_puts("C.Charging");
							lcd_puts("");
							lcd_goto_xy(-4,3);
							lcd_puts("D.Donate");
							
							while(flag == 1)
							{
								if(PINA != 0b11110000)
								{
									_delay_ms(5);
									keypressed = PINA;//taking the column value into integer
									DDRA ^= 0b11111111;//making rows as inputs and columns as output
									_delay_ms(1);
									PORTA ^= 0b11111111;//powering columns
									
									_delay_ms(1);
									
									keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
									//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
									
									if(keypressed == BTN_A)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     "); 
										lcd_puts("Collect coins");
										
										//int cnt;
										for(cnt = 1; cnt <= 2; cnt++)
										{
											OCR1A = 65;	/* Set servo shaft at -90� position */
											_delay_ms(1000);
											OCR1A = 300;	/* Set servo shaft at 0� position */
											_delay_ms(1000);
											
										}
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_B)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Collect water");
										
										DDRD |= (1<<PD0);
										
 										PORTD &= ~(1 << PD0); //Set PD0 low
 										_delay_ms(4000);
 										PORTD |= (1 << PD0); //Set PD0 high
										
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_C)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Charge device");
										DDRD |= (1<<PD2);
										PORTD &= ~(1 << PD2); //Set PD2 low
										_delay_ms(20000);
										PORTD |= (1 << PD2); //Set PD2 high
										
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_D)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("D.Donate");
										_delay_ms(2000);
										
										flag = 0;
										bot_count = 0;
										break;
									}
								}
							}
						}
					}
				}
				flag = 1;
			}
			if(keypressed == BTN_3)
			{
				bot_count = 1;
				
				while (flag == 1)
				{
					lcd_clear();
					lcd_goto_xy(0,0);
					lcd_puts("     ");
					lcd_puts("Press * when done");
					_delay_ms(800);
					
					if(PINA != 0b11110000)
					{
						_delay_ms(5);
						keypressed = PINA;//taking the column value into integer
						DDRA ^= 0b11111111;//making rows as inputs and columns as output
						_delay_ms(1);
						PORTA ^= 0b11111111;//powering columns
						
						_delay_ms(1);
						
						keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
						//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
						
						if(keypressed == BTN_STR)
						{
							lcd_clear();
							lcd_goto_xy(0,0);
							lcd_puts("     ");
							lcd_puts("A.Coins");
							lcd_goto_xy(0,1);
							lcd_puts("B.Water");
							lcd_puts("");
							lcd_goto_xy(-4,2);
							lcd_puts("C.Charging");
							lcd_puts("");
							lcd_goto_xy(-4,3);
							lcd_puts("D.Donate");
							
							while(flag == 1)
							{
								if(PINA != 0b11110000)
								{
									_delay_ms(5);
									keypressed = PINA;//taking the column value into integer
									DDRA ^= 0b11111111;//making rows as inputs and columns as output
									_delay_ms(1);
									PORTA ^= 0b11111111;//powering columns
									
									_delay_ms(1);
									
									keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
									//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
									
									if(keypressed == BTN_A)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Collect coins");
										
										for(cnt = 1; cnt <= 3; cnt++)
										{
											OCR1A = 65;	/* Set servo shaft at -90� position */
											_delay_ms(1000);
											OCR1A = 300;	/* Set servo shaft at 0� position */
											_delay_ms(1000);

											bot_count++;
											
										}
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_B)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Collect water");
										
										DDRD |= (1<<PD0);
										
										PORTD &= ~(1 << PD0); //Set PD0 low
										_delay_ms(4000);
										PORTD |= (1 << PD0); //Set PD0 high
										
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_C)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Charge device");
										DDRD |= (1<<PD2);
										PORTD &= ~(1 << PD2); //Set PD2 low
										_delay_ms(30000);
										PORTD |= (1 << PD2); //Set PD2 high
										
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_D)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("D.Donate");
										_delay_ms(2000);
										
										flag = 0;
										bot_count = 0;
										break;
									}
								}
							}
						}
					}
				}
				flag = 1;
			}
			if(keypressed == BTN_4)
			{
				bot_count = 1;
				
				while (flag == 1)
				{
					lcd_clear();
					lcd_goto_xy(0,0);
					lcd_puts("     ");
					lcd_puts("Press * when done");
					_delay_ms(800);
					
					if(PINA != 0b11110000)
					{
						_delay_ms(5);
						keypressed = PINA;//taking the column value into integer
						DDRA ^= 0b11111111;//making rows as inputs and columns as output
						_delay_ms(1);
						PORTA ^= 0b11111111;//powering columns
						
						_delay_ms(1);
						
						keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
						//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
						
						if(keypressed == BTN_STR)
						{
							lcd_clear();
							lcd_goto_xy(0,0);
							lcd_puts("     ");
							lcd_puts("A.Coins");
							lcd_goto_xy(0,1);
							lcd_puts("B.Water");
							lcd_puts("");
							lcd_goto_xy(-4,2);
							lcd_puts("C.Charging");
							lcd_puts("");
							lcd_goto_xy(-4,3);
							lcd_puts("D.Donate");
							
							while(flag == 1)
							{
								if(PINA != 0b11110000)
								{
									_delay_ms(5);
									keypressed = PINA;//taking the column value into integer
									DDRA ^= 0b11111111;//making rows as inputs and columns as output
									_delay_ms(1);
									PORTA ^= 0b11111111;//powering columns
									
									_delay_ms(1);
									
									keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
									//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
									
									if(keypressed == BTN_A)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Collect coins");
										
										for(cnt = 1; cnt <= 4; cnt++)
										{
											OCR1A = 65;	/* Set servo shaft at -90� position */
											_delay_ms(1000);
											OCR1A = 300;	/* Set servo shaft at 0� position */
											_delay_ms(1000);
						
											bot_count++;
											
										}
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_B)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Collect water");
										
										DDRD |= (1<<PD0);


										PORTD &= ~(1 << PD0); //Set PD0 low
										_delay_ms(4000);
										PORTD |= (1 << PD0); //Set PD0 high
										
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_C)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Charge device");
										DDRD |= (1<<PD2);
										PORTD &= ~(1 << PD2); //Set PD2 low
										_delay_ms(40000);
										PORTD |= (1 << PD2); //Set PD2 high
										
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_D)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("D.Donate");
										_delay_ms(2000);
										
										flag = 0;
										bot_count = 0;
										break;
									}
								}
							}
						}
					}
				}
				flag = 1;
			}
			if(keypressed == BTN_5)
			{
				bot_count = 1;
				
				while (flag == 1)
				{
					lcd_clear();
					lcd_goto_xy(0,0);
					lcd_puts("     ");
					lcd_puts("Press * when done");
					_delay_ms(800);
					
					if(PINA != 0b11110000)
					{
						_delay_ms(5);
						keypressed = PINA;//taking the column value into integer
						DDRA ^= 0b11111111;//making rows as inputs and columns as output
						_delay_ms(1);
						PORTA ^= 0b11111111;//powering columns
						
						_delay_ms(1);
						
						keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
						//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
						
						if(keypressed == BTN_STR)
						{
							lcd_clear();
							lcd_goto_xy(0,0);
							lcd_puts("     ");
							lcd_puts("A.Coins");
							lcd_goto_xy(0,1);
							lcd_puts("B.Water");
							lcd_puts("");
							lcd_goto_xy(-4,2);
							lcd_puts("C.Charging");
							lcd_puts("");
							lcd_goto_xy(-4,3);
							lcd_puts("D.Donate");
							
							while(flag == 1)
							{
								if(PINA != 0b11110000)
								{
									_delay_ms(5);
									keypressed = PINA;//taking the column value into integer
									DDRA ^= 0b11111111;//making rows as inputs and columns as output
									_delay_ms(1);
									PORTA ^= 0b11111111;//powering columns
									
									_delay_ms(1);
									
									keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
									//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
									
									if(keypressed == BTN_A)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Collect coins");
										
										for(cnt = 1; cnt <= 5; cnt++)
										{
											OCR1A = 65;	/* Set servo shaft at -90� position */
											_delay_ms(1000);
											OCR1A = 300;	/* Set servo shaft at 0� position */
											_delay_ms(1000);
											
											bot_count++;
											
										}
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_B)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Collect water");
										
										DDRD |= (1<<PD0);

										PORTD &= ~(1 << PD0); //Set PD0 low
										_delay_ms(4000);
										PORTD |= (1 << PD0); //Set PD0 high
										
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_C)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Charge device");
										DDRD |= (1<<PD2);
										PORTD &= ~(1 << PD2); //Set PD2 low
										_delay_ms(50000);
										PORTD |= (1 << PD2); //Set PD2 high
										
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_D)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("D.Donate");
										_delay_ms(2000);
										
										flag = 0;
										bot_count = 0;
										break;
									}
								}
							}
						}
					}
				}
				flag = 1;
			}
			if(keypressed == BTN_6)
			{
				bot_count = 1;
				
				while (flag == 1)
				{
					lcd_clear();
					lcd_goto_xy(0,0);
					lcd_puts("     ");
					lcd_puts("Press * when done");
					_delay_ms(800);
					
					if(PINA != 0b11110000)
					{
						_delay_ms(5);
						keypressed = PINA;//taking the column value into integer
						DDRA ^= 0b11111111;//making rows as inputs and columns as output
						_delay_ms(1);
						PORTA ^= 0b11111111;//powering columns
						
						_delay_ms(1);
						
						keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
						//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
						
						if(keypressed == BTN_STR)
						{
							lcd_clear();
							lcd_goto_xy(0,0);
							lcd_puts("     ");
							lcd_puts("A.Coins");
							lcd_goto_xy(0,1);
							lcd_puts("B.Water");
							lcd_puts("");
							lcd_goto_xy(-4,2);
							lcd_puts("C.Charging");
							lcd_puts("");
							lcd_goto_xy(-4,3);
							lcd_puts("D.Donate");
							
							while(flag == 1)
							{
								if(PINA != 0b11110000)
								{
									_delay_ms(5);
									keypressed = PINA;//taking the column value into integer
									DDRA ^= 0b11111111;//making rows as inputs and columns as output
									_delay_ms(1);
									PORTA ^= 0b11111111;//powering columns
									
									_delay_ms(1);
									
									keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
									//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
									
									if(keypressed == BTN_A)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Collect coins");
										
										for(cnt = 1; cnt <= 6; cnt++)
										{
											OCR1A = 65;	/* Set servo shaft at -90� position */
											_delay_ms(1000);
											OCR1A = 300;	/* Set servo shaft at 0� position */
											_delay_ms(1000);
											
											bot_count++;
											
										}
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_B)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Collect water");
										
										DDRD |= (1<<PD0);
										
										PORTD &= ~(1 << PD0); //Set PD0 low
										_delay_ms(4000);
										PORTD |= (1 << PD0); //Set PD0 high
										
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_C)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Charge device");
										DDRD |= (1<<PD2);

										PORTD &= ~(1 << PD2); //Set PD2 low
										_delay_ms(60000);
										PORTD |= (1 << PD2); //Set PD2 high	
																		
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_D)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("D.Donate");
										_delay_ms(2000);
										
										flag = 0;
										bot_count = 0;
										break;
									}
								}
							}
						}
					}
				}
				flag = 1;
			}
			if(keypressed == BTN_7)
			{
				bot_count = 1;
				
				while (flag == 1)
				{
					lcd_clear();
					lcd_goto_xy(0,0);
					lcd_puts("     ");
					lcd_puts("Press * when done");
					_delay_ms(800);
					
					if(PINA != 0b11110000)
					{
						_delay_ms(5);
						keypressed = PINA;//taking the column value into integer
						DDRA ^= 0b11111111;//making rows as inputs and columns as output
						_delay_ms(1);
						PORTA ^= 0b11111111;//powering columns
						
						_delay_ms(1);
						
						keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
						//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
						
						if(keypressed == BTN_STR)
						{
							lcd_clear();
							lcd_goto_xy(0,0);
							lcd_puts("     ");
							lcd_puts("A.Coins");
							lcd_goto_xy(0,1);
							lcd_puts("B.Water");
							lcd_puts("");
							lcd_goto_xy(-4,2);
							lcd_puts("C.Charging");
							lcd_puts("");
							lcd_goto_xy(-4,3);
							lcd_puts("D.Donate");
							
							while(flag == 1)
							{
								if(PINA != 0b11110000)
								{
									_delay_ms(5);
									keypressed = PINA;//taking the column value into integer
									DDRA ^= 0b11111111;//making rows as inputs and columns as output
									_delay_ms(1);
									PORTA ^= 0b11111111;//powering columns
									
									_delay_ms(1);
									
									keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
									//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
									
									if(keypressed == BTN_A)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Collect coins");
										
										for(cnt = 1; cnt <= 7; cnt++)
										{
											OCR1A = 65;	/* Set servo shaft at -90� position */
											_delay_ms(1000);
											OCR1A = 300;	/* Set servo shaft at 0� position */
											_delay_ms(1000);
											
											bot_count++;
											
										}
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_B)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Collect water");
										
										DDRD |= (1<<PD0);
										
										PORTD &= ~(1 << PD0); //Set PD0 low
										_delay_ms(4000);
										PORTD |= (1 << PD0); //Set PD0 high
										
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_C)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Charge device");
										DDRD |= (1<<PD2);
										PORTD &= ~(1 << PD2); //Set PD2 low
										_delay_ms(70000);
										PORTD |= (1 << PD2); //Set PD2 high
										
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_D)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("D.Donate");
										_delay_ms(2000);
										
										flag = 0;
										bot_count = 0;
										break;
									}
								}
							}
						}
					}
				}
				flag = 1;
			}
			if(keypressed == BTN_8)
			{
				bot_count = 1;
				
				while (flag == 1)
				{
					lcd_clear();
					lcd_goto_xy(0,0);
					lcd_puts("     ");
					lcd_puts("Press * when done");
					_delay_ms(800);
					
					if(PINA != 0b11110000)
					{
						_delay_ms(5);
						keypressed = PINA;//taking the column value into integer
						DDRA ^= 0b11111111;//making rows as inputs and columns as output
						_delay_ms(1);
						PORTA ^= 0b11111111;//powering columns
						
						_delay_ms(1);
						
						keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
						//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
						
						if(keypressed == BTN_STR)
						{
							lcd_clear();
							lcd_goto_xy(0,0);
							lcd_puts("     ");
							lcd_puts("A.Coins");
							lcd_goto_xy(0,1);
							lcd_puts("B.Water");
							lcd_puts("");
							lcd_goto_xy(-4,2);
							lcd_puts("C.Charging");
							lcd_puts("");
							lcd_goto_xy(-4,3);
							lcd_puts("D.Donate");
							
							while(flag == 1)
							{
								if(PINA != 0b11110000)
								{
									_delay_ms(5);
									keypressed = PINA;//taking the column value into integer
									DDRA ^= 0b11111111;//making rows as inputs and columns as output
									_delay_ms(1);
									PORTA ^= 0b11111111;//powering columns
									
									_delay_ms(1);
									
									keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
									//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
									
									if(keypressed == BTN_A)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Collect coins");
										
										for(cnt = 1; cnt <= 8; cnt++)
										{
											OCR1A = 65;	/* Set servo shaft at -90� position */
											_delay_ms(1000);
											OCR1A = 300;	/* Set servo shaft at 0� position */
											_delay_ms(1000);
										
											bot_count++;
											
										}
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_B)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Collect water");
										
										DDRD |= (1<<PD0);
										
										PORTD &= ~(1 << PD0); //Set PD0 low
										_delay_ms(4000);
										PORTD |= (1 << PD0); //Set PD0 high
										
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_C)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Charge device");
										DDRD |= (1<<PD2);
										PORTD &= ~(1 << PD2); //Set PD2 low
										_delay_ms(80000);
										PORTD |= (1 << PD2); //Set PD2 high
										
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_D)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("D.Donate");
										_delay_ms(2000);
										
										flag = 0;
										bot_count = 0;
										break;
									}
								}
							}
						}
					}
				}
				flag = 1;
			}
			if(keypressed == BTN_9)
			{
				bot_count = 1;
				
				while (flag == 1)
				{
					lcd_clear();
					lcd_goto_xy(0,0);
					lcd_puts("     ");
					lcd_puts("Press * when done");
					_delay_ms(800);
					
					if(PINA != 0b11110000)
					{
						_delay_ms(5);
						keypressed = PINA;//taking the column value into integer
						DDRA ^= 0b11111111;//making rows as inputs and columns as output
						_delay_ms(1);
						PORTA ^= 0b11111111;//powering columns
						
						_delay_ms(1);
						
						keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
						//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
						
						if(keypressed == BTN_STR)
						{
							lcd_clear();
							lcd_goto_xy(0,0);
							lcd_puts("     ");
							lcd_puts("A.Coins");
							lcd_goto_xy(0,1);
							lcd_puts("B.Water");
							lcd_puts("");
							lcd_goto_xy(-4,2);
							lcd_puts("C.Charging");
							lcd_puts("");
							lcd_goto_xy(-4,3);
							lcd_puts("D.Donate");
							
							while(flag == 1)
							{
								if(PINA != 0b11110000)
								{
									_delay_ms(5);
									keypressed = PINA;//taking the column value into integer
									DDRA ^= 0b11111111;//making rows as inputs and columns as output
									_delay_ms(1);
									PORTA ^= 0b11111111;//powering columns
									
									_delay_ms(1);
									
									keypressed = ~(keypressed | PINA); //taking row value and OR ing it to column value
									//Similar to //kepressed |= PIND; keypressed ^= 0xFF;
									
									if(keypressed == BTN_A)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Collect coins");
										
										for(cnt = 1; cnt <= 9; cnt++)
										{
											OCR1A = 65;	/* Set servo shaft at -90� position */
											_delay_ms(1000);
											OCR1A = 300;	/* Set servo shaft at 0� position */
											_delay_ms(1000);
										
											bot_count++;
											
										}
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_B)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Collect water");
										
										DDRD |= (1<<PD0);
										
										PORTD &= ~(1 << PD0); //Set PD0 low
										_delay_ms(4000);
										PORTD |= (1 << PD0); //Set PD0 high
										
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_C)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("Charge device");
										DDRD |= (1<<PD2);
										PORTD &= ~(1 << PD2); //Set PD2 low
										_delay_ms(90000);
										PORTD |= (1 << PD2); //Set PD2 high
										
										flag = 0;
										bot_count = 0;
										break;
									}
									if(keypressed == BTN_D)
									{
										lcd_clear();
										lcd_goto_xy(0,0);
										lcd_puts("     ");
										lcd_puts("D.Donate");
										_delay_ms(2000);
										
										flag = 0;
										bot_count = 0;
										break;
									}
								}
							}
						}
					}
				}
				flag = 1;
			}
		}
	}
}
			
