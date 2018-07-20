#include<avr/io.h>
#include<util/delay.h>
#define lcd PORTB
#define rs  0
#define rw  1
#define en  2
void lcd_init();
void lcd_command(unsigned char);
void lcd_data(unsigned char);
void lcd_string(unsigned char *str);

int main()
{	//unsigned char d;

	DDRB = 0XFF;
	PORTD=0xFF;
	DDRD=0x00;
	unsigned int c=0;


	lcd_init();
	lcd_command(0x80);
	lcd_string("CAR PARKING");
	_delay_ms(250);
	
	while(1)
	{
		if((PIND&0b00000010)==0) //IF SENSOR WORKS AS A SWITCH
		{
			PORTD |=0b00000001;
		    lcd_command(0x80);	
			_delay_ms(50);
	        lcd_string("1-FILLED");
			c++;
		}
		else
		{
		    lcd_command(0x80);
			_delay_ms(50);
		    lcd_string("1-VACANT");
			c--;
		}
		if((PIND&0b00001000)==0)
		{
			PORTD |=0b0000100;
		    lcd_command(0x88);	
			_delay_ms(50);
	        lcd_string("2-FILLED");
			c++;
		}
		else
		{
		    lcd_command(0x88);
			_delay_ms(50);
		    lcd_string("2-VACANT");
			c--;
		}
		if((PIND&0b00100000)==0)
		{
			PORTD |=0b00010000;
		    lcd_command(0xc0);	
			_delay_ms(50);
	        lcd_string("3-FILLED");
			c++;
		}
		else
		{
		    lcd_command(0xc0);
			_delay_ms(50);
		    lcd_string("3-VACANT");
			c--;
		}
		if((PIND&0b10000000)==0)
		{
			PORTD|=0b01000000;
		    lcd_command(0xc8);	
			_delay_ms(50);
	        lcd_string("4-FILLED");
			c++;
		}
		else
		{
		    lcd_command(0xc8);
			_delay_ms(50);
		    lcd_string("4-VACANT");
			c--;
		}
		if(c==4)
		{
			lcd_command(0x80);
			_delay_ms(100);
			lcd_string("Entry Full");			//gate closed
		}
		else
		{
			//gate open
		}
	}
		  
	return 0;
}
void lcd_init()
{
	lcd_command(0x02);
 	lcd_command(0x28);
	lcd_command(0x06);
	lcd_command(0x0c);
}
void lcd_command(unsigned char com)
	{
	lcd = com & 0xF0;		//send higher bit

	lcd &= ~(1<<rs); 		//rs =0
	lcd &= ~(1<<rw);		//rw =0
	lcd |=(1<<en);			//en =1
	_delay_ms(1);
	lcd &= ~(1<<en);		//en =0
	_delay_ms(1);

	lcd = (com<<4) & 0xF0;	//send lower bit

	lcd &= ~(1<<rs); 		//rs =0
	lcd &= ~(1<<rw);		//rw =0
	lcd |=(1<<en);			//en =1
	_delay_ms(1);
	lcd &= ~(1<<en);		//en =0
	_delay_ms(1);
	}
void lcd_data(unsigned char value)
	{

	lcd =value & 0xF0;		//send higher bit

	lcd |= (1<<rs); 		//rs =1
	lcd &= ~(1<<rw);		//rw =0
	lcd |=(1<<en);			//en =1
	_delay_ms(1);
	lcd &= ~(1<<en);		//en =0
	_delay_ms(1);


	lcd =(value<<4) & 0xF0;	//send lower bit

	lcd |= (1<<rs); 		//rs =1
	lcd &= ~(1<<rw);		//rw =0
	lcd |=(1<<en);			//en =1
	_delay_ms(1);
	lcd &= ~(1<<en);		//en =0
	_delay_ms(1);
	}

void lcd_string(unsigned char *str)
{
	char i=0;
	while(str[i]!='\0')
	{
	lcd_data(str[i]);
	i++;
	}
}