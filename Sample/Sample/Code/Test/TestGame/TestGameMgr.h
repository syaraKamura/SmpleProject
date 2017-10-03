/*
				ファイル名		:TestGameMgr.h
				作成者			:
				作成日時		:2017/09/09
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __TEST_GAME_MGR_H__
#define __TEST_GAME_MGR_H__

//	------- インクルード宣言

//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

//	------- 構造体&共用体

//	------- グローバル関数

/*
	初期化
*/
void TestGameMgr_Init();

/*
	終了処理
*/
void TestGameMgr_Finalize();

/*
	更新
*/
void TestGameMgr_Updata();

/*
	描画
*/
void TestGameMgr_Draw();

//	------- インライン関数(ヘッダー内関数)

#endif // __TEST_GAME_MGR_H__