/*
				ファイル名		:Figure.h
				作成者			:
				作成日時		:2017/08/29
				ソース説明		:
					
					図形
				
				備考
				
				
				
!*/

#ifndef __FIGURE_H__
#define __FIGURE_H__

//	------- インクルード宣言

//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

//	------- 構造体&共用体

typedef struct{
	
	int posX;					//図形の描画座標
	int posY;
	int width;					//サイズ
	int height;
	unsigned int FigureColor;	//図形の色
	char str[256];				//表示する文字列
	unsigned int strColor;		//文字列の色
	int alpha;					//透過度(0 ~ 255)

	bool isDispEdge;			//枠を描画するか
	unsigned int EdgeColor;		//枠の色
}FIGURE_DATA;


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
extern void Figure_SetData(FIGURE_DATA* pFig,int posX,int posY,int width,int height,unsigned int FigColor,int alpha,const char* str,unsigned int strColor,bool isDispEdge = false,unsigned int edgeColor = GetColor(255,255,255));


/*
	四角形
	int x1				:左上のX座標
	int y1				:左上のY座標
	int x2				:右下のX座標
	int y2				:右下のY座標
	unsigned int color	:色
	int fillFlag		:塗りつぶしするか	0:塗りつぶさない 1:塗りつぶす
*/
extern void Figure_Draw2DBox(int x1,int y1,int x2,int y2,unsigned int color,int fillFlag);

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
extern void Figure_Draw2DBoxString(int x1,int y1,int x2,int y2,unsigned int boxColor,int fillFlag,const char* str,unsigned int strColor);

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
extern void Figure_Draw2DBoxFormatString(int posX,int posY,unsigned int boxColor,unsigned int strColor,const char* str,...);


/*
	文字列付き四角形を設定したデータをもとに設定する
	FIGURE_DATA fig
*/
extern void Figure_Draw2DBoxString(FIGURE_DATA fig);

//	------- インライン関数(ヘッダー内関数)


#endif // __FIGURE_H__