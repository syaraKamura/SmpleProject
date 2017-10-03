/*
				ファイル名		:PackManStageMgr.cpp
				作成者			:
				作成日時		:2017/09/09
				ソース説明		:
				
					ステージを管理する
				
				備考
				
				
				
!*/

//	------- インクルード宣言
#include "Common/GameCommon/GameCommon.h"

#include "PackManStageMgr.h"

//	------- 固定定数宣言

//	-------	マクロ定義

const int CHIP_SIZE = 32;		//チップサイズ

//	------- 列挙体

enum {
	ePackManStageMainStep_Init,
	ePackManStageMainStep_SetUp,
	ePackManStageMainStep_Main,
	ePackManStageMainStep_Exit,
	ePackManStageMainStep_ExitDone,
};

//	------- 構造体&共用体

//	------- データテーブル

/*
	テストデータ
*/
 static const int s_cStageTbl[] = {

	 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
	 7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,3,
	 7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,3,
	 7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,3,
	 7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,3,
	 7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,3,
	 7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,3,
	 7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,3,
	 7,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,3,
	 4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,

 };

//	------- スタティック変数宣言

//	------- グローバル変数宣言

//	------- スタティックプロトタイプ宣言(内部関数)

//	------- プロトタイプ宣言していないスタティック関数(内部関数)

/*
	更新
*/
static void _Updata(PACKMAN_STAGE_MGR* ix){

	switch(ix->step){
	case ePackManStageMainStep_Init:

		if(Graphics_IsASyncLoadEnd(&ix->img)){
			ix->step = ePackManStageMainStep_SetUp;
		}

		break;
	case ePackManStageMainStep_SetUp:

		for(int i = 0;i < ix->pStageData->GetSize();i++){
			ix->pStageData->SetValueToIdx(i,s_cStageTbl[i]);
		}

		ix->step = ePackManStageMainStep_Main;
		break;
	case ePackManStageMainStep_Main:

		break;
	case ePackManStageMainStep_Exit:

		if(ix->cnt == 0){

			Graphics_Delete(&ix->img);

			delete ix->pStageData;
		}

		ix->cnt ++;
		
		if(ix->cnt > 2){
			ix->step = ePackManStageMainStep_ExitDone;
		}

		break;
	case ePackManStageMainStep_ExitDone:
		Task_KillRequest(ix);	
		ix->isKill = true;
		break;
	}

}

/*
	描画
*/
static void _Draw(PACKMAN_STAGE_MGR* ix){

	if(ix->step != ePackManStageMainStep_Main) return ;

	s32 width = ix->pStageData->GetWidth();
	s32 height = ix->pStageData->GetHeight();

	for(int y = 0;y < height;y++){
		for(int x = 0;x < width;x++){
			
			s32 drawX = x * CHIP_SIZE;
			s32 drawY = y * CHIP_SIZE;
			s32 w = drawX + CHIP_SIZE;
			s32 h = drawY + CHIP_SIZE;

			s32 u = ix->pStageData->GetArray(x,y) % 4;
			s32 v = ix->pStageData->GetArray(x,y) / 4;

			if(ix->pStageData->GetArray(x,y) < 9){
				DrawBox(drawX,drawY,w,h,COLOR_BLUE,TRUE);
			}else{
				DrawBox(drawX,drawY,w,h,COLOR_GRAY,TRUE);
				
			}
			Graphics_DrawSplit(&ix->img,drawX,drawY,u,v,32,32,TRUE,FALSE);
		}
	}

}


//	------- グローバル関数

/*
	生成
*/
PACKMAN_STAGE_MGR* PackManStageMgr_Create(){

	PACKMAN_STAGE_MGR* ix = Task_CreateBase(_Updata,_Draw,NULL,PACKMAN_STAGE_MGR,eTaskClassType_Class00);
	
	if(ix != NULL){

		ix->cnt = 0;
		ix->step = ePackManStageMainStep_Init;

		ix->pStageData = new Array2D<int>(20,10);

		Graphics_ASyncLoad(&ix->img,"Data/Graphic/Test/PackMan/Field.png");

		//削除フラグをオフにする
		ix->isKill = false;

		return ix;

	}
	return NULL;
}

/*
	終了をリクエストする
	PACKMAN_STAGE_MGR* ix:
*/
void PackManStageMgr_RequestKill(PACKMAN_STAGE_MGR* ix){
	//データがなければ処理を抜ける
	if(ix == NULL) return ;
	ix->step = ePackManStageMainStep_Exit;
	ix->cnt = 0;
}




// --------- ユーザー使用関数


/*
	ステージのフィールドデータを取得する
	PACKMAN_STAGE_MGR* ix
	s32 posX		:X座標
	s32 posY		:Y座標
	return	-1		:ステージ範囲外 
			0以上	:通行判定
			0		:通行可能
			1		:通行不可能
*/
ePackManStage_FieldStatus PackManStageMgr_GetFieldPassible(PACKMAN_STAGE_MGR* ix,s32 posX,s32 posY){
	
	s32 x = posX / CHIP_SIZE;
	s32 y = posY / CHIP_SIZE;
	
	return (ePackManStage_FieldStatus)ix->pStageData->GetArray(posX,posY);
}


/*
	ステージの範囲外の座標にいるか判断する
	PACKMAN_STAGE_MGR* ix
	s32 posX
	s32 posY
	return	true	:範囲外にいる
			false	:範囲以内にいる
*/
bool PackManStageMgr_IsOutOfRange(PACKMAN_STAGE_MGR* ix,s32 posX,s32 posY){
	s32 x = posX / CHIP_SIZE;
	s32 y = posY / CHIP_SIZE;

	bool isOutOfRange = ix->pStageData->IsOutOfRange(x,y);

	return isOutOfRange;
}