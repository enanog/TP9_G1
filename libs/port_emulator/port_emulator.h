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

/**
 * @brief Initializes the mode (input or output) of a specific pin on a given port.
 *
 * @param port   Port to which the pin belongs (PORTA, PORTB, PORTD)
 * @param pin    Pin number within the port (0–7 for PORTA && PORTB, 0-15 for PORTD).
 * @param state  Desired mode for the pin: INPUT (0) or OUTPUT (1).
 */
void GPIO_PinInit(uint8_t port, uint8_t pin, uint8_t state);

/**
 * @brief Sets the logical state (HIGH, LOW, TOGGLE) of a specific output pin.
 *
 * @param port   Port to which the pin belongs (e.g., GPIOA, GPIOB, etc.).
 * @param pin    Pin number within the port (0–7).
 * @param state  Desired logical state: HIGH, LOW, or TOGGLE.
 *
 * If the pin is not configured as OUTPUT, the function returns immediately.
 */
void GPIO_SetPinState(uint8_t port, uint8_t pin, uint8_t state);

/**
 * @brief Applies a masked output operation (HIGH, LOW, TOGGLE) to multiple output pins.
 *
 * @param port   Port to which the pins belong (e.g., GPIOA, GPIOB, etc.).
 * @param mask   Bitmask indicating which pins to affect.
 * @param state  Desired operation: HIGH, LOW, or TOGGLE.
 *
 * Verifies that all masked pins are configured as OUTPUT.
 * If any masked pin is not an OUTPUT, the function returns.
 * By default, all pins are configured as OUTPUT.
 */
uint8_t GPIO_ReadPin(uint8_t port, uint8_t pin);

/**
 * @brief Reads the logical state of a specific input pin.
 *
 * @param port   Port to which the pin belongs (e.g., GPIOA, GPIOB, etc.).
 * @param pin    Pin number within the port (0–7).
 *
 * @return The logical state (0 or 1) of the pin or INPUT_ERROR (-1)
 *         if the pin is not configured as INPUT.
 */
void GPIO_SetMaskedOutput(uint8_t port, uint16_t mask, uint8_t state);

#endif /* PORT_EMULATOR_H */
