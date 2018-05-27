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
