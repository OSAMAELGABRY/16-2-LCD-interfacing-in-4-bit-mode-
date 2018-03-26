/*
 * LCD_Config.h
 *
 *  Created on: Mar 4, 2018
 *      Author: osama
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

//****************LCD PORT******************
#define LCD_PORT DIO_PORTC
//*************CONTROL pins position**********

#define LCD_RS         DIO_PIN2
#define LCD_ENABLE     DIO_PIN3
// RW TO GROUND

//********************************************
//no change here
//DATA pins position
#define LCD_D4     DIO_PIN4
#define LCD_D5     DIO_PIN5
#define LCD_D6     DIO_PIN6
#define LCD_D7     DIO_PIN7
//********************************************




#endif /* LCD_CONFIG_H_ */
