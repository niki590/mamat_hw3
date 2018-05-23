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

PAPC  APC_Create(char* id)
{
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
int isFull(PAPC check)
{
	return check->top == check->capacity - 1;
}
int isEmpty(PAPC check)
{
	return check->top == (-1);
}
Result APC_Insert_Soldier(PAPC apc, PSOLDIER soldier)
{
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
void APC_Print(PAPC nag)
{
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
PSOLDIER APC_Pop(PAPC apc)
{
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
PAPC APC_Duplicate(PAPC old)
{
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
void APC_Delete(PAPC apc)
{
	if (apc == NULL)
	{
		printf(ARG_ERR_MSG);
		return;
	}
	for (int i = 0; i<=apc->top; i++)
		Soldier_Delete(apc->array[i]);
	free(apc->array);
	free(apc->ID);
}
