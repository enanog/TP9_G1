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

// Default Little Endian environment
//#define BIG_ENDIAN;
enum
{
	INPUT = 0,
	OUTPUT,
};

enum
{
	PORTA = 0,
	PORTB,
	PORTD,
};

#define PDDR	// Port Data Direction Register

void bitSet(uint8_t port, uint8_t n);

#endif /* PORT_EMULATOR_H */
