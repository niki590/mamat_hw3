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
	char* new1 = (char*)malloc(MAX_LINE_LENGTH);
	char* new2 = (char*)malloc(MAX_LINE_LENGTH);
	strcpy(new1, (char*)str1_t);
	strcpy(new2, (char*)str2_t);
	strtok(new1, TK);	
	strtok(new2, TK);
	int str1n = atoi(new1);
	int str2n= atoi(new2);
	free(new1);
	free(new2);
	if (str1n > str2n)
		return true;
	return false;
}
void String_print(Element line_t)
{
	char* line = (char*)line_t;
	printf("%s\n", line);
}
bool Battlefield_Exist()
{
	if (Battlefield == NULL)
	{
		printf("Error: No Battlefield\n");
		return false;;
	}
	return true;
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
	char check[MAX_LINE_LENGTH + 1];
	bool finished = false;
	while (!finished)
	{
		if (!fgets(line, MAX_LINE_LENGTH, stdin))
		{
			finished = true; //end of commands
			return;
		}
		strcpy(check, line);
		strtok(check, TK);
		if (!strcmp(check, "Exit"))
		{
			Battlefield_Delete(cmd);
			return ;
		}
		else if (!strcmp(check,"Exe"))
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
	/*char* line = (char*)malloc(MAX_LINE_LENGTH + 1);
	if (line == NULL)
	{
		printf(MALLOC_ERR_MSG);
		Battlefield_Delete(cmd);
	}
	*/
	char* iter = List_Get_First(cmd);
	if (iter == NULL)
	{
		printf("No Commands to Execute\n");
		printf("**********All Commands Executed**********\n\n");
		return;
	}
	while (iter != NULL)
	{
		Execute_Command(iter,cmd);
		iter = List_Get_Next(cmd);
	}
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
	else if (!strcmp(splited[1], "Add_W"))
	{
		if (!Battlefield_Exist()) return;
		if (Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: War Zone Already Exists\n");
			return;
		}
		PWarZone new_wz = WarZone_Create(splited[2], Squad_Duplicate, Squad_Delete, Squad_Compare, Squad_Print);
		List_Add_Elem(Battlefield, new_wz);
		WarZone_Delete(new_wz);
	}
	else if (!strcmp(splited[1], "Del_W"))
	{
		if (!Battlefield_Exist()) return;
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		List_Remove_Elem(Battlefield, splited[2]);
	}
	else if (!strcmp(splited[1], "R_W"))
	{
		if (!Battlefield_Exist()) return;
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		PWarZone wz = List_Get_Elem(Battlefield, splited[2]);
		if (!WarZone_Raise_Alert(wz))
		{
			Battlefield_Emergency(Battlefield, wz);
			return;
		}
	}
	else if (!strcmp(splited[1], "Add_Sq"))
	{
		if (!Battlefield_Exist()) return;
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
		if (!Battlefield_Exist()) return;
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
		if (WarZone_SquadExist(List_Get_Elem(Battlefield, splited[2]), splited[3]))
			WarZone_Del_Squad(List_Get_Elem(Battlefield, splited[2]), splited[3]);
		else
			printf("Error: No Such Squad\n");
	}
	else if (!strcmp(splited[1], "M_Sq"))
	{
		if (!Battlefield_Exist()) return;
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
		if (!WarZone_SquadExist(List_Get_Elem(Battlefield, splited[2]), splited[4]))
		{
			printf("Error: No Such Squad\n");
			return;
		}
		if (!Battlefield_Move_Squad(Battlefield, splited[2], splited[3], splited[4]))
			Battlefield_Delete(cmd);
	}
	else if (!strcmp(splited[1], "Add_Sold"))
	{
		if (!Battlefield_Exist()) return;
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		PWarZone curr_wz = List_Get_Elem(Battlefield, splited[2]);
		if (!WarZone_SquadExist(curr_wz, splited[3]))
		{
			printf("Error: No Such Squad\n");
			return;
		}
		if (Battlefield_SoldExist(Battlefield, splited[4]))
		{
			printf("Error: Soldier Already Exists\n");
			return;
		}
		if (!Battlefield_Add_Sold(Battlefield, splited[2], splited[3], splited[4], splited[5]))
			Battlefield_Delete(cmd);
	}
	else if (!strcmp(splited[1], "Del_Sold"))
	{
		if (!Battlefield_Exist()) return;
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		PWarZone curr_wz = List_Get_Elem(Battlefield, splited[2]);
		if(!WarZone_SquadExist(curr_wz,splited[3]))
		{
			printf("Error: No Such Squad\n");
			return;
		}
		PSQUAD curr_sq = List_Get_Elem(WarZone_Get_Squ_List(curr_wz), splited[3]);
		if (!Squad_SoldExist(curr_sq, splited[4]))
		{
			printf("Error: No Such Soldier\n");
			return;
		}
		Squad_Delete_Soldier(curr_sq, splited[4]);
	}
	else if (!strcmp(splited[1], "Add_APC"))
	{
		if (!Battlefield_Exist()) return;
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		PWarZone curr_wz = List_Get_Elem(Battlefield, splited[2]);
		if (!WarZone_SquadExist(curr_wz, splited[3]))
		{
			printf("Error: No Such Squad\n");
			return;
		}
		if (Battlefield_APCExist(Battlefield, splited[4]))
		{
			printf("Error: APC Already Exists\n");
			return;
		}
		if (!Battlefield_Add_APC(Battlefield, splited[2], splited[3], splited[4]))
			Battlefield_Delete(cmd);
	}
	else if (!strcmp(splited[1], "Del_APC"))
	{
		if (!Battlefield_Exist()) return;
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		PWarZone curr_wz = List_Get_Elem(Battlefield, splited[2]);
		if (!WarZone_SquadExist(curr_wz, splited[3]))
		{
			printf("Error: No Such Squad\n");
			return;
		}
		PSQUAD curr_sq = List_Get_Elem(WarZone_Get_Squ_List(curr_wz), splited[3]);
		if (!Squad_APCExist(curr_sq, splited[4]))
		{
			printf("Error: No Such APC\n");
			return;
		}
		Squad_Delete_APC(curr_sq, splited[4]);
	}
	else if (!strcmp(splited[1], "Sold_Insert"))
	{
		if (!Battlefield_Exist()) return;
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		PWarZone curr_wz = List_Get_Elem(Battlefield, splited[2]);
		if (!WarZone_SquadExist(curr_wz, splited[3]))
		{
			printf("Error: No Such Squad\n");
				return;
		}
		PLIST squ_list = WarZone_Get_Squ_List(curr_wz);
		PSQUAD curr_squ = List_Get_Elem(squ_list, splited[3]);
		if (!Squad_APCExist(curr_squ, splited[4]))
		{
			printf("Error: No Such APC\n");
			return;
		}
		if (!Squad_SoldExist(curr_squ, splited[5]))
		{
			printf("Error: No Such Soldier\n");
			return;
		}
		bool mem_failed = false;
		Squad_Insert_Sold_APC(curr_squ, splited[4], splited[5], &mem_failed);
			if (mem_failed)
			{
				Battlefield_Delete(cmd);
			}
	}
	else if (!strcmp(splited[1], "APC_Pop"))
	{
		if (!Battlefield_Exist()) return;
		if (!Battlefield_WZ_Exist(Battlefield, splited[2]))
		{
			printf("Error: No Such War Zone\n");
			return;
		}
		PWarZone curr_wz = List_Get_Elem(Battlefield, splited[2]);
		if (!WarZone_SquadExist(curr_wz, splited[3]))
		{
			printf("Error: No Such Squad\n");
			return;
		}
		PSQUAD curr_sq = List_Get_Elem(WarZone_Get_Squ_List(curr_wz), splited[3]);
		if (!Squad_APCExist(curr_sq, splited[4]))
		{
			printf("Error: No Such APC\n");
			return;
		}
		bool mem_failed = false;
		if ((!Squad_APC_Pop(curr_sq, splited[4], &mem_failed)) && (mem_failed == true))
		{
			Battlefield_Delete(cmd);
		}
	}
	else if (!strcmp(splited[1], "Print"))
	{
		if (!Battlefield_Exist()) return;
		printf("Battlefield:\n");
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