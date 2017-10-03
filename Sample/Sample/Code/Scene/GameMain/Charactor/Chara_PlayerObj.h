#pragma once

#include "CharactorObj.h"

typedef struct{
	int level;
	int exp;
	CHARA_OBJ* pCh;		//�L�����N�^�[
}CHARA_PLAYER_OBJ;


//�v���C���[�L�����N�^�[�̏�����
//�L�����N�^�[�I�u�W�F�N�g�@���W�@�p�x�@���f���̎��(CharComRes �̋��p�̎Q��)
CHARA_PLAYER_OBJ* CharaPlayerObj_Create(VECTOR pos,VECTOR rot,int modelKind);
//�폜
void CharPlayerObj_Destory(CHARA_PLAYER_OBJ* ix);
//�X�V����
void CharPlayerObj_Updata(CHARA_PLAYER_OBJ* ix);
//�`�揈��
void CharPlayerObj_Draw(CHARA_PLAYER_OBJ* ix);

//�X�e�[�^�X�̐ݒ�
//���x���@�o���l�@�̗́@�U���́@�h��́@�ړ��X�s�[�h
void CharPlayerObj_SetStatus(CHARA_PLAYER_OBJ* ix,int level,int exp,int hp,int attack,int defence,float moveSpeed);
//���W�ݒ�
void CharPlayerObj_SetPosition(CHARA_PLAYER_OBJ* ix,VECTOR pos);
void CharPlayerObj_SetRotate(CHARA_PLAYER_OBJ* ix,VECTOR rot);
void CharPlayerObj_SetScal(CHARA_PLAYER_OBJ* ix,VECTOR scal);

VECTOR CharPlayerObj_GetScal(CHARA_PLAYER_OBJ* ix);
VECTOR CharPlayerObj_GetRotate(CHARA_PLAYER_OBJ* ix);
//���W��ԋp����
VECTOR CharPlayerObj_GetPosition(CHARA_PLAYER_OBJ* ix);
//�X�e�[�^�X��ԋp����
STATUS_DATA* CharPlayerObj_GetStatus(CHARA_PLAYER_OBJ* ix);