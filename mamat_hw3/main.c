#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "APC.h"



void part2()
{
	PSOLDIER niki = Soldier_Create("niki", "1");
	PSOLDIER new_niki = Soldier_Duplicate(niki);
	Soldier_Print(new_niki);
	Soldier_Delete(new_niki);
	PSOLDIER alon = Soldier_Create("alon", "2");
	PSOLDIER ofry = Soldier_Create("ofry", "3");
	PSOLDIER ophiron = Soldier_Create("ophiron", "3");
	PSOLDIER shuli = Soldier_Create("shuli", "3");
	PSOLDIER ron = Soldier_Create("ron", "3");
	PSOLDIER toomuch = Soldier_Create("toomuch", "1");
	PAPC brauda = APC_Create("Bradua");
	PSOLDIER lol=APC_Pop(brauda);
	//check if possible to add APC with the same name in the prog
	//result - failed - the apc was created without intervention
	//needed solution: linked list that acounts for all names given
	//so far - so its possible to check validity of name
	//this is needed for both apcs and soldiers
	PAPC brauda_nd = APC_Create("new_one");
	APC_Insert_Soldier(brauda, niki);
	APC_Insert_Soldier(brauda, alon);
	APC_Insert_Soldier(brauda, ofry);
	APC_Insert_Soldier(brauda, shuli);
	APC_Insert_Soldier(brauda, ophiron);
	APC_Insert_Soldier(brauda, ron);
	APC_Print(brauda);
	//check is full operation
	//result: succeeded
	APC_Insert_Soldier(brauda, toomuch);
	Soldier_Delete(toomuch);
	APC_Print(brauda);
	//check APC_Duplicate
	//result: succeeded
	PAPC brauda2 = APC_Duplicate(brauda);
	PSOLDIER pop = APC_Pop(brauda);
	Soldier_Delete(pop);
	APC_Print(brauda);
	APC_Print(brauda2);
	APC_Delete(brauda);
	APC_Delete(brauda2);
	APC_Delete(brauda_nd);
	//check print of empty apc - 
	//outcome printed as function's args error
	//according to doc - supposed to print
	//:"Brauda_nd", Occupancy: 0/6"
}
int main()
{
	part2();
	printf("finish");
}