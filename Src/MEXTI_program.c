#include "bit_math.h"
#include "std_types.h"

#include "MEXTI_private.h"
#include "MEXTI_Config.h"
#include "MEXTI_interface.h"

// Array of function pointers for callbacks
static void (*Global_ptr)(void) = {0};

//---------------- SYSTEM CONFIGURATION ----------------//

void EXTI_voidSetInterruptPort(EXTI_line_t Copy_uddtLine, EXTI_Port_t Copy_uddtPort)
{
    u8 reg_index = Copy_uddtLine / 4;     // Each EXTICR register handles 4 lines
    u8 bit_pos   = (Copy_uddtLine % 4) * 4;

    // Clear old value
    SYSCFG->EXTICR[reg_index] &= ~(0xF << bit_pos);

    // Set new port value (A=0, B=1, C=2...)
    SYSCFG->EXTICR[reg_index] |= (Copy_uddtPort << bit_pos);
}

//---------------- INTERRUPT CONTROL ----------------//

void EXTI_voidEnable(EXTI_line_t Copy_uddtLine)
{
    SET_BIT(EXTI->IMR, Copy_uddtLine);  // Unmask interrupt
}

void EXTI_voidDisable(EXTI_line_t Copy_uddtLine)
{
    CLR_BIT(EXTI->IMR, Copy_uddtLine);  // Mask interrupt
}

void EXTI_voidSetTrigger(EXTI_line_t Copy_uddtLine, EXTI_TriggerMode_t Copy_uddtMode)
{
    switch(Copy_uddtMode)
    {
        case EXTI_Rising:
            SET_BIT(EXTI->RTSR, Copy_uddtLine);   // Enable rising
            CLR_BIT(EXTI->FTSR, Copy_uddtLine);   // Disable falling
            break;

        case EXTI_Falling:
            SET_BIT(EXTI->FTSR, Copy_uddtLine);   // Enable falling
            CLR_BIT(EXTI->RTSR, Copy_uddtLine);   // Disable rising
            break;

        case EXTI_OnChange:
            SET_BIT(EXTI->RTSR, Copy_uddtLine);   // Enable both edges
            SET_BIT(EXTI->FTSR, Copy_uddtLine);
            break;
    }
}

void EXTI_voidCallBack(void(*ptr)(void), u8 Copy_u8ExtiNumber)
{
    if(Copy_u8ExtiNumber <= 15 && ptr != 0)
    {

        Global_ptr=ptr;
    }
}

void EXTI0_IRQHandler(void)
{
	Global_ptr();
	EXTI->PR |=(1<<0);
}

