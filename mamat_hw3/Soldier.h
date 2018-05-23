#ifndef _Soldier_h
#define _Soldier_h
#include "defs.h"

typedef  struct Soldier_t* PSOLDIER;
PSOLDIER Soldier_Duplicate(PSOLDIER Soldier);
void Soldier_Print(PSOLDIER Soldier);
PSOLDIER Soldier_Create(char *id, char *pos);
void Soldier_Delete(PSOLDIER sold);
#endif