#ifndef _APC_h
#define _APC_h
#include "defs.h"
#include "Soldier.h"

typedef struct APC_t* PAPC;
PAPC  APC_Create(char* id);
int isFull(PAPC check);
int isEmpty(PAPC check);
Result APC_Insert_Soldier(PAPC apc, PSOLDIER soldier);
void APC_Print(PAPC nag);
PSOLDIER APC_Pop(PAPC apc);
PAPC APC_Duplicate(PAPC old);
void APC_Delete(PAPC apc);

#endif
