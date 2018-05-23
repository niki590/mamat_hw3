#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "APC.h"

void part1()
{
	PSOLDIER niki = Soldier_Create("niki", "1");
	PSOLDIER alon = Soldier_Create("alon", "2");
	PSOLDIER ofry = Soldier_Create("ofry", "3");
	PAPC brauda = APC_Create("Bradua");
	APC_Insert_Soldier(brauda,niki);
	APC_Insert_Soldier(brauda, alon);
	APC_Insert_Soldier(brauda, ofry);
	PSOLDIER pop=APC_Pop(brauda);
	APC_Print(brauda);
}

int main()
{
	part1();
}