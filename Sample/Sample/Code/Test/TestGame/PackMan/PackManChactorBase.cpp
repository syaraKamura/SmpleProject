/*
				ファイル名		:PackManCharactorBase.cpp
				作成者			:
				作成日時		:2017/09/20
				ソース説明		:
				
					キャラクターの基底
				
				備考
				
				
				
!*/

//	------- インクルード宣言

#include "TDXLib.h"

#include "PackManChactorBase.h"

//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

//	------- 構造体&共用体

//	------- データテーブル

//	------- スタティック変数宣言

//	------- グローバル変数宣言

//	------- スタティックプロトタイプ宣言(内部関数)

//	------- プロトタイプ宣言していないスタティック関数(内部関数)

//	------- グローバル関数
/*
	初期化
	PACKMAN_CHARACTOR_BASE* ix
	s32 posX
	s32 posY
	GRAPHICS_RES* pRes				:画像データ
	ePackManCharactorBase_Type type	:キャラクターの種類
*/
void PackManCharactorBase_Init(PACKMAN_CHARACTOR_BASE* ix,s32 posX,s32 posY,GRAPHICS_RES* pRes,ePackManCharactorBase_Type type){

	ix->posX = posX;
	ix->posY = posY;
	ix->pRes = pRes;
	ix->type = type;
	ix->isMove = false;
}

/*
	終了処理
	PACKMAN_CHARACTOR_BASE* ix
*/
void PackManCharactorBase_Finalize(PACKMAN_CHARACTOR_BASE* ix){

	ix->posX = 0;
	ix->posY = 0;
	ix->pRes = NULL;
	ix->type = ePackManCharactorBase_Type_None;
	ix->isMove = false;

}

/*
	描画する
	PACKMAN_CHARACTOR_BASE* ix
	ePackManCharactorBase_Graphic kind
*/
void PackManCharactorBase_Draw(PACKMAN_CHARACTOR_BASE* ix){

	//画像データがなければ処理を抜ける
	if(ix->pRes == NULL) return ;

	Graphics_DrawSplit(ix->pRes,ix->posX,ix->posY,0,0,32,32,TRUE,FALSE);

}

/*
	座標の設定
	PACKMAN_CHARACTOR_BASE* ix
	s32 posX	:X座標
	s32 posY	:Y座標
*/
void PackManCharctorBase_SetPosition(PACKMAN_CHARACTOR_BASE* ix,s32 posX,s32 posY){

	ix->posX = posX;
	ix->posY = posY;

}


/*
	座標の取得
	PACKMAN_CHARACTOR_BASE* ix
	s32* posX		:X座標
	s32* posY		:Y座標
*/
void PackManCharactorBase_GetPosition(PACKMAN_CHARACTOR_BASE* ix,s32* posX,s32* posY){
	*posX = ix->posX;
	*posY = ix->posY;
}


/*
	行動フラグの状態を取得する
	PACKMAN_CHARACTOR_BASE* ix
	return	true	:行動している
			false	:行動していない
*/
bool PacjNabCharactorBase_IsMove(PACKMAN_CHARACTOR_BASE* ix){
	return ix->isMove;
}


/*
	行動フラグをOnにする
	PACKMAN_CHARACTOR_BASE* ix
*/
void PackManCharactorBase_MoveOn(PACKMAN_CHARACTOR_BASE* ix){
	ix->isMove = true;
}

/*
	行動フラグをOffにする
	PACKMAN_CHARACTOR_BASE* ix
*/
void PackManCharactorBase_MoveOff(PACKMAN_CHARACTOR_BASE* ix){
	ix->isMove = false;
}

