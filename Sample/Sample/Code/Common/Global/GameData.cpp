/*
				ファイル名		:GameData.cpp
				作成者			:
				作成日時		:2017/08/22
				ソース説明		:
				
					ゲームデータを管理する
					主にデータの保存やデータの読み込み等を行う
				
				備考
				
				
				
!*/

//	------- インクルード宣言
#include "Common/GameCommon/GameCommon.h"
#include "GameData.h"
//	------- 固定定数宣言

//	-------	マクロ定義
#define HASH(S,A,V,E) ((S << 16) + (A << 8) + (V << 4) + (E << 1))
#define SAVE HASH('S','A','V','E')

#define FILE_NAME "SAVE.txt"

//	------- 列挙体

//	------- 構造体&共用体

//	------- データテーブル

//	------- スタティック変数宣言
static GAME_DATA s_GameData;
//	------- グローバル変数宣言

//	------- スタティックプロトタイプ宣言(内部関数)

//	------- プロトタイプ宣言していないスタティック関数(内部関数)

//	------- グローバル関数

/*
	ゲームデータの初期化
*/
void GameData_Initialize(){
	memset(&s_GameData,0,sizeof(GAME_DATA));
	s_GameData.hash = SAVE;
	strcpy_s(s_GameData.name,26,"日本語");
}

/*
	ゲームデータの読み込み
*/
void GameData_Load(){
	
	s64 hash = SAVE;
	GAME_DATA data;
	FILE* fp;

	fopen_s(&fp,FILE_NAME,"rb");

	if(fp == NULL){
		Debug_LogPrintf("SAVEデータを開けませんでした。\n");
		return ;
	}

	fread(&data,1,sizeof(GAME_DATA),fp);

	fclose(fp);
	
	if(data.hash != SAVE){
		Debug_LogPrintf("SAVEデータが不正です。\n");
		memset(&data,0,sizeof(GAME_DATA));
	}else{
		Debug_LogPrintf("SAVEデータの読み込みに成功しました。\n");
		s_GameData = data;
		Debug_LogPrintf("name:%s\n",data.name);

	}


}

/*
	ゲームデータの書き込み
*/
void GameData_Save(){

	const GAME_DATA* pData = GameData_GetGameData();

	FILE* fp;

	fopen_s(&fp,FILE_NAME,"wb");

	if(fp == NULL){
		Debug_LogPrintf("SAVEデータを開けませんでした。\n");
		return ;
	}

	fwrite(pData,1,sizeof(GAME_DATA),fp);

	Debug_LogPrintf("SAVEデータへ保存ができました\n");
	fclose(fp);

	Debug_LogPrintf("HASH = %d\n",SAVE);

}

// ----ゲームデータの取得(大枠)

/*
	ゲームデータ全体を返却する
*/
const GAME_DATA* GameData_GetGameData(){
	return &s_GameData;
}



// ----ゲームデータの取得(個別)

/*
	ゲームのフラグの状態を返却する
	s32	flagIdx	:フラグ番号
	return	true	:フラグがON
			false	:フラグがOFF
*/
bool GameData_IsFlag(s32 flagIdx){

	//フラグの範囲外を指定されたらOFFフラグを返却する
	if(flagIdx < 0 || flagIdx >= FLAGS_DATA_NUM){
		Debug_LogPrintf("Func: %s line:%d\n フラグの範囲外を指定しました。\n",__FUNCTION__,__LINE__);
		return false;
	}

	//0より大きければtrueを返却する
	return s_GameData.gameFlag.flags[flagIdx] > 0;
}

/*
	指定のフラグ番号を設定する
	s32		flagIdx	:フラグ番号
	BOOL	flag	:フラグを設定する
*/
void GameData_SetGameDataFlag(s32 flagIdx,BOOL flag){

	//フラグの範囲外を指定されたら処理を抜ける
	if(flagIdx < 0 || flagIdx >= FLAGS_DATA_NUM){
		Debug_LogPrintf("Func: %s line:%d\n フラグの範囲外に設定しようとしました。\n",__FUNCTION__,__LINE__);	
		return;
	}
	s_GameData.gameFlag.flags[flagIdx] = flag;

}


#ifdef __MY_DEBUG__




#endif //__MY_DEBUG__