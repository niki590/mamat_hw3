#ifndef _LIST_H_
#define _LIST_H_
#include "defs.h"

typedef  struct List_t* PLIST;
typedef Element(*Copy_Function)(Element);
typedef void(*Free_Function)(Element);
typedef bool(*Compare_Function)(PKey, PKey);
typedef void(*Print_Func)(Element);
PLIST List_Create(Copy_Function copy, Free_Function free, Compare_Function comp, Print_Func print);
void List_Delete(PLIST list);
void List_Print(PLIST list);

#endif
