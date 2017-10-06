/*
				ファイル名		:Framework.h
				作成者			:
				作成日時		:2017/09/30
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

//	------- インクルード宣言

//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

//	------- 構造体&共用体
typedef struct{
	void (*InitFunc)();
	void (*FinalzieFunc)();
	void (*UpdataFunc)();
	void (*DrawFunc)();
}FRAMEWORK_DATA;
//	------- グローバル関数

/*
	framework初期化
	const FRAMEWORK_DATA cFramework	:frameworkを設定
	int fps							:フレームレートを設定(設定がなければ60fps)
	int fpsSample					:フレームレートのサンプル数を設定(設定がなければサンプル数60)
*/
void Framework_Init(const FRAMEWORK_DATA cFramework,int fps = 60,int fpsSample = 60);

/*
	framework終了処理
*/
void Framework_Finalize();

/*
	更新処理開始
*/
void Framework_UpdataBgin();

/*
	描画処理
*/
void Framework_Draw();

/*
	更新処理終了
*/
void Framework_UpdataEnd();

//	------- インライン関数(ヘッダー内関数)



#endif // __FRAMEWORK_H__