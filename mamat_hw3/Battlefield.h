#ifndef _Battlefield_h
#define _Battlefield_h
#include "WarZone.h"


PLIST Battlefield_Create();
bool Battlefield_SoldExist(PLIST battle, char *sold_id);
bool Battlefield_APCExist(PLIST Battle, char *id);
bool Battlefield_WZ_Exist(PLIST battle, char * id);
bool Battlefield_Squad_Exist(PLIST battle, char * id);
#endif
