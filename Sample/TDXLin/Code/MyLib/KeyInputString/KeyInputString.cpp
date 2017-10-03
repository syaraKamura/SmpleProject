/*

	文字列入力関係


!*/


#include "DxLib.h"
#include "KeyInputString.h"
#include "MyLib/Task/Task.h"

#ifdef __WINDOWS__

const int WAIT_TIME = 2;


enum eStep{
	eStep_Init,
	eStep_Main,
	eStep_Exit,
	eStep_ExitDone,
};


/*
	次のステップを設定する
	KEY_INPUT_STRING_OBJ*	ix
	eStep					step	:次のステップ
*/
static void _SetNextStep(KEY_INPUT_STRING_OBJ* ix,eStep step){
	ix->step = step;
	ix->cnt = 0;
}

/*
	描画
	KEY_INPUT_STRING_OBJ* ix
*/
static void _Draw(KEY_INPUT_STRING_OBJ* ix){

	if(ix->step != eStep_Main) return ;

	//文字入力が終了していないなら
	if(CheckKeyInput(ix->handle) == 0){
		//入力中の文字を描画する
		DrawKeyInputString( ix->posX , ix->posY , ix->handle );
	}
}

static void _KeyInputProc(KEY_INPUT_STRING_OBJ* ix){

	//文字入力が終了していないなら処理を抜ける
	if(CheckKeyInput(ix->handle) == 0) return ;
	
	//入力した文字を受け取る
	if(ix->keyInputStringType == eKeyInputStringType_NumCharOnly){
		//入力された数列を受け取る
		ix->inputNumber = GetKeyInputNumber(ix->handle);
	}else{
		//入力した文字列を受け取る
		GetKeyInputString(ix->inputString,ix->handle);
	}
	
	//文字入力を非アクティブにする
	ix->isKeyInputActive = false;

	//文字入力が終了した
	ix->isEndKeyInput = true;

}


/*
	更新
	KEY_INPUT_STRING_OBJ* ix
*/
static void _Updata(KEY_INPUT_STRING_OBJ* ix){

	switch(ix->step){
	case eStep_Init:

		_SetNextStep(ix,eStep_Main);
		break;
	case eStep_Main:

		_KeyInputProc(ix);

		break;
	case eStep_Exit:

		if(ix->cnt == 0){
			//文字列入力ハンドルを開放する
			DeleteKeyInput(ix->handle);
			ix->handle = 0;
		}

		ix->cnt ++ ;

		if(ix->cnt > WAIT_TIME){
			Task_KillRequest(ix);
			ix->step = eStep_ExitDone;
		}

		break;
	case eStep_ExitDone:
		break;
	}

}


/*
	文字列入力の生成
	int					drawPosX			:描画座標X
	int					drawPosY			:描画座標Y
	eKeyInputStringType keyInputStringType	:文字入力タイプ
*/
KEY_INPUT_STRING_OBJ* KeyInputString_Create(int drawPosX,int drawPosY,eKeyInputStringType keyInputStringType){

	KEY_INPUT_STRING_OBJ* ix = Task_CreateBase(_Updata,_Draw,NULL,KEY_INPUT_STRING_OBJ,eTaskClassType_Class00);

	//タスク確保ができているなら
	if(ix != NULL){

		//文字列を0で初期化する
		memset(ix->inputString,0,INPUT_STRING_LENGTH+1);
		
		//入力した数列を初期化する
		ix->inputNumber = 0;

		//文字列入力タイプを設定する
		ix->keyInputStringType = keyInputStringType;

		if(keyInputStringType == eKeyInputStringType_All){
			//すべての文字型の入力を受け付ける
			ix->handle =  MakeKeyInput(INPUT_STRING_LENGTH,TRUE,FALSE,FALSE);
		}else if(keyInputStringType == eKeyInputStringType_SingCharOnly){
			//半角文字のみの入力を受けつける
			ix->handle =  MakeKeyInput(INPUT_STRING_LENGTH,TRUE,TRUE,FALSE);
		}else{
			//数字字のみの入力を受けつける
			ix->handle =  MakeKeyInput(INPUT_STRING_LENGTH,TRUE,FALSE,TRUE);
		}

		//描画座標を設定
		ix->posX = drawPosX;
		ix->posY = drawPosY;

		//最初のステップを設定する
		ix->step = eStep_Init;

		//カウンターの初期化
		ix->cnt = 0;

		//文字入力がアクティブでない状態にする
		ix->isKeyInputActive = false;

		//文字入力が終了していない状態にする
		ix->isEndKeyInput = false;

		return ix;
	}
	return NULL;
}

/*
	破棄
*/
void KeyInputString_Destroy(KEY_INPUT_STRING_OBJ* ix){
	_SetNextStep(ix,eStep_Exit);
}


//------------ ユーザー使用関数

/*
	文字入力をアクティブする
	KEY_INPUT_STRING_OBJ* ix
*/
void KeyInputString_KeyInputActive(KEY_INPUT_STRING_OBJ* ix){
	//キー入力をアクティブにする
	SetActiveKeyInput(ix->handle);

	ix->isKeyInputActive = true;

	//文字入力が終了していない状態にする
	ix->isEndKeyInput = false;

	//文字列を0で初期化する
	memset(ix->inputString,0,INPUT_STRING_LENGTH+1);

	//入力した数列を初期化する
	ix->inputNumber = 0;

}

//------------- ゲッター関数

/*
	文字入力がアクティブになっているか判断する
	KEY_INPUT_STRING_OBJ* ix
	return	true	:文字入力がアクティブになっている
			false	:文字入力がアクティブになっていない
*/
bool KeyInputString_GetKeyInputActiveFlag(KEY_INPUT_STRING_OBJ* ix){
	return ix->isKeyInputActive;
}

/*
	文字入力が終了したか返却する
	KEY_INPUT_STRING_OBJ* ix
	return	true	:文字入力が終了している
			false	:文字入力が終了していない
*/
bool KeyInputString_IsEndKeyInput(KEY_INPUT_STRING_OBJ* ix){
	return ix->isEndKeyInput;
}

/*
	入力した文字列を返却する
	KEY_INPUT_STRING_OBJ* ix
	return 入力した文字列
*/
const char* KeyInputString_GetKeyInputString(KEY_INPUT_STRING_OBJ* ix){
	return ix->inputString;
}

/*
	入力した数列を返却する
	KEY_INPUT_STRING_OBJ* ix
	return 入力した数列を返却する
*/
int KeyInputString_GetKeyInputNumber(KEY_INPUT_STRING_OBJ* ix){
	return ix->inputNumber;
}

#endif //__WINDOWS__
