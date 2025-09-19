
#ifndef MGPIO_INTERFACE_H_
#define MGPIO_INTERFACE_H_

typedef enum
{
	PORTA,
	PORTB,
	PORTC
}PORTS;

typedef enum
{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
}PINS;

typedef enum
{
	INPUT,
	OUTPUT,
	Alternative_Func,
	Analog
}MODES;

typedef enum
{
	Push_Pull,
	Open_Drain
}OUT_TYPE;

typedef enum
{
	Low_Speed,
	Med_Speed,
	High_Speed,
	VHIGH_Speed
}SPEED;

typedef enum
{
	PIN_Low,
	PIN_High
}Value;

typedef enum
{
	NOPULLUPORPULLDOWN,
	PULLUP,
	PULLDOWN
}INPUT_MODE;

typedef enum
{
	AF0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
}ALT_FUNC;


void MGPIO_voidSetMode(PORTS Copy_uddtport,PINS Copy_uddtpin,MODES Copy_uddtmode);
/*_____________________________________output mode_______________________*/
void MGPIO_voidSetOutputConfig(PORTS Copy_uddtport,PINS Copy_uddtpin,OUT_TYPE Copy_uddttype,SPEED Copy_uddtSpeed);
void MGPIO_voidSetPinValue(PORTS Copy_uddtport,PINS Copy_uddtpin,Value Copy_uddtvalue);
void MGPIO_voidSetAtomicPinValue(PORTS Copy_uddtport,PINS Copy_uddtpin,Value Copy_uddtvalue);
/*_____________________________________INput mode_______________________*/
void MGPIO_voidSetInputConfig(PORTS Copy_uddtport,PINS Copy_uddtpin,INPUT_MODE Copy_uddtmode);
u8   MGPIO_u8GetPinValue(PORTS Copy_uddtport,PINS Copy_uddtpin);
/*_____________________________________Alternative mode_______________________*/
void MGPIO_voidSetAlternativeConfig(PORTS Copy_uddtport,PINS Copy_uddtpin,ALT_FUNC Copy_uddtAltfunc);

#endif /* MGPIO_INTERFACE_H_ */
