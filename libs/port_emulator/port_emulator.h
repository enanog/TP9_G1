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

#define GPIO_ERR_INPUT 0xFF
#define GPIO_ERR_INPUT_MASK 0xFFFF

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

#ifndef BIG_ENDIAN
	enum
	{
		PORTA = 0,
		PORTB,
		PORTD,
	};
#else
	enum
	{
		PORTB = 0,
		PORTA,
		PORTD,
	};
#endif

/**
 * @brief Initializes the mode (input or output) of a specific pin on a given port.
 *
 * @param port   Port to which the pin belongs (PORTA, PORTB, PORTD)
 * @param pin    Pin number within the port (0–7 for PORTA && PORTB, 0-15 for PORTD).
 * @param state  Desired mode for the pin: INPUT (0) or OUTPUT (1).
 */
void GPIO_PinInit(uint8_t port, uint8_t pin, uint8_t state);


void GPIO_MaskInit(uint8_t port, uint16_t mask, uint8_t state);


void GPIO_SetPinState(uint8_t port, uint8_t pin, uint8_t state);


void GPIO_SetMaskedOutput(uint8_t port, uint16_t mask, uint8_t state);


uint8_t GPIO_ReadPin(uint8_t port, uint8_t pin);


uint16_t GPIO_MaskRead(uint8_t port, uint16_t mask);

#endif /* PORT_EMULATOR_H */
