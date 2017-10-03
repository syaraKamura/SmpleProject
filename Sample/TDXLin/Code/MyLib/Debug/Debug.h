
//�f�o�b�O�@�\���y�ɂȂ�֐����L�q���Ă���

#pragma once

#include <stdio.h>
#include <assert.h>

enum eDebugType{
	eDebugType_Flag,		//�t���O��ON�̎��Ɏ��s�����
	eDebugType_Func,		//�ݒ肵���֐������s����
};


typedef struct{
	char debugName[256];	//�f�o�b�O��
	eDebugType debugType;	//�f�o�b�O�̎��
	bool (*FuncUpdata)();	//�߂�l��true�̊Ԏ��s����
	bool (*FuncDraw)();		//�߂�l��true�̊Ԏ��s����
	void (*FuncFlagOn)();	//�t���O���I���̎��Ɉ�x���s�����
	void (*FuncFlagOff)();	//�t���O���I�t�̎��Ɉ�x���s�����
	bool isFlag;			//���s���邩�H

}DEBUG_FUNC_DATA;

typedef struct{
	char objectName[256];
	DEBUG_FUNC_DATA* pdebuFunc;
	int debugFuncNum;			//�f�o�b�O���X�g�̐�
}DEBUG_DATA;

void Debug_Print(const char* str,...);
void Debug_DrawString();

//�����t��
extern void Debug_Println(const char* str,...);
extern void Debug_Printf(int posX,int posY,unsigned int color,const char* str,...);
extern void Debug_LogPrintf(const char* str,...);

#ifdef __MY_DEBUG__



//�w�肵��������false�Ȃ�A�T�[�g
#define ASSERT(x)	do { \
	if(!(x)){				 \
		static char buf[256]="";\
		sprintf_s(buf,"Assertion failed: %s file: %s line: %d\n",#x,__FILE__,__LINE__);\
		OutputDebugString(buf);\
		exit(1);	/*�����I��*/\
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
	�f�o�b�O���ڂ̓o�^
	DEBUG_FUNC_DATA*	debugData	:�f�o�b�O�f�[�^
	const char*			objectName	:�f�o�b�O���ږ�
	size_t				size		:�f�[�^�T�C�Y
*/
extern void Debug_Entory(DEBUG_FUNC_DATA* debugData,const char* objectName,size_t size);

/*
	�f�o�b�O�t���O�̏�Ԃ��擾����
	const char* objectName	:�f�o�b�O���ږ�
	const char* debugName	:�f�o�b�O��
	return	true	:�t���O���I��
			false	:�t���O���I�t
*/
extern bool Debug_IsFlag(const char* objectName,const char* debugName);

/*
	������
*/
extern void Debug_Initialize();
/*
	�I������
*/
extern void Debug_Finalize();

/*
	�X�V
*/
extern void Debug_Updata();
/*
	�`��
*/
extern void Debug_Draw();

#endif // __MY_DEBUG__