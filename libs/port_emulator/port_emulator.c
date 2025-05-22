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

#define _PDDR portD.PDDR.WORD
#define _PDIR portD.PDIR.WORD
#define _PDOR portD.PDOR.WORD
#define sizePort 8

#define _offsetPort(port) ((!(port))? 8: 0)
#define _bitSet(x, n) ((x) | (1 << (n)))
#define _bitClr(x, n) ((x) & ~(1 << (n)))
#define _bitGet(x, n) (((x) >> (n)) & 1)
#define _bitToggle(x, n) ((x) ^ (1 << (n)))
#define _maskOn(x, mask) ((x) | (mask))
#define _maskOff(x, mask) ((x) & ~(mask))
#define _maskToggle(x, mask) ((x) ^ (mask))
#define _maskGet(x, mask) ((x) & (mask))

enum {
    GPIO_ERR_NOTERROR = 0,               // Not an error
    GPIO_ERR_INVALID_DIRECTION,          // Invalid direction (INPUT/OUTPUT)
    GPIO_ERR_INVALID_STATE,              // Invalid output state (HIGH/LOW/TOGGLE)
    GPIO_ERR_WRITE_TO_INPUT,             // Writing to pin configured as input
    GPIO_ERR_READ_OUTPUT_AS_INPUT        // Reading from a pin configured as output
};

typedef union
{
	uint8_t byte[2];
	uint16_t WORD;
}gpio_port_d_t;

typedef struct
{
	gpio_port_d_t PDDR;	// Port Data Direction Register
	gpio_port_d_t PDIR;	// Port Data Input Register
	gpio_port_d_t PDOR;	// Port Data Output Register
}gpio_register_t;


static uint8_t GPIO_Error(uint8_t port, uint8_t pin, uint8_t code);

static gpio_register_t portD = { .PDDR.WORD = 0, .PDIR.WORD = 0x1AAD, .PDOR.WORD = 0};

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void GPIO_PinInit(uint8_t port, uint8_t pin, uint8_t state)
{
	if(GPIO_Error(port, pin, 0))
	{	
		return; // Port does not exist or Pin index exceeds port size
	}
	else if(state > 1)
	{
		GPIO_Error(port, pin, GPIO_ERR_INVALID_DIRECTION);
		return;
	} 
	uint8_t offset = _offsetPort(port);
	_PDDR = (state)? _bitSet(_PDDR , pin + offset): _bitClr(_PDDR , pin + offset);
}

void GPIO_MaskInit(uint8_t port, uint16_t mask, uint8_t state)
{
	if(GPIO_Error(port, 0, 0)) // Port does not exist, don't care about pin
	{	
		return;
	}
	else if (state != INPUT && state != OUTPUT)
    {
        GPIO_Error(port, 0, GPIO_ERR_INVALID_DIRECTION);
        return;
    }
    else if((mask > 0xFF && (port == PORTA || port == PORTB)))
    {
		GPIO_Error(port, 0XFF, 0);
		return;		
	}
	
	uint8_t offset = _offsetPort(port);
	_PDDR = (state)? _maskOn(_PDDR , mask << offset): _maskOff(_PDDR , mask << offset);
}

void GPIO_SetPinState(uint8_t port, uint8_t pin, uint8_t state)
{
	uint8_t offset = _offsetPort(port);
	if(GPIO_Error(port, pin, 0)) 
	{	
		return;
	}
	else if(_bitGet(_PDDR, pin + offset) != OUTPUT)
	{
		GPIO_Error(port, pin, GPIO_ERR_WRITE_TO_INPUT);
		return;
	}
	
	switch(state)
	{
		case HIGH:
			_PDOR = _bitSet(_PDOR, pin + offset);
			break;

		case LOW:
			_PDOR = _bitClr(_PDOR, pin + offset);
			break;

		case TOGGLE:
			_PDOR = _bitToggle(_PDOR, pin + offset);
			break;

		default:
			GPIO_Error(port, pin, GPIO_ERR_INVALID_STATE);
			break;
	}
}

void GPIO_SetMaskedOutput(uint8_t port, uint16_t mask, uint8_t state)
{
	uint8_t offset = _offsetPort(port);

	if(GPIO_Error(port, 0, 0)) // Port does not exist, don't care about pin
	{	
		return;
	}
	
	// Loop through each bit in the port's range
	uint8_t range = (port == PORTA)? 2*sizePort: sizePort;
    for (uint8_t i = offset; i < range; i++)
    {
		// If the current bit is included in the mask and the pin is not set as OUTPUT
        if (_bitGet(_PDDR, i) != OUTPUT && _bitGet(mask, i - offset))
        {
            GPIO_Error(port, i - offset, GPIO_ERR_WRITE_TO_INPUT);
            return;
        }
    }
    
	switch(state)
	{
		case HIGH:
			_PDOR = _maskOn(_PDOR, mask << offset);
			break;

		case LOW:
			_PDOR = _maskOff(_PDOR, mask << offset);
			break;

		case TOGGLE:
			_PDOR = _maskToggle(_PDOR, mask << offset);
			break;

		default:
			GPIO_Error(port, 0, GPIO_ERR_INVALID_STATE); // 0x0 indicates don't care about pin
			break;
	}
}

uint8_t GPIO_ReadPin(uint8_t port, uint8_t pin)
{
	uint8_t offset = _offsetPort(port);
	if(GPIO_Error(port, pin, 0)) 
	{	
		return GPIO_ERR_INPUT;
	}
	else if(_bitGet(_PDDR, pin + offset) != INPUT)
	{
		GPIO_Error(port, pin, GPIO_ERR_READ_OUTPUT_AS_INPUT);
		return GPIO_ERR_INPUT;
	}
	
	// Read the pin state from the _PDDR register
	uint8_t state = _bitGet(_PDIR, pin + offset);
	return state;	// Return the read state
}

uint16_t GPIO_MaskRead(uint8_t port, uint16_t mask)
{
	uint8_t offset = _offsetPort(port);

	if(GPIO_Error(port, 0, 0)) // Port does not exist, don't care about pin
	{	
		return GPIO_ERR_INPUT_MASK;
	}
	
	// Loop through each bit in the port's range
	uint8_t range = (port == PORTA)? 2*sizePort: sizePort;
    for (uint8_t i = offset; i < range; i++)
    {
		// If the current bit is included in the mask and the pin is not set as OUTPUT
        if (_bitGet(_PDDR, i) != INPUT && _bitGet(mask, i - offset))
        {
            GPIO_Error(port, i - offset, GPIO_ERR_READ_OUTPUT_AS_INPUT);
            return GPIO_ERR_INPUT_MASK;
        }
    }
	
	uint16_t state = _maskGet(_PDIR, mask << offset);
	return (!port)? state >> offset: state;
}

/*******************************************************************************
 *******************************************************************************
                             LOCAL DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static uint8_t GPIO_Error(uint8_t port, uint8_t pin, uint8_t code) 
{
	uint8_t error = 0;
	
	if(!code)
	{
		if(port > 2)
		{
			error = 1;
			printf("\nError: specified port does not exist.\n");
		}
		else if((pin >= sizePort && (port == PORTA || port == PORTB)) || (pin >= 2*sizePort && port == PORTD))
		{
			if(pin != 0xFF)
			{
				error = 1;
				printf("\nError: attempting to access pin %d on port %c, which exceeds port size.", pin, 'A'+port);
			}
			else
			{
				error = 1;
				printf("\nError: attempting to access a pin of port %c which exceeds port size.", 'A'+port);
			}
		}
	}
	switch (code) 
	{
		case GPIO_ERR_NOTERROR:
			break;
		case GPIO_ERR_INVALID_DIRECTION:
			error = 1;
			printf("\nError: invalid direction mode specified. Use INPUT (0) or OUTPUT (1).");
			break;
		case GPIO_ERR_INVALID_STATE:
	    	error = 1;
	    	printf("\nError: invalid output state specified. Use HIGH (1), LOW (0), or TOGGLE (2).");
	    	break;
	    case GPIO_ERR_WRITE_TO_INPUT:
	    	error = 1;
	    	printf("\nWarning: trying to write to a pin configured as input. Operation ignored.");
	    	break;
	    case GPIO_ERR_READ_OUTPUT_AS_INPUT:
	    	error = 1;
	    	printf("\nWarning: attempting to read an output pin as input. Returning 0xFF or 0xFFFF as error value.");
	    	break;
	    default:
	    	error = 1;
	    	printf("Error: unknown GPIO error.\n");
	    	break;
    }
    
    return error;
}