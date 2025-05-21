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
	}
	return 0;
}
