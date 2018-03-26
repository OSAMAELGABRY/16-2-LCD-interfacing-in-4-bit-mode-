#include "Datatypes.h"
#include "LCD_Config.h"
#include "DIO_Int.h"
#include <util/delay.h>
/***********************************************************************
This program for using LCD in 4 bit mode ,, the difference from 8 bit
is that there is only 4 pins to send data or commands to LCD ,, the idea
is to send the 8 bits on two times "4 bit at time " (4 bit called nibble)
"the code differs in sending command ,data and Initialization functions "
and the rest function remains the same
there is unnoticeable latency
 ************************************************************************/


/**************************************************************
 This function writes single character on the LCD
 *************************************************************/
void LCD_vWriteData( u8 Data)
{
	//Setting  RS pin to "HIGH" to make LCD accept Data
	DIO_vSetPinValue(LCD_PORT,LCD_RS,DIO_HIGH);

	//Sending the higher nibble of DATA to LCD port
	DIO_vSetHighNibblePortValueHighNibblData(LCD_PORT,Data);

	//Setting  LCD_ENABLE pin to "high"
	DIO_vSetPinValue(LCD_PORT,LCD_ENABLE,DIO_HIGH);
	_delay_ms(1);

	//Setting  LCD_ENABLE pin  to low
	DIO_vSetPinValue(LCD_PORT,LCD_ENABLE,DIO_LOW);
	_delay_ms(1);

	//Sending the lower nibble of DATA to LCD port
	DIO_vSetHighNibblePortValueLowNibblData(LCD_PORT,Data);
	_delay_ms(1);

	//Setting  LCD_ENABLE pin to "high"
	DIO_vSetPinValue(LCD_PORT,LCD_ENABLE,DIO_HIGH);
	_delay_ms(1);

	//Setting  LCD_ENABLE pin  to low
	DIO_vSetPinValue(LCD_PORT,LCD_ENABLE,DIO_LOW);
	_delay_ms(2);

}


/*****************************************************************
// This function writes string on the LCD
 *****************************************************************/
void LCD_vWriteDataString(u8 * Data)
{
	while(*Data )
	{
		LCD_vWriteData(*Data++);

	}
}

/*****************************************************************
 This function send a command to the LCD
******************************************************************/
void LCD_vWriteCommand(u8 Command)
{
	//Setting  RS pin to "LOW" to make LCD accept commands
	DIO_vSetPinValue(LCD_PORT,LCD_RS,DIO_LOW);

	//Sending the higher nibble of Command to LCD port
	DIO_vSetHighNibblePortValueHighNibblData(LCD_PORT,Command);

	//Setting  LCD_ENABLE pin to "high"
	DIO_vSetPinValue(LCD_PORT,LCD_ENABLE,DIO_HIGH);
	_delay_ms(1);

	//Setting  LCD_ENABLE pin  to low
	DIO_vSetPinValue(LCD_PORT,LCD_ENABLE,DIO_LOW);
	_delay_ms(1);

	//Sending the lower nibble of Command to LCD port
	DIO_vSetHighNibblePortValueLowNibblData(LCD_PORT,Command);
	_delay_ms(1);

	//Setting  LCD_ENABLE pin to "high"
	DIO_vSetPinValue(LCD_PORT,LCD_ENABLE,DIO_HIGH);
	_delay_ms(1);

	//Setting  LCD_ENABLE pin  to low
	DIO_vSetPinValue(LCD_PORT,LCD_ENABLE,DIO_LOW);
	_delay_ms(2);

}

/*****************************************************************
This function sets the direction of the 6 pins of
LCD defined in the configuration file to output
4 pins for Data and 2 For control RS and Enable
 *****************************************************************/
void LCD_vPort(void)
{
    //setting the 4 pins of data to OUTPUT
	DIO_vSETPinDirection(LCD_PORT,LCD_D4,DIO_OUTPUT);
	DIO_vSETPinDirection(LCD_PORT,LCD_D5,DIO_OUTPUT);
	DIO_vSETPinDirection(LCD_PORT,LCD_D6,DIO_OUTPUT);
	DIO_vSETPinDirection(LCD_PORT,LCD_D7,DIO_OUTPUT);

    //setting the 2 pins of Control RS & ENABLE to OUTPUT
	DIO_vSETPinDirection(LCD_PORT,LCD_RS, DIO_OUTPUT);
	DIO_vSETPinDirection(LCD_PORT,LCD_ENABLE, DIO_OUTPUT);

}


/*****************************************************************
This function do all things to make LCD ready to accept data
and commands and it must be the first to call in main to make
every thing works as needed
*****************************************************************/
void Lcd_vInitialization (void)
{
	LCD_vPort();
	_delay_ms(100);
	LCD_vWriteCommand(0x33);  //initialize the LCD in 4 BIT mode
	LCD_vWriteCommand(0x32);
	LCD_vWriteCommand(0x28);   //initialize the LCD in 2 lines & 5*7 matrix
	LCD_vWriteCommand(0x0e);  // Display on & cursor on
	LCD_vWriteCommand(0x01);    //Clear display screen

}


/*****************************************************************
This function clears the display
 ****************************************************************/
void LCD_vClear(void)
{
	LCD_vWriteCommand(0b00000001);
}


/*******************************************************************
This function moves the cursor to the specified location from 1 to 32
*******************************************************************/
void LCD_vPosition(u8 position)
{
	if (position > 16)
		LCD_vWriteCommand((175 +position));
	else
		LCD_vWriteCommand((127+position));
	_delay_ms(10);
}


/**********************************************************************
This function moves the cursor 1st position
 *********************************************************************/
void LCD_vCursorHome(void)
{
	LCD_vWriteCommand(0b00000010);
}


/********************************************************************
This function shifts the display to right n times with delay seconds
 *********************************************************************/
void LCD_vDisplayRshift(u8 n ,u8 delay)
{
	u8 counter;
	for (counter=0;counter<n;counter++)
	{
		LCD_vWriteCommand(0b00011100);
		_delay_ms(1000*delay);
	}
}


/********************************************************************
This function shifts the display to left n times with delay seconds
*********************************************************************/
void LCD_vDisplayLshift(u8 n,u8 delay)
{
	u8 counter;
	for (counter=0;counter<n;counter++)
	{
		LCD_vWriteCommand(0b00011000);
		_delay_ms(1000*delay);
	}
}

/********************************************************************
This function writes a number to LCD  form  -32768 to 32767
*********************************************************************/
void LCD_vWriteNumber(s16 number)
{
	u8 number_matrix[5];
	itoa(number,number_matrix,10);
	LCD_vWriteDataString(number_matrix);
}
