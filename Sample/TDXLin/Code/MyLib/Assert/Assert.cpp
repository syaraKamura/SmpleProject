/*
				ファイル名		:Assert.cpp
				作成者			:
				作成日時		:
				ソース説明		:2017/09/30
				
				
				備考
				
				
				
!*/

//	------- インクルード宣言
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "DxLib.h"

#include "../Keyboard/Keyboard.h"
#include "../FontMgr/FontMgr.h"
#include "Assert.h"


//	------- 固定定数宣言
const int FONT_SIZE = 8;
//	-------	マクロ定義

//	------- 列挙体

//	------- 構造体&共用体
typedef struct{
	char fileName[1024];	//ファイル名
	char funcName[256];		//関数名
	char variableName[256];	//変数名
	int lineNum;			//行数
	bool isAssert;			//アサートフラグ
}ASSERT_INFO;

//	------- データテーブル

//	------- スタティック変数宣言
static FontMgr* pFont;
static ASSERT_INFO s_Assert;
//	------- グローバル変数宣言

//	------- スタティックプロトタイプ宣言(内部関数)

//	------- プロトタイプ宣言していないスタティック関数(内部関数)

static int _PosY(int n){
	return n * FONT_SIZE;
}

//	------- グローバル関数

void Assert_Initailize(){

	memset(&s_Assert,0,sizeof(ASSERT_INFO));
	pFont = new FontMgr();

	pFont->CreateFontHandle("ＭＳ ゴシック",FONT_SIZE,1,-1,GetColor(255,0,0));


}

void Assert_Finalize(){
	memset(&s_Assert,0,sizeof(ASSERT_INFO));

	delete pFont;

}



void Assert_Updata(){

	if(Keyboard_Press(KEY_INPUT_B)){
		Assert_AssertFlagOff();
	}

}


void Assert_Draw(){
	
	pFont->Draw(0,_PosY(1),GetColor(255,0,0),255,"                    <<Fatal Error!!>>");
	pFont->Draw(0,_PosY(2),GetColor(255,0,0),255,"****************************************************");
	pFont->Draw(0,_PosY(3),GetColor(255,0,0),255,"                  致命的エラーが発生しました");	
	pFont->Draw(0,_PosY(4),GetColor(255,0,0),255,"****************************************************");
	pFont->Draw(0,_PosY(5),GetColor(255,0,0),255,"VariableName : %s",s_Assert.variableName);
	pFont->Draw(0,_PosY(6),GetColor(255,0,0),255,"Filename     : %s",s_Assert.fileName);
	pFont->Draw(0,_PosY(7),GetColor(255,0,0),255,"FuncName     : %s",s_Assert.funcName);
	pFont->Draw(0,_PosY(8),GetColor(255,0,0),255,"Line         : %d",s_Assert.lineNum);
	
	pFont->Draw(0,_PosY(12),GetColor(255,0,0),255,"Press B Key Continue.");
	pFont->Draw(0,_PosY(13),GetColor(255,0,0),255,"Bキーで続行します.");
	
}





// ---- ユーザー関数

/*
	アサート状態にする
*/
void Assert_AssertFlagOn(){
	s_Assert.isAssert = true;
}

/*
	アサート状態を解除する
*/
void Assert_AssertFlagOff(){
	s_Assert.isAssert = false;
}

/*
	アサートの状態を設定する
	const char* fileName		:ファイルネーム
	const char* funcName		:関数名
	const char* variableName	:変数名
	int			line			:行数
*/
void Assert_SetInfomation(const char* fileName,const char* funcName,const char* variableName,int line){

	strcpy_s(s_Assert.fileName,fileName);
	strcpy_s(s_Assert.funcName,funcName);
	strcpy_s(s_Assert.variableName,variableName);
	s_Assert.lineNum = line;
	Assert_AssertFlagOn();
}

/*
	アサートの状態を返却する
	return	true	:アサート状態
			false	:アサート状態ではない
*/
bool Assert_GetAssertFlag(){
	bool flag = s_Assert.isAssert;
	return flag;
}
