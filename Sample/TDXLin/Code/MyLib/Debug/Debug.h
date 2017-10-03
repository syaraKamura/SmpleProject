
//デバッグ機能が楽になる関数を記述していく

#pragma once

#include <stdio.h>
#include <assert.h>

enum eDebugType{
	eDebugType_Flag,		//フラグがONの時に実行される
	eDebugType_Func,		//設定した関数を実行する
};


typedef struct{
	char debugName[256];	//デバッグ名
	eDebugType debugType;	//デバッグの種類
	bool (*FuncUpdata)();	//戻り値がtrueの間実行する
	bool (*FuncDraw)();		//戻り値がtrueの間実行する
	void (*FuncFlagOn)();	//フラグがオンの時に一度実行される
	void (*FuncFlagOff)();	//フラグがオフの時に一度実行される
	bool isFlag;			//実行するか？

}DEBUG_FUNC_DATA;

typedef struct{
	char objectName[256];
	DEBUG_FUNC_DATA* pdebuFunc;
	int debugFuncNum;			//デバッグリストの数
}DEBUG_DATA;

void Debug_Print(const char* str,...);
void Debug_DrawString();

//書式付き
extern void Debug_Println(const char* str,...);
extern void Debug_Printf(int posX,int posY,unsigned int color,const char* str,...);
extern void Debug_LogPrintf(const char* str,...);

#ifdef __MY_DEBUG__



//指定した条件がfalseならアサート
#define ASSERT(x)	do { \
	if(!(x)){				 \
		static char buf[256]="";\
		sprintf_s(buf,"Assertion failed: %s file: %s line: %d\n",#x,__FILE__,__LINE__);\
		OutputDebugString(buf);\
		exit(1);	/*強制終了*/\
	}					 \
}while(0)
#define ASSERT_MES(x,...) do{\
	if(!(x)){\
	static char buf[256]="";\
	sprintf_s(buf,"%s\n",__VA_ARGS__);\
	OutputDebugString(buf);\
	ASSERT(x);\
	}\
}while(0)


/*
	デバッグ項目の登録
	DEBUG_FUNC_DATA*	debugData	:デバッグデータ
	const char*			objectName	:デバッグ項目名
	size_t				size		:データサイズ
*/
extern void Debug_Entory(DEBUG_FUNC_DATA* debugData,const char* objectName,size_t size);

/*
	デバッグフラグの状態を取得する
	const char* objectName	:デバッグ項目名
	const char* debugName	:デバッグ名
	return	true	:フラグがオン
			false	:フラグがオフ
*/
extern bool Debug_IsFlag(const char* objectName,const char* debugName);

/*
	初期化
*/
extern void Debug_Initialize();
/*
	終了処理
*/
extern void Debug_Finalize();

/*
	更新
*/
extern void Debug_Updata();
/*
	描画
*/
extern void Debug_Draw();

#endif // __MY_DEBUG__