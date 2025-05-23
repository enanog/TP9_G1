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
#include "libs/leds_emulator/leds_emulator.h"
#include "libs/nstdio/nstdio.h"

void ClearInputBuffer();

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



int main() {
    GPIO_MaskInit(PORTA, 0xFF, OUTPUT);
	GPIO_SetMaskedOutput(PORTA, 0xFF, OUTPUT);
	
	uint8_t prog = RUNNING;
	char str[4];
	//readString("Hola", str);
	printf("%s", str);
	showMenu();
	
	display_leds(15, 0xff);
	showMenu();
    return 0;
}

void ClearInputBuffer(void)
{
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}

void showMenu() {
    printf("\t\t\t=========== LED SIMULATOR MENU ===========\n");
    printf("\t\t\t [0-7]  Turn ON a specific LED\n");
    printf("\t\t\t [t]    Toggle all LEDs\n");
    printf("\t\t\t [c]    Clear (turn off) all LEDs\n");
    printf("\t\t\t [s]    Set (turn on) all LEDs\n");
    printf("\t\t\t [q]    Quit program\n");
    printf("\t\t\t==========================================\n");
    printf("\n\n\n\t\t\t\t\tPress a key to continue...");
    ClearInputBuffer();
    CLEAR_SCREEN();
}

//int main(void)
//{
////	uint8_t prog = RUNNING;
//	GPIO_MaskInit(PORTA, 0xFF, OUTPUT);
//	GPIO_SetMaskedOutput(PORTA, 0xFF, OUTPUT);
//	/*while(prog)
//	{
//		
//		switch(prog)
//		{
//			case LED_SELECTOR:
//				break;
//
//			case NOT_LED:
//				break;
//
//			case OFF_ALL:
//				break;
//
//			case ON_ALL:
//				break;
//
//			case FINISH:
//				prog = STOP;
//				break;
//
//			default:
//				printf("Se ingreso un comando erroneo.\n");
//				break;
//		}
//	}*/
//
//	return 0;
//}

