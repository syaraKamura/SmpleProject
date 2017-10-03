#include "Common/GameCommon/GameCommon.h"

#include "MapObj.h"


//�}�b�v�I�u�W�F�N�g�̐���
MAP_OBJ* MapObj_Create(const char* fileName,VECTOR pos,bool isDisp){

	//�������m��
	MAP_OBJ* ix = (MAP_OBJ*)Memory_Alloc(sizeof(MAP_OBJ));

	if(ix != NULL){

		//���f���ݒ�
		Model_Init(&ix->modle,(const TCHAR*)fileName);
		
		//���W�̐ݒ�
		ix->pos = pos;

		//�T�C�Y�̐ݒ�
		ix->scal = VGet(1.0f,1.0f,1.0f);
		
		//�p�x�̐ݒ�
		ix->rot = VGet(0.0f,0.0f,0.0f);

		//���f���̕\���ݒ�
		Model_SetDispFlag(&ix->modle,isDisp);
		
		return ix;

	}
	return NULL;
}

//�}�b�v�I�u�W�F�N�g�폜
void MapObj_Destory(MAP_OBJ* ix){
	
	Model_Finalize(&ix->modle);
	//�������J��
	Memory_SafeFree(ix);
}

//�}�b�v�I�u�W�F�N�g�`��
void MapObj_Draw(MAP_OBJ* ix){
	Model_Draw(&ix->modle,ix->pos,ix->scal,ix->rot);
}

//���W�̐ݒ�
void MapObj_SetPosition(MAP_OBJ* ix,VECTOR pos){
	ix->pos = pos;
}

//�p�x�̐ݒ�
void MapObj_SetRotate(MAP_OBJ* ix,VECTOR rot){
	ix->rot = rot;
}

//�T�C�Y�̐ݒ�
void MapObj_SetScal(MAP_OBJ* ix,VECTOR scal){
	ix->scal = scal;
}

