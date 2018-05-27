#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Battlefield.h"
#include "List.h"
#define TK " \n\t"
//Static Vars used for main
static PLIST Battlefield;

//Declarations
void Execute_Command(char *line,PLIST cmd);
void Execute_List(PLIST cmd);
//Functions for command list
void String_free(Element str_t)
{
	char* str = (char*)str_t;
	free(str);
}
bool String_compare(Element str1_t, Element str2_t)
{
	char* str1 = (char*)str1_t;
	char* str2 = (char*)str2_t;
	if(str1[0]>str2[0])
		return true;
	return false;
}
void String_print(Element line_t)
{
	char* line = (char*)line_t;
	printf("%s\n", line);
}

//THE MAIN
void Battlefield_Delete(PLIST cmd)
{
	List_Delete(Battlefield);
	List_Delete(cmd);
}
void Get_Commands()
{
	PLIST cmd = List_Create(NULL, String_free, String_compare, String_print);
	char line[MAX_LINE_LENGTH+1];
	bool finished = false;
	while (!finished)
	{
		if (!fgets(line, MAX_LINE_LENGTH, stdin))
		{
			finished = true; //end of commands
			return;
		}
		char first[MAX_LINE_LENGTH + 1];
		strcpy(first, line);
		strtok(first, TK);
		if (!strcmp(first, "Exit"))
		{
			Battlefield_Delete(cmd);
			return ;
		}
		else if (!strcmp(first,"Exe"))
		{
			Execute_List(cmd);
			List_Delete(cmd);
			cmd = List_Create(NULL, String_free, String_compare, String_print);
		}
		else
		List_Special_Insert(cmd, line);
	}
}
void Execute_List(PLIST cmd)
{
	char* line = (char*)malloc(MAX_LINE_LENGTH + 1);
	if (line == NULL)
	{
		printf(MALLOC_ERR_MSG);
		Battlefield_Delete(cmd);
	}
	char* iter = List_Get_First(cmd);
	if (iter == NULL)
	{
		printf("No Commands to Execute\n");
		free(line);
		return;
	}
	strcpy(line, iter);
	while (line != NULL)
	{
		Execute_Command(line,cmd);
		iter = List_Get_Next(cmd);
		if (iter == NULL)
		{
			line = NULL;
			continue;
		}
		strcpy(line, iter);
	}
	free(line);
	printf("**********All Commands Executed**********\n\n");
	return;
}
void Execute_Command(char *line,PLIST cmd)
{
	char *commands = strtok(line, TK);
	char *splited[MAX_VALUES_CMD];
	for (int i = 0; i < MAX_VALUES_CMD; i++)
		splited[i] = NULL;
	int counter = 0;
	while ((commands != NULL) && (counter < MAX_VALUES_CMD))
	{
		splited[counter] = commands;
		commands = strtok(NULL, TK);
		counter++;
	}
	if (!strcmp(splited[1], "Create_B"))
	{
		Battlefield = Battlefield_Create();
		printf("Battlefield Created!\n");
		return;
	}
	if (Battlefield == NULL)
	{
		printf("Error: No Battlefield\n");
		return;
	}
	else if (!strcmp(splited[1], "Add_W"))
	{
		
		if (Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: War Zone Already Exists\n");
			return;
		}
		PWarZone new_wz = WarZone_Create(splited[2], Squad_Duplicate, Squad_Delete, Squad_Compare, Squad_Delete);
		List_Add_Elem(Battlefield, new_wz);
		WarZone_Delete(new_wz);
	}
	else if (!strcmp(splited[1], "Del_W"))
	{
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		List_Remove_Elem(Battlefield, splited[2]);
	}
	else if (!strcmp(splited[1], "R_W"))
	{
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		PWarZone wz = List_Get_Elem(Battlefield, splited[2]);
		if (!WarZone_Raise_Alert(wz))
		{
			Battlefield_Emergency(Battlefield, wz);
		}
	}
	else if (!strcmp(splited[1], "Add_Sq"))
	{
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		if (Battlefield_Squad_Exist(Battlefield, splited[3]))
		{
			printf("Error: Squad Already Exists\n");
			return;
		}
		PWarZone wz = List_Get_Elem(Battlefield, splited[2]);
		if (!WarZone_Add_Squad(wz, splited[3]))
		{
			Battlefield_Delete(cmd);
		}
	}
	else if (!strcmp(splited[1], "Del_Sq"))
	{
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		if (!Battlefield_Squad_Exist(Battlefield, splited[3]))
		{
			printf("Error: No Such Squad\n");
			return;
		}
		WarZone_Del_Squad(List_Get_Elem(Battlefield, splited[2]), splited[3]);
	}
	else if (!strcmp(splited[1], "M_Sq"))
	{
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such Origin War Zone\n");
			return;
		}
		if (!Battlefield_WZ_Exist(Battlefield, splited[3]))
		{
			printf("Error: No Such Dest War Zone\n");
			return;
		}
		if (!Battlefield_Squad_Exist(Battlefield, splited[3]))
		{
			printf("Error: No Such Dest Squad\n");
			return;
		}
		if (!Battlefield_Move_Squad(Battlefield, splited[2], splited[3], splited[4]))
			Battlefield_Delete(cmd);


	}
	else if (!strcmp(splited[1], "Add_Sold"))
	{
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		if (!Battlefield_Squad_Exist(Battlefield, splited[3]))
		{
			printf("Error: No Such Squad\n");
			return;
		}
		if (Battlefield_SoldExist(Battlefield, splited[4]))
		{
			printf("Error: Soldier Already Exists\n");
			return;
		}
		if (Battlefield_Add_Sold(Battlefield, splited[2], splited[3], splited[4], splited[5]))
			Battlefield_Delete(cmd);
	}
	else if (!strcmp(splited[1], "Del_ Sold"))
	{
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		if (!Battlefield_Squad_Exist(Battlefield, splited[3]))
		{
			printf("Error: No Such Squad\n");
			return;
		}
		if (!Battlefield_SoldExist(Battlefield, splited[4]))
		{
			printf("Error: No Such Soldier\n");
			return;
		}
		PWarZone curr_wz = List_Get_Elem(Battlefield, splited[2]);
		PLIST squ_list = WarZone_Get_Squ_List(curr_wz);
		PSQUAD curr_squ = List_Get_Elem(squ_list, splited[3]);
		Squad_Delete_Soldier(curr_squ, splited[4]);
	}
	else if (!strcmp(splited[1], "Add_APC"))
	{
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		if (!Battlefield_Squad_Exist(Battlefield, splited[3]))
		{
			printf("Error: No Such Squad\n");
			return;
		}
		if (Battlefield_APCExist(Battlefield, splited[4]))
		{
			printf("Error: APC Already Exists\n");
			return;
		}
		if (Battlefield_Add_APC(Battlefield, splited[2], splited[3], splited[4]))
			Battlefield_Delete(cmd);
	}
	else if (!strcmp(splited[1], "Del_APC"))
	{
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		if (!Battlefield_Squad_Exist(Battlefield, splited[3]))
		{
			printf("Error: No Such Squad\n");
			return;
		}
		if (!Battlefield_APCExist(Battlefield, splited[4]))
		{
			printf("Error: No Such APC\n");
			return;
		}
		PWarZone curr_wz = List_Get_Elem(Battlefield, splited[2]);
		PLIST squ_list = WarZone_Get_Squ_List(curr_wz);
		PSQUAD curr_squ = List_Get_Elem(squ_list, splited[3]);
		Squad_Delete_APC(curr_squ, splited[4]);
	}
	else if (!strcmp(splited[1], "Sold_Insert"))
	{
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		if (!Battlefield_Squad_Exist(Battlefield, splited[3]))
		{
			printf("Error: No Such Squad\n");
			return;
		}
		if (!Battlefield_APCExist(Battlefield, splited[4]))
		{
			printf("Error: No Such APC\n");
			return;
		}
		if (!Battlefield_SoldExist(Battlefield, splited[5]))
		{
			printf("Error: No Such Soldier\n");
			return;
		}
		if (Battlefield_Sold_ToAPC(Battlefield, splited[2], splited[3], splited[4], splited[5]))
			Battlefield_Delete(cmd);
	}
	else if (!strcmp(splited[1], "APC_Pop"))
	{
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		if (!Battlefield_Squad_Exist(Battlefield, splited[3]))
		{
			printf("Error: No Such Squad\n");
			return;
		}
		if (!Battlefield_APCExist(Battlefield, splited[4]))
		{
			printf("Error: No Such APC\n");
			return;
		}
		PWarZone curr_wz = List_Get_Elem(Battlefield, splited[2]);
		PLIST squ_list = WarZone_Get_Squ_List(curr_wz);
		PSQUAD curr_squ = List_Get_Elem(squ_list, splited[3]);
		bool mem_failed = false;
		Squad_APC_Pop(curr_squ, splited[4], &mem_failed);
		if (mem_failed)
			Battlefield_Delete(cmd);
	}
	else if (!strcmp(splited[1], "Print"))
	{
		printf("Battlefield\n");
		List_Print(Battlefield);
	}
	else 
	{
		printf("Error: Illegal Command\n");
		return;
	}
}


int main()
{
	Battlefield = NULL;
	Get_Commands();
	return 0;
}