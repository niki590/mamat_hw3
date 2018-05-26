#ifndef _WARZONE_H_
#define _WARZONE_H_
#include "defs.h"
#include "List.h"
#include "Squad.h"

typedef struct WarZone* PWarZone;
typedef Element(*Copy_Function)(Element);
typedef void(*Free_Function)(Element);
typedef bool(*Compare_Function)(PKey, PKey);
typedef void(*Print_Func)(Element);
typedef struct WarZone* PWarZone;
PWarZone WarZone_Create(char * wzID, Copy_Function copy1, Free_Function free1, Compare_Function comp1, Print_Func print1);
bool WarZone_SoldExist(PWarZone zone, char* id);
bool WarZone_APCExist(PWarZone zone, char* id);
Element WarZone_Duplicate(Element wz);
void WarZone_Delete(Element WarZone);
void WarZone_Print(Element WarZone);
int WarZone_Raise_Alert(PWarZone wz);
bool WarZone_Compare(Element WarZone_t, Element name_t);

#endif