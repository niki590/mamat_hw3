#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Soldier.h"

typedef struct Soldier_t {
	char* ID;
	char* POS;
}Soldier;

//******************************************************************************
//* function name :Soldier_Create
//* Description :recieves a soldier id and position and creates a new user
//* Parameters:ID number and soldier position
//* Return Value: pointer to new soldier struct
//******************************************************************************
PSOLDIER Soldier_Create(Element id_t, Element pos_t)
{
	char* id = (char*)id_t;
	char* pos = (char*)pos_t;
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
//******************************************************************************
//* function name :Soldier_Delete
//* Description :recieves a pointer to soldier and deletes it
//* Parameters: pointer to soldier
//* Return Value: NA
//******************************************************************************
void Soldier_Delete(Element sold_t)
{
	PSOLDIER sold = (PSOLDIER)sold_t;
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
//******************************************************************************
//* function name :Soldier_Print
//* Description :recieves a pointer to soldier and prints its stats
//* Parameters: pointer to soldier
//* Return Value: NA
//******************************************************************************
void Soldier_Print(Element sold_t)
{
	PSOLDIER sold = (PSOLDIER)sold_t;
	if (sold == NULL)
	{
		printf(ARG_ERR_MSG);
		return;
	}
	printf("%s , %s\n", sold->ID, sold->POS);
}
//******************************************************************************
//* function name :Soldier_Duplicate
//* Description :recieves a pointer to soldier and creates a duplicate of the soldier
//in terms of same id and pos
//* Parameters: pointer to soldier
//* Return Value: pointer to soldier
//******************************************************************************
PSOLDIER Soldier_Duplicate(Element Soldier_t)
{
	PSOLDIER Soldier = (PSOLDIER)Soldier_t;
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





