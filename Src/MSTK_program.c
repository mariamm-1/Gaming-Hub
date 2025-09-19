
#include "std_types.h"
#include "bit_math.h"
#include "MSTK_private.h"
#include "MSTK_config.h"
#include "MSTK_interface.h"

u8 flag=0;
void(*Global_ptr)(void)=NULL;

void MSTK_voidInit(void)
{
	//HSI -->16MHZ
#if(SYSTICK_CLOCK_SOURCE==STK_AHB)
	// clock -->16MHZ
	//tick time -->62.5 nanosec
	STK->CTRL |=(1<<ClockSource);
	STK->CTRL &=~(1<<STK_Enable);

#elif(SYSTICK_CLOCK_SOURCE==STK_AHB_8)
	// clock -->2MHZ
	//tick time -->0.5 usec
	STK->CTRL &=~(1<<ClockSource);
	STK->CTRL &=~(1<<STK_Enable);
#endif
}

void MSTK_voidStartTimer(u32 Copy_u32ReloadValue)
{
	STK->LOAD =Copy_u32ReloadValue;
	STK->VAL =0;
	STK->CTRL |=(1<<STK_Enable);
}

void MSTK_voidCtrlIntState(STK_INTSTATE Copy_uddtIntState)
{
	switch (Copy_uddtIntState) {
	case Systick_IntEnable:
		STK->CTRL |=(1<<TICKINT);
		break;
	case Systick_IntDisable:
		STK->CTRL &=~(1<<TICKINT);
		break;
	default:
		break;
	}

}
u8   MSTK_u8ReadFlag(void)
{
	return GET_BIT(STK->CTRL,Countflag);
}

u32  MSTK_u32GetElapsedTickSingleShot(void)
{
	return ((STK->LOAD)-(STK->VAL));
}
u32  MSTK_u32GetRemainingTickSingleShot(void)
{
	return (STK->VAL);
}

void MSTK_voidDelayms(u32 Copy_u32Delayms)
{
	//tick time -->0.5usec
	MSTK_voidCtrlIntState(Systick_IntDisable);
	MSTK_voidStartTimer(Copy_u32Delayms*2000);
	while(MSTK_u8ReadFlag()==0);
	STK->CTRL  &=~(1<<STK_Enable);
}
void MSTK_voidDelayus(u32 Copy_u32Delayus)
{
	MSTK_voidCtrlIntState(Systick_IntDisable);
	MSTK_voidStartTimer(Copy_u32Delayus*2);
	while(MSTK_u8ReadFlag()==0);
	STK->CTRL  &=~(1<<STK_Enable);
}

void MSTK_voidCallBack(void(*ptr)(void),u32 Copy_u8TicktimeUS)
{
	flag=0;
	Global_ptr=ptr;
	MSTK_voidStartTimer(Copy_u8TicktimeUS*2);
}

void MSTK_voidCallBackSingle(void(*ptr)(void),u32 Copy_u8TicktimeUS)
{
	flag=1;
	Global_ptr=ptr;
	MSTK_voidStartTimer(Copy_u8TicktimeUS*2);
}

/*
void SysTick_Handler(void)
{
	if(Global_ptr!=NULL)
	{
	Global_ptr();
	}

	if(flag==1)
	{
		MSTK_voidCtrlIntState(Systick_IntDisable);
	}
}
*/


