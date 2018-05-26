#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "APC.h"
#include "Soldier.h"

typedef struct APC_t
{
	char *ID;
	int top;
	int capacity;
	PSOLDIER* array;
}APC;
//******************************************************************************
//* function name: APC_Create 
//* Description : Creates apc
//* Parameters: the ID of apc as a char*
//* Return Value: pointer to the apc created
//******************************************************************************
PAPC  APC_Create(Element apc_id)
{
	char* id = (char*)apc_id;
	if (id == NULL)
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	if ((id == NULL) || (strlen(id)>MAX_ID_LENGTH))
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PAPC newapc = (PAPC)malloc(sizeof(APC));
	if (newapc == NULL)  //malloc check
	{
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	newapc->ID = (char*)malloc(strlen(id) + 1);
	if (newapc->ID == NULL)  //malloc check
	{
		printf(MALLOC_ERR_MSG);
		return NULL;
	} 
	strcpy(newapc->ID, id);
	newapc->top = -1;
	newapc->capacity = APC_MAX_Soldiers;
	newapc->array = (PSOLDIER*)malloc(6 * sizeof(PSOLDIER));
	if (newapc->array == NULL)
	{
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	for (int i = 0; i <= APC_MAX_Soldiers-1; i++)
		newapc->array[i] = NULL;
	return newapc;
}
//******************************************************************************
//* function name: isFull
//* Description : check if apc is full
//* Parameters: pointer to apc
//* Return Value: 1 for full, 0 for not full
//******************************************************************************
int isFull(Element check_t)
{
	PAPC check = (PAPC)check_t;
	return check->top == check->capacity - 1;
}
//******************************************************************************
//* function name: isEmpty
//* Description : check if apc is empty
//* Parameters: pointer to apc
//* Return Value: 1 for empty, 0 for not empty
//******************************************************************************
int isEmpty(Element check_t)
{
	PAPC check = (PAPC)check_t;
	return check->top == (-1);
}
//******************************************************************************
//* function name: APC_Insert_Soldier
//* Description : inserts existing soldier into given apc
//* Parameters: pointer to apc, pointer to soldier
//* Return Value: SUCCESS or FAILURE of inserting
//******************************************************************************
Result APC_Insert_Soldier(Element apc_t, Element soldier_t)
{
	PAPC apc = (PAPC)apc_t;
	PSOLDIER soldier = (PSOLDIER)soldier_t;
	if ((apc == NULL)||(soldier==NULL))
	{
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	if (isFull(apc))
	{
		printf("Error: APC is Full\n");
		return FAILURE;
	}
	(apc->top)++;
	apc->array[apc->top] = soldier;
	return SUCCESS;
}
//******************************************************************************
//* function name: APC_Print
//* Description : Prints all the needed fields of given apc
//* Parameters: pointer to apc
//* Return Value: NA
//******************************************************************************
void APC_Print(Element nag_t)
{
	PAPC nag = (PAPC)nag_t;
	if (nag == NULL)
	{
		printf(ARG_ERR_MSG);
		return ;
	}
	if (nag == NULL) {
		printf(ARG_ERR_MSG);
		return;
	}
	if (nag->top == -1)
	{
		printf("%s , Occupancy: 0/%d\n", nag->ID, APC_MAX_Soldiers);
		return;
	}
	printf("%s , Occupancy: %d/%d\n", nag->ID, (nag->top) + 1, APC_MAX_Soldiers);
	int k = (nag->top) + 1;
	for (int i = 1; i <= (nag->top) + 1; i++)
	{
		printf("Seat %d: ", i);
		Soldier_Print(nag->array[k - i]);
	}
}
//******************************************************************************
//* function name: APC_Pop
//* Description : Pop the last in top of apc stack and return pointer to him
//* Parameters: pointer to apc
//* Return Value: pointer to popped soldier
//******************************************************************************
PSOLDIER APC_Pop(Element apc_t)
{
	PAPC apc = (PAPC)apc_t;
	if (apc == NULL)
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	if (isEmpty(apc))
	{
		printf("Error: APc is Empty\n");
		return NULL;
	}
	PSOLDIER save = apc->array[apc->top];
	apc->array[apc->top] = NULL;
	(apc->top)--;
	return save;
}
//******************************************************************************
//* function name: APC_Duplicate
//* Description : Duplicate given apc and all the fields of it
//* Parameters: pointer to apc
//* Return Value: pointer to the new duplicated apc
//******************************************************************************
Element APC_Duplicate(Element old_t)
{
	PAPC old = (PAPC)old_t;
	if (old == NULL)
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PAPC new = APC_Create(old->ID);
	new->top = old->top;
	new->capacity = old->capacity;
	for (int i = 0; i <= old->top; i++)
	{
		new->array[i] = Soldier_Duplicate(old->array[i]);
		if (new->array[i] == NULL)
		{
			printf(MALLOC_ERR_MSG);
			return NULL;
		}
	}
	return new;
}
//******************************************************************************
//* function name: APC_Delete
//* Description : Delete given apc and all its fields
//* Parameters: pointer to apc
//* Return Value: NA
//******************************************************************************
void APC_Delete(Element apc_t)
{
	PAPC apc = (PAPC)apc_t;
	if (apc == NULL)
	{
		printf(ARG_ERR_MSG);
		return;
	}
	for (int i = 0; i<=apc->top; i++)
		Soldier_Delete(apc->array[i]);
	free(apc->array);
	free(apc->ID);
	free(apc);
}
//******************************************************************************
//* function name: APC_Compare
//* Description : Compares two apc by id
//* Parameters: pointeres to the apc's
//* Return Value: bool
//******************************************************************************
bool APC_Compare(Element apc1_t,Element name_t)
{
	PAPC apc1 = (PAPC)apc1_t;
	char* name = (char*)name_t;
	if (!strcmp(apc1->ID, name))
		return true;
	return false;
}

//******************************************************************************
//* function name: APC_soldier_count
//* Description : returs num of sold' in apc
//* Parameters: pointer to apc
//* Return Value: num of sold'
//******************************************************************************
int APC_soldier_count(PAPC nag)
{
	if (nag == NULL)
	{
		printf(ARG_ERR_MSG);
		return -1;
	}
	return (nag->top + 1);
}
//******************************************************************************
//* function name: APC_SoldExist
//* Description : returs if solider with given name exist in apc
//* Parameters: pointer to apc and id of soldier
//* Return Value: true for exist,false otherwise
//******************************************************************************
bool APC_SoldExist(PAPC nag,char* id)
{
	if ((nag == NULL)||(id==NULL))
	{
		printf(ARG_ERR_MSG);
		return false;
	}
	for (int i = 0; i <= nag->top; i++)
	{
		if (Soldier_Compare(nag->array[i], id))
			return true;
	}
	return false;
}
