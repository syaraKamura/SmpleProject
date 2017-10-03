#pragma once

typedef struct{
	VECTOR pos;			//���W
	VECTOR rotate;		//����
	VECTOR scal;		//�T�C�Y
	MATRIX matrix;		//�s��
	MODEL_DATA_HANDLE model;
}PLAYER_OBJ;


//����
PLAYER_OBJ* PlayerObj_Create(const TCHAR* fileName);
//�폜
void PlayerObj_Destroy(PLAYER_OBJ* ix);

//�X�V
void PlayerObj_Updata(PLAYER_OBJ* ix);
//�`��
void PlayerObj_Draw(PLAYER_OBJ* ix);

//���W�̐ݒ�
void PlayerObj_SetPositon(PLAYER_OBJ* ix,float x,float y,float z);
void PlayerObj_SetPositon(PLAYER_OBJ* ix,VECTOR pos);

//�p�x�̐ݒ�
void PlayerObj_SetRotate(PLAYER_OBJ* ix,VECTOR rot);

//�T�C�Y�ύX
void PlayerObj_SetScal(PLAYER_OBJ* ix,VECTOR scal);

//�p�x�擾
VECTOR PlayerObj_GetRoate(PLAYER_OBJ* ix);
//���W�̎擾
VECTOR PlayerObj_GetPosition(PLAYER_OBJ* ix);