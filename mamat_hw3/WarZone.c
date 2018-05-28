#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "WarZone.h"

typedef struct WarZone {
	char * ID;
	PLIST squ_list;
	int lvl;
}WARZONE;
//******************************************************************************
//* function name: WarZone_Create 
//* Description : Creates new WarZone
//* Parameters: copy,free,compare and print functions by pointers, wz id
//* Return Value: pointer to the WarZone 
//******************************************************************************
PWarZone WarZone_Create(char *id, Copy_Function copy1, Free_Function free1, Compare_Function comp1, Print_Func print1)
{
	if (id == NULL)
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PWarZone wz = (PWarZone)malloc(sizeof(WARZONE));
	if (wz == NULL)
	{
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	wz->squ_list = List_Create(copy1, free1, comp1, print1);
	if (wz->squ_list == NULL)
	{
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	wz->ID = (char*)malloc(MAX_ID_LENGTH + 1);
	if (wz->ID == NULL)
	{
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	strcpy(wz->ID, id);
	wz->lvl = 0;
	return wz;
}
//******************************************************************************
//* function name: WarZone_Duplicate
//* Description : Duplicates the WarZone
//* Parameters: pointer to WarZone
//* Return Value: pointer to Duplicated WarZone
//******************************************************************************
Element WarZone_Duplicate(Element wz)
{
	if (wz == NULL)
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PWarZone old_wz = (PWarZone)wz;
	PWarZone new_wz = WarZone_Create(old_wz->ID, List_Get_Copy(old_wz->squ_list), List_Get_Free(old_wz->squ_list)
		, List_Get_Comp(old_wz->squ_list), List_Get_Print(old_wz->squ_list));
	if (new_wz == NULL)
	{
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	new_wz->lvl = old_wz->lvl;
	bool mem_failed = false;
	List_Duplicate(old_wz->squ_list, new_wz->squ_list, &mem_failed);
	if (mem_failed)
	{
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	return new_wz;
}
//******************************************************************************
//* function name: WarZone_Delete
//* Description : Deletes the WarZone
//* Parameters: pointer to WarZone
//* Return Value: NA
//******************************************************************************
void WarZone_Delete(Element WarZone) {
	if (WarZone == NULL)
	{
		printf(ARG_ERR_MSG);
		return;
	}
	PWarZone wz = (PWarZone)WarZone;
	free(wz->ID);
	List_Delete(wz->squ_list);
	free(wz);
}
//******************************************************************************
//* function name: WarZone_Print 
//* Description : Prints the WarZone
//* Parameters: pointer to WarZone
//* Return Value: NA
//******************************************************************************
void WarZone_Print(Element WarZone) {
	if (WarZone == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	PWarZone wz = (PWarZone)WarZone;
	printf("WarZone: %s , Alert State: %d\n\n", wz->ID, wz->lvl);
	List_Print(wz->squ_list);
}
//******************************************************************************
//* function name:WarZone_Raise_Alert 
//* Description : raises alert lvl of warzone, and activates emergency protocol if needed
//* Parameters: pointer to WarZone
//* Return Value: new alert lvl
//******************************************************************************
int WarZone_Raise_Alert(PWarZone wz)
{
	if (wz == NULL)
	{
		printf(ARG_ERR_MSG);
		return -1;
	}
	wz->lvl++;
	if (wz->lvl == 3)
	{
		wz->lvl = 0;
		return wz->lvl;
	}
	else
	{
		return wz->lvl;
	}
}
//******************************************************************************
//* function name: WarZone_SoldExist
//* Description : checks if solider with given name exist in given warzone
//* Parameters: pointer to warzone, id of soldier
//* Return Value: true if exist, false otherwise 
//******************************************************************************
bool WarZone_SoldExist(PWarZone zone,char* id)
{
	if (zone == NULL)
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PSQUAD curr_sq = List_Get_First(zone->squ_list);
	while (curr_sq != NULL)
	{
		if (Squad_SoldExist(curr_sq, id))
			return true;
		curr_sq = List_Get_Next(zone->squ_list);
	}
	return false;
}
//******************************************************************************
//* function name: WarZone_APCExist
//* Description : checks if apc with given name exist in given warzone
//* Parameters: pointer to warzone, id of apc
//* Return Value: true if exist, false otherwise 
//******************************************************************************
bool WarZone_APCExist(PWarZone zone, char* id)
{
	if (zone == NULL)
	{
		printf(ARG_ERR_MSG);
		return false;
	}
	PSQUAD curr_sq = List_Get_First(zone->squ_list);
	while (curr_sq != NULL)
	{
		if (Squad_APCExist(curr_sq, id))
			return true;
		curr_sq = List_Get_Next(zone->squ_list);
	}
	return false;
}
//******************************************************************************
//* function name: WarZone_Compare
//* Description : checks if warzone given is with name given
//* Parameters: pointer to warzone, id of warzone
//* Return Value: true if exist, false otherwise 
//******************************************************************************
bool WarZone_Compare(Element WarZone_t, Element name_t)
{
	PWarZone WarZone = (PWarZone)WarZone_t;
	char* name = (char*)name_t;
	if (!strcmp(WarZone->ID, name))
		return true;
	return false;
}
//******************************************************************************
//* function name: WarZone_SquadExist
//* Description : checks if squad with given name exist in given warzone
//* Parameters: pointer to warzone, id of squad
//* Return Value: true if exist, false otherwise 
//******************************************************************************
bool WarZone_SquadExist(PWarZone zone, char* id)
{
	if (zone == NULL)
	{
		printf(ARG_ERR_MSG);
		return false;
	}
	PSQUAD curr_sq = List_Get_First(zone->squ_list);
	while (curr_sq != NULL)
	{
		if (Squad_Compare(curr_sq, id))
			return true;
		curr_sq = List_Get_Next(zone->squ_list);
	}
	return false;
}
//******************************************************************************
//* function name: Battlefield_Add_Squad
//* Description : creates squad with given name and adds it to given wz
//* Parameters: pointer to wz, id of squad
//* Return Value: SUCCESS or FAILURE 
//******************************************************************************
Result WarZone_Add_Squad(PWarZone wz, char *id)
{
	PSQUAD new = Squad_Create(id, Soldier_Duplicate, Soldier_Delete, Soldier_Compare, Soldier_Print,
		APC_Duplicate, APC_Delete, APC_Compare, APC_Print);
	if (new == NULL)
	{
		printf(MALLOC_ERR_MSG);
		return FAILURE;
	}
	if (!List_Add_Elem(wz->squ_list, new))
	{
		printf(MALLOC_ERR_MSG);
		return FAILURE;
	}
	Squad_Delete(new);
	return SUCCESS;
}
//******************************************************************************
//* function name: Battlefield_Del_Squad
//* Description : Deletes squad with given name and adds it to given wz
//* Parameters: pointer to wz, id of squad
//* Return Value: SUCCESS or FAILURE 
//******************************************************************************
void WarZone_Del_Squad(PWarZone wz, char *id)
{
		List_Remove_Elem(wz->squ_list, id);
}
//******************************************************************************
//* function name: WarZone_Get_Squ_List
//* Description : gives access to squ_list
//* Parameters: pointer to warzone
//* Return Value: pointer to squ_list of wz
//******************************************************************************
PLIST WarZone_Get_Squ_List(PWarZone wz)
{
	if (wz == NULL)
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	return wz->squ_list;
}
//******************************************************************************
//* function name: WarZone_Get_OD
//* Description : returns given ez id
//* Parameters: pointer to warzone
//* Return Value: pointer to name
//******************************************************************************
char* WarZone_Get_ID(PWarZone wz)
{
	return wz->ID;
}