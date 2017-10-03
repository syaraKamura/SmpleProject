/*
				ファイル名		:ScripFlag.cpp
				作成者			:
				作成日時		:2071/08/20
				ソース説明		:スクリプトが扱うフラグを扱う
				
				
				備考
				
				
				
!*/

//	------- インクルード宣言
#include "Common/GameCommon/GameCommon.h"
#include "ScriptFlag.h"

//	------- 固定定数宣言

static const u8 FLAG_ON = 1;
static const u8 FLAG_OFF = 0;

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
	スクリプトフラグを初期化する
	SCRIPT_FLAG_DATA*	flag
*/
void ScriptFlag_Initialize(SCRIPT_FLAG_DATA* flag){
	
	//すべてのフラグを0にする
	for(int i = 0;i < FLAG_DATA_NUM;i++){
		flag->flag[i] = 0;
	}
}

/*
	フラグデータの読み込みを行う
	SCRIPT_FLAG_DATA*	flag
*/
void ScriptFlag_Load(SCRIPT_FLAG_DATA* flag){

	/*
		☆メモ

			◇処理について
				データが存在しているならばフラグデータの読み込みを行う
				データが存在していないならば何もしない。

			◇読み込みデータについて
				読み込みデータの拡張子は「.svf」
				読み込みデータのファイル名は「flagments」
	*/

}

/*
	フラグデータの保存を行う
	SCRIPT_FLAG_DATA*	flag		:
	const char*			path		:保存先のファイル名を含めたパスを入力する(例. data/save/flags)
*/
bool ScriptFlag_Save(SCRIPT_FLAG_DATA* flag,const char* path){
	
	/*
		☆メモ

			◇保存データについて
				保存データの拡張子は「.svf」
				保存データのファイル名は「flagments」

	*/
	return true;
}

/*
	指定のフラグ番号をオンにする
	SCRIPT_FLAG_DATA*	flag	:
	s32					index	:フラグ番号
*/
void ScriptFlag_FlagOn(SCRIPT_FLAG_DATA* flag,s32 index){
	
	//範囲外なら処理を抜ける
	if(index < 0 || index >= FLAG_DATA_NUM) return ;
	
	flag->flag[index] = FLAG_ON;
}

/*
	指定のフラグ番号をオフにする
	SCRIPT_FLAG_DATA*	flag	:
	s32					index	:フラグ番号
*/
void ScriptFlag_FlagOff(SCRIPT_FLAG_DATA* flag,s32 index){
	//範囲外なら処理を抜ける
	if(index < 0 || index >= FLAG_DATA_NUM) return ;
	
	flag->flag[index] = FLAG_OFF;
}

/*
	指定のフラグ番号のフラグ状態を返却する(範囲外の場合は必ずオフを返却する)
	SCRIPT_FLAG_DATA*	flag	:
	s32					index	:フラグ番号
	return	0:フラグオフ
			1:フラグオン
*/
u8 ScriptFlag_GetFlag(SCRIPT_FLAG_DATA* flag,s32 index){
	//範囲外なら処理を抜ける
	if(index < 0 || index >= FLAG_DATA_NUM) return FLAG_OFF;
	return flag->flag[index];
}
