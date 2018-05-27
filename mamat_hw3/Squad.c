#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Squad.h"

typedef struct Squad {
	PLIST sold_list;
	PLIST apc_list;
	int size;
	char *ID;
}SQUAD;

//******************************************************************************
//* function name: Squad_Create 
//* Description : Creates new squad
//* Parameters: copy,free,compare and print functions by pointers for both solider
//*				and apc structs, "1" indicates solider func' and "2" for apc func'
//* Return Value: pointer to the squad 
//******************************************************************************
PSQUAD Squad_Create(char *id, Copy_Function copy1, Free_Function free1, Compare_Function comp1, Print_Func print1,
	Copy_Function copy2, Free_Function free2, Compare_Function comp2, Print_Func print2)
{
	if ((copy1 == NULL) || (free1 == NULL) || (comp1 == NULL) || (print1 == NULL)
		|| (copy2 == NULL) || (free2 == NULL) || (comp2 == NULL) || (print2 == NULL)||(id==NULL))
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PSQUAD squ = (PSQUAD)malloc(sizeof(SQUAD));
	if (squ == NULL)
	{
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	squ->sold_list = List_Create(copy1, free1, comp1, print1);
	if (squ->sold_list == NULL)
	{
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	squ->apc_list = List_Create(copy2, free2, comp2, print2);
	if (squ->apc_list == NULL)
	{
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	squ->ID = (char*)malloc(MAX_ID_LENGTH + 1);
	if (squ->ID == NULL)
	{
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	strcpy(squ->ID, id);
	squ->size = 0;
	return squ;
}
//******************************************************************************
//* function name: Squad_Delete 
//* Description : Deletes the squad
//* Parameters: pointer to squad
//* Return Value: NA
//******************************************************************************
void Squad_Delete(PSQUAD squ)
{
	if (squ == NULL)
	{
		printf(ARG_ERR_MSG);
		return ;
	}
	free(squ->ID);
	List_Delete(squ->sold_list);
	List_Delete(squ->apc_list);
	free(squ);
}
//******************************************************************************
//* function name: Squad_Print 
//* Description : Prints the squad
//* Parameters: pointer to squad
//* Return Value: NA
//******************************************************************************
void Squad_Print(PSQUAD squ)
{
	if (squ == NULL)
	{
		printf(ARG_ERR_MSG);
		return ;
	}
	printf("Squad: %s , Total troops: %d\n", squ->ID, squ->size);
	printf("APCs:\n");
	List_Print(squ->apc_list);
	printf("Soldiers:\n");
	List_Print(squ->sold_list);
}
//******************************************************************************
//* function name: Squad_Duplicate
//* Description : Duplicates the squad
//* Parameters: pointer to squad
//* Return Value: pointer to Duplicated squad
//******************************************************************************
PSQUAD Squad_Duplicate(PSQUAD old_squ)
{
	if (old_squ == NULL)
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PSQUAD new_squ = Squad_Create(old_squ->ID, List_Get_Copy(old_squ->sold_list), List_Get_Free(old_squ->sold_list)
		, List_Get_Comp(old_squ->sold_list), List_Get_Print(old_squ->sold_list),
		List_Get_Copy(old_squ->apc_list), List_Get_Free(old_squ->apc_list), List_Get_Comp(old_squ->apc_list), List_Get_Print(old_squ->apc_list));
	if (new_squ == NULL)
	{
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	bool mem_failed = false;
	new_squ->size = old_squ->size;
	List_Duplicate(old_squ->apc_list, new_squ->apc_list,&mem_failed);
	if (mem_failed)
	{
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	List_Duplicate(old_squ->sold_list, new_squ->sold_list,&mem_failed);
	if (mem_failed)
	{
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	return new_squ;
}
//******************************************************************************
//* function name: Squad_Add_Soldier
//* Description : creates a soldier and adds to given squad
//* Parameters: pointer to squad,soldier id and pos, boolain that indicates if malloc failed
//* Return Value: result of add
//******************************************************************************
Result Squad_Add_Soldier(PSQUAD squ, char *id,char* pos ,Pbool mem_failed)
{
	if ((squ == NULL) || (id == NULL)||(pos==NULL))
	{
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	PSOLDIER new_sold = Soldier_Create(id, pos);
	if (new_sold == NULL)
	{
		printf(MALLOC_ERR_MSG);
		*mem_failed = true;
		return FAILURE;
	}
	if (!List_Add_Elem(squ->sold_list, new_sold))
	{
		printf(MALLOC_ERR_MSG);
		*mem_failed = true;
		return FAILURE;
	}
	Soldier_Delete(new_sold);
	squ->size++;
	return SUCCESS;
}
//******************************************************************************
//* function name: Squad_Add_APC
//* Description : creates a apc and adds to given squad
//* Parameters: pointer to squad,apc id , boolain that indicates if malloc failed
//* Return Value: result of add
//******************************************************************************
Result Squad_Add_APC(PSQUAD squ, char *id, Pbool mem_failed)
{
	if ((squ == NULL) || (id == NULL))
	{
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	PAPC new_apc = APC_Create(id);
	if (new_apc == NULL)
	{
		printf(MALLOC_ERR_MSG);
		*mem_failed = true;
		return FAILURE;
	}
	if (!List_Add_Elem(squ->apc_list, new_apc))
	{
		printf(MALLOC_ERR_MSG);
		*mem_failed = true;
		return FAILURE;
	}
	APC_Delete(new_apc);
	return SUCCESS;
}
//******************************************************************************
//* function name: Squad_Insert_Sold_APC
//* Description : recieves pointer to squad, apc ID and soldier ID
//* and adds soldier to apc stack if possible
//* Parameters: pointer to squad and ID of apc and soldier
//* Return Value: Success if soldier was pushed into apc stack
//* and Failure else
//******************************************************************************
Result Squad_Insert_Sold_APC(PSQUAD squ, char* apcID, char* soldID, Pbool mem_failed)
{
	if ((squ == NULL) || (apcID == NULL) || (soldID == NULL))
	{
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	PAPC apcexists = List_Get_Elem(squ->apc_list, apcID);
	PSOLDIER soldexists = List_Get_Elem(squ->sold_list, soldID);
	if ((apcexists == NULL) || (soldexists == NULL))//no such apc or soldier in squad list
		return FAILURE;
	else
	{
		PSOLDIER dup = Soldier_Duplicate(soldexists);
		if (dup == NULL)
		{
			*mem_failed = true;
			printf(MALLOC_ERR_MSG);
			return FAILURE;
		}
		Result ins = APC_Insert_Soldier(apcexists, dup);
		if (ins == FAILURE) // if apc is full
		{
			Soldier_Delete(dup);
			return FAILURE;
		}
		List_Remove_Elem(squ->sold_list, soldID);
		return SUCCESS;
	}
}
//******************************************************************************
//* function name: Squad_APC_Pop 
//* Description : receives pointer to squad and name of apc, pops a soldier
//*				 from that apc(if exists) and adds it to soldier list
//* Parameters: pointer to squad and ID of apc, mem_failed indicator
//* Return Value: Success if soldier was popped from given apc and Failure else
//******************************************************************************
Result Squad_APC_Pop(PSQUAD squ, char* apcID, Pbool mem_failed)
{
	if ((squ == NULL) || (apcID == NULL))
	{
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	PAPC exists = List_Get_Elem(squ->apc_list, apcID);
	if (exists == NULL)//no such apc in squad list
		return FAILURE;
	else
	{
		PSOLDIER popped = APC_Pop(exists);
		if (popped == NULL)//soldier wasn't popped form apc
			return FAILURE;
		else
		{
			Result added = List_Add_Elem(squ->sold_list, popped);
			Soldier_Delete(popped);
			if (added == FAILURE)
			{
				printf(MALLOC_ERR_MSG);
				*mem_failed = true;
				return FAILURE;
			}
			else
				return SUCCESS;
		}
	}
}
//******************************************************************************
//* function name: Squad_Delete_Soldier 
//* Description : recieves soldID and checks if exists in squad soldier list
//* and if it does deletes it
//* Parameters: pointer to squad and ID of soldier
//* Return Value: Success if deleted soldier and Failure else
//******************************************************************************
Result Squad_Delete_Soldier(PSQUAD squ, char* soldID)
{
	if ((squ == NULL) || (soldID == NULL))
	{
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	PSOLDIER exists = List_Get_Elem(squ->sold_list, soldID);
	if (exists == NULL)
		return FAILURE;
	else
	{
		List_Remove_Elem(squ->sold_list, soldID);
		squ->size--;
	}
	return SUCCESS;
}
//******************************************************************************
//* function name: Squad_Delete_APC 
//* Description :  if apc with given id exists in squad ,deletes it
//* Parameters: pointer to squad and ID of apc
//* Return Value: Success if deleted apc and Failure else
//******************************************************************************
Result Squad_Delete_APC(PSQUAD squ, char* apcID)
{
	if ((squ == NULL) || (apcID == NULL))
	{
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	PAPC exists = List_Get_Elem(squ->apc_list, apcID);
	if (exists == NULL)
		return FAILURE;
	squ->size -= APC_soldier_count(exists);
	if (List_Remove_Elem(squ->apc_list, apcID))
		return SUCCESS;
	return FAILURE;
}
//******************************************************************************
//* function name : Squad_SoldExist
//* Description : checks if soldier with given name exists in  squad
//* Parameters: pointer to squad and id of soldier
//* Return Value: true if exist, false otherwise
//******************************************************************************
bool Squad_SoldExist(PSQUAD squ, char * id)
{
	if ((squ == NULL) || (id == NULL))
	{
		printf(ARG_ERR_MSG);
		return false;
	}
	if (List_Get_Elem(squ->sold_list, id) != NULL)
		return true;
	PAPC curr_apc= List_Get_First(squ->apc_list);
	while (curr_apc != NULL)
	{
		if (APC_SoldExist(curr_apc, id))
			return true;
		curr_apc = List_Get_Next(squ->apc_list); 
	}
	return false;
}

//******************************************************************************
//* function name : Squad_APCExist
//* Description : checks if apc with given name exists in squad
//* Parameters: pointer to squad and id of apc
//* Return Value: true if exist, false otherwise
//******************************************************************************
bool Squad_APCExist(PSQUAD squ, char * id)
{
	if ((squ == NULL) || (id == NULL))
	{
		printf(ARG_ERR_MSG);
		return false;
	}
	PAPC curr_apc = List_Get_First(squ->apc_list);
	while (curr_apc != NULL)
	{
		if (APC_SoldExist(curr_apc, id))
			return true;
		curr_apc = List_Get_Next(squ->apc_list);
	}
	return false;
}
//******************************************************************************
//* function name: Squad_Compare
//* Description : checks if squad given is with name given
//* Parameters: pointer to warzone, id of warzone
//* Return Value: true if exist, false otherwise 
//******************************************************************************
bool Squad_Compare(Element squad_t, Element name_t)
{
	PSQUAD squad = (PSQUAD)squad_t;
	char* name = (char*)name_t;
	if (!strcmp(squad->ID, name))
		return true;
	return false;
}




