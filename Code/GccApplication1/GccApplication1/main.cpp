/*
 * GccApplication1.cpp
 *
 * Created: 1/5/2024 4:56:51 PM
 * Author : 
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int overflow=0;
unsigned long int  Counter=0;
float distance=0.0;
int i = 0,j=1;
void masir_yabi (void);
void move_front (void);
void move_back (void);
void move_right (void);
void move_left (void);


ISR(TIMER0_OVF_vect)
{

	overflow++; 
	TCNT0=0x00;
//PORTB ^= (1 << PORTB0); 
}


int main(void)
{
   DDRC  = 0x0f;
   DDRD  = 0xf0;
   
   DDRA |= (1 << DDA0);
   DDRA &= ~(1 << DDA1);
   
   DDRB=0xff;
   
   TCCR0=0x02;
   TCNT0=0x00;
   OCR0=0x00;
   TIMSK|=(1<<TOIE0);
   	
	sei(); 	

  while (1) 
  {

		PORTA = 0X01;
		_delay_us(15);
		PORTA = 0X00;
		
	while(!((PINA & (1 << PINA1)) == (1 << PINA1)));
		overflow=0;
		TCNT0=0;
		TCCR0=0x02;	
		
		
			
	while(((PINA & (1 << PINA1)) == (1 << PINA1)));
		TCCR0=0x00;
		
		Counter=(overflow*256)+TCNT0;
		distance=(Counter/2)*0.03432 ;
		
		if(Counter < 30000)
		{		
			if(distance <5)
			{
				PORTB = 0b00000001;
				PORTD  = 0x00;
				PORTC  = 0x00;				
			}else
			{
			PORTB = 0b00000000;
			i++;
			if (i==1)
			{
				move_front();
			}else if (i==10)
			{
				move_back();
					
			}else if (i==20)
			{
				move_right();
					
			}
			else if (i==30)
			{
				move_left();
				
			}
			else if (i==40)
			{
				i=0;			
			}
			

			}
		   
		  _delay_ms(500);
		}

	
       

					   
  }
}
void masir_yabi (void)
{
	move_front();
	_delay_ms(1000);
	move_right();
	_delay_ms(1000);
	move_left();
	_delay_ms(1000);
	move_back();
	_delay_ms(1000);
	PORTD  = 0;
	PORTC  = 0;
}

void move_front (void)
{
PORTD  = 0B00010000;
PORTC  = 0B00000101;		
}
void move_back  (void){
 PORTD = 0B00100000;
PORTC = 0B00001010;
}
void move_right (void)
{
PORTD = 0B01000000;
PORTC = 0B00001000;
}
void move_left (void)
{
PORTD = 0B10000000;
PORTC = 0B00000010;
}


/*
	while(((PINA & (1 << PINA1)) == (1 << PINA1)));
	
	
	overflow=0;
	TCNT0=0;
	TCCR0=0x02;

	while((PINA & (1 << PINA1)));
	
	TCCR0=0x00;
	Counter=(overflow*256)+TCNT0;
	distance=(Counter/2)*0.03432 ;
	PORTB = distance;
	
		PORTA |= (1 << PORTA0);
		_delay_us(10);
		PORTA &= (~(1 <<PORTA0));
		
		while(!(PINA & (1 << PINA1))){};
		
		overflow=0;
		TCNT0=0;
		TCCR0=0x02;
		
		while((PINA & (1 << PINA1))){};
		
		TCCR0=0x00;
		
		Counter=(overflow*256)+TCNT0;
		distance=(Counter/2)*0.03432 ;
		PORTB = distance;

				   if(Counter<30000) {
					   if(distance < 5)
					   {
						   PORTB |= (1 << 0);
						   }else{
						   PORTB &= (~(1 << 0));
					   }
					   
				   }
				   
				   
				   if ((PIND & (1 << PINA0)) == 0 )
				   {
					   PORTD  = 0B00010000;
					   PORTC  = 0B00000101;
				   }
				   else if((PIND & (1 << PINA1)) == 0 )
				   {
					   PORTD = 0B00100000;
					   PORTC = 0B00001010;
				   }
				   
				   else if((PIND & (1 << PINA2)) == 0 )
				   {
					   PORTD = 0B01000000;
					   PORTC = 0B00001000;
				   }
				   else if ((PIND & (1 << PINA3)) == 0 )
				   {
					   PORTD = 0B10000000;
					   PORTC = 0B00000010;
				   }
				   else{
					   
					   PORTD = 0;
					   PORTC = 0;
				   }
*/