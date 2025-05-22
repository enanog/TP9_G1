/* ---------------------------------------------------
 * port_emulator.c
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

#include <stdint.h>
#include "port_emulator.h"

#define _PORTA portD.REGISTER.PORT.A
#define _PORTB portD.REGISTER.PORT.B
#define _WORD portD.REGISTER.WORD
#define _MODE portD.MODE
#define sizePort 8

#define _offsetPort(port) ((!(port))? 8: 0)
#define _bitSet(x, n) ((x) | (1 << (n)))
#define _bitClr(x, n) ((x) & ~(1 << (n)))
#define _bitGet(x, n) (((x) >> (n)) & 1)
#define _bitToggle(x, n) ((x) ^ (1 << (n)))
#define _maskOn(x, mask) ((x) | (mask))
#define _maskOff(x, mask) ((x) & ~(mask))
#define _maskToggle(x, mask) ((x) ^ (mask))

/*
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
*/

gpio_register_t portD = { .REGISTER.WORD = 0, .MODE = 0};

static void* getPort(uint8_t port);
static void bitSet(uint8_t port, uint8_t bit);
static void bitClr(uint8_t port, uint8_t bit);
static void bitToggle(uint8_t port, uint8_t bit);
static void maskOn(uint8_t port, uint16_t mask);
static void maskOff(uint8_t port, uint16_t mask);
static void maskToggle(uint8_t port, uint16_t mask);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void GPIO_PinInit(uint8_t port, uint8_t pin, uint8_t state)
{
	uint8_t offset = _offsetPort(port);
	_MODE = (state)? _bitSet(_MODE , pin + offset): _bitClr(_MODE , pin + offset);
}

void GPIO_SetPinState(uint8_t port, uint8_t pin, uint8_t state)
{
	uint8_t offset = _offsetPort(port);

	// Check if the pin is configured as OUTPUT
	if(_bitGet(_MODE, pin + offset) != OUTPUT)
	{
		return;
	}

	switch(state)
	{
		case HIGH:
			bitSet(port, pin);
			break;

		case LOW:
			bitClr(port, pin);
			break;

		case TOGGLE:
			bitToggle(port, pin);
			break;

		default:
			break;
	}
}

uint8_t GPIO_ReadPin(uint8_t port, uint8_t pin)
{
	uint8_t offset = _offsetPort(port);
	if(_bitGet(_MODE, pin + offset) != INPUT)
	{
		return INPUT_ERROR;
	}

	// Read the pin state from the _WORD register
	uint8_t state = _bitGet(_WORD, pin + offset);
	return state;	// Return the read state
}

void GPIO_SetMaskedOutput(uint8_t port, uint16_t mask, uint8_t state)
{
	for(uint8_t i = _offsetPort(port); i < 2*sizePort; i++)
	{
		if(_bitGet(_MODE, i) != OUTPUT && _bitGet(mask, i))
		{
			return;
		}
	}
	switch(state)
	{
		case HIGH:
			maskOn(port, mask);
			break;

		case LOW:
			maskOff(port, mask);
			break;

		case TOGGLE:
			maskToggle(port, mask);
			break;

		default:
			break;
	}
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/**
 * @brief Returns a pointer to the internal memory representation of a GPIO port.
 *
 * @param port  Identifier for the port (PORTA, PORTB, or PORTD).
 *
 * @return Pointer to the corresponding port structure or variable.
 *         Returns NULL if the port is invalid.
 */
static void *getPort(uint8_t port)
{
	switch(port)
	{
		case PORTA:
			return &_PORTA;
		case PORTB:
			return &_PORTB;
		case PORTD:
			return &portD;
		default:
			return NULL;
	}
}

/**
 * @brief Sets a specific bit to HIGH in the specified port.
 *
 * @param port  Port identifier (PORTA, PORTB, PORTD).
 * @param bit   Bit number within the port (0–7 for POTA and PORTB;
 * 				0-15 for PORTD).
 */
static void bitSet(uint8_t port, uint8_t bit)
{
	// Handle special case for PORTD
	if(port == PORTD)
	{
		_WORD = _bitSet(_WORD, bit);
		return;
	}

	// Get a pointer to the port structure
	gpio_port_t *p = getPort(port);
	if(p == NULL)
	{
		return;
	}
	p->byte = _bitSet(p->byte, bit);
}

/**
 * @brief Clears a specific pin (sets it to LOW) in the specified port.
 *
 * @param port  Port identifier (PORTA, PORTB, PORTD).
 * @param bit   Bit number within the port (0–7 for POTA and PORTB;
 * 				0-15 for PORTD).
 */
static void bitClr(uint8_t port, uint8_t bit)
{
	if(port == PORTD)
	{
		_WORD = _bitClr(_WORD, bit);
		return;
	}

	gpio_port_t *p = getPort(port);
	if(p == NULL)
	{
		return;
	}
	p->byte = _bitClr(p->byte, bit);
}

/**
 * @brief Toggles the state of a specific pin in the specified port.
 *
 * @param port  Port identifier (PORTA, PORTB, PORTD).
 * @param bit   Bit number within the port (0–7 for POTA and PORTB;
 * 				0-15 for PORTD).
 */
static void bitToggle(uint8_t port, uint8_t bit)
{
	if(port == PORTD)
	{
		_WORD = _bitToggle(_WORD, bit);
		return;
	}

	gpio_port_t *p = getPort(port);
	if(p == NULL)
	{
		return;
	}
	p->byte = _bitToggle(p->byte, bit);
}

static void maskOn(uint8_t port, uint16_t mask)
{
	if(port == PORTD)
	{
		_WORD = _maskOn(_WORD, mask);
		return;
	}

	gpio_port_t *p = getPort(port);
	if(p == NULL)
	{
		return;
	}

	p->byte = _maskOn(p->byte, mask);
}

/**
 * @brief Sets multiple bits to HIGH using a bitmask.
 *
 * @param port  Port identifier (PORTA, PORTB, PORTD).
 * @param mask  Bitmask indicating which pins to set.
 */
static void maskOff(uint8_t port, uint16_t mask)
{
	if(port == PORTD)
	{
		_WORD = _maskOff(_WORD, mask);
		return;
	}

	gpio_port_t *p = getPort(port);
	if(p == NULL)
	{
		return;
	}
	p->byte = _maskOff(p->byte, mask);
}

/**
 * @brief Clears (sets to LOW) multiple bits using a bitmask.
 *
 * @param port  Port identifier (PORTA, PORTB, PORTD).
 * @param mask  Bitmask indicating which pins to clear.
 */
static void maskToggle(uint8_t port, uint16_t mask)
{
	if(port == PORTD)
	{
		_WORD = _maskToggle(_WORD, mask);
		return;
	}

	gpio_port_t *p = getPort(port);
	if(p == NULL)
	{
		return;
	}
	p->byte = _maskToggle(p->byte, mask);
}

