/*
				ファイル名		:PackManStageMgr.h
				作成者			:
				作成日時		:2017/09/09
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __PACKMAN_STAGE_MGR_H__
#define __PACKMAN_STAGE_MGR_H__

//	------- インクルード宣言


//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

enum ePackManStage_FieldStatus{
	
	ePackManStage_FieldStatus_Disabled = -1,//無効な値が返ってきた

	ePackManStage_FieldStatus_Passible,		//通行可能
	ePackManStage_FieldStatus_NoPassible,	//通行不可能
	
	
	ePackManStage_FieldStatus_None = 99,	//データなし
};

//	------- 構造体&共用体

typedef struct{
	
	s32 cnt;
	s32 step;
	
	GRAPHICS_RES img;
	Array2D<int>* pStageData;

	bool isKill;
}PACKMAN_STAGE_MGR;
//	------- グローバル関数

/*
	生成
*/
PACKMAN_STAGE_MGR* PackManStageMgr_Create();

/*
	終了をリクエストする
	PACKMAN_STAGE_MGR* ix:
*/
void PackManStageMgr_RequestKill(PACKMAN_STAGE_MGR* ix);



/*
	ステージのフィールドデータを取得する
	PACKMAN_STAGE_MGR* ix
	int posX		:X座標
	int posY		:Y座標
	return	ePackManStage_FieldStatus_Disabled			:ステージ範囲外 
			ePackManStage_FieldStatus_Passible			:通行可能
			ePackManStage_FieldStatus_NoPassible		:通行不可能
*/
ePackManStage_FieldStatus PackManStageMgr_GetFieldPassible(PACKMAN_STAGE_MGR* ix,s32 posX,s32 posY);

/*
	ステージの範囲外の座標にいるか判断する
	PACKMAN_STAGE_MGR* ix
	s32 posX
	s32 posY
	return	true	:範囲外にいる
			false	:範囲以内にいる
*/
bool PackManStageMgr_IsOutOfRange(PACKMAN_STAGE_MGR* ix,s32 posX,s32 posY);

//	------- インライン関数(ヘッダー内関数)

#endif // __PACKMAN_STAGE_MGR_H__