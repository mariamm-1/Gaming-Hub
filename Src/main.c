#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "std_types.h"
#include "bit_math.h"

#include "MRCC_Interface.h"
#include "MSTK_interface.h"
#include "MGPIO_interface.h"
#include "MSPI_interface.h"
#include "MUART_interface.h"
#include "MEXTI_interface.h"
#include "HLedMatrix_interface.h"
#include "HTFT_interface.h"
#include "Games_interface.h"



int main()
{
	// === System Init ===
	MRCC_voidInit();
	// Enable clocks
	MRCC_voidEnablePeripheral(AHB1_BUS, AHB1_GPIOA);
	MRCC_voidEnablePeripheral(AHB1_BUS, AHB1_GPIOB);
	MRCC_voidEnablePeripheral(AHB1_BUS, AHB1_GPIOC);
	MRCC_voidEnablePeripheral(APB2_BUS, APB2_SPI1);
	MRCC_voidEnablePeripheral(APB2_BUS, APB2_USART1);

	MSTK_voidInit();
	MSPI_voidMasterInit();


	// SPI pins config (for TFT)
    //SCK
	MGPIO_voidSetMode(PORTA, PIN5, Alternative_Func);
	MGPIO_voidSetAlternativeConfig(PORTA, PIN5, AF5);
    //SDA TO SPI1 MOSI
	MGPIO_voidSetMode(PORTA, PIN7, Alternative_Func);
	MGPIO_voidSetAlternativeConfig(PORTA, PIN7, AF5);

   // TTL Pins
	MGPIO_voidSetMode(PORTB, PIN6, Alternative_Func);
	MGPIO_voidSetAlternativeConfig(PORTB,PIN6,AF7);
	MGPIO_voidSetMode(PORTB, PIN7, Alternative_Func);
	MGPIO_voidSetAlternativeConfig(PORTB,PIN7,AF7);



	MUART_voidInit();         // UART1 for PC <-> STM32

	u8 choice;

	while(1)
	{
		// === Receive Command from Python GUI ===

		choice=MUART_u8Recieve();
		// === Parse Command ===
		switch(choice)
		{
		case 'A':
			HLedMatrix_voidInit();
			HLEDMATRIX_voidBlinkMatrix(3,100);
			playSnake();
			break;
		case 'B':
			HTFT_voidInit();
			TicTacToe();
			break;
		case 'C':
			HTFT_voidInit();
			MemoryGame_Run();
			break;
		case 'D':
			HTFT_voidInit();
		    playDino();
			break;

		default:

			break;
		}

	}

}





