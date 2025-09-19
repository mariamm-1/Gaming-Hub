
#ifndef MSTK_INTERFACE_H_
#define MSTK_INTERFACE_H_

typedef enum
{
	Systick_IntEnable,
	Systick_IntDisable
}STK_INTSTATE;


void MSTK_voidInit(void);
void MSTK_voidStartTimer(u32 Copy_u32ReloadValue);
void MSTK_voidCtrlIntState(STK_INTSTATE Copy_uddtIntState);
u8   MSTK_u8ReadFlag(void);
u32  MSTK_u32GetElapsedTickSingleShot(void);
u32  MSTK_u32GetRemainingTickSingleShot(void);

void MSTK_voidDelayms(u32 Copy_u32Delayms);
void MSTK_voidDelayus(u32 Copy_u32Delayus);


void MSTK_voidCallBack(void(*ptr)(void),u32 Copy_u8TicktimeUS);
void MSTK_voidCallBackSingle(void(*ptr)(void),u32 Copy_u8TicktimeUS);



#endif /* MSTK_INTERFACE_H_ */
