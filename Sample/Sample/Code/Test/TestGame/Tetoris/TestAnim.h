#pragma once

#include "Common/GameCommon/GameCommon.h"

enum eAnimKind{

	eAnimKind_In,		
	eAnimKind_Out,
	eAnimKind_Rot,
	eAnimKind_RandomMove,
};

typedef struct{
	GRAPHICS_RES res;
	int posX;
	int posY;
	double scal;
	double rot;
	eAnimKind anim;
	int step;
	int cnt;
	int dir;
}TEST_ANIM_OBJ;

//アニメーションを変更する
void TestAnimObj_ChangeAnim(TEST_ANIM_OBJ* ix,eAnimKind anim);

//座標を設定する
void TestAnimObj_SetPosition(TEST_ANIM_OBJ* ix,int posX,int posY);

/*
アニメションの生成
	
	@pram fileName	:	読み込む画像のパス
	@pram PosX		:	X座標
	@pram PosY		:	Y座標
	@pram Scal		:	サイズ
	@pram rot		:	角度
	@pram anim		:	アニメーションの種類
	


	@return	
*/
TEST_ANIM_OBJ* TestAnimObj_Create(const char* fileName,int posX,int posY,double scal,double rot,eAnimKind anim);

//アニメーションの削除
void TestAnimObj_Destroy(TEST_ANIM_OBJ* ix);