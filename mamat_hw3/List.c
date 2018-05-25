#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct Node_t
{
	Element data;
	struct Node_t* next;
	struct Node_t* prev;
} NODE, *PNODE;

typedef struct List_t 
{
	NODE* head;
	NODE* iter;
	Copy_Function copy_func;
	Free_Function free_func;
	Compare_Function comp_func;
	Print_Func print_func;
	unsigned int size;
} LIST;

//******************************************************************************
//* function name: List_Create 
//* Description : Creates new linked list
//* Parameters: copy,free,compare and print functions by pointers
//* Return Value: pointer to the list 
//******************************************************************************
PLIST List_Create(Copy_Function copy, Free_Function free, Compare_Function comp, Print_Func print)
{
	if ((copy == NULL) || (free == NULL) || (comp == NULL) || (print == NULL))
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PLIST new = (PLIST)malloc(sizeof(LIST));
	if (new==NULL)
	{
		printf(MALLOC_ERR_MSG);
	return NULL;
	}
	new->comp_func = comp;
	new->copy_func = copy;
	new->free_func = free;
	new->head = NULL;
	new->iter = NULL;
	new->print_func = print;
	new->size = 0;
	return new;
}
//******************************************************************************
//* function name: List_Delete 
//* Description : Deletes the list and all it fields
//* Parameters: pointer to list
//* Return Value: NA
//******************************************************************************
void List_Delete(PLIST list)
{
	if (list == NULL)
	{
		printf(ARG_ERR_MSG);
		return;
	}
	PNODE next = NULL;
	PNODE curr = list->head;
	for (int i = 0; i < list->size; i++)
	{
		next = curr->next;
		list->free_func(curr);
		curr = next;
	}
	free(list);
}
//******************************************************************************
//* function name: List_Print
//* Description : Prints linked list
//* Parameters: pointer to list
//* Return Value: NA 
//******************************************************************************
void List_Print(PLIST list)
{
	if (list == NULL)
	{
		printf(ARG_ERR_MSG);
		return;
	}
	PNODE curr = list->head;
	for (int i = 0; i < list->size; i++)
	{
		list->print_func(curr);
		curr = curr->next;
	}
}

//******************************************************************************
//* function name: List_Add_Elem
//* Description : adds an item given to the end of list
//* Parameters: pointer to list, pointer to element
//* Return Value: result of adding 
//******************************************************************************
Result List_Add_Elem(PLIST list, Element item)
{
	if ((list == NULL)||(item==NULL))
	{
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	PNODE new_node = (PNODE)malloc(sizeof(NODE));
	if (new_node == NULL)
	{
		printf(MALLOC_ERR_MSG);
		return FAILURE;
	}
	new_node->next = NULL;
	list->iter = list->head;
	for (int i = 0; i < list->size; i++)
		list->iter = list->iter->next;
	assert(list->iter->next == NULL);
	list->iter->next = new_node;
	new_node->prev = list->iter;
	list->size++;
	new_node->data = list->copy_func(item);
	if (new_node->data == NULL)
	{
		printf(MALLOC_ERR_MSG);
		return FAILURE;
	}
	return SUCCESS;
}
