#ifndef _Soldier_h
#define _Soldier_h
#include "defs.h"

typedef  struct Soldier_t* PSOLDIER;
PSOLDIER Soldier_Duplicate(Element Soldier_t);
void Soldier_Print(Element Soldier_t);
PSOLDIER Soldier_Create(Element id_t, Element pos_t);
void Soldier_Delete(Element sold_t);
bool Soldier_Compare(Element sol_t, Element id_t);
#endif