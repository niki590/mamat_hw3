#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Battlefield.h"
#include "List.h"

void Execute_Command(char *line);
void Execute_List(PLIST cmd);


#define TK " \n\t"
static PLIST Battlefield;

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

void part3()
{
	bool mem_failed = false;
	Result check;
	PAPC returned;
	PSOLDIER niki = Soldier_Create("niki", "1");
	PSOLDIER alon = Soldier_Create("alon", "2");
	PSOLDIER ofry = Soldier_Create("ofry", "3");
	PSOLDIER ophiron = Soldier_Create("ophiron", "3");
	PSOLDIER shuli = Soldier_Create("shuli", "3");
	PSOLDIER ron = Soldier_Create("ron", "3");
	PAPC brauda = APC_Create("A");
	PAPC brauda2 = APC_Create("B");
	APC_Insert_Soldier(brauda, niki);
	APC_Insert_Soldier(brauda, alon);
	APC_Insert_Soldier(brauda, ofry);
	APC_Insert_Soldier(brauda, shuli);
	APC_Insert_Soldier(brauda, ophiron);
	APC_Insert_Soldier(brauda, ron);
	PLIST first = List_Create(APC_Duplicate, APC_Delete, APC_Compare, APC_Print);
	PLIST second = List_Create(APC_Duplicate, APC_Delete, APC_Compare, APC_Print);
	check = List_Add_Elem(first, brauda);
	check = List_Add_Elem(first, brauda2);
	List_Duplicate(first, second, mem_failed);
	check = List_Add_Elem(first, brauda); // this point first:A>B>A , second: A>B
	returned = List_Get_First(first);
	returned = List_Get_Next(first);
	APC_Print(returned); //prints nagmash B (empty)
	check = List_Remove_Elem(second, "A");
	List_Print(second);  // second: B
	check = List_Remove_Elem(second, "B");
	List_Print(second);  // second: NA
	List_Print(first);
	List_Delete(first);
	List_Print(second);
	List_Delete(second);
	APC_Delete(brauda);
	APC_Delete(brauda2);

}
void part_4()
{
	bool mem_failed = false;
	PSQUAD nikigang = Squad_Create("nikigang", Soldier_Duplicate, Soldier_Delete, Soldier_Compare, Soldier_Print,
		APC_Duplicate, APC_Delete, APC_Compare, APC_Print);
	//Adding soldiers
	Result sol1 = Squad_Add_Soldier(nikigang, "ohad1","1",mem_failed);
	sol1 = Squad_Add_Soldier(nikigang, "ohad2", "1", mem_failed);
	sol1 = Squad_Add_Soldier(nikigang, "ohad3", "1", mem_failed);
	sol1 = Squad_Add_Soldier(nikigang, "ohad4", "1", mem_failed);
	sol1 = Squad_Add_Soldier(nikigang, "itamar1","2", mem_failed);
	sol1 = Squad_Add_Soldier(nikigang, "itamar2", "2", mem_failed);
	sol1 = Squad_Add_Soldier(nikigang, "itamar3", "2", mem_failed);
	sol1 = Squad_Add_Soldier(nikigang, "itamar4", "2", mem_failed);
	sol1 = Squad_Add_Soldier(nikigang, "itamar5", "2", mem_failed);
	sol1 = Squad_Add_Soldier(nikigang, "itamar6", "2", mem_failed);
	//Adding apcs
	Result apc1 = Squad_Add_APC(nikigang, "brauda1", mem_failed);
	apc1 = Squad_Add_APC(nikigang, "brauda2", mem_failed);
	apc1 = Squad_Add_APC(nikigang, "brauda3", mem_failed);
	apc1 = Squad_Add_APC(nikigang, "brauda4", mem_failed);
	apc1 = Squad_Add_APC(nikigang, "brauda5", mem_failed);

	//Move sold into apcs
	sol1 = Squad_Insert_Sold_APC(nikigang, "brauda1", "ohad1", mem_failed);
	sol1 = Squad_Insert_Sold_APC(nikigang, "brauda1", "itamar1", mem_failed);
	sol1 = Squad_Insert_Sold_APC(nikigang, "brauda1", "ohad2", mem_failed);
	sol1 = Squad_Insert_Sold_APC(nikigang, "brauda1", "itamar2", mem_failed);
	sol1 = Squad_Insert_Sold_APC(nikigang, "brauda1", "itamar3", mem_failed);
	sol1 = Squad_Insert_Sold_APC(nikigang, "brauda1", "itamar4", mem_failed);
	sol1 = Squad_Insert_Sold_APC(nikigang, "brauda1", "ohad3", mem_failed);
	//********************************************************************************
	Result pop1 = Squad_APC_Pop(nikigang, "brauda1",mem_failed);
	//Squad_Print(nikigang);
	//check squad duplicate squad delete functions
	PSQUAD ofrygang = Squad_Duplicate(nikigang);
	Squad_Delete(nikigang);
	Result del1 = Squad_Delete_Soldier(ofrygang, "ohad3");
	del1 = Squad_Delete_Soldier(ofrygang, "ohad1");
	del1 = Squad_Delete_APC(ofrygang, "brauda3");
	Squad_Print(ofrygang);
	del1 = Squad_Delete_APC(ofrygang, "brauda1");
	Squad_Print(ofrygang);
	Squad_Delete(ofrygang);
}

void Battlefield_Delete()
{
	List_Delete(Battlefield);
}


void Get_Commands()
{
	PLIST cmd = List_Create(NULL, String_free, String_compare, String_print);
	char line[MAX_LINE_LENGTH+1];
	bool finished = false;
	while (finished)
	{
		if (!fgets(line, MAX_LINE_LENGTH, stdin))
			finished = true; //end of commands
		if (!strcmp(line, "Exit"))
		{
			Battlefield_Delete();
			List_Delete(cmd);
			return ;
		}
		if (!strcmp(line, "Exe"))
		{
			Execute_List(cmd);
			List_Delete(cmd);
			cmd = List_Create(NULL, String_free, String_compare, String_print);
		}
		List_Special_Insert(cmd, line);
	}
}

void Execute_List(PLIST cmd)
{
	char* line = (char*)malloc(MAX_LINE_LENGTH + 1);
	if (line == NULL)
	{
		printf(MALLOC_ERR_MSG);
		Battlefield_Delete();
	}
	strcpy(line, List_Get_First(cmd));
	if (line == NULL)
	{
		printf("No Commands to Execute\n");
		free(line);
		return;
	}
	while (line != NULL)
	{
		Execute_Command(line);
		strcpy(line, List_Get_Next(cmd));
	}
	printf("**********All Commands Executed**********\n\n");
	return;
}

void Execute_Command(char *line)
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
			Battlefield_Delete();
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

	}
	else if (!strcmp(splited[1], "Add_Sold"))
	{

	}
	else if (!strcmp(splited[1], "Del_ Sold"))
	{

	}
	else if (!strcmp(splited[1], "Add_APC"))
	{

	}
	else if (!strcmp(splited[1], "Del_APC"))
	{

	}
	else if (!strcmp(splited[1], "APC_Pop"))
	{

	}
	else if (!strcmp(splited[1], "Print"))
	{

	}
	else 
	{
		printf("Error: Illegal Command\n");
	}
}


int main()
{
	Battlefield = NULL;

}