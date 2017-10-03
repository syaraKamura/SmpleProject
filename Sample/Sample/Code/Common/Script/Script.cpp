/*
				ファイル名		:Script.cpp
				作成者			:
				作成日時		:2017/08/16
				ソース説明		:
				
				ADVを再生するためのスクリプトプログラムを記述していく
				
				備考
				
				☆メモ
					
					◇スクリプト設計について
					
					◇スクリプトの記述規約について

					◇スクリプトの関数リスト
						

						変数定義ができるようにする
						変数の宣言時は必ず0またはfalseの状態で初期が行われるようにする
						変数の型 変数名 

						変数名 = 0 や 変数名 = 変数名 + 1、変数名 = true　というような
						また、変数名1 = 変数名1 + 変数名2 * 4 / 2 というような記述にも対応させる
						ただし、変数は整数のみが扱える程度のものを作成する

						〇変数の型
							FLAG	:TRUE , FALSE の2値のみが扱える　
							INTEGER	整数を扱うことができる

						〇変数の定義について
							FLAG isFlag
							INTEGER inInteger

						〇内部での動き
							プログラム内部ではListで宣言した変数を保持する
							宣言時に同じ名前の変数名が宣言された場合はエラーとみなす
							スクリプトの再生が終了したら保持した変数のデータはすべて開放する





						記述に対応することができるように作成する


						◇文字列描画
						MES	メッセージ						:メッセージの描画
						TOLK キャラクター名 話す言葉		:キャラクターが話していることを描画する
						
						◇システム系
						IF	条件式							:条件式
						ELSEIF								:
						ENDIF								:
						GOTO ラベル名						:指定のラベルを探索してラベルの位置に移動する
						LABEL ラベル名						:ラベル
						FLAGS ID							:指定の番号のフラグを取得する


						◇リソース読み込み
						LOADGRAPHICS ファイル名 ID			:画像の読み込み
						DRAWGRAPHICS ID X座標 Y座標			:画像の描画
						DELETEGRAPHICS ID					:画像を削除する
						LOADSOUND ファイル名 SoundType ID	:サウンドの読み込み
						PLAYSOUDN ID						:サウンドの再生
						STOPSOUND ID						:サウンドを止める
						DELETESOUND ID						:サウンドを削除する

						◇キャラクターの移動処理
						MOVEPOSX ID 移動量					:指定IDのキャラクターを移動量だけX方向へ移動させる
						MOVEPOSY ID	移動量					:指定IDのキャラクターを移動量だけY方向へ移動させる




					◇やることリスト
						
						


				
				
!*/

//	------- インクルード宣言
#include "Common/GameCommon/GameCommon.h"
#include "ScriptFlag.h"
#include "ScriptVariable.h"
#include "Script.h"


//	------- 固定定数宣言

const int SCRIPT_MAX_LINE = 1024;	//スクリプトの読み込み最大行
const int SCRIPT_MAX_LENGTH = 256;	//スクリプトの読み込み最大文字列

const int WAIT_TIME = 2;

//	-------	マクロ定義

//	------- 列挙体

enum eStep{
	eStep_Init,
	eStep_SetUp,
	eStep_Main,
	eStep_Exit,
	eStep_ExitDone,
};

//	------- 構造体&共用体



typedef struct{
	VARIABLE_DATA* pFunction;							//リスト化する
	char script[SCRIPT_MAX_LINE][SCRIPT_MAX_LENGTH];	//スクリプト
	int line;											//現在の行
	int maxLine;										//最大行数
	char fileName[SCRIPT_MAX_LENGTH];					//ファイル名
}SCRIPT_DATA;

typedef struct{
	SCRIPT_DATA* pScriptData;	//スクリプトデータ

	eStep step;					//実行ステップ
	int waitCnt;				//待ち時間
	
}SCRIPT_OBJ;

//	------- データテーブル

//	------- スタティック変数宣言

static SCRIPT_OBJ* s_pHdl;

//	------- グローバル変数宣言

//	------- スタティックプロトタイプ宣言(内部関数)

//	------- プロトタイプ宣言していないスタティック関数(内部関数)

/*
	次のステップを設定する
*/
void _SetNextStep(SCRIPT_OBJ* ix,eStep step){
	ix->waitCnt = 0;
	ix->step = step;
}

/*
	更新処理
	SCRIPT_OBJ*		ix
*/
void _Updata(SCRIPT_OBJ* ix){

	switch(ix->step){
	case eStep_Init:

		_SetNextStep(ix,eStep_SetUp);
		break;
	case eStep_SetUp:

		_SetNextStep(ix,eStep_Main);
		break;
	case eStep_Main:

		break;
	case eStep_Exit:

		if(ix->waitCnt == 0){

		}

		ix->waitCnt ++;

		if(ix-> waitCnt > WAIT_TIME){

			Task_KillRequest(ix);
			_SetNextStep(ix,eStep_Exit);
		}

		break;
	case eStep_ExitDone:
		s_pHdl = NULL;
		break;
	}

}

/*
	描画処理
	SCRIPT_OBJ*		ix
*/
void _Draw(SCRIPT_OBJ* ix){

	//メインステップでなければ処理を抜ける
	if(ix->step != eStep_Main) return ;


}

//	------- グローバル関数

/*
	スクリプト処理の生成
	s32		scriptIdx	:再生するスクリプト番号
*/
void Script_Creata(s32 scriptIdx){

	SCRIPT_OBJ* ix = Task_CreateBase(_Updata,_Draw,NULL,SCRIPT_OBJ,eTaskClassType_Class00);

	if(ix != NULL){
		
	
		s_pHdl = ix;
	}

}

/*
	終了したか？
	return	true	:実行終了した
			false	:実行中
*/
bool Script_IsEnd(){
	if(s_pHdl){
		return false;
	}else{
		return true;
	}
}
