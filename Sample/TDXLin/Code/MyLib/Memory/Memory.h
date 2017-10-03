#pragma once

#ifdef __MY_DEBUG__
	#define Memory_SafeFree(x) _Memory_SafeFree(x,__FILE__,__LINE__);			//メモリの開放
	#define Memory_Alloc(x) _Memory_Alloc(x,__FILE__,__LINE__);				//メモリの取得
	#define Memory_AllocZeroClear(x) _Memory_AllocZero(x,__FILE__,__LINE__);	//メモリを取得し初期化を行う

	

#else
	#define Memory_SafeFree(x) _Memory_SafeFree(x);			//メモリの開放
	#define Memory_Alloc(x) _Memory_Alloc(x);				//メモリの取得
	#define Memory_AllocZeroClear(x) _Memory_AllocZero(x);	//メモリを取得し初期化を行う
#endif

#define Memory_ZeroClear(x,size) memset(x,0,sizeof(size));

extern void _Memory_SafeFree(void *x,const char* fileName = "",int line = 0);			//メモリの開放
extern void* _Memory_Alloc(size_t Size,const char* fileName = "",int line = 0);		//メモリーの確保
extern void* _Memory_AllocZero(size_t Size,const char* fileName = "",int line = 0);	//メモリを確保し0で初期化をする

//確保したメモリの数を返却する
extern int Memory_GetAllocNum();