/*
				ファイル名		:PackManCharactorBase.h
				作成者			:
				作成日時		:2017/09/20
				ソース説明		:
				
					キャラクターの基底
				
				備考
				
				
				
!*/

#ifndef __PACKMAN_CHARACTOR_BASE_H__
#define __PACKMAN_CHARACTOR_BASE_H__

//	------- インクルード宣言

//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

enum ePackManCharactorBase_Type{
	ePackManCharactorBase_Type_None,		//タイプなし
	ePackManCharactorBase_Type_Player,		//プレイヤーキャラクター
	ePackManCharactorBase_Type_Enemy,		//敵
};

//	------- 構造体&共用体
typedef struct{
	ePackManCharactorBase_Type type;	//キャラクタータイプ
	s32 posX;							//座標
	s32 posY;
	GRAPHICS_RES* pRes;					//画像データ
	bool isMove;						//移動しているか
}PACKMAN_CHARACTOR_BASE;

//	------- グローバル関数

/*
	初期化
	PACKMAN_CHARACTOR_BASE* ix
	s32 posX
	s32 posY
	GRAPHICS_RES* pRes				:画像データ
	ePackManCharactorBase_Type type	:キャラクターの種類
*/
void PackManCharactorBase_Init(PACKMAN_CHARACTOR_BASE* ix,s32 posX,s32 posY,GRAPHICS_RES* pRes,ePackManCharactorBase_Type type);

/*
	終了処理
	PACKMAN_CHARACTOR_BASE* ix
*/
void PackManCharactorBase_Finalize(PACKMAN_CHARACTOR_BASE* ix);

/*
	描画する
	PACKMAN_CHARACTOR_BASE* ix
	ePackManCharactorBase_Graphic kind
*/
void PackManCharactorBase_Draw(PACKMAN_CHARACTOR_BASE* ix);

/*
	座標の設定
	PACKMAN_CHARACTOR_BASE* ix
	s32 posX	:X座標
	s32 posY	:Y座標
*/
void PackManCharctorBase_SetPosition(PACKMAN_CHARACTOR_BASE* ix,s32 posX,s32 posY);


/*
	座標の取得
	PACKMAN_CHARACTOR_BASE* ix
	s32* posX		:X座標
	s32* posY		:Y座標
*/
void PackManCharactorBase_GetPosition(PACKMAN_CHARACTOR_BASE* ix,s32* posX,s32* posY);


/*
	行動フラグの状態を取得する
	PACKMAN_CHARACTOR_BASE* ix
	return	true	:行動している
			false	:行動していない
*/
bool PacjNabCharactorBase_IsMove(PACKMAN_CHARACTOR_BASE* ix);


/*
	行動フラグをOnにする
	PACKMAN_CHARACTOR_BASE* ix
*/
void PackManCharactorBase_MoveOn(PACKMAN_CHARACTOR_BASE* ix);

/*
	行動フラグをOffにする
	PACKMAN_CHARACTOR_BASE* ix
*/
void PackManCharactorBase_MoveOff(PACKMAN_CHARACTOR_BASE* ix);


//	------- インライン関数(ヘッダー内関数)


#endif // __PACKMAN_CHARACTOR_BASE_H__
