
#include "std_types.h"
#include "bit_math.h"
#include "MGPIO_private.h"
#include "MGPIO_interface.h"


void MGPIO_voidSetMode(PORTS Copy_uddtport,PINS Copy_uddtpin,MODES Copy_uddtmode)
{
	if((Copy_uddtport == PORTA) && ((Copy_uddtpin==PIN13) ||(Copy_uddtpin==PIN14)||(Copy_uddtpin==PIN15)))
	{
		/*do nothing*/
	}
	else if((Copy_uddtport == PORTB) && ((Copy_uddtpin==PIN3) ||(Copy_uddtpin==PIN4)||(Copy_uddtpin==PIN5)))
	{
		/*do nothing*/
	}
	else
	{
		switch (Copy_uddtport)
		{
		case PORTA:
			GPIOA->MODER &=~(GPIO_MUSK<<(Copy_uddtpin*2));
			GPIOA->MODER |=(Copy_uddtmode<<(Copy_uddtpin*2));
			break;
		case PORTB:
			GPIOB->MODER &=~(GPIO_MUSK<<(Copy_uddtpin*2));
			GPIOB->MODER |=(Copy_uddtmode<<(Copy_uddtpin*2));
			break;
		case PORTC:
			GPIOC->MODER &=~(GPIO_MUSK<<(Copy_uddtpin*2));
			GPIOC->MODER |=(Copy_uddtmode<<(Copy_uddtpin*2));
			break;
		default:
			break;
		}
	}

}

void MGPIO_voidSetOutputConfig(PORTS Copy_uddtport,PINS Copy_uddtpin,OUT_TYPE Copy_uddttype,SPEED Copy_uddtSpeed)
{
	if((Copy_uddtport == PORTA) && ((Copy_uddtpin==PIN13) ||(Copy_uddtpin==PIN14)||(Copy_uddtpin==PIN15)))
	{
		/*do nothing*/
	}
	else if((Copy_uddtport == PORTB) && ((Copy_uddtpin==PIN3) ||(Copy_uddtpin==PIN4)||(Copy_uddtpin==PIN5)))
	{
		/*do nothing*/
	}
	else
	{
		switch (Copy_uddtport)
		{
		case PORTA:
			GPIOA->OTYPER   &=~(1<<Copy_uddtpin);
			GPIOA->OTYPER   |=(Copy_uddttype<<Copy_uddtpin);
			GPIOA->OSPEEDER &=~(GPIO_MUSK<<(Copy_uddtpin*2));
			GPIOA->OSPEEDER |=(Copy_uddtSpeed<<(Copy_uddtpin*2));
			break;
		case PORTB:
			GPIOB->OTYPER   &=~(1<<Copy_uddtpin);
			GPIOB->OTYPER   |=(Copy_uddttype<<Copy_uddtpin);
			GPIOB->OSPEEDER &=~(GPIO_MUSK<<(Copy_uddtpin*2));
			GPIOB->OSPEEDER |=(Copy_uddtSpeed<<(Copy_uddtpin*2));
			break;
		case PORTC:
			GPIOC->OTYPER   &=~(1<<Copy_uddtpin);
			GPIOC->OTYPER   |=(Copy_uddttype<<Copy_uddtpin);
			GPIOC->OSPEEDER &=~(GPIO_MUSK<<(Copy_uddtpin*2));
			GPIOC->OSPEEDER |=(Copy_uddtSpeed<<(Copy_uddtpin*2));
			break;
		default:
			break;
		}
	}

}
void MGPIO_voidSetPinValue(PORTS Copy_uddtport,PINS Copy_uddtpin,Value Copy_uddtvalue)
{
	if((Copy_uddtport == PORTA) && ((Copy_uddtpin==PIN13) ||(Copy_uddtpin==PIN14)||(Copy_uddtpin==PIN15)))
	{
		/*do nothing*/
	}
	else if((Copy_uddtport == PORTB) && ((Copy_uddtpin==PIN3) ||(Copy_uddtpin==PIN4)||(Copy_uddtpin==PIN5)))
	{
		/*do nothing*/
	}
	else
	{
		switch (Copy_uddtport)
		{
		case PORTA:
			if(Copy_uddtvalue==PIN_Low)
			{
				GPIOA->ODR &=~(1<<Copy_uddtpin);
				//Clr_Bit(GPIOA->ODR,Copy_uddtpin);
			}
			else if(Copy_uddtvalue==PIN_High)
			{
				GPIOA->ODR |=(1<<Copy_uddtpin);
			}
			break;
		case PORTB:
			if(Copy_uddtvalue==PIN_Low)
			{
				GPIOB->ODR &=~(1<<Copy_uddtpin);
				//Clr_Bit(GPIOA->ODR,Copy_uddtpin);
			}
			else if(Copy_uddtvalue==PIN_High)
			{
				GPIOB->ODR |=(1<<Copy_uddtpin);
			}
			break;
		case PORTC:
			if(Copy_uddtvalue==PIN_Low)
			{
				GPIOC->ODR &=~(1<<Copy_uddtpin);
				//Clr_Bit(GPIOA->ODR,Copy_uddtpin);
			}
			else if(Copy_uddtvalue==PIN_High)
			{
				GPIOC->ODR |=(1<<Copy_uddtpin);
			}
			break;
		default:
			break;
		}
	}

}
void MGPIO_voidSetAtomicPinValue(PORTS Copy_uddtport,PINS Copy_uddtpin,Value Copy_uddtvalue)
{
	if((Copy_uddtport == PORTA) && ((Copy_uddtpin==PIN13) ||(Copy_uddtpin==PIN14)||(Copy_uddtpin==PIN15)))
	{
		/*do nothing*/
	}
	else if((Copy_uddtport == PORTB) && ((Copy_uddtpin==PIN3) ||(Copy_uddtpin==PIN4)||(Copy_uddtpin==PIN5)))
	{
		/*do nothing*/
	}
	else
	{
		switch (Copy_uddtport) {
		case PORTA:
			if(Copy_uddtvalue==PIN_High)
			{
				GPIOA->BSRR =(1<<Copy_uddtpin);
			}
			else if(Copy_uddtvalue==PIN_Low)
			{
				GPIOA->BSRR =(1<<(Copy_uddtpin+16));
			}
			break;
		case PORTB:
			if(Copy_uddtvalue==PIN_High)
			{
				GPIOB->BSRR =(1<<Copy_uddtpin);
			}
			else if(Copy_uddtvalue==PIN_Low)
			{
				GPIOB->BSRR =(1<<(Copy_uddtpin+16));
			}
			break;
		case PORTC:
			if(Copy_uddtvalue==PIN_High)
			{
				GPIOC->BSRR =(1<<Copy_uddtpin);
			}
			else if(Copy_uddtvalue==PIN_Low)
			{
				GPIOC->BSRR =(1<<(Copy_uddtpin+16));
			}
			break;
		default:
			break;
		}

	}
}

void MGPIO_voidSetInputConfig(PORTS Copy_uddtport,PINS Copy_uddtpin,INPUT_MODE Copy_uddtmode)
{
	if((Copy_uddtport == PORTA) && ((Copy_uddtpin==PIN13) ||(Copy_uddtpin==PIN14)||(Copy_uddtpin==PIN15)))
	{
		/*do nothing*/
	}
	else if((Copy_uddtport == PORTB) && ((Copy_uddtpin==PIN3) ||(Copy_uddtpin==PIN4)||(Copy_uddtpin==PIN5)))
	{
		/*do nothing*/
	}
	else
	{
		switch (Copy_uddtport) {
		case PORTA:
			GPIOA->PUPDR &=~(GPIO_MUSK<<(Copy_uddtpin*2));
			GPIOA->PUPDR |=(Copy_uddtmode<<(Copy_uddtpin*2));
			break;
		case PORTB:
			GPIOB->PUPDR &=~(GPIO_MUSK<<(Copy_uddtpin*2));
			GPIOB->PUPDR |=(Copy_uddtmode<<(Copy_uddtpin*2));
			break;
		case PORTC:
			GPIOC->PUPDR &=~(GPIO_MUSK<<(Copy_uddtpin*2));
			GPIOC->PUPDR |=(Copy_uddtmode<<(Copy_uddtpin*2));
			break;
		default:
			break;
		}

	}



}
u8   MGPIO_u8GetPinValue(PORTS Copy_uddtport,PINS Copy_uddtpin)
{
	u8 LOC_u8PinValue=3;
	switch (Copy_uddtport) {
	case PORTA:
		LOC_u8PinValue=GET_BIT(GPIOA->IDR,Copy_uddtpin);
		break;
	case PORTB:
		LOC_u8PinValue=GET_BIT(GPIOB->IDR,Copy_uddtpin);
		break;
	case PORTC:
		LOC_u8PinValue=GET_BIT(GPIOC->IDR,Copy_uddtpin);
		break;
	default:
		break;
	}
	return LOC_u8PinValue;
}

void MGPIO_voidSetAlternativeConfig(PORTS Copy_uddtport,PINS Copy_uddtpin,ALT_FUNC Copy_uddtAltfunc)
{
	if(Copy_uddtpin<=7)
	{
		switch (Copy_uddtport) {
		case PORTA:
			GPIOA->AFRL &=~(ALT_FUNC_MUSK<<(Copy_uddtpin*4));
			GPIOA->AFRL |=(Copy_uddtAltfunc<<(Copy_uddtpin*4));
			break;
		case PORTB:
			GPIOB->AFRL &=~(ALT_FUNC_MUSK<<(Copy_uddtpin*4));
			GPIOB->AFRL |=(Copy_uddtAltfunc<<(Copy_uddtpin*4));
			break;
		case PORTC:
			GPIOC->AFRL &=~(ALT_FUNC_MUSK<<(Copy_uddtpin*4));
			GPIOC->AFRL |=(Copy_uddtAltfunc<<(Copy_uddtpin*4));
			break;
		default:
			break;
		}
	}
	else if((Copy_uddtpin<=15)&&(Copy_uddtpin>=8))
	{
		switch (Copy_uddtport) {
		case PORTA:
			GPIOA->AFRH &=~(ALT_FUNC_MUSK<<((Copy_uddtpin-8)*4));
			GPIOA->AFRH |=(Copy_uddtAltfunc<<((Copy_uddtpin-8)*4));
			break;
		case PORTB:
			GPIOB->AFRH &=~(ALT_FUNC_MUSK<<((Copy_uddtpin-8)*4));
			GPIOB->AFRH |=(Copy_uddtAltfunc<<((Copy_uddtpin-8)*4));
			break;
		case PORTC:
			GPIOC->AFRH &=~(ALT_FUNC_MUSK<<((Copy_uddtpin-8)*4));
			GPIOC->AFRH |=(Copy_uddtAltfunc<<((Copy_uddtpin-8)*4));
			break;
		default:
			break;
		}

	}


}




