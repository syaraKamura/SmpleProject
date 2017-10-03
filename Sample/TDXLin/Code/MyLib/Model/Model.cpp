#include "Model.h"

//���f��������
//���f���̓ǂݍ��݂��s��
void Model_Init(MODEL_DATA_HANDLE* pHdl,const TCHAR* fileName){

	pHdl->mhandle = MV1LoadModel(fileName);
	
	if(pHdl->mhandle != -1){
		pHdl->modleData.isDispFlag = true;		//�\�����
		pHdl->modleData.pos = MV1GetPosition(pHdl->mhandle);
		pHdl->modleData.rot = MV1GetRotationXYZ(pHdl->mhandle);
		pHdl->modleData.scale = MV1GetScale(pHdl->mhandle);

		pHdl->animNum = MV1GetAnimNum(pHdl->mhandle);	//�A�j���[�V�����̐����擾����

	}else{
		pHdl->mhandle = 0;
	}

}

/*
	���f���̃A�j���[�V�����f�[�^��ǂݍ���
*/

/*
	���f���̃A�j���[�V������ݒ肷��
*/

/*
	���f���A�j���[�V�����̍Đ�
	MODEL_DATA_HANDLE* pHdl
*/

/*
	���f���A�j���[�V�����V�����p�����Ԃ�
	MODEL_DATA_HANDLE* pHdl
	return	true	:�I��
			false	:�A�j���[�V������
*/		

//���f���`��
void Model_Draw(MODEL_DATA_HANDLE* pHdl,VECTOR pos,VECTOR scal,VECTOR rot){
	
	if(!pHdl->modleData.isDispFlag) return ;

	MV1SetRotationXYZ(pHdl->mhandle,rot);
	MV1SetPosition(pHdl->mhandle,pos);
	MV1SetScale(pHdl->mhandle,scal);
		
	MV1DrawModel(pHdl->mhandle);
}

//�s����g�p���ă��f����`�悷��
void Model_Draw(MODEL_DATA_HANDLE* pHdl,MATRIX matrix){
	if(!pHdl->modleData.isDispFlag) return ;

	MV1SetMatrix(pHdl->mhandle,matrix);
	MV1DrawModel(pHdl->mhandle);

}

//���f���̕\���A��\���̐ݒ���s��
void Model_SetDispFlag(MODEL_DATA_HANDLE* pHdl,bool isDisp){
	pHdl->modleData.isDispFlag = isDisp;
}

//�R���W���������\�z����
void Model_SetCollisitionInfomation(MODEL_DATA_HANDLE* pHdl,int frameIndex/* = -1*/,int XDivNum/*= 32*/,int YDivNum/* = 8*/,int ZDivNum/* = 32*/){
	
	pHdl->modelCollData.frameIndex = frameIndex;
	pHdl->modelCollData.XDivNum = XDivNum;
	pHdl->modelCollData.YDivNum = YDivNum;
	pHdl->modelCollData.ZDivNum = ZDivNum;

	MV1SetupCollInfo(pHdl->mhandle,frameIndex,XDivNum,YDivNum,ZDivNum);
}

//�R���W���������X�V����
void Model_UpdataCollisitionInfomation(MODEL_DATA_HANDLE* pHdl){
	MV1RefreshCollInfo(pHdl->mhandle,pHdl->modelCollData.frameIndex);
}

//�R���W���������폜����
void Model_DestoryCollisionInfomation(MODEL_DATA_HANDLE* pHdl){
	MV1TerminateCollInfo(pHdl->mhandle,pHdl->modelCollData.frameIndex);
}

//���f���̃f�[�^��ԋp����
const MODEL_DATA Model_GetData(MODEL_DATA_HANDLE* pHdl){
	pHdl->modleData.rot = MV1GetRotationXYZ(pHdl->mhandle);
	pHdl->modleData.pos = MV1GetPosition(pHdl->mhandle);
	pHdl->modleData.scale = MV1GetScale(pHdl->mhandle);
	return pHdl->modleData;
}

int Model_GetAnimNum(MODEL_DATA_HANDLE* pHdl){
	return pHdl->animNum;
}

//���f���I������
void Model_Finalize(MODEL_DATA_HANDLE* pHdl){
	MV1DeleteModel(pHdl->mhandle);
}