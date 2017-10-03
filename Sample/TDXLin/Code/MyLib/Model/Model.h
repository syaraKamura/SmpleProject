#pragma once

#include "DxLib.h"

typedef struct{
	int frameIndex;
	int XDivNum;
	int YDivNum;
	int ZDivNum;
}MODEL_COLLISTION_DATA;

typedef struct{
	VECTOR pos;			//���W
	VECTOR rot;			//�p�x
	VECTOR scale;		//�X�P�[��
	bool isDispFlag;	//�\����\����ݒ肷��
}MODEL_DATA;

typedef struct{
	int mhandle;							//���f���n���h��
	MODEL_DATA modleData;					//���f���f�[�^
	MODEL_COLLISTION_DATA modelCollData;	//���f���̃R���W�����f�[�^
	int animNum;							//�A�j���[�V�����̐�
	int animIndex;							//�A�j���[�V�����ԍ�
	int AnimScrMHadel;						//�A�^�b�`����A�j���[�V�����������Ă��郂�f���n���h��
}MODEL_DATA_HANDLE;


//���f��������
extern void Model_Init(MODEL_DATA_HANDLE* pHdl,const TCHAR* fileName);

//���f���`��
extern void Model_Draw(MODEL_DATA_HANDLE* pHdl,VECTOR pos,VECTOR scal,VECTOR rot);
//�s����g�p���ă��f����`�悷��
extern void Model_Draw(MODEL_DATA_HANDLE* pHdl,MATRIX matrix);

//���f���I������
extern void Model_Finalize(MODEL_DATA_HANDLE* pHdl);

//Setter

//���f���̕\���A��\���̐ݒ���s��
extern void Model_SetDispFlag(MODEL_DATA_HANDLE* pHdl,bool isDisp);

//�R���W���������\�z����
extern void Model_SetCollisitionInfomation(MODEL_DATA_HANDLE* pHdl,int frameIndex = -1,int XDivNum = 32,int YDivNum = 8,int ZDivNum = 32);
//�R���W���������폜����
extern void Model_DestoryCollisionInfomation(MODEL_DATA_HANDLE* pHdl);

//�R���W���������X�V����
extern void Model_UpdataCollisitionInfomation(MODEL_DATA_HANDLE* pHdl);

//Getter

//���f���̃f�[�^��ԋp����
extern const MODEL_DATA Model_GetData(MODEL_DATA_HANDLE* pHdl);

