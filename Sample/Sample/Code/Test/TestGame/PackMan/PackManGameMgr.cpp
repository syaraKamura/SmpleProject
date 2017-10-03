/*
				ファイル名		:PackManGameMgr.cpp
				作成者			:
				作成日時		:2017/09/09
				ソース説明		:
				
				
				備考
				
				
				
!*/

//	------- インクルード宣言
#include "Common/GameCommon/GameCommon.h"

#include "PackManStageMgr.h"

#include "PackManGameMgr.h"
//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

enum eStep{

	eStep_Init,
	eStep_SetUp,
	eStep_Main,
	eStep_Exit,
	eStep_ExitDone,

};

//	------- 構造体&共用体
typedef struct{

	s32 cnt;
	eStep step;

	PACKMAN_STAGE_MGR* pStage;

}PACKMAN_GAME_MGR;

//	------- データテーブル

//	------- スタティック変数宣言
static PACKMAN_GAME_MGR* s_pMgr;
//	------- グローバル変数宣言

//	------- スタティックプロトタイプ宣言(内部関数)

//	------- プロトタイプ宣言していないスタティック関数(内部関数)

static void _Updata(PACKMAN_GAME_MGR* ix){

	switch(ix->step){

	case eStep_Init:

		ix->step = eStep_SetUp;
		break;
	case eStep_SetUp:

		ix->step = eStep_Main;
		break;
	case eStep_Main:

		if(Keyboard_Press(KEY_INPUT_X)){

			ix->step = eStep_Exit;
		}
		
		break;
	case eStep_Exit:

		if(ix->cnt == 0){
			PackManStageMgr_RequestKill(ix->pStage);
		}

		ix->cnt++;
		
		if(ix->cnt > 2){

			ix->step = eStep_ExitDone;
			Task_KillRequest(ix);
		}

		break;
	case eStep_ExitDone:
		
		break;
	}

}


static void _Del(PACKMAN_GAME_MGR* ix){

	s_pMgr = NULL;
}

//	------- グローバル関数


/*
	生成
*/
void TestPackManGameMgr_Create(){

	PACKMAN_GAME_MGR* ix =  Task_CreateBase(_Updata,NULL,_Del,PACKMAN_GAME_MGR,eTaskClassType_Class00);

	if(ix != NULL){
		ix->cnt = 0;
		ix->step = eStep_Init;

		ix->pStage = PackManStageMgr_Create();

		s_pMgr = ix;

	}

}

/*
	終了判定
	return	true	:終了
			false	:実行中
*/
bool TestPackManGameMgr_IsEnd(){
	if(s_pMgr){
		return false;
	}else{
		return true;
	}
}