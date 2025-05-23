/* ---------------------------------------------------
 * nstdio.c
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
#include "nstdio.h"

#define TOUPPER(c) (((c) >= 'a' && (c) <= 'z')? 'A'+(c)-'a' : (c))
#define TOLOWER(c) (((c) >= 'A' && (c) <= 'Z')? 'a'+(c)-'A' : (c))

#define isDigit(c) ((c) >= '0' && (c) <= '9')
#define isByte(c) (isDigit(c) || (TOUPPER(c) >= 'A' && TOUPPER(c) <= 'F'))
#define isLetter(c) (TOUPPER(c) >= 'A' && TOUPPER(c) <= 'Z')

static uint8_t isInt(const char *str);
static uint8_t isFloat(const char *str);
static uint8_t isHex(const char *str);
static int strToInt(const char *str);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void nscaf(scanCallback *callbacks, void **destinations, uint8_t count)
{

}

uint8_t readInt(const char *str, void *dest)
{
	if(!isInt(str))
	{
		printf("[ERROR] '%s' is not a valid int.\n", str);
		return 0;
	}
	*((int *)dest) = strToInt(str);

	return 1;
}

uint8_t readFloat(const char *str, void *dest)
{
	if(!isFloat(str))
	{
		printf("[ERROR] '%s' is not a valid float.\n", str);
		return 0;
	}
	*((float *)dest) = strToFloat(str);

	return 1;
}

uint8_t readHex(const char *str, void *dest);
uint8_t readChar(const char *str, void *dest);
uint8_t readString(const char *str, void *dest);



/*******************************************************************************
 *******************************************************************************
                             LOCAL DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static uint8_t isInt(const char *str)
{
	if(*str == '+' || *str == '-')
	{
		str++;
	}
	while(*str)
	{
		if(!isDigit(*str++))
		{
			return 0;
		}
	}
	return 1;
}

static uint8_t isFloat(const char *str)
{
	uint8_t has_dot = 0;
	if(*str == '+' || *str == '-')
	{
		str++;
	}
	while(*str)
	{
		if(*str == '.' || *str == ',')
		{
			if(has_dot)
			{
				return 0;
			}
			has_dot = 1;
			str++;
		}
		else if(!isDigit(*str++))
		{
			return 0;
		}
	}
	return 1;
}
static uint8_t isHex(const char *str)
{
	if(*str++ != '0')
	{
		return 0;
	}
	if(TOUPPER(*str++) != 'X')
	{
		return 0;
	}
	while(*str)
	{
		if(!isByte(*str++))
		{
			return 0;
		}
	}
	return 1;
}

static int strToInt(const char *str)
{
	uint8_t i = 0;
	int num;
	int8_t sign = 1;

	if(str[i] == '+' || str[i] == '-')
	{
		sign = (str[i++] == '+')? 1: -1;
	}
	for(; str[i] != '\0'; i++)
	{
		num = num*10 + (str - '0');
	}

	return sign * num;
}

static int strToInt(const char *str)
{
	uint8_t i = 0;
	float num;
	float sign = 1;

	if(str[i] == '+' || str[i] == '-')
	{
		sign = (str[i++] == '+')? 1: -1;
	}
	for(; str[i] != '\0' && str[i] != '.' && str[i] != ','; i++)
	{
		num = num*10 + (str - '0');
	}

	if(str[i++] == '\0')
	{
		return sign * num;
	}

	uint8_t dot_index;
	for(dot_index = i - 1; str[i] != '\0'; i++)
	{
		num = num + (str - '0') / pow(10, i-dot_index);
	}

	return sign * num;
}
