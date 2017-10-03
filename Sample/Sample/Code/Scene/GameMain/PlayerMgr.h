#pragma once

#include "Charactor\Chara_PlayerObj.h"

void PlayerMgr_Init();
void PlayerMgr_Updata();
void PlayerMgr_Draw();
void PlayerMgr_Finalize();

CHARA_PLAYER_OBJ* PlayerMgr_GetPlayer();