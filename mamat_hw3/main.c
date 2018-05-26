#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Battlefield.h"
#define TK " \n\t"

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
	Result check;
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

int main()
{
	PLIST cmd = List_Create(NULL, String_free, String_compare, NULL);
	char line[MAX_LINE_LENGTH];
	line[255] = '\0';
	char *command;
	while (fgets(line, MAX_LINE_LENGTH, stdin))
	{
		Special_Insert(line);

	}



	while (fgets(line, MAX_LINE_LENGTH, stdin))
	{
		command = strtok(line, TK);
		char *splited[3];
		for (int i = 0; i < 3; i++)
			splited[i] = NULL;
		int counter = 0;
		if (command == NULL)
			continue;
		while ((command != NULL) && (counter<3))
		{
			splited[counter] = command;
			command = strtok(NULL, TK);
			counter++;
		}
}