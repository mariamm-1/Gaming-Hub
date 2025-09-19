/*
 * bit_math.h
 *
 *  Created on: Sep 4, 2025
 *      Author: Nour
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(VAR,BITNO)  (VAR) |= (1 << (BITNO))
#define CLR_BIT(VAR,BITNO)  (VAR) &= ~(1 << (BITNO))
#define TOG_BIT(VAR,BITNO) (VAR) ^=  (1 << (BITNO))
#define GET_BIT(VAR,BITNO) (((VAR) >> (BITNO)) & 0x01)

#define NULL     ((void*)0)

#endif /* BIT_MATH_H_ */
