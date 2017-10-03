/*
				ファイル名		:GameData.h
				作成者			:
				作成日時		:2017/08/22
				ソース説明		:
				
					ゲームデータを管理する
					主にデータの保存やデータの読み込み等を行う
				
				備考
				
				
				
!*/

#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__

//	------- インクルード宣言

#include "Common/GameCommon/GameCommon.h"

//	------- 固定定数宣言
static const int FLAGS_DATA_NUM = 4096;
//	-------	マクロ定義

//	------- 列挙体

//	------- 構造体&共用体
typedef struct{
	s8 flags[FLAGS_DATA_NUM];
}GAME_FLAGS_DATA;

typedef struct{
	s32 hash;					//ハッシュ ここ値が異なる場合不正なセーブデータとする
	GAME_FLAGS_DATA gameFlag;
	char name[26];
}GAME_DATA;
//	------- グローバル関数

/*
	ゲームデータの初期化
*/
void GameData_Initialize();
/*
	ゲームデータの読み込み
*/
void GameData_Load();
/*
	ゲームデータの書き込み
*/
void GameData_Save();

// ----ゲームデータの取得(大枠)

/*
	ゲームデータ全体を返却する
*/
const GAME_DATA* GameData_GetGameData();


// ----ゲームデータの取得(個別)

/*
	ゲームのフラグの状態を返却する
	s32	flagIdx	:フラグ番号
	return	true	:フラグがON
			false	:フラグがOFF
*/
bool GameData_IsFlag(s32 flagIdx);

/*
	指定のフラグ番号を設定する
	s32		flagIdx	:フラグ番号
	BOOL	flag	:フラグを設定する
*/
void GameData_SetGameDataFlag(s32 flagIdx,BOOL flag);

//	------- インライン関数(ヘッダー内関数)


#endif	//__GAME_DATA_H__
