/*
 * Bit_Min.h
 *
 *  Created on: Feb 24, 2018
 *      Author: osama
 */

#ifndef BIT_MIN_H_
#define BIT_MIN_H_
#define Set_Bit(Var,BitNo) Var|=(1<<BitNo)
#define Clr_Bit(Var,BitNo)  Var &= (~(1<<BitNo))
#define Toggle_Bit(Var,BitNo)  Var^=(1<<BitNo)
#define Get_Bit(Var,BitNo)  (Var>>BitNo)&1
#endif /* BIT_MIN_H_ */
