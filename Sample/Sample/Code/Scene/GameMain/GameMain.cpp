
//------------------------------------------------- インクルード
#include "Common/GameCommon/GameCommon.h"
#include "Common/CommonRes/CommonRes.h"
#include "Charactor/CharctorRes/CharComRes.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Charactor/EnemyMgr.h"
//------------------------------------------------- 定数定義(define & const)

//------------------------------------------------- 列挙体定義

enum eStep{
	eStep_Init,
	eStep_SetUp,
	eStep_Main,
};

//------------------------------------------------- 構造体定義(structer & union)

typedef struct{
	int step;
	int cnt;
}WORK_OBJ;

//------------------------------------------------- テーブル定義
const char* strTbl[] = {
	"Now Loading",
	"Now Loading.",
	"Now Loading..",
	"Now Loading...",
	"Now Loading..",
	"Now Loading.",
};

//------------------------------------------------- スタティック変数定義
//------------------------------------------------- グローバル変数定義
static WORK_OBJ* s_pWork; 
//------------------------------------------------- プロトタイプ宣言
//------------------------------------------------- スタティック定義
//------------------------------------------------- グローバル定義

static void _Updata(WORK_OBJ* ix){


	switch(ix->step){
	case eStep_Init:
		CharComRes_LoadRequest();
		ix->step = eStep_SetUp;
		break;
	case eStep_SetUp:
		if(CharComRes_IsLoadEnd()){
			PlayerMgr_Init();
			EnemyMgr_Init(10);
			ix->step = eStep_Main;
		}
		ix->cnt++;
		break;
	case eStep_Main:
	
		PlayerMgr_Updata();
		EnemyMgr_Updata();

#ifdef __MY_DEBUG__
		if(Keyboard_Press(KEY_INPUT_X)){
			//前の画面へ戻る
			Scene_Change(Scene_GetPrevSceneId());
		}
#endif 

		break;
	}

}

static void _Draw(WORK_OBJ* ix){
	
	if(ix->step != eStep_Main){
		//NowLoadingの表記
		int changeTiming = (ix->cnt / 20 )% 6;
		double rot = (double)(ix->cnt / 10.0);
		DrawString(0,460,strTbl[changeTiming],GetColor(255,255,255));
		Graphics_DrawRot(ComRes_GetGraphics(eComResID_UI_Star),0,0,rot,TRUE);
		return;
	}
	
	Model_Draw(CharComRes_GetModelData(eCharComResId_Map),VGet(0,0,0),VGet(1,1,1),VGet(0,0,0));

	PlayerMgr_Draw();
	EnemyMgr_Draw();
}

void GameMain_Init(){
	
	WORK_OBJ* ix = (WORK_OBJ*)Memory_Alloc(sizeof(WORK_OBJ));

	if(ix != NULL){

		ix->step = eStep_Init;
		ix->cnt = 0;

		CharComRes_Init();
		s_pWork = ix;
	}
}

void GameMain_UpData(){
	_Updata(s_pWork);	
}
void GameMain_Draw(){
	_Draw(s_pWork);
}

void GameMmain_Finalize(){

	PlayerMgr_Finalize();
	EnemyMgr_Finalize();

	CharComRes_Finalize();

	Memory_SafeFree(s_pWork);

}