/*
				ファイル名		:ScriptVariable.h
				作成者			:
				作成日時		:2017/08/20
				ソース説明		:スクリプトで扱う変数の管理を行う
				
				
				備考
				
				
				
!*/

#ifndef __SCRIPT_VARIABLE_H__
#define __SCRIPT_VARIABLE_H__

//	------- インクルード宣言

//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

enum eVariable{
	eVariable_Integer,	//int型
	eVariable_Boolean,	//bool型
	eVariable_None,		//かたなし
};


//	------- 構造体&共用体

typedef struct{
	char variableName[64];
	int val;
	eVariable variableKind;		//変数の種類
}VARIABLE_DATA;

//	------- グローバル関数

//	------- インライン関数(ヘッダー内関数)

#endif	//__SCRIPT_VARIABLE_H__