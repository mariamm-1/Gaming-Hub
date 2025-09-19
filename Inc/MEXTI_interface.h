#ifndef MEXTI_INTERFACE_H_
#define MEXTI_INTERFACE_H_

//ENUM N3ARAF BIHA EL LINES

typedef enum{
	EXTI_LINE0,
	EXTI_LINE1,
	EXTI_LINE2,
	EXTI_LINE3,
	EXTI_LINE4,
	EXTI_LINE5,
	EXTI_LINE6,
	EXTI_LINE7,
	EXTI_LINE8,
	EXTI_LINE9,
	EXTI_LINE10,
	EXTI_LINE11,
	EXTI_LINE12,
	EXTI_LINE13,
	EXTI_LINE14,
	EXTI_LINE15
}EXTI_line_t;

typedef enum{
	EXTI_Falling,
	EXTI_Rising,
	EXTI_OnChange
}EXTI_TriggerMode_t;

typedef enum{
	EXTI_PORTA,
	EXTI_PORTB,
	EXTI_PORTC
}EXTI_Port_t;

//system configuration (
void EXTI_voidSetInterruptPort(EXTI_line_t Copy_uddtLine,EXTI_Port_t Copy_uddtPort);
//external interrupt
void EXTI_voidEnable(EXTI_line_t Copy_uddtLine);
void EXTI_voidDisable(EXTI_line_t Copy_uddtLine);
void EXTI_voidSetTrigger(EXTI_line_t Copy_uddtLine,EXTI_TriggerMode_t Copy_uddtMode);
void EXTI_voidCallBack(void(*ptr)(void),u8 Copy_u8ExtiNumber);


#endif
