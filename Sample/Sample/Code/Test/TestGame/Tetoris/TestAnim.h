#pragma once

#include "Common/GameCommon/GameCommon.h"

enum eAnimKind{

	eAnimKind_In,		
	eAnimKind_Out,
	eAnimKind_Rot,
	eAnimKind_RandomMove,
};

typedef struct{
	GRAPHICS_RES res;
	int posX;
	int posY;
	double scal;
	double rot;
	eAnimKind anim;
	int step;
	int cnt;
	int dir;
}TEST_ANIM_OBJ;

//�A�j���[�V������ύX����
void TestAnimObj_ChangeAnim(TEST_ANIM_OBJ* ix,eAnimKind anim);

//���W��ݒ肷��
void TestAnimObj_SetPosition(TEST_ANIM_OBJ* ix,int posX,int posY);

/*
�A�j���V�����̐���
	
	@pram fileName	:	�ǂݍ��މ摜�̃p�X
	@pram PosX		:	X���W
	@pram PosY		:	Y���W
	@pram Scal		:	�T�C�Y
	@pram rot		:	�p�x
	@pram anim		:	�A�j���[�V�����̎��
	


	@return	
*/
TEST_ANIM_OBJ* TestAnimObj_Create(const char* fileName,int posX,int posY,double scal,double rot,eAnimKind anim);

//�A�j���[�V�����̍폜
void TestAnimObj_Destroy(TEST_ANIM_OBJ* ix);