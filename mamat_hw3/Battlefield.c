#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Battlefield.h"


PLIST Battlefield_Create()
{
	return List_Create(WarZone_Duplicate, WarZone_Delete, WarZone_Compare, WarZone_Print);
}
//******************************************************************************
//* function name: Battlefield_SoldExist
//* Description : checks if solider with given name exist anywhere in battlefield
//* Parameters: pointer to battlefield, id of soldier
//* Return Value: true if exist, false otherwise 
//******************************************************************************
bool Battlefield_SoldExist(PLIST battle,char *sold_id )
{
	PWarZone zone = List_Get_First(battle);
	while (zone != NULL)
	{
		if (WarZone_SoldExist(zone, sold_id))
			return true;
		zone = List_Get_Next(battle);
	}
	return false;
}
//******************************************************************************
//* function name: Battlefield_APCExist
//* Description : checks if apc with given name exist anywhere in battlefield
//* Parameters: pointer to battlefield, id of apc
//* Return Value: true if exist, false otherwise 
//******************************************************************************
bool Battlefield_APCExist(PLIST battle,char *id)
{
	PWarZone zone = List_Get_First(battle);
	while (zone != NULL)
	{
		if (WarZone_APCExist(zone, id))
			return true;
		zone = List_Get_Next(battle);
	}
	return false;
}
//******************************************************************************
//* function name: Battlefield_WZ_Exist
//* Description : checks if wz with given name exist anywhere in battlefield
//* Parameters: pointer to battlefield, id of wz
//* Return Value: true if exist, false otherwise 
//******************************************************************************
bool Battlefield_WZ_Exist(PLIST battle, char * id)
{
	PWarZone zone = List_Get_First(battle);
	while (zone != NULL)
	{
		if (WarZone_Compare(zone, id))
			return true;
		zone = List_Get_Next(battle);
	}
	return false;
}

//******************************************************************************
//* function name: Battlefield_Squad_Exist
//* Description : checks if squad with given name exist anywhere in battlefield
//* Parameters: pointer to battlefield, id of squad
//* Return Value: true if exist, false otherwise 
//******************************************************************************
bool Battlefield_Squad_Exist(PLIST battle, char * id)
{
	PWarZone zone = List_Get_First(battle);
	while (zone != NULL)
	{
		if (WarZone_SquadExist(zone, id))
			return true;
		zone = List_Get_Next(battle);
	}
	return false;
}
//******************************************************************************
//* function name: Battlefield_Emergency
//* Description : recieves pointer to a battlefield and  a
//* pointer of the emergency warzone and moves all squads from
//* other warzones to the given one
//* Parameters: pointer to warzone and pointer to battlefield
//* Return Value: NA 
//******************************************************************************
void Battlefield_Emergency(PLIST bf, PWarZone wz)
{
	if ((bf == NULL) || (wz == NULL))
	{
		printf(ARG_ERR_MSG);
		return;
	}
	PLIST emer_wz_squ_list = WarZone_Get_Squ_List(wz);
	char* emer_eze_id = WarZone_Get_ID(wz);
	PWarZone curr_wz = List_Get_First(bf);
	while (curr_wz != NULL)
	{
		if (WarZone_Compare(curr_wz, emer_eze_id))
		{
			curr_wz = List_Get_Next(bf);
			if (curr_wz == NULL)
			{
				return;
			}
		}
		PLIST squ_list = WarZone_Get_Squ_List(curr_wz);
		PSQUAD curr_squ = List_Get_First(squ_list);
		while (curr_squ != NULL)
		{
			List_Add_Elem(emer_wz_squ_list, curr_squ);
			List_Remove_Elem(squ_list,Squad_Name(curr_squ));
			curr_squ = List_Get_Next(squ_list);
		}
		curr_wz = List_Get_Next(bf);
	}
}
//******************************************************************************
//* function name: Battlefield_Move_Squad
//* Description : moves squad from one war zone to other one
//* Parameters: pointer to Battlefield, origin wz id, dest wz id, squad id
//* Return Value: Result of operation 
//******************************************************************************
Result Battlefield_Move_Squad(PLIST bf, char* src_wz_id,char* dest_wz_id,char* id)
{
	PWarZone src_wz = List_Get_Elem(bf, src_wz_id);
	PWarZone dest_wz = List_Get_Elem(bf, dest_wz_id);
	PLIST src_squ_list = WarZone_Get_Squ_List(src_wz);
	PLIST dest_squ_list = WarZone_Get_Squ_List(dest_wz);
	PSQUAD search = List_Get_First(src_squ_list);
	while (search != NULL)
	{
		if (Squad_Compare(search, id))
		{
			if (!List_Add_Elem(dest_squ_list, search))
			{
				printf(MALLOC_ERR_MSG);
				return FAILURE; // means malloc failed
			}
			List_Remove_Elem(src_squ_list, id);
			return SUCCESS;
		}
	}
	return FAILURE;
}
//******************************************************************************
//* function name: Battlefield_Add_Sold
//* Description : adds soldier to battlefield in given squad
//* Parameters: pointer to Battlefield ,wz id,  squad id, soldier id,soldier pos
//* Return Value: Result of operation 
//******************************************************************************
Result Battlefield_Add_Sold(PLIST bf, char* wz_id, char* sq_id, char* id,char* pos)
{
	PWarZone wz = List_Get_Elem(bf, wz_id);
	PLIST squ_list = WarZone_Get_Squ_List(wz);
	PSQUAD sq= List_Get_Elem(squ_list, sq_id);
	bool mem_failed = false;
	Squad_Add_Soldier(sq, id, pos, &mem_failed);
	if (mem_failed)
	{
		printf(MALLOC_ERR_MSG);
		return FAILURE;
	}
	return SUCCESS;
}
//******************************************************************************
//* function name: Battlefield_Add_APC
//* Description : adds apc to battlefield in given wz and squad
//* Parameters: pointer to Battlefield ,wz id,  squad id, apc id
//* Return Value: Result of operation 
//******************************************************************************
Result Battlefield_Add_APC(PLIST bf, char* wz_id, char* sq_id, char* id)
{
	PWarZone wz = List_Get_Elem(bf, wz_id);
	PLIST squ_list = WarZone_Get_Squ_List(wz);
	PSQUAD sq = List_Get_Elem(squ_list, sq_id);
	bool mem_failed = false;
	Squad_Add_APC(sq, id, &mem_failed);
	if (mem_failed)
	{
		printf(MALLOC_ERR_MSG);
		return FAILURE;
	}
	return SUCCESS;
}
//******************************************************************************
//* function name: Battlefield_Sold_ToAPC
//* Description : adds soldier to apc given in secifed place
//* Parameters: pointer to Battlefield ,wz id,  squad id, apc id, sold id
//* Return Value: Result of operation 
//******************************************************************************
Result Battlefield_Sold_ToAPC(PLIST bf, char* wz_id, char* sq_id, char* apc_id,char* id)
{
	PWarZone wz = List_Get_Elem(bf, wz_id);
	PLIST squ_list = WarZone_Get_Squ_List(wz);
	PSQUAD sq = List_Get_Elem(squ_list, sq_id);
	bool mem_failed = false;
	Squad_Insert_Sold_APC(sq, apc_id, id, &mem_failed);
	if (mem_failed)
	{
		printf(MALLOC_ERR_MSG);
		return FAILURE;
	}
	return SUCCESS;
}