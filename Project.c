#include <reg51.h>

// Function Declarations
void delay(void);
void LCD_Ready(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_init(void);
void display_temp(unsigned char);
void display_gas(float);
void convert_display_LCD(float);

// ADC
sbit CS = P2^0;
sbit Read = P2^1;
sbit Write = P2^2;
sbit INTR = P2^3;

// Sensor
sbit temperature = P2^4;

// LED Outputs
sbit LED_1 = P3^2;
sbit LED_2 = P3^3;

// LCD Display
sbit RS = P2^5;
sbit RW = P2^6;
sbit EN = P2^7;
sbit busy = P1^7;

// A threshold value for the gas sensor output
float threshold = 3.0;

int main(void)
{
	float value;
	unsigned char temp;
	
	// LED Outputs
	LED_1 = 0;
	LED_2 = 0;
	
	// LCD Display
	RS = 0;
	RW = 0;
	EN = 0;
	busy = 0;
	P1 = 0x00;
	LCD_init();
	
	// ADC
	P0 = 0xFF;
	CS = 0;
	INTR = 1;
	Read = 1;
	Write = 1;
	temperature = 1;
	
	// ADC Logic
	while(1)
	{
		Write = 0;
		Write = 1;
		while(INTR);
		Read = 0;
		value = P0*5.0/256.0;
		temp = temperature;
		display_temp(temp);
		display_gas(value);
		Read = 1;
	}
	return 0;
}

void delay(void) // Delay Subroutine
{
	TMOD = 0x01;
	TL0 = 0x00;
	TH0 = 0x00;
	TR0 = 1;
	while(!TF0);
	TR0 = 0;
	TF0 = 0;
}

void LCD_Ready(void) // Subroutine to check if LCD is busy
{
	busy = 1;
	RS = 0;
	RW = 1;
	do
	{
		EN = 0;
		delay();
		EN = 1;
	}while(busy);
	busy = 0;
}

void LCD_CMD(unsigned char CMD) // Subroutine to send a command to LCD
{
	LCD_Ready();
	P1 = CMD;
	RS = 0;
	RW = 0;
	EN = 1;
	delay();
	EN = 0;
}

void LCD_DATA(unsigned char DATA) // Subroutine to send data to LCD
{
	LCD_Ready();
	P1 = DATA;
	RS = 1;
	RW = 0;
	EN = 1;
	delay();
	EN = 0;
}

void LCD_init(void) // Subroutine to initialize LCD
{
	unsigned char msg1[] = "TEMP: ", msg2[] = "GAS: ", i;
	LCD_CMD(0x38);
	LCD_CMD(0x0E);
	LCD_CMD(0x01);
	LCD_CMD(0x80);
	for( i = 0 ; i < (sizeof(msg1)/sizeof(msg1[0]))-1 ; i++ )
		LCD_DATA(msg1[i]);
	LCD_CMD(0xC0);
	for( i = 0 ; i < (sizeof(msg2)/sizeof(msg2[0]))-1 ; i++ )
		LCD_DATA(msg2[i]);
}

void display_temp(unsigned char temp) // Subroutine to display Temperature Sensor data on LCD
{
	LED_1 = temp;
	LCD_CMD(0x8B);
	LCD_DATA(temp+48);
	delay();
}

void display_gas(float value) // Subroutine to display Gas Sensor data on LCD
{
	unsigned char i;
	LCD_CMD(0xCB);
	convert_display_LCD(value);
	if(value>=threshold)
	{
		LED_2 = 1;
		for(i = 0; i < 15 ; i++)
			delay();
	}
	else
	{
		LED_2 = 0;
		for(i = 0; i < 15 ; i++)
			delay();
	}
}

void convert_display_LCD(float value) // Subroutine to display a float value on LCD with 2 bit precision
{
	unsigned char INT = (unsigned char) value;
	unsigned char DEC = (unsigned char) ((value - (float)INT)*100);
	unsigned char digit1 = DEC/10, digit2 = DEC%10;
	LCD_DATA(INT+48);
	LCD_DATA('.');
	LCD_DATA(digit1+48);
	LCD_DATA(digit2+48);
}