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
	int size;
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
		list->free_func(curr->data);
		free(curr);
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
		list->print_func(curr->data);
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
	PNODE save = NULL;
	save = list->head;
	for (int i = 0; i < list->size-1; i++)
		save = save->next;
	if (save == NULL)
		list->head = new_node;
	else
		save->next = new_node;
	new_node->prev = save;
	list->size++;
	new_node->data = list->copy_func(item);
	if (new_node->data == NULL)
	{
		printf(MALLOC_ERR_MSG);
		return FAILURE;
	}
	return SUCCESS;
}
//******************************************************************************
//* function name: List_Remove_Elem
//* Description : removes an item with same key as given from list
//* Parameters: pointer to a list, a key 
//* Return Value: result of removing 
//******************************************************************************
Result List_Remove_Elem(PLIST list, PKey item)
{
	if ((list == NULL) || (item == NULL))
	{
		printf(ARG_ERR_MSG);
		return FAILURE;
	}
	PNODE save;
	save = list->head;
	for (int i = 0; i < list->size; i++)
	{
		if (list->comp_func(item, save->data))
		{
			PNODE back = save->prev;
			PNODE forward =save->next;
			list->free_func(save->data);
			free(save);
			list->size--;
			back->next = forward;
			forward->prev = back;
			return SUCCESS;
		}
		save = save->next;
	}
	return FAILURE;
}
//******************************************************************************
//* function name: List_Get_First
//* Description : Returns the data in the first node of list
//* Parameters: pointer to a list 
//* Return Value: pointer to the data
//******************************************************************************
Element List_Get_First(PLIST list)
{
	list->iter = list->head;
	if (list == NULL) 
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	if (list->head == NULL)
	{
		printf("no nodes in list");
		return NULL;
	}
	return list->head->data;
}
//******************************************************************************
//* function name: List_Get_Next
//* Description : Returns the data in the next node(accroding to num of calls)
//* Parameters: pointer to a list 
//* Return Value: pointer to the data
//******************************************************************************
Element List_Get_Next(PLIST list)
{
	if (list == NULL)
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	if (list->iter->next == NULL)
		return NULL;
	list->iter = list->iter->next;
	return list->iter->data;
}
//******************************************************************************
//* function name: List_Duplicate
//* Description : Duplicates the list and all its fields 
//* Parameters: pointer to source list and pointer to destination list.
//*				and bool  that indicate if malloc failed
//* Return Value: NA
//******************************************************************************
void List_Duplicate(PLIST src, PLIST dst,bool mem_failed)
{
	if ((src == NULL)||(dst==NULL))
	{
		printf(ARG_ERR_MSG);
		return;
	}
	PNODE curr = src->head;
	PNODE duplc = NULL;
	Result adding;
	for (int i = 0; i < src->size; i++)
	{
		Element new1 = src->copy_func(curr->data);
		if (new1 == NULL)
		{
			mem_failed = true;
			return;
		}
		adding = List_Add_Elem(dst, new1);
		if (adding == FAILURE)
		{
			mem_failed = true;
			return;
		}
		curr = curr->next;
	}
}
//******************************************************************************
//* function name: List_Get_Elem
//* Description : Recieves pointer to list and a key and returns the data that corresponds with it
//* Parameters: pointer to the data and to the list 
//* Return Value: pointer to 
//******************************************************************************
Element List_Get_Elem(PLIST list,PKey key)
{
	if ((list == NULL)||(key==NULL))
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	PNODE curr = list->head;
	for (int i = 0; i < list->size; i++)
	{
		if (list->comp_func(curr->data, key))
			return curr->data;
		curr = curr->next;
	}
	return NULL;
}
