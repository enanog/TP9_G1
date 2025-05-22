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

	GPIO_PinInit(PORTA, 0, INPUT);
	GPIO_PinInit(PORTA, 1, OUTPUT);
	GPIO_PinInit(PORTA, 3, OUTPUT);
	GPIO_PinInit(PORTB, 2, INPUT);
	GPIO_PinInit(PORTB, 5, OUTPUT);
	GPIO_PinInit(PORTB, 7, OUTPUT);

	GPIO_SetMaskedOutput(PORTD, 0xFFFF, HIGH);
	GPIO_SetMaskedOutput(PORTB, 0x00FF, LOW);
	GPIO_SetMaskedOutput(PORTA, 0x00FF, TOGGLE);
	GPIO_SetMaskedOutput(PORTD, 0xFFFF, TOGGLE);

	GPIO_SetPinState(PORTA, 0, TOGGLE);
	GPIO_SetPinState(PORTA, 1, LOW);
	GPIO_SetMaskedOutput(PORTD, 0xFFFF, TOGGLE);
	GPIO_SetPinState(PORTB, 0, HIGH);
	GPIO_SetPinState(PORTD, 0, LOW);



	return 0;
}
