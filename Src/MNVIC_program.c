
#include "std_types.h"
#include "bit_math.h"
#include "MNVIC_private.h"
#include "MNVIC_interface.h"

u8 GLB_u8Value=0;

void MNVIC_voidEnable(u8 Copy_u8Position)
{
	NVIC->ISER[Copy_u8Position/REG_DIV] |=(1<<(Copy_u8Position%REG_DIV));
}
void MNVIC_voidDisable(u8 Copy_u8Position)
{
	NVIC->ICER[Copy_u8Position/REG_DIV] |=(1<<(Copy_u8Position%REG_DIV));
}
void MNVIC_voidSetPendingFlag(u8 Copy_u8Position)
{
	NVIC->ISPR[Copy_u8Position/REG_DIV] |=(1<<(Copy_u8Position%REG_DIV));
}
void MNVIC_voidClearPendingFlag(u8 Copy_u8Position)
{
	NVIC->ICPR[Copy_u8Position/REG_DIV] |=(1<<(Copy_u8Position%REG_DIV));
}
u8   MNVIC_u8ReadingActiveState(u8 Copy_u8Position)
{
	return GET_BIT(NVIC->IABR[Copy_u8Position/REG_DIV],(Copy_u8Position%REG_DIV));
}

void MNVIC_voidSetGroupMode(NVIC_Group_t Copy_uddtGroupMode)
{
	GLB_u8Value=Copy_uddtGroupMode;
	u32 LOC_u32value=0;
	LOC_u32value=VectKey |(Copy_uddtGroupMode<<8);
	SCB_AIRCR=LOC_u32value;
}

void MNVIC_voidSetInterruptPriority(u8 Copy_u8Position,u8 Copy_u8Group,u8 Copy_u8SubGroup)
{
	switch (GLB_u8Value) {
	case Group16Sub0:
		NVIC->IPR[Copy_u8Position] =Copy_u8Group<<4;
		break;
	case Group8Sub2:
		NVIC->IPR[Copy_u8Position] =Copy_u8Group<<5 |Copy_u8SubGroup<<4;
		break;
	case Group4Sub4:
		NVIC->IPR[Copy_u8Position] =Copy_u8Group<<6 |Copy_u8SubGroup<<4;
		break;
	case Group2Sub8:
		NVIC->IPR[Copy_u8Position] =Copy_u8Group<<7 |Copy_u8SubGroup<<4;
		break;
	case Group0Sub16:
		NVIC->IPR[Copy_u8Position] =Copy_u8SubGroup<<4;
		break;
	default:
		break;
	}


}



