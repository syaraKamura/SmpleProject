/*

	ゲームで汎用的に使用するヘッダーファイルやコードをまとめた
	汎用ソースファイル

	GameCommonをインクルードすることでMyLibのソースが使用可能になる

*/

#ifndef __GAME_COMMON_H__
#define __GAME_COMMON_H__

#if 0
#include "DxLib.h"
#include "MyLib/Graphics/Graphics.h"
#include "MyLib/Keyboard/Keyboard.h"
#include "MyLib/Touch/Touch.h"
#include "MyLib/Model/Model.h"
#include "MyLib/Debug/Debug.h"
#include "MyLib/Memory/Memory.h"
#include "MyLib/Task/Task.h"
#include "MyLib/Communication/Communication.h"
#include "MyLib/KeyInputString/KeyInputString.h"
#include "MyLib/Sound/Sound.h"
#include "MyLib/Figure/Figure.h"

#include "MyLib/Easing/Easing.h"

#include "MyLib/FontMgr/FontMgr.h"
#endif 

#include "../TDXLin/TDXLib.h"

#include "Scene/Scene.h"
#include <math.h>

#ifdef __WINDOWS__
	#include <crtdbg.h>
#endif	//__WINDOWS__


//	----- よく使う色の定数
#define COLOR_WHITE GetColor(255,255,255)	//白
#define COLOR_BLACK GetColor(0,0,0)			//黒
#define COLOR_GRAY	GetColor(123,123,123)	//灰色
#define COLOR_RED	GetColor(255,0,0)		//赤
#define COLOR_GREEN	GetColor(0,255,0)		//緑
#define COLOR_BLUE	GetColor(0,0,255)		//青
#define COLOR_YELLOW GetColor(255,255,0)	//黄色


enum eClampType{
	eClampType_ClampStop,
	eClampType_ClampLoop,
};


/*
	選択クランプ
	int*			val			:変更する値
	int				add			:加算する値
	int				min			:最小値
	int				max			:最大値
	eClampType		clampType	:クランプの種類
*/
void GameCommon_SelectClamp(int* val,int add,int min,int max,eClampType clampType);

/*
	選択クランプ(float型)
	float*		val			:変更する値
	float		add			:加算する値
	float		min			:最小値
	float		max			:最大値
	eClampType	clampType	:クランプの種類
*/
void GemeCommon_SelectClampF(float* val,float add,float min,float max,eClampType clampType);

#endif	//__GAME_COMMON_H__