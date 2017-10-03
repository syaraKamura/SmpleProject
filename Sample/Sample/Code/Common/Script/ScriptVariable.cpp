/*
				ファイル名		:ScriptVariable.cpp
				作成者			:
				作成日時		:2017/08/20
				ソース説明		:スクリプトで扱う変数の管理を行う
				
				
				備考
				
				
				
!*/

//	------- インクルード宣言
#include "Common/GameCommon/GameCommon.h"
#include "ScriptVariable.h"

//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

//	------- 構造体&共用体

typedef struct _tag_VARIABLE_LIST{
	VARIABLE_DATA* variable;
	_tag_VARIABLE_LIST* pNext;
}VARIABLE_LIST;

//リストの先頭と末尾を記憶しておく構造体
typedef struct{
	VARIABLE_LIST* pTop;		//先頭のポインター
	VARIABLE_LIST* pBottom;		//末尾のポインター
}BUFFER_MEMORISE;

//	------- データテーブル

//	------- スタティック変数宣言
static VARIABLE_LIST s_Var;			//変数リスト
static BUFFER_MEMORISE s_Memorise;	//記憶用
//	------- グローバル変数宣言

//	------- スタティックプロトタイプ宣言(内部関数)

//	------- プロトタイプ宣言していないスタティック関数(内部関数)

/*
	すでに同じ名前の変数が存在しているか判断する
	VARIABLE_DATA*	pVarData
	return	true	:存在している
			false	:存在していない
*/
static bool _IsExitVarialbleName(VARIABLE_DATA* pVarData){
	//すでに存在しているか？
	//true:存在している	false:存在していない
	bool isExist = false;

	//初めての変数登録でなければ判断をする
	if(s_Memorise.pTop != NULL){
		
		for(VARIABLE_LIST* pData = s_Memorise.pTop;pData != s_Memorise.pBottom;pData = s_Memorise.pTop->pNext){
			if(strcmp(pData->variable->variableName,pVarData->variableName) == 0){
					isExist = true;
					break;
			}
		}

	}
	return isExist;
}

//	------- グローバル関数

/*
	初期化処理(必ずスクリプト使用時に呼ばなければならない)
*/
void ScriptVariable_Initalize(){
	
	s_Var.variable = NULL;
	s_Var.pNext = NULL;

	//データの先頭と末尾を設定
	s_Memorise.pTop = s_Memorise.pBottom = s_Var.pNext;
	
}

/*
	終了処理(必ずスクリプトを終了する際に呼ばなければならない)
*/
void ScriptVariable_Finalize(){
	
	VARIABLE_LIST* pNowData = s_Memorise.pTop;
	VARIABLE_LIST* pDelData = NULL;

	//すべてのデータを削除する
	while(pNowData != NULL){
		pDelData = pNowData;
		Memory_SafeFree(pDelData);
		pNowData = pNowData->pNext;
	}


}

/*
	変数の追加
	VARIABLE_DATA*	pVarData	:登録するデータ
	return	true	:登録成功
			false	:登録失敗
*/
bool ScriptVariable_Add(VARIABLE_DATA* pVarData){
	
	//同じ名前の変数が存在していたら登録をしない
	if(_IsExitVarialbleName(pVarData) == true) return false;
	
	
	//メモリの確保
	VARIABLE_LIST* pNewData = (VARIABLE_LIST*)Memory_Alloc(sizeof(VARIABLE_LIST));
	
	//メモリの確保に失敗した
	if(pNewData == NULL){
		return false;
	}
	
	pNewData->pNext = NULL;
	
	//新しいデータを設定
	s_Memorise.pBottom->variable = pVarData;
	s_Memorise.pBottom = pNewData;
	s_Memorise.pBottom->pNext = NULL;
	
	return true;

}

/*
	指定の名前の変数の値を返却する
	const char*		variableName	:変数の名前
	return	NULL以外:指定の変数名のデータを返却する
			NULL	:指定の変数名を見つけられなかった
*/
VARIABLE_DATA* ScriptVariable_GetVariable(const char* variableName){

	//見つけたデータを格納する
	VARIABLE_DATA* pVarData = NULL;

	//初めての変数登録でなければ判断をする
	if(s_Memorise.pTop != NULL){
		
		for(VARIABLE_LIST* pData = s_Memorise.pTop;pData != s_Memorise.pBottom;pData = s_Memorise.pTop->pNext){
			if(strcmp(pData->variable->variableName,variableName) == 0){
				pVarData = pData->variable;
				break;
			}
		}
	}
	return pVarData;
}

/*
	指定の名前の変数の値を更新する
	VARIABLE_DATA*	pVarData	:設定する変数データ
*/
void ScriptVariabl_SetUpVariable(VARIABLE_DATA* pVarData){

	//初めての変数登録でなければ判断をする
	if(s_Memorise.pTop != NULL){
		
		//変数が見つかったか？
		bool isFindVariable = false;
		VARIABLE_LIST* pTmp = NULL;


		for(VARIABLE_LIST* pData = s_Memorise.pTop;pData != s_Memorise.pBottom;pData = s_Memorise.pTop->pNext){
			if(strcmp(pData->variable->variableName,pVarData->variableName) == 0 &&
				pData->variable->variableKind == pVarData->variableKind){
				pData->variable = pVarData;
				pTmp = pData;
				pTmp->pNext = NULL;
				isFindVariable = true;
				break;
			}
		}

		//見つけられた
		if(isFindVariable == true){

			//変更された、データを最後尾へ移動する。



		}

	}

}