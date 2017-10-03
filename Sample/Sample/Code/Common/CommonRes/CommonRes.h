/*
	汎用リソース

	ゲーム全体が始まる前に読み込みを行う。
	ゲームが終了するときにリソースを開放する

!*/

#pragma once

#include "MyLib/Graphics/Graphics.h"
#include "MyLib/Model/Model.h"

enum eComResID{
	eComResID_UI_Star,
	eComResID_IMG_SHOT,

	eComResID_MAX,
};

//初期化
void ComRes_Init();
//狩猟処理
void ComRes_Finalize();

//リソースの読み込みが終了したか？
bool ComRes_IsLoadEnd();

//画像データを返却する
GRAPHICS_RES* ComRes_GetGraphics(eComResID comResID);