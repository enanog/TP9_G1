/* ---------------------------------------------------
 * TP9:Tipos de datos avanzados y Herramientas de
 * desarrollo.
 * ---------------------------------------------------
 * GRUPO 1:
 * 	CASTRO, Tomás
 * 	FRIGERIO, Dylan
 * 	VALENZUELA, Agustín
 * 	YAGGI, Lucca
 *
 * Profesores:
 * 	MAGLIIOLA, Nicolas
 * 	JACOBY, Daniel
 * 	VACATELLO, Pablo
 *
 * fecha: 26/05/2025
 * ---------------------------------------------------*/

#include <stdio.h>
#include <stdint.h>
#include "libs/port_emulator/port_emulator.h"

enum
{
	LED_SELECTOR = 0,
	NOT_LED,
	OFF_ALL,
	ON_ALL,
	FINISH
};

enum
{
	STOP = 0,
	RUNNING,
};

int main(void)
{
	/**/
	GPIO_PinInit(PORTA, 0, INPUT);
	GPIO_PinInit(PORTA, 1, OUTPUT);
	GPIO_PinInit(PORTA, 3, OUTPUT);
	
	GPIO_PinInit(PORTB, 2, INPUT);
	GPIO_PinInit(PORTB, 5, OUTPUT);
	GPIO_PinInit(PORTB, 7, OUTPUT);
	
	GPIO_PinInit(PORTA, 8, OUTPUT);
	GPIO_PinInit(PORTB, 8, OUTPUT);
	GPIO_PinInit(PORTD, 16, OUTPUT);
	GPIO_MaskInit(PORTA, 0x1000, OUTPUT);
	GPIO_MaskInit(PORTB, 0x1000, OUTPUT);
	GPIO_MaskInit(4, 0, OUTPUT);
	
	GPIO_MaskInit(PORTA, 0x00FF, INPUT);
	GPIO_MaskInit(PORTB, 0x00FF, INPUT);
	GPIO_MaskInit(PORTD, 0xFFFF, OUTPUT);
	
	GPIO_SetMaskedOutput(PORTD, 0xFFFF, HIGH);
	GPIO_SetMaskedOutput(PORTB, 0x00FF, LOW);
	GPIO_SetMaskedOutput(PORTA, 0x00FF, TOGGLE);
	GPIO_MaskInit(PORTD, 0xFFFF, INPUT);
	GPIO_SetMaskedOutput(PORTD, 0xFFFF, TOGGLE);
	GPIO_MaskInit(PORTD, 0xFFFF, OUTPUT);
	GPIO_SetPinState(PORTA, 0, TOGGLE);
	GPIO_SetPinState(PORTA, 1, LOW);
	GPIO_SetPinState(PORTB, 0, TOGGLE);
	GPIO_SetPinState(PORTB, 0, HIGH);
	
	GPIO_ReadPin(PORTA, 0);
	GPIO_ReadPin(PORTB, 0);
	GPIO_ReadPin(4, 0);
	GPIO_MaskInit(PORTD, 0xFFFF, INPUT);
	printf("PORTA: ");
	for(uint8_t i = 8; i >= 1; i--)
		printf("%d ", GPIO_ReadPin(PORTA, i-1));
	printf("\n");
	printf("PORTB: ");
	for(uint8_t i = 8; i >= 1; i--)
		printf("%d ", GPIO_ReadPin(PORTB, i-1));
	
	
	GPIO_PinInit(PORTD, 1, OUTPUT);
	printf("\nPORTA: %X", GPIO_MaskRead(PORTA, 0xFF));
	printf("\nPORTB: %X", GPIO_MaskRead(PORTB, 0xFF));
	printf("\nPORTD: %X", GPIO_MaskRead(PORTD, 0xFFFF));
	/**/
	
	/*
	uint8_t prog = RUNNING;

	while(prog)
	{
		switch(prog)
		{
			case LED_SELECTOR:
				break;

			case NOT_LED:
				break;

			case OFF_ALL:
				break;

			case ON_ALL:
				break;

			case FINISH:
				prog = STOP;
				break;

			default:
				printf("Se ingreso un comando erroneo.\n");
				break;
		}
	}*/

	return 0;
}
