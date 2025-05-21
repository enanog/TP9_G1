/* ---------------------------------------------------
 * port_emulator.h
 * ---------------------------------------------------
 * GRUPO 1:
 * 	CASTRO, Tomás
 *	FRIGERIO, Dylan
 * 	VALENZUELA, Agustín
 * 	YAGGI, Lucca
 *
 * Profesores:
 * 	MAGLIIOLA, Nicolas
 * 	JACOBY, Daniel
 * 	VACATELLO, Pablo
 *
 * fecha: 21/05/2025
 * ---------------------------------------------------*/

#include <stdio.h>

#ifndef PORT_EMULATOR_H
#define PORT_EMULATOR_H

#define INPUT_ERROR 0xFF
// Default Little Endian environment
//#define BIG_ENDIAN;
enum
{
	INPUT = 0,
	OUTPUT,
};

enum
{
	HIGH = 0,
	LOW,
	TOGGLE,
};

enum
{
	PORTA = 0,
	PORTB,
	PORTD,
};

enum
{
	PDIR = 0,	// Port Data Input Register
	PDOR,		// Port Data Output Register
};

typedef union
{
	struct
	{
		uint8_t _0 : 1;
		uint8_t _1 : 1;
		uint8_t _2 : 1;
		uint8_t _3 : 1;
		uint8_t _4 : 1;
		uint8_t _5 : 1;
		uint8_t _6 : 1;
		uint8_t _7 : 1;
	}bit;
	uint8_t byte;
}gpio_port_t;

typedef union
{
#ifndef BIG_ENDIAN
	struct
	{
		gpio_port_t B;
		gpio_port_t A;
	}PORT;
#else
	struct
	{
		gpio_port_t A;
		gpio_port_t B;
	}PORT;
#endif
	uint16_t WORD;
}gpio_port_d_t;

typedef struct
{
	gpio_port_d_t REGISTER;
	uint16_t MODE;
}gpio_register_t;

extern gpio_register_t portD;

void GPIO_PinInit(uint8_t port, uint8_t pin, uint8_t state);
void GPIO_SetPinState(uint8_t port, uint8_t pin, uint8_t state);
uint8_t GPIO_ReadPin(uint8_t port, uint8_t pin);
void GPIO_SetMaskedOutput(uint8_t port, uint16_t mask, uint8_t state);

#endif /* PORT_EMULATOR_H */
