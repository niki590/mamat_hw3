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
		if (WarZone_Compare(zone, id))
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
	PWarZone next_wz = NULL;
	PLIST emer_wz_squ_list = WarZone_Get_Squ_List(wz);
	PWarZone curr_wz = List_Get_First(bf);
	if (WarZone_Compare(curr_wz, wz))
	{
		curr_wz = List_Get_Next(bf);
	}
	while (curr_wz != NULL)
	{
		next_wz = List_Get_Next(bf);
		if (WarZone_Compare(next_wz, wz))
		{
			next_wz = List_Get_Next(bf);
		}
		PSQUAD next_squ = NULL;
		PLIST squ_list = WarZone_Get_Squ_List(curr_wz);
		PSQUAD curr_squ = List_Get_First(squ_list);
		while (curr_wz != NULL)
		{
			next_squ = List_Get_Next(squ_list);
			List_Add_Elem(emer_wz_squ_list, curr_squ);
			List_Remove_Elem(squ_list, curr_squ);
			curr_squ = next_squ;
		}
		curr_wz = next_wz;
	}
}