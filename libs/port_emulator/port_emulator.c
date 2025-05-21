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

typedef struct
{
	uint8_t b0 : 1;
	uint8_t b1 : 1;
	uint8_t b2 : 1;
	uint8_t b3 : 1;
	uint8_t b4 : 1;
	uint8_t b5 : 1;
	uint8_t b6 : 1;
	uint8_t b7 : 1;
}pin_t;

#ifndef BIG_ENDIAN
	typedef struct
	{
		pin_t B;
		pin_t A;
	}port_t;
#else
	typedef struct
	{
		pin_t A;
		pin_t B;
	}port_t;
#endif

typedef union
{
	port_t byte;
	uint16_t D;
}alu_t;

typedef struct
{
	alu_t register;
	uint8_t mode;
}register_t;

#define bitSet
#define bitClr
#define bitGet
#define bitToggle
#define maskOn
#define maskOff
#define maskToggle
