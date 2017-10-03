#include "Memory.h"
#include "MyLib/Debug/Debug.h"
#include "DxLib.h"

static int s_AllocNum = 0;

//メモリの開放
void _Memory_SafeFree(void *x,const char* fileName /*= ""*/,int line /*= 0*/){
	if(x != NULL){
#ifdef __DXLIB
	DxFree(x);

	#ifdef __MY_DEBUG__
		int strLen = strlen(fileName);
		const int point = (strLen - 16) < 1 ? 0 :(strLen - 16);
		const char* name = (fileName + (point));
		Debug_LogPrintf("DeleteMemory: Filename:%s Line:%d\n",name,line);
	#endif

#else
	free(x);
#endif
	s_AllocNum--;
		x = NULL;
	}
}

//メモリーの確保
void* _Memory_Alloc(size_t Size,const char* fileName /*= ""*/,int line /*= 0*/){

#ifdef __DXLIB
	void* memory = DxAlloc(Size,fileName,line);
	#ifdef __MY_DEBUG__
		int strLen = strlen(fileName);
		const int point = (strLen - 16) < 1 ? 0 :(strLen - 16);
		const char* name = (fileName + (point));
		Debug_LogPrintf("AllocMemory: Filename:%s Line:%d\n",name,line);
	#endif
#else
	void* memory = malloc(Size);
#endif
	if(memory != NULL){
		s_AllocNum++;
		return memory;
	}
	return NULL;
}


void* _Memory_AllocZero(size_t Size,const char* fileName /*= ""*/,int line /*= 0*/){
#ifdef __DXLIB
	void* memory = DxCalloc(Size,fileName,line);
	#ifdef __MY_DEBUG__
		int strLen = strlen(fileName);
		const int point = (strLen - 16) < 1 ? 0 :(strLen - 16);
		const char* name = (fileName + (point));
		Debug_LogPrintf("AllocMemory: Filename:%s Line:%d\n",name,line);
	#endif
#else
	void* memory = malloc(Size);
#endif
	if(memory != NULL){
		s_AllocNum++;
		return memory;
	}
	return NULL;
}

//確保したメモリの数を返却する
int Memory_GetAllocNum(){
	return s_AllocNum;
}
