/*
 * MRCC_program.c
 *
 *  Created on: Aug 18, 2025
 *      Author: Nour
 */


#include "std_types.h"
#include "bit_math.h"

#include "MRCC_Interface.h"
#include "MRCC_Private.h"
#include "MRCC_Config.h"


void MRCC_voidInit()
{

	//High speed internal oscillator
	#if (SYSTEM_CLOCK==HSI_CLOCK)
		//HSI ON
		RCC->CR|=(1<<HSION);

		while(!GET_BIT(RCC->CR,HSIRDY));
		//Switch HSI
		RCC->CFGR&=~(SW_MASK<<SW0);
		RCC->CFGR|=(HSI_Oscillator<<SW0);

	//High speed external oscillator
	#elif (SYSTEM_CLOCK==HSE_CLOCK)
		#if(HSE_OSC==MECHANICAL_CLOCK)
			RCC->CR&=~(1<<HSEBYP);
		#elif (HSE_OSC==RC_CLOCK)
			RCC->CR|=(1<<HSEBYP);
		#endif

		//HSE ON
		RCC->CR|=(1<<HSEON);
		//Wait till ready
		while(!GET_BIT(RCC->CR,HSERDY));
		//Switch HSE
		RCC->CFGR&=~(SW_MASK<<SW0);
		RCC->CFGR|=(HSE_Oscillator<<SW0);
		//Disable HSI
		RCC->CR&=~(1<<HSION);
	//Phase locked loop(multiplies/divides HSI or HSE) it takes HSI or HSE as an input & generates a higher freq. clock
	#elif (SYSTEM_CLOCK==PLL)
		//Enable HSE
		RCC->CR|=(1<<HSEON);
	   //Wait till ready
		while(!GET_BIT(RCC->CR,HSERDY));
		//Configure PLL
		PLLCFGR = (PLL_M) |
		              (PLL_N << 6) |
		              (((PLL_P/2) - 1) << 16) |
		              (1 << 22);            // PLL source = HSE

		//Enable PLL
		CR |= (1 << 24);                // PLLON
		while(!(CR & (1 << 25)));       // Wait PLLRDY

		//Select PLL as system clock
		CFGR &= ~(3 << 0);              // Clear SW bits
		CFGR |= (2 << 0);               // Set SW=10 → PLL selected
		while(((CFGR >> 2) & 0x3) != 0x2); // Wait until SWS=PLL


	#endif
}

void MRCC_voidEnablePeripheral(System_Bus_t Copy_uddtBus,u8 Copy_u8Peripheral)
{
	switch(Copy_uddtBus)
	{
		case AHB1_BUS:
		RCC->AHB1ENR|=(1<<Copy_u8Peripheral);
		break;
		case AHB2_BUS:
		RCC->AHB2ENR|=(1<<Copy_u8Peripheral);
		break;
		case APB1_BUS:
		RCC->APB1ENR|=(1<<Copy_u8Peripheral);
		break;
		case APB2_BUS:
		RCC->APB2ENR|=(1<<Copy_u8Peripheral);
		break;
		default:
		break;
	}
}
void MRCC_voidDisablePeripheral(System_Bus_t Copy_uddtBus,u8 Copy_u8Peripheral)
{
	switch(Copy_uddtBus)
	{
		case AHB1_BUS:
		RCC->AHB1ENR&=~(1<<Copy_u8Peripheral);
		break;
		case AHB2_BUS:
		RCC->AHB2ENR&=~(1<<Copy_u8Peripheral);
		break;
		case APB1_BUS:
		RCC->APB1ENR&=~(1<<Copy_u8Peripheral);
		break;
		case APB2_BUS:
		RCC->APB2ENR&=~(1<<Copy_u8Peripheral);
		break;
		default:
		break;
	}

}

