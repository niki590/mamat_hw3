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
Result List_Add_Elem(PLIST list, Element item);
Result List_Remove_Elem(PLIST list, PKey item);
Element List_Get_First(PLIST list);
Element List_Get_Next(PLIST list);
void List_Duplicate(PLIST src, PLIST dst, bool mem_failed);
Element List_Get_Elem(PLIST list, PKey key);
Copy_Function List_Get_Copy(PLIST list);
Free_Function List_Get_Free(PLIST list);
Compare_Function List_Get_Comp(PLIST list);
Print_Func List_Get_Print(PLIST list);

#endif
