/*
				ファイル名		:ScriptFlag.h
				作成者			:
				作成日時		:2017/08/20
				ソース説明		:スクリプトが扱うフラグを扱う
				


				
				備考
				
				
				
!*/

#ifndef __SCRIPT_FLAG_H__
#define __SCRIPT_FLAG_H__

//	------- インクルード宣言

//	------- 固定定数宣言

static const int FLAG_DATA_NUM = 4096;

//	-------	マクロ定義

//	------- 列挙体

//	------- 構造体&共用体

typedef struct{
	u8 flag[FLAG_DATA_NUM];
}SCRIPT_FLAG_DATA;

//	------- グローバル関数

/*
	スクリプトフラグを初期化する
	SCRIPT_FLAG_DATA*	flag
*/
void ScriptFlag_Initialize(SCRIPT_FLAG_DATA* flag);
/*
	フラグデータの読み込みを行う
	SCRIPT_FLAG_DATA*	flag
*/
void ScriptFlag_Load(SCRIPT_FLAG_DATA* flag);
/*
	フラグデータの保存を行う
	SCRIPT_FLAG_DATA*	flag		:
	const char*			path		:保存先のファイル名を含めたパスを入力する(例. data/save/flags)
*/
bool ScriptFlag_Save(SCRIPT_FLAG_DATA* flag,const char* path);

/*
	指定のフラグ番号をオンにする
	SCRIPT_FLAG_DATA*	flag	:
	s32					index	:フラグ番号
*/
void ScriptFlag_FlagOn(SCRIPT_FLAG_DATA* flag,s32 index);
/*
	指定のフラグ番号をオフにする
	SCRIPT_FLAG_DATA*	flag	:
	s32					index	:フラグ番号
*/
void ScriptFlag_FlagOff(SCRIPT_FLAG_DATA* flag,s32 index);
/*
	指定のフラグ番号のフラグ状態を返却する(範囲外の場合は必ずオフを返却する)
	SCRIPT_FLAG_DATA*	flag	:
	s32					index	:フラグ番号
	return	0:フラグオフ
			1:フラグオン
*/
u8 ScriptFlag_GetFlag(SCRIPT_FLAG_DATA* flag,s32 index);

//	------- インライン関数(ヘッダー内関数)

#endif	//__SCRIPT_FLAG_H__
