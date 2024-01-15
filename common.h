#ifndef ASM_OVER_LANG_COMMON_H
#define ASM_OVER_LANG_COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef char				int8;
typedef unsigned char		uint8;
typedef signed char			sint8;
typedef char*				pint8;
typedef unsigned char*		puint8;
typedef signed char*		psint8;

typedef short				int16;
typedef unsigned short		uint16;
typedef signed short		sint16;
typedef short*				pint16;
typedef unsigned short*		puint16;
typedef signed short*		psint16;

typedef int 				int32;
typedef unsigned int 		uint32;
typedef signed int 			sint32;
typedef int*				pint32;
typedef unsigned int*		puint32;
typedef signed int*			psint32;

#define ASM_OVER_LANG_ERROR(err_msg, ...)				\
fprintf(stderr, err_msg, ##__VA_ARGS__);				\
exit(EXIT_FAILURE);						

#define ASM_OVER_LANG_ASSERT(cond, err_msg, ...)		\
if(!(cond))												\
{														\
	fprintf(stderr, err_msg, ##__VA_ARGS__);			\
	exit(EXIT_FAILURE);									\
}

#define ASCII(x) (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'a') ? true : false

#endif
