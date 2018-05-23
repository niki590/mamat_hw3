#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Soldier.h"

typedef struct Soldier_t {
	char* ID;
	char* POS;
}Soldier;

PSOLDIER Soldier_Create(char *id, char *pos)
{
	if (id == NULL)
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PSOLDIER new = (PSOLDIER)malloc(sizeof(Soldier));
	if (new == NULL)
	{
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	new->POS = (char *)malloc(MAX_ID_LENGTH + 1);
	new->ID = (char *)malloc(MAX_ID_LENGTH + 1);
	strcpy(new->POS, pos);
	strcpy(new->ID, id);
	return new;
}

void Soldier_Delete(PSOLDIER sold)
{
	if (sold == NULL)
	{
		printf(ARG_ERR_MSG);
		return;
	}
	free(sold->ID);
	free(sold->POS);
	free(sold);
	return;
}
void Soldier_Print(PSOLDIER sold)
{
	if (sold == NULL)
	{
		printf(ARG_ERR_MSG);
		return;
	}
	printf("%s , %s\n",sold->ID,sold->POS);
}
PSOLDIER Soldier_Duplicate(PSOLDIER Soldier)
{
	if (Soldier == NULL) {
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PSOLDIER New_Soldier = Soldier_Create(Soldier->ID, Soldier->POS);
	if (New_Soldier == NULL) {
		printf(MALLOC_ERR_MSG);
		return NULL;
	}
	return New_Soldier;
}




