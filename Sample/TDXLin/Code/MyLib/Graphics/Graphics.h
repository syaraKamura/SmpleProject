#pragma once

#include "DxLib.h"

typedef struct{
	int graphicHandle;	//画像ハンドル
	int basePosX;		//画面の始点位置
	int basePosY;
	int offsetPosX;		//画像の中心座標
	int offsetPosY;
	int drawPosX;		//描画座標
	int drawPosY;
	int width;			//画像サイズ
	int height;
	//int pad;			//ぱでぃんぐ
}GRAPHICS_RES;

//画像読み込み基底
extern bool Graphics_LoadBase(GRAPHICS_RES* graphics,const char* fileName,int offsetPosX = 0,int offsetPosY = 0,int basePosX = 0,int basePosY = 0);
//画像読み込み
extern bool Graphics_Load(GRAPHICS_RES* graphics,const char* fileName);

//画像の非同期読み込み基底
extern void Graphics_ASyncLoadBase(GRAPHICS_RES* graphics,const char*fileName,int offsetPosX = 0,int offsetPosY = 0,int basePosX = 0,int basePosY = 0);
//画像の非同期読み込み
extern void Graphics_ASyncLoad(GRAPHICS_RES* graphics,const char* fileName);

//画像の非同期読み込みが終了しているか？
extern bool Graphics_IsASyncLoadEnd(GRAPHICS_RES* graphics);

extern void Graphics_Delete(GRAPHICS_RES* graphics);

//画像の描画
/*
	処理について	画像描画規定
	関数名			Graphics_DrawBase
	引数			GRAPHICS_RES*	graphics	:グラフィックリソース構造体
	引数			int				posX		:X座標
	引数			int				posY		:Y座標
	引数			int				scrX		:描画を行う画像内での左上の座標U(100なら 画像内座標100からwidthまでの範囲を描画する)
	引数			int				scrY		:描画を行う画像内での左上の座標V(100なら 画像内座標100からheightまでの範囲を描画する)
	引数			int				width		:画像サイズ
	引数			int				heihgt		:画像サイズ
	引数			int				centerX		:回転の中心座標X
	引数			int				centerY		:回転の中心座標Y
	引数			double			ExtRate		:拡大率(1.0が通常サイズ)
	引数			double			angle		:描画角度
	引数			int				transFlag	:画像の透明度を有効にするか？(TRUE:有効 FALSE:無効)
	引数			int				turnFlag	:画像を反転させるか?(TRUE:反転する FALSE:反転しない)
!*/
extern void Graphics_DrawBase(GRAPHICS_RES* graphics,int posX,int posY,int scrX,int scrY,int width,int heihgt,int centerX,int centerY,double ExtRate,double angle,int transFlag,int turnFlag);
/*
	処理について	画像描画
	関数名			Graphics_DrawBase
	引数			GRAPHICS_RES*	graphics	:グラフィックリソース構造体
	引数			int				posX		:X座標
	引数			int				posY		:Y座標
	引数			int				transFlag	:画像の透明度を有効にするか？(TRUE:有効 FALSE:無効)
	引数			int				turnFlag	:画像を反転させるか?(TRUE:反転する FALSE:反転しない)
!*/
extern void Graphics_Draw(GRAPHICS_RES* graphics,int posX,int posY,int transFlag,int turnFlag = FALSE);

/*
	処理について	画像描画(画像の中心を起点に回転をする)
	関数名			Graphics_DrawRot
	引数			GRAPHICS_RES*	graphics	:グラフィックリソース構造体
	引数			int				posX		:X座標
	引数			int				posY		:Y座標
	引数			double			angle		:描画角度
	引数			int				transFlag	:画像の透明度を有効にするか？(TRUE:有効 FALSE:無効)
	引数			int				turnFlag	:画像を反転させるか?(TRUE:反転する FALSE:反転しない)
!*/
extern void Graphics_DrawRot(GRAPHICS_RES* graphics,int posX,int posY,double angle,int transFlag,int turnFlag = FALSE);

/*

	処理について	画像を分割して描画
	関数名			Graphics_DrawRot
	引数			GRAPHICS_RES*	graphics	:グラフィックリソース構造体
	引数			int				posX		:X座標
	引数			int				posY		:Y座標
	引数			int				scrX		:U座標
	引数			int				scrY		:V座標
	引数			int				transFlag	:画像の透明度を有効にするか？(TRUE:有効 FALSE:無効)
	引数			int				turnFlag	:画像を反転させるか?(TRUE:反転する FALSE:反転しない)

!*/
extern void Graphics_DrawDiv(GRAPHICS_RES* graphcis,int posX,int posY,int scrX,int scrY,int width,int height,int transFlag,int trunFlag);

/*
	
	処理について	画像を指定したサイズで分割し描画する
	関数名			Graphics_DrawRot
	引数			GRAPHICS_RES*	graphics	:グラフィックリソース構造体
	引数			int				posX		:X座標
	引数			int				posY		:Y座標
	引数			int				scrX		:U座標
	引数			int				scrY		:V座標
	引数			int				transFlag	:画像の透明度を有効にするか？(TRUE:有効 FALSE:無効)
	引数			int				turnFlag	:画像を反転させるか?(TRUE:反転する FALSE:反転しない)
!*/
extern void Graphics_DrawSplit(GRAPHICS_RES* graphics,int posX,int posY,int u,int v,int splitSizeX,int splitSizeY,int transFlag,int trunFlag);

//画像の基準スクリーン座標を設定する
extern void Graphics_SetBasePos(GRAPHICS_RES* graphics,int posX,int posY);

//画像の中心座標を設定する
extern void Graphics_SetOffsetPos(GRAPHICS_RES* graphics,int posX,int posY);

//座標を返却する
extern int Graphics_GetPosX(GRAPHICS_RES graphics);
extern int Graphics_GetPosY(GRAPHICS_RES graphics);

//画像サイズを返却する
extern int Graphics_GetWidth(GRAPHICS_RES graphics);
extern int Graphics_GetHeight(GRAPHICS_RES graphics);

