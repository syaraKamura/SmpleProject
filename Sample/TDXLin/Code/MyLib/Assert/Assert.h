/*
				ファイル名		:Assert.h
				作成者			:
				作成日時		:2017/09/30
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __ASSERT_H__
#define __ASSERT_H__

//	------- インクルード宣言

//	------- 固定定数宣言

//	-------	マクロ定義

#define MESAGE(x)
#define ASSERT_MESSAGE(...) MESAGE(__VA_ARGS__) 

#define ERR_ASSERT(x,...)  do {}while(0)

//指定した条件がfalseならアサート
#define ASSERT(x)	do { \
	if(!(x)){				 \
		static char buf[256]="";\
		sprintf_s(buf,"Assertion failed: %s file: %s line: %d\n",#x,__FILE__,__LINE__);\
		OutputDebugString(buf);\
		Assert_SetInfomation(__FILE__,_func_,#x,__LINE__);\
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


//	------- 列挙体

//	------- 構造体&共用体

//	------- グローバル関数

void Assert_Initailize();

void Assert_Finalize();

void Assert_Updata();

void Assert_Draw();


// ---- ユーザー関数

/*
	アサート状態にする
*/
void Assert_AssertFlagOn();

/*
	アサート状態を解除する
*/
void Assert_AssertFlagOff();

/*
	アサートの状態を設定する
	const char* fileName		:ファイルネーム
	const char* funcName		:関数名
	const char* variableName	:変数名
	int			line			:行数
*/
void Assert_SetInfomation(const char* fileName,const char* funcName,const char* variableName,int line);
/*
	アサートの状態を返却する
	return	true	:アサート状態
			false	:アサート状態ではない
*/
bool Assert_GetAssertFlag();


//	------- インライン関数(ヘッダー内関数)


#endif // __ASSERT_H__