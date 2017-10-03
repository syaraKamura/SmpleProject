/*

	文字列入力関係

*/

#pragma once

#ifdef __WINDOWS__

const int INPUT_STRING_LENGTH = 200;	//日本語で100文字分


enum eKeyInputStringType{
	eKeyInputStringType_All,				//すべての文字型の入力を許可する
	eKeyInputStringType_SingCharOnly,		//半角文字型のみ入力を許可する
	eKeyInputStringType_NumCharOnly,		//数字入力のみ許可する
};

typedef struct{

	int step;
	int cnt;

	int handle;									//文字列入力用ハンドル
	eKeyInputStringType	keyInputStringType;		//文字列入力タイプ
	char inputString[INPUT_STRING_LENGTH + 1];	//入力された文字列
	int inputNumber;							//入力された数列を受け取る
	bool isKeyInputActive;						//文字入力がアクティブになっているか？
	bool isEndKeyInput;							//文字入力が終了したか？

	int posX;	//描画座標
	int posY;

}KEY_INPUT_STRING_OBJ;


/*
	文字列入力の生成
	int					drawPosX			:描画座標X
	int					drawPosY			:描画座標Y
	eKeyInputStringType keyInputStringType	:文字入力タイプ
*/
extern KEY_INPUT_STRING_OBJ* KeyInputString_Create(int drawPosX,int drawPosY,eKeyInputStringType keyInputStringType);

/*
	破棄
*/
extern void KeyInputString_Destroy(KEY_INPUT_STRING_OBJ* ix);

//------------ ユーザー使用関数

/*
	文字入力をアクティブする
	KEY_INPUT_STRING_OBJ* ix
*/
extern void KeyInputString_KeyInputActive(KEY_INPUT_STRING_OBJ* ix);
//------------- ゲッター関数

/*
	文字入力がアクティブになっているか判断する
	KEY_INPUT_STRING_OBJ* ix
	return	true	:文字入力がアクティブになっている
			false	:文字入力がアクティブになっていない
*/
extern bool KeyInputString_GetKeyInputActiveFlag(KEY_INPUT_STRING_OBJ* ix);

/*
	文字入力が終了したか返却する
	KEY_INPUT_STRING_OBJ* ix
	return	true	:文字入力が終了している
			false	:文字入力が終了していない
*/
extern bool KeyInputString_IsEndKeyInput(KEY_INPUT_STRING_OBJ* ix);

/*
	入力した文字列を返却する
	KEY_INPUT_STRING_OBJ* ix
	return 入力した文字列
*/
extern const char* KeyInputString_GetKeyInputString(KEY_INPUT_STRING_OBJ* ix);

/*
	入力した数列を返却する
	KEY_INPUT_STRING_OBJ* ix
	return 入力した数列を返却する
*/
extern int KeyInputString_GetKeyInputNumber(KEY_INPUT_STRING_OBJ* ix);

#endif //__WINDOWS__
