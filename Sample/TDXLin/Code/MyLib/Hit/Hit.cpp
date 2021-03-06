/*

	汎用あたり判定


!*/

#include "DxLib.h"

#include "Hit.h"


//四角形と点あたり判定

/*
	四角形と四角形のあたり判定
	HIT_DATA rec1:四角形1
	HIT_DATA rec2:四角形2
	return	true	:当たっている
			false	:当たっていない
*/
bool Hit2D_BoxToBox(HIT_DATA rec1,HIT_DATA rec2){

	if(((rec1.posX >= rec2.posX && rec1.posX <= rec2.posX + rec2.width) || 
		(rec1.posX + rec1.width >= rec2.posX && rec1.posX + rec1.width <= rec2.posX + rec2.width)) ||
		((rec1.posY >= rec2.posY && rec1.posY <= rec2.posY + rec2.height) || 
		(rec1.posY + rec1.height >= rec2.posY && rec1.posY + rec1.height <= rec2.posY + rec2.height))){
			return true;
	}
	return false;
}

/*
	円と点のあたり判定
	HIT_DATA circle	:円
	HIT_DATA dot	:点
	return	true	:当たっている
			false	:当たっていない
*/
bool Hit2D_CircleToDot(HIT_DATA circle,HIT_DATA dot){

	//中心座標に修正
	int centerX = circle.posX + circle.width / 2;
	int centerY = circle.posY + circle.height / 2;

	int x = centerX - dot.posX;
	int y = centerY - dot.posY;
	float r = circle.radius;

	if(x*x+y*y <= r*r){
		return true;
	}

	return false;
}

/*
	円と円のあたり判定
	HIT_DATA corcle1:円1
	HIT_DATA corcle2:円2
	return	true	:当たっている
			false	:当たっていない
*/
bool Hit2D_CircleToCircle(HIT_DATA circle1,HIT_DATA circle2){

	//中心座標に修正
	int centerX1 = circle1.posX + circle1.width / 2;
	int centerY1 = circle1.posY + circle1.height / 2;

	int centerX2 = circle2.posX + circle2.width / 2;
	int centerY2 = circle2.posY + circle2.height / 2;


	int x = centerX1 - centerX2;
	int y = centerY1 - centerY2;
	float r = circle1.radius + circle2.radius;

	if(x*x+y*y <= r*r){
		return true;
	}

	return false;
}

/*
	ヒットデータ構造体型にして返却します
	int posX		:X座標
	int posY		:Y座標
	int width		:横幅
	int height		:縦幅
	float radius	:半径
	return HIT_DATA型を返却
*/
HIT_DATA HIT2D_GetHitData(int posX,int posY,int width,int height,float radius){
	HIT_DATA data = {posX,posY,width,height,radius};
	return data;
}