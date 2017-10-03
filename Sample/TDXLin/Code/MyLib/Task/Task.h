#pragma once


typedef void (*FUNCTYPE)(void*);

enum eTaskClassType{
	eTaskClassType_Class00,
	eTaskClassType_Class01,
	eTaskClassType_Class02,
	eTaskClassType_Class03,
	eTaskClassType_Class04,
	eTaskClassType_Class05,
	eTaskClassType_Class06,
	eTaskClassType_Class07,
	eTaskClassType_Class08,

	eTaskClassType_MAX,

};

#ifdef __MY_DEBUG__
extern void* Task_Create(FUNCTYPE Proc,FUNCTYPE Draw,FUNCTYPE Del,int FuncType,eTaskClassType ClassType,const char* fileName,int line);
#else
extern void* Task_Create(FUNCTYPE Proc,FUNCTYPE Draw,FUNCTYPE Del,int FuncType,eTaskClassType ClassType);
#endif


extern void Task_KillRequest(void* ix);

extern void Task_Init();
extern void Task_Finalize();
extern void Task_Entory();
extern void Task_Updata();
extern void Task_Draw();
extern void Task_Dalete();

#ifdef __MY_DEBUG__
#define Task_CreateBase(Func,Draw,Del,FuncType,ClassType) (FuncType*)Task_Create((FUNCTYPE) Func,(FUNCTYPE) Draw, (FUNCTYPE) Del,sizeof(FuncType),ClassType,__FILE__,__LINE__)
#else
#define Task_CreateBase(Func,Draw,Del,FuncType,ClassType) (FuncType*)Task_Create((FUNCTYPE) Func,(FUNCTYPE) Draw,(FUNCTYPE) Del,sizeof(FuncType),ClassType)
#endif


