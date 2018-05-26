#ifndef _APC_h
#define _APC_h
#include "defs.h"
#include "Soldier.h"

typedef struct APC_t* PAPC;
PAPC  APC_Create(Element apc_id);
int isFull(Element check);
int isEmpty(Element check);
Result APC_Insert_Soldier(Element apc, Element soldier);
void APC_Print(Element nag);
PSOLDIER APC_Pop(Element apc);
Element APC_Duplicate(Element old);
void APC_Delete(Element apc);
bool APC_Compare(Element apc1_t, Element apc2_t);
int APC_soldier_count(PAPC nag);
bool APC_SoldExist(PAPC nag, char* id);
#endif
