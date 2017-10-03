/*
				ファイル名		:TestGameMain.cpp
				作成者			:
				作成日時		:2017/09/09
				ソース説明		:
				
				
				備考
				
				
				
!*/

//	------- インクルード宣言
#include "Common/GameCommon/GameCommon.h"

#include "Tetoris/TestTetoris.h"
#include "PackMan/PackManGameMgr.h"

#include "TestGameMgr.h"
//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

enum eStep{
	eStep_Select,
	eStep_Create,
	eStep_Play,
};

//	------- 構造体&共用体

typedef struct{
	void (*CreateFunc)();	//ゲーム生成
	bool (*IsEndFunc)();	//ゲームが終了しているか
	char name[256];			//名前
}GAME_DATA;

typedef struct{

	s32 select;
	const GAME_DATA* pGame;
	eStep step;
	FontMgr font;

}WORK_OBJ;


//	------- データテーブル
static const GAME_DATA s_cGameTbl[] = {
	//ゲーム生成関数			終了確認関数				名前
	{TestTetoris_Init,			TestTetoris_IsEnd,			"テトリス"	},
	{TestPackManGameMgr_Create,	TestPackManGameMgr_IsEnd,	"パックマン"},
};
//	------- スタティック変数宣言

static s32 TblNum = sizeof(s_cGameTbl) / sizeof(s_cGameTbl[0]);

static WORK_OBJ s_work;

//	------- グローバル変数宣言

//	------- スタティックプロトタイプ宣言(内部関数)

//	------- プロトタイプ宣言していないスタティック関数(内部関数)

static void _Updata(WORK_OBJ* ix){

	
	switch(ix->step){
	case eStep_Select:

		if(Keyboard_Repeat(KEY_INPUT_UP)){

			GameCommon_SelectClamp(&ix->select,-1,0,TblNum,eClampType_ClampLoop);

		}else if(Keyboard_Repeat(KEY_INPUT_DOWN)){
			GameCommon_SelectClamp(&ix->select,1,0,TblNum,eClampType_ClampLoop);
		}

		if(Keyboard_Press(KEY_INPUT_Z)){
			ix->pGame = &s_cGameTbl[ix->select];
			ix->step = eStep_Create;

		}else if(Keyboard_Press(KEY_INPUT_X)){
			Scene_Change(Scene_GetPrevSceneId());
		}


		break;
	case eStep_Create:
		
		if(ix->pGame && ix->pGame->CreateFunc){
			ix->pGame->CreateFunc();
			ix->step = eStep_Play;
		}else{
			ix->step = eStep_Select;
		}

		break;
	case eStep_Play:

		if(ix->pGame && ix->pGame->IsEndFunc){

			if(ix->pGame->IsEndFunc()){
				ix->pGame = NULL;
				ix->step = eStep_Select;
			}

		}else{
			ix->step = eStep_Select;
		}

		break;
	}

}

static void _Draw(WORK_OBJ* ix){

	
	switch(ix->step){
	case eStep_Select:

		ix->font.Draw(20,20,"テストゲーム選択",COLOR_WHITE);

		for(int i = 0;i < TblNum;i++){
			const GAME_DATA* pGame = &s_cGameTbl[i];
			ix->font.Draw(20,i * 20 + 60,pGame->name,COLOR_WHITE);
		}
		
		ix->font.Draw(0,ix->select * 20 + 60,"◆",COLOR_WHITE);

		break;
	case eStep_Create:
		
		break;
	case eStep_Play:

		break;
	}

}


//	------- グローバル関数


/*
	初期化
*/
void TestGameMgr_Init(){

	memset(&s_work ,0,sizeof(WORK_OBJ));

	//パソコンに入っているフォントからフォントを生成する
	s_work.font.CreateFontHandle("ＭＳ 明朝",16,1,-1);

}

/*
	終了処理
*/
void TestGameMgr_Finalize(){

	//フォント削除
	s_work.font.DeleteFont();

}

/*
	更新
*/
void TestGameMgr_Updata(){

	_Updata(&s_work);
	
}

/*
	描画
*/
void TestGameMgr_Draw(){

	_Draw(&s_work);

}