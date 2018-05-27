#ifndef _Defs_h
#define _Defs_h

/**includes & defines**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef void* Element;
typedef Element* PElement;
typedef void* PKey;
typedef bool* Pbool;

#define MAX_ARG 10					// for main input line
#define MAX_INPUT_LINE 100			// for main input line
#define APC_MAX_Soldiers 6			// for APC
#define MAX_ID_LENGTH 8			    // for Structs IDs
#define MAX_LINE_LENGTH 256  
#define MAX_VALUES_CMD 6			// max num of fields in command

#define MALLOC_ERR_MSG "Error: Cant perform Malloc\n"
#define ARG_ERR_MSG "Error: Function's Args Error\n"



typedef enum Result_ { FAILURE, SUCCESS } Result;

#endif
