#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "APC.h"
#include "List.h"



/*void part2()
{
	PSOLDIER niki = Soldier_Create("niki", "1");
	PSOLDIER alon = Soldier_Create("alon", "2");
	PSOLDIER ofry = Soldier_Create("ofry", "3");
	PSOLDIER ophiron = Soldier_Create("ophiron", "3");
	PSOLDIER shuli = Soldier_Create("shuli", "3");
	PSOLDIER ron = Soldier_Create("ron", "3");
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
	PLIST first = List_Create(APC_Duplicate, APC_Delete, APC_Compare, APC_Print);
	Result check = List_Add_Elem(first, brauda);
	List_Print(first);
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
*/
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

int main()
{
	part3();
	printf("WOHOHOHOHOHO\n");
}