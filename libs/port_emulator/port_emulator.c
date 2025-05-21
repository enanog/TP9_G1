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
	uint8_t MODE;
}gpio_register_t;

#define _PORTA portD.REGISTER.PORT.A
#define _PORTB portD.REGISTER.PORT.B

#define _bitSet(port, n) ((port) | (1 << (n)))
#define _bitClr(port, n) ((port) & ~(1 << (n)))
#define _bitGet(port, n) ((port >> (n)) & 1)
#define _bitToggle(port, n) ((port) ^ (1 << (n)))
#define _maskOn(port, mask) ((port) | (mask))
#define _maskOff(port, mask) ((port) & (mask))
#define _maskToggle(port, mask) ((port) ^ (mask))

static gpio_register_t portD = { .REGISTER.WORD = 0, .MODE = 0};


static void* getPort(uint8_t port)
{
	switch(port)
	{
		case PORTA:
			return &_PORTA;
		case PORTB:
		case PORTD:
			return &_PORTB;
		default:
			return NULL;
	}
}

void bitSet(uint8_t port, uint8_t n)
{
	gpio_port_t *p = getPort(port);
	if(p != NULL)
	{
		return;
	}
	p->byte = _bitSet(p->byte, n);
}

void bitClr(uint8_t port, uint8_t n)
{
	gpio_port_t *p = getPort(port);
	if(p != NULL)
	{
		return;
	}
	p->byte = _bitClr(p->byte, n);
}

void bitSet(uint8_t port, uint8_t n)
{
	gpio_port_t *p = getPort(port);
	if(p != NULL)
	{
		return;
	}
	p->byte = _bitSet(p->byte, n);
}
