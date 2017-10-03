#pragma once

#ifdef __MY_DEBUG__
	#define Memory_SafeFree(x) _Memory_SafeFree(x,__FILE__,__LINE__);			//�������̊J��
	#define Memory_Alloc(x) _Memory_Alloc(x,__FILE__,__LINE__);				//�������̎擾
	#define Memory_AllocZeroClear(x) _Memory_AllocZero(x,__FILE__,__LINE__);	//���������擾�����������s��

	

#else
	#define Memory_SafeFree(x) _Memory_SafeFree(x);			//�������̊J��
	#define Memory_Alloc(x) _Memory_Alloc(x);				//�������̎擾
	#define Memory_AllocZeroClear(x) _Memory_AllocZero(x);	//���������擾�����������s��
#endif

#define Memory_ZeroClear(x,size) memset(x,0,sizeof(size));

extern void _Memory_SafeFree(void *x,const char* fileName = "",int line = 0);			//�������̊J��
extern void* _Memory_Alloc(size_t Size,const char* fileName = "",int line = 0);		//�������[�̊m��
extern void* _Memory_AllocZero(size_t Size,const char* fileName = "",int line = 0);	//���������m�ۂ�0�ŏ�����������

//�m�ۂ����������̐���ԋp����
extern int Memory_GetAllocNum();