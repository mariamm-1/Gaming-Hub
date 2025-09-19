
#ifndef MNVIC_INTERFACE_H_
#define MNVIC_INTERFACE_H_

typedef enum
{
	Group16Sub0=3,
	Group8Sub2,
	Group4Sub4,
	Group2Sub8,
	Group0Sub16
}NVIC_Group_t;


void MNVIC_voidEnable(u8 Copy_u8Position);
void MNVIC_voidDisable(u8 Copy_u8Position);
void MNVIC_voidSetPendingFlag(u8 Copy_u8Position);
void MNVIC_voidClearPendingFlag(u8 Copy_u8Position);
u8   MNVIC_u8ReadingActiveState(u8 Copy_u8Position);
void MNVIC_voidSetGroupMode(NVIC_Group_t Copy_uddtGroupMode);
void MNVIC_voidSetInterruptPriority(u8 Copy_u8Position,u8 Copy_u8Group,u8 Copy_u8SubGroup);

#endif /* MNVIC_INTERFACE_H_ */
