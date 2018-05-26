#define _CRT_SECURE_NO_WARNINGS
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
	{
		list->head = new_node;
		list->iter = list->head;
	}
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
		if (list->comp_func(save->data, item))
		{
			PNODE back = save->prev;
			PNODE forward =save->next;
			list->free_func(save->data);
			free(save);
			list->size--;
			if (list->size == 0)	   //only 1 item in list
				list->head = NULL;
			else if (back == NULL)	   //deleting first item in list
			{
				list->head = forward;
				forward->prev = NULL;
			}
			else if (forward == NULL)   //deleting last item in list
			{
				back->next = forward;
			}
			else						//deleting any other item	
			{
				back->next = forward;
				forward->prev = back;
			}
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
	Result adding;
	for (int i = 0; i < src->size; i++)
	{
		adding = List_Add_Elem(dst, curr->data);
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
Element List_Get_Elem(PLIST list, PKey key)
{
	if ((list == NULL) || (key == NULL))
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
//******************************************************************************
//* function name: List_Get_Copy
//* Description : Recieves pointer to list and returns its copy function
//* Parameters: pointer to the list 
//* Return Value: pointer to copy func
//******************************************************************************
Copy_Function List_Get_Copy(PLIST list)
{
	if (list == NULL)
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	return list->copy_func;
}
//******************************************************************************
//* function name: List_Get_Free
//* Description : Recieves pointer to list and returns its delete function
//* Parameters: pointer to the list 
//* Return Value: pointer to free func
//******************************************************************************
Free_Function List_Get_Free(PLIST list)
{
	if (list == NULL)
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	return list->free_func;
}
//******************************************************************************
//* function name: List_Get_Comp
//* Description : Recieves pointer to list and returns its compare function
//* Parameters: pointer to the list 
//* Return Value: pointer to compare func
//******************************************************************************
Compare_Function List_Get_Comp(PLIST list)
{
	if (list == NULL)
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	return list->comp_func;
}
//******************************************************************************
//* function name: List_Get_Print
//* Description : Recieves pointer to list and returns its Print function
//* Parameters: pointer to the list 
//* Return Value: pointer to print func
//******************************************************************************
Print_Func List_Get_Print(PLIST list)
{
	if (list == NULL)
	{
		printf(ARG_ERR_MSG);
		return NULL;
	}
	return list->print_func;
}

void Special_Insert(PLIST list, char *cmd)
{
	PNODE new_node = (PNODE)malloc(sizeof(NODE));
	if (new_node == NULL)
	{
		printf(MALLOC_ERR_MSG);
		return;
	}
	PNODE new_node = (PNODE)malloc(sizeof(NODE));
	new_node->data = (char*)malloc(strlen(cmd));
	if (new_node->data == NULL)
	{
		printf(MALLOC_ERR_MSG);
		return;
	}
	strcpy(new_node->data, cmd);
	if (list->head == NULL)
	{
		list->head = new_node;
		new_node->next = NULL;
		new_node->prev = NULL;
		return;
	}
	PNODE curr = list->head;
	while ((curr->next != NULL) && (list->comp_func(cmd, curr->data)))
		curr = curr->next; 
	if (curr->next == NULL)
	{
		if (curr->prev == NULL)
		{
			if (list->comp_func(cmd, curr->data))
			{
				curr->next = new_node;
				new_node->next = NULL;
				new_node->prev = curr;
				return;
			}
			else
			{
				list->head = new_node;
				new_node->prev = NULL;
				new_node->next = curr;
				curr->prev = new_node;
				return;
			}
		}
		if (list->comp_func(cmd, curr->data))
		{
			new_node->prev = curr;
			new_node->next = NULL;
			curr->next = new_node;
			return;
		}
	}
	PNODE node1= curr->prev;
	PNODE node2 = curr->next;
	new_node->prev = node1;;
	new_node->next = curr;
	node1->next = new_node;
	curr->prev = new_node;
	return;
}
