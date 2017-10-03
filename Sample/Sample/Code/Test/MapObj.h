#pragma once


typedef struct{
	MODEL_DATA_HANDLE modle;	//���f���ǂݍ���
	VECTOR pos;					//���W
	VECTOR rot;					//�p�x
	VECTOR scal;				//�T�C�Y
}MAP_OBJ;

//�}�b�v�I�u�W�F�N�g�̐���
MAP_OBJ* MapObj_Create(const char* fileName,VECTOR pos,bool isDisp);
//�}�b�v�I�u�W�F�N�g�폜
void MapObj_Destory(MAP_OBJ* ix);
//�}�b�v�I�u�W�F�N�g�`��
void MapObj_Draw(MAP_OBJ* ix);
//���W�̐ݒ�
void MapObj_SetPosition(MAP_OBJ* ix,VECTOR pos);
//�p�x�̐ݒ�
void MapObj_SetRotate(MAP_OBJ* ix,VECTOR rot);
//�T�C�Y�̐ݒ�
void MapObj_SetScal(MAP_OBJ* ix,VECTOR scal);