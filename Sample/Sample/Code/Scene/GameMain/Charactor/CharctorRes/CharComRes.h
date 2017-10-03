#pragma once

/*

	キャラクターが使用するデータの読み込みを行う

	ゲームメインに移行した際にデータの読み込みを行う

		※非同期読み込みが望ましい。

	

*/


enum eCharComResId{

	//モデル
	eCharComResId_Charactor,	//キャラクター
	eCharComResId_Enemy1,		//敵
	eCharComResId_Enemy2,		//敵2
	eCharComResId_Map,			//マップ
	//画像
	eCharComResId_UI_HpGage,	//体力ゲージ

	//csvデータ
	
	eCharComResId_Max,
};

//メモリの確保
void CharComRes_Init();

void CharComRes_Finalize();

//読み込みリクエスト
void CharComRes_LoadRequest();

//読み込みが終了したか判断する
//true:読み込み終了 false:読み込み中
bool CharComRes_IsLoadEnd();

//データを返却する
MODEL_DATA_HANDLE* CharComRes_GetModelData(eCharComResId idx);

//データを返却する
GRAPHICS_RES* CharComRes_GetGraphics(eCharComResId idx);

int CharComRes_GetCsvDataSize(eCharComResId idx);

const char* CharComRes_GetCsvData(eCharComResId idx);