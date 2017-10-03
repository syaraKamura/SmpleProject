#include "DxLib.h"
#include "Graphics.h"
#include "MyLib/Debug/Debug.h"

static void _ZeroClear(GRAPHICS_RES* graphics){
	
	graphics->graphicHandle = 0;
	graphics->width = 0;
	graphics->height = 0;
	graphics->offsetPosX = 0;
	graphics->offsetPosY = 0;
	graphics->basePosX = 0;
	graphics->basePosY = 0;
	graphics->drawPosX = 0;
	graphics->drawPosY = 0;

}


//画像読み込み
//true:画像読み込み成功 false:画像読み込み失敗
bool Graphics_LoadBase(GRAPHICS_RES* graphics,const char* fileName,int offsetPosX/* = 0*/,int offsetPosY/* = 0*/,int basePosX/* = 0*/,int basePosY/* = 0*/){

	graphics->graphicHandle = LoadGraph(fileName);

	if(graphics->graphicHandle == -1){
		Debug_Print("画像読み込みに失敗しました。(%s)\n",fileName);
		return false;
	}

	//画像サイズ取得
	GetGraphSize(graphics->graphicHandle,&graphics->width,&graphics->height);

	graphics->offsetPosX = offsetPosX;
	graphics->offsetPosY = offsetPosY;

	graphics->basePosX = basePosX;
	graphics->basePosY = basePosY;

	graphics->drawPosX = 0;
	graphics->drawPosY = 0;

	//graphics->pad = 0;
	
	return true;
}

bool Graphics_Load(GRAPHICS_RES* graphics,const char* fileName){
	return Graphics_LoadBase(graphics,fileName);
}

//画像の非同期読み込み基底
void Graphics_ASyncLoadBase(GRAPHICS_RES* graphics,const char*fileName,int offsetPosX/* = 0*/,int offsetPosY/* = 0*/,int basePosX/* = 0*/,int basePosY/* = 0*/){
	SetUseASyncLoadFlag(TRUE);
	Graphics_LoadBase(graphics,fileName,offsetPosX,offsetPosY,basePosX,basePosY);
	SetUseASyncLoadFlag(FALSE);
}

//画像の非同期読み込み
void Graphics_ASyncLoad(GRAPHICS_RES* graphics,const char* fileName){
	Graphics_ASyncLoadBase(graphics,fileName);
}


//画像の非同期読み込みが終了しているか？
bool Graphics_IsASyncLoadEnd(GRAPHICS_RES* graphics){

	//非同期読み込みが終了しているか？
	if(CheckHandleASyncLoad(graphics->graphicHandle) == FALSE){
		//画像サイズ取得(非同期読み込み中では画像サイズの取得ができないため)
		GetGraphSize(graphics->graphicHandle,&graphics->width,&graphics->height);
		return true;
	}
	return false;
}

void Graphics_Delete(GRAPHICS_RES* graphics){
	
	if(graphics->graphicHandle == 0){
		return ;
	}

	DeleteGraph(graphics->graphicHandle);
	
	_ZeroClear(graphics);
}
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
void Graphics_DrawBase(GRAPHICS_RES* graphics,int posX,int posY,int scrX,int scrY,int width,int heihgt,int centerX,int centerY,double ExtRate,double angle,int transFlag,int turnFlag){
	if(graphics == NULL || graphics->graphicHandle == 0){
		return ;
	}

	graphics->drawPosX = graphics->basePosX - graphics->offsetPosX + posX + centerX;
	graphics->drawPosY = graphics->basePosY - graphics->offsetPosY + posY + centerY;


	DrawRectRotaGraph2(graphics->drawPosX,graphics->drawPosY,scrX,scrY,width,heihgt,centerX,centerY,ExtRate,angle,graphics->graphicHandle ,transFlag, turnFlag);
}

/*
	処理について	画像描画
	関数名			Graphics_DrawBase
	引数			GRAPHICS_RES*	graphics	:グラフィックリソース構造体
	引数			int				posX		:X座標
	引数			int				posY		:Y座標
	引数			int				transFlag	:画像の透明度を有効にするか？(TRUE:有効 FALSE:無効)
	引数			int				turnFlag	:画像を反転させるか?(TRUE:反転する FALSE:反転しない)
!*/
void Graphics_Draw(GRAPHICS_RES* graphics,int posX,int posY,int transFlag,int turnFlag/* = FALSE*/){
	Graphics_DrawBase(graphics,posX,posY,0,0,graphics->width,graphics->height,0,0,1.0,0.0,transFlag,turnFlag);
}

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
void Graphics_DrawRot(GRAPHICS_RES* graphics,int posX,int posY,double angle,int transFlag,int turnFlag){

	int width = graphics->width;
	int height = graphics->height;
	int centerX = width / 2;
	int centerY = height / 2;
	Graphics_DrawBase(graphics,posX,posY,0,0,width,height,centerX,centerY,1.0,angle,transFlag,turnFlag);
}

/*

	処理について	画像を分割して描画
	関数名			Graphics_DrawRot
	引数			GRAPHICS_RES*	graphics	:グラフィックリソース構造体
	引数			int				posX		:X座標
	引数			int				posY		:Y座標
	引数			int				scrX		:U1座標(左上)
	引数			int				scrY		:V1座標
	引数			int				width		:U2座標(右下)
	引数			int				height		:V2座標
	引数			int				transFlag	:画像の透明度を有効にするか？(TRUE:有効 FALSE:無効)
	引数			int				turnFlag	:画像を反転させるか?(TRUE:反転する FALSE:反転しない)

!*/
void Graphics_DrawDiv(GRAPHICS_RES* graphcis,int posX,int posY,int scrX,int scrY,int width,int height,int transFlag,int trunFlag){

	Graphics_DrawBase(graphcis,posX,posY,scrX,scrY,width,height,0,0,1.0,0.0,transFlag,trunFlag);

}

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
void Graphics_DrawSplit(GRAPHICS_RES* graphics,int posX,int posY,int u,int v,int splitSizeX,int splitSizeY,int transFlag,int trunFlag){

	if(splitSizeX <= 0 || splitSizeX > graphics->width) return ;
	if(splitSizeY <= 0 || splitSizeY > graphics->height) return ;

	int splitXNum = graphics->width / splitSizeX;
	int splitYNum = graphics->height / splitSizeY;

	if(u < 0 || u > splitXNum) return ;
	if(v < 0 || v > splitYNum) return ;

	int u1 = u * splitSizeX;
	int v1 = v * splitSizeY;
	int u2 = u1 + splitSizeX;
	int v2 = v1 + splitSizeY;


	Graphics_DrawDiv(graphics,posX,posY,u1,v1,u2,v2,transFlag,trunFlag);

}


//画像の基準スクリーン座標を設定する
void Graphics_SetBasePos(GRAPHICS_RES* graphics,int posX,int posY){
	if(graphics == NULL) return ;
	graphics->basePosX = posX;
	graphics->basePosY = posY;
}

//画像の中心座標を設定する
void Graphics_SetOffsetPos(GRAPHICS_RES* graphics,int posX,int posY){
	if(graphics == NULL) return ;
	graphics->offsetPosX = posX;
	graphics->offsetPosY = posY;
}

//座標を返却する
int Graphics_GetPosX(GRAPHICS_RES graphics){
	if(graphics.graphicHandle == 0){
		return 0;
	}
	return graphics.drawPosX;
}

int Graphics_GetPosY(GRAPHICS_RES graphics){
	if(graphics.graphicHandle == 0){
		return graphics.drawPosY;
	}
	return graphics.drawPosY;
}

//画像サイズを返却する
int Graphics_GetWidth(GRAPHICS_RES graphics){
	if(graphics.graphicHandle == 0){
		return 0;
	}
	return graphics.width;
}

int Graphics_GetHeight(GRAPHICS_RES graphics){
	if(graphics.graphicHandle == 0){
		return 0;
	}
	return graphics.height;

}

