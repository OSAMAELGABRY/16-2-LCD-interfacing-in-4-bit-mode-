#include <util/delay.h>
#include "LCD_prog.h"
#include "Datatypes.h"
int main (void)
{
	Lcd_vInitialization ();
	LCD_vWriteDataString((u8*)"Test1");
	LCD_vPosition(17);
	LCD_vWriteDataString((u8*)"Test2");
	_delay_ms(1000);
	while (1)
	{
		LCD_vDisplayRshift(11,1);   //shift display to right 11 times with 1 second delay
		LCD_vDisplayLshift(11,1);   //shift display to left 11 times with 1 second delay
	}
}
