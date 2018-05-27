#ifndef _Battlefield_h
#define _Battlefield_h
#include "WarZone.h"


PLIST Battlefield_Create();
bool Battlefield_SoldExist(PLIST battle, char *sold_id);
bool Battlefield_APCExist(PLIST Battle, char *id);
bool Battlefield_WZ_Exist(PLIST battle, char * id);
bool Battlefield_Squad_Exist(PLIST battle, char * id);
void Battlefield_Emergency(PLIST bf, PWarZone wz);
Result Battlefield_Move_Squad(PLIST bf, char* src_wz_id, char* dest_wz_id, char* id);
Result Battlefield_Add_Sold(PLIST bf, char* wz_id, char* sq_id, char* id, char* pos);
Result Battlefield_Add_APC(PLIST bf, char* wz_id, char* sq_id, char* id);
Result Battlefield_Sold_ToAPC(PLIST bf, char* wz_id, char* sq_id, char* apc_id, char* id);

#endif
