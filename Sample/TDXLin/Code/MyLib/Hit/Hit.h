#pragma once

//あたり判定とか

typedef struct{
	int posX;		//座標
	int posY;
	int width;		//サイズ
	int height;
	float radius;	//半径
}HIT_DATA;

//四角形と点あたり判定

/*
	四角形と四角形のあたり判定
	HIT_DATA rec1:四角形1
	HIT_DATA rec2:四角形2
	return	true	:当たっている
			false	:当たっていない
*/
extern bool Hit2D_BoxToBox(HIT_DATA rec1,HIT_DATA rec2);

/*
	円と点のあたり判定
	HIT_DATA circle	:円
	HIT_DATA dot	:点
	return	true	:当たっている
			false	:当たっていない
*/

extern bool Hit2D_CircleToDot(HIT_DATA circle,HIT_DATA dot);
/*
	円と円のあたり判定
	HIT_DATA corcle1:円1
	HIT_DATA corcle2:円2
	return	true	:当たっている
			false	:当たっていない
*/
extern bool Hit2D_CircleToCircle(HIT_DATA circle1,HIT_DATA circle2);

/*
	ヒットデータ構造体型にして返却します
	int posX		:X座標
	int posY		:Y座標
	int width		:横幅
	int height		:縦幅
	float radius	:半径
	return HIT_DATA型を返却
*/
extern HIT_DATA HIT2D_GetHitData(int posX,int posY,int width,int height,float radius);