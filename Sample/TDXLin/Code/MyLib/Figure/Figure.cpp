/*
				ファイル名		:Figure.cpp
				作成者			:
				作成日時		:2017/08/29
				ソース説明		:
				
					図形
				
				備考
				
				
				
!*/

//	------- インクルード宣言
#include "DxLib.h"

#include "Figure.h"

//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

//	------- 構造体&共用体


//	------- データテーブル

//	------- スタティック変数宣言

//	------- グローバル変数宣言

//	------- スタティックプロトタイプ宣言(内部関数)

//	------- プロトタイプ宣言していないスタティック関数(内部関数)

//	------- グローバル関数

/*
	図形のデータを設定する
	FIGURE_DATA*	pFig								:設定するデータ
	int				posX								:X座標
	int				posY								:Y座標
	int				width								:横幅
	int				height								:縦幅
	unsigned int	FigColor							:図形の色
	int				alpha								:透過度 (0 ~ 255)
	const char*		str									:文字列
	unsigned int	strColor							:文字列の色
	bool			isDispEdge = false					:図形に枠を描画するか?(デフォルトは描画しない)
	unsigned int	edgeColor = GetColor(255,255,255)	:枠の色 (デフォルトは白)
*/
void Figure_SetData(FIGURE_DATA* pFig,int posX,int posY,int width,int height,unsigned int FigColor,int alpha,const char* str,unsigned int strColor,bool isDispEdge/* = false*/,unsigned int edgeColor/* = GetColor(255,255,255)*/){

	pFig->posX = posX;
	pFig->posY = posY;
	pFig->width = width;
	pFig->height = height;
	pFig->FigureColor = FigColor;
	pFig->alpha = alpha;
	strcpyDx(pFig->str, str);
	pFig->strColor = strColor;
	pFig->isDispEdge = isDispEdge;
	pFig->EdgeColor = edgeColor;

}

/*
	文字列を設定する
	FIGURE_DATA* pFig
	const char* str
*/
void Figure_SetDataString(FIGURE_DATA* pFig,const char* str){
	strcpyDx(pFig->str, str);
}

/*
	書式付き文字列を設定する
	FIGURE_DATA* pFig
	const char* str
	...
*/
void Figure_SetDataFormatString(FIGURE_DATA* pFig,const char* str,...){

	char buffer[1024];
	va_list ap;

	va_start(ap,str);
	vsprintf_s(buffer,str,ap);
	va_end(ap);

	Figure_SetDataString(pFig,buffer);
}

/*
	座標の設定をする
	FIGURE_DATA* pFig
	int posX
	int posY
*/
void Figure_SetDataPosition(FIGURE_DATA* pFig,int posX,int posY){
	pFig->posX = posX;
	pFig->posY = posY;
}

/*
	枠の描画状態を設定する
	true:描画 false:描画しない

	FIGURE_DATA* pFig
	bool		isDisp	:描画状態を設定する

*/
void Figur_SetDataEdgeDrawFlag(FIGURE_DATA* pFig,bool isDisp){
	pFig->isDispEdge = isDisp;
}




/*
	四角形
	int x1				:左上のX座標
	int y1				:左上のY座標
	int x2				:右下のX座標
	int y2				:右下のY座標
	unsigned int color	:色
	int fillFlag		:塗りつぶしするか	0:塗りつぶさない 1:塗りつぶす
*/
void Figure_Draw2DBox(int x1,int y1,int x2,int y2,unsigned int color,int fillFlag){
	DrawBox(x1,y1,x2,y2,color,fillFlag);
}

/*
	　文字列を設定できる四角形
	 int x1					:左上のX座標
	 int y1					:左上のY座標
	 int x2					:右下のX座標
	 int y2					:右下のY座標
	 unsigned int boxColor	:色
	 int fillFlag			:塗りつぶしするか	0:塗りつぶさない 1:塗りつぶす
	 const char* str		:文字列
	 unsigned int strColor	:文字の色
*/
void Figure_Draw2DBoxString(int x1,int y1,int x2,int y2,unsigned int boxColor,int fillFlag,const char* str,unsigned int strColor){

	int strlen = strlenDx(str);		//文字列の長さを受け取る
	int fontSize = GetFontSize();	//現在のフォントサイズを受け取る
	int strWide = strlen * fontSize;//文字列の幅
	
	int centerX = (x1 + x2 - strWide/2) / 2;
	int centerY = (y1 + y2 - fontSize/2) / 2;

	DrawBox(x1,y1,x2,y2,boxColor,fillFlag);
	DrawString(centerX,centerY,str,strColor);
}

/*
	書式付き文字列を設定できる四角形

		ボックスの大きさは文字列の長さとフォントサイズで設定される

	int posX				:描画X座標
	int posY				:描画Y座標
	unsigned int boxColor	:ボックスの色
	unsigned int strColor	:文字列の色
	const char* str			:文字列
	...						:
*/
void Figure_Draw2DBoxFormatString(int posX,int posY,unsigned int boxColor,unsigned int strColor,const char* str,...){

	char buffer[1024];
	va_list ap;

	va_start(ap,str);
	vsprintf_s(buffer,str,ap);
	va_end(ap);



	int strlen = strlenDx(buffer);		//文字列の長さを受け取る
	int fontSize = GetFontSize();	//現在のフォントサイズを受け取る
	int strWide = strlen * ((fontSize / 2) + 1);//文字列の幅
	

	//ボックスのサイズ
	int width = posX + strWide + 10;
	int heigth = posY + fontSize + 40;

	int centerX = (width - strWide - 10 / 2);
	int centerY = (heigth - fontSize - 40 / 2);

	DrawBox(posX,posY,width,heigth,boxColor,TRUE);
	DrawString(centerX,centerY,buffer,strColor);

	


}

/*
	文字列付き四角形を設定したデータをもとに設定する
	FIGURE_DATA fig
*/
void Figure_Draw2DBoxString(FIGURE_DATA fig){
	
	int width = fig.posX + fig.width;
	int height = fig.posY + fig.height;
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,fig.alpha);
	Figure_Draw2DBoxString(fig.posX,fig.posY,width,height,fig.FigureColor,TRUE,fig.str,fig.strColor);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	
	if(fig.isDispEdge == true){
		DrawBox(fig.posX,fig.posY,width,height,fig.EdgeColor,FALSE);
	}

}
