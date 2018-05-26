#ifndef _SQUAD_H_
#define _SQUAD_H_
#include "defs.h"
#include "List.h"
#include "Soldier.h"
#include "APC.h"

typedef struct Squad* PSQUAD;
typedef Element(*Copy_Function)(Element);
typedef void(*Free_Function)(Element);
typedef bool(*Compare_Function)(PKey, PKey);
typedef void(*Print_Func)(Element);
PSQUAD Squad_Create(char *id, Copy_Function copy1, Free_Function free1, Compare_Function comp1, Print_Func print1,
	Copy_Function copy2, Free_Function free2, Compare_Function comp2, Print_Func print2);
void Squad_Delete(PSQUAD squ);
void Squad_Print(PSQUAD squ);
PSQUAD Squad_Duplicate(PSQUAD old_squ);
Result Squad_Add_Soldier(PSQUAD squ, char *id, char* pos, bool mem_failed);
Result Squad_Insert_Sold_APC(PSQUAD squ, char* apcID, char* soldID, bool mem_failed);
Result Squad_APC_Pop(PSQUAD squ, char* apcID, bool mem_failed);
Result Squad_Delete_Soldier(PSQUAD squ, char* soldID);
Result Squad_Delete_APC(PSQUAD squ, char* apcID);


#endif