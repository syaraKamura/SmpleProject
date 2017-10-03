#pragma once 

#include "CharactorObj.h"

typedef struct{
	int id;				//ID
	int movePattaern;	//�ړ��p�^�[��
	int attackPattern;	//�U���p�^�[��
	VECTOR targetPos;
	CHARA_OBJ* pCh;
}CHARA_ENEMY_OBJ;


CHARA_ENEMY_OBJ* CharEnemyObj_Creata(int id,VECTOR pos,VECTOR rot,int modelKind,int movePattern = 0,int attackPattern = 0);
void CharEnemyObj_Destory(CHARA_ENEMY_OBJ* ix);

//�X�V����
void CharEnemyObj_Updata(CHARA_ENEMY_OBJ* ix);
//�`�揈��
void CharEnemyObj_Draw(CHARA_ENEMY_OBJ* ix);
//�X�e�[�^�X�̐ݒ�
void CharEnemyObj_SetStatus(CHARA_ENEMY_OBJ* ix,int hp,int attack,int defence,float moveSpeed);
//���W�ݒ�
void CharEnemyObj_SetPosition(CHARA_ENEMY_OBJ* ix,VECTOR pos);
//�p�x�̐ݒ�
void CharEnemyObj_SetRotate(CHARA_ENEMY_OBJ* ix,VECTOR rot);
//�T�C�Y�̐ݒ�
void CharEnemyObj_SetScal(CHARA_ENEMY_OBJ* ix,VECTOR scal);
//�T�C�Y��ԋp����
VECTOR CharEnemyObj_GetScal(CHARA_ENEMY_OBJ* ix);
//�p�x��ԋp����
VECTOR CharEnemyObj_GetRotate(CHARA_ENEMY_OBJ* ix);
//���W��ԋp����
VECTOR CharEnemyObj_GetPosition(CHARA_ENEMY_OBJ* ix);
//�X�e�[�^�X��ԋp����
STATUS_DATA* CharEnemyObj_GetStatus(CHARA_ENEMY_OBJ* ix);