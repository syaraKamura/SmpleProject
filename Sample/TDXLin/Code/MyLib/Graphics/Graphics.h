#pragma once

#include "DxLib.h"

typedef struct{
	int graphicHandle;	//�摜�n���h��
	int basePosX;		//��ʂ̎n�_�ʒu
	int basePosY;
	int offsetPosX;		//�摜�̒��S���W
	int offsetPosY;
	int drawPosX;		//�`����W
	int drawPosY;
	int width;			//�摜�T�C�Y
	int height;
	//int pad;			//�ςł���
}GRAPHICS_RES;

//�摜�ǂݍ��݊��
extern bool Graphics_LoadBase(GRAPHICS_RES* graphics,const char* fileName,int offsetPosX = 0,int offsetPosY = 0,int basePosX = 0,int basePosY = 0);
//�摜�ǂݍ���
extern bool Graphics_Load(GRAPHICS_RES* graphics,const char* fileName);

//�摜�̔񓯊��ǂݍ��݊��
extern void Graphics_ASyncLoadBase(GRAPHICS_RES* graphics,const char*fileName,int offsetPosX = 0,int offsetPosY = 0,int basePosX = 0,int basePosY = 0);
//�摜�̔񓯊��ǂݍ���
extern void Graphics_ASyncLoad(GRAPHICS_RES* graphics,const char* fileName);

//�摜�̔񓯊��ǂݍ��݂��I�����Ă��邩�H
extern bool Graphics_IsASyncLoadEnd(GRAPHICS_RES* graphics);

extern void Graphics_Delete(GRAPHICS_RES* graphics);

//�摜�̕`��
/*
	�����ɂ���	�摜�`��K��
	�֐���			Graphics_DrawBase
	����			GRAPHICS_RES*	graphics	:�O���t�B�b�N���\�[�X�\����
	����			int				posX		:X���W
	����			int				posY		:Y���W
	����			int				scrX		:�`����s���摜���ł̍���̍��WU(100�Ȃ� �摜�����W100����width�܂ł͈̔͂�`�悷��)
	����			int				scrY		:�`����s���摜���ł̍���̍��WV(100�Ȃ� �摜�����W100����height�܂ł͈̔͂�`�悷��)
	����			int				width		:�摜�T�C�Y
	����			int				heihgt		:�摜�T�C�Y
	����			int				centerX		:��]�̒��S���WX
	����			int				centerY		:��]�̒��S���WY
	����			double			ExtRate		:�g�嗦(1.0���ʏ�T�C�Y)
	����			double			angle		:�`��p�x
	����			int				transFlag	:�摜�̓����x��L���ɂ��邩�H(TRUE:�L�� FALSE:����)
	����			int				turnFlag	:�摜�𔽓]�����邩?(TRUE:���]���� FALSE:���]���Ȃ�)
!*/
extern void Graphics_DrawBase(GRAPHICS_RES* graphics,int posX,int posY,int scrX,int scrY,int width,int heihgt,int centerX,int centerY,double ExtRate,double angle,int transFlag,int turnFlag);
/*
	�����ɂ���	�摜�`��
	�֐���			Graphics_DrawBase
	����			GRAPHICS_RES*	graphics	:�O���t�B�b�N���\�[�X�\����
	����			int				posX		:X���W
	����			int				posY		:Y���W
	����			int				transFlag	:�摜�̓����x��L���ɂ��邩�H(TRUE:�L�� FALSE:����)
	����			int				turnFlag	:�摜�𔽓]�����邩?(TRUE:���]���� FALSE:���]���Ȃ�)
!*/
extern void Graphics_Draw(GRAPHICS_RES* graphics,int posX,int posY,int transFlag,int turnFlag = FALSE);

/*
	�����ɂ���	�摜�`��(�摜�̒��S���N�_�ɉ�]������)
	�֐���			Graphics_DrawRot
	����			GRAPHICS_RES*	graphics	:�O���t�B�b�N���\�[�X�\����
	����			int				posX		:X���W
	����			int				posY		:Y���W
	����			double			angle		:�`��p�x
	����			int				transFlag	:�摜�̓����x��L���ɂ��邩�H(TRUE:�L�� FALSE:����)
	����			int				turnFlag	:�摜�𔽓]�����邩?(TRUE:���]���� FALSE:���]���Ȃ�)
!*/
extern void Graphics_DrawRot(GRAPHICS_RES* graphics,int posX,int posY,double angle,int transFlag,int turnFlag = FALSE);

/*

	�����ɂ���	�摜�𕪊����ĕ`��
	�֐���			Graphics_DrawRot
	����			GRAPHICS_RES*	graphics	:�O���t�B�b�N���\�[�X�\����
	����			int				posX		:X���W
	����			int				posY		:Y���W
	����			int				scrX		:U���W
	����			int				scrY		:V���W
	����			int				transFlag	:�摜�̓����x��L���ɂ��邩�H(TRUE:�L�� FALSE:����)
	����			int				turnFlag	:�摜�𔽓]�����邩?(TRUE:���]���� FALSE:���]���Ȃ�)

!*/
extern void Graphics_DrawDiv(GRAPHICS_RES* graphcis,int posX,int posY,int scrX,int scrY,int width,int height,int transFlag,int trunFlag);

/*
	
	�����ɂ���	�摜���w�肵���T�C�Y�ŕ������`�悷��
	�֐���			Graphics_DrawRot
	����			GRAPHICS_RES*	graphics	:�O���t�B�b�N���\�[�X�\����
	����			int				posX		:X���W
	����			int				posY		:Y���W
	����			int				scrX		:U���W
	����			int				scrY		:V���W
	����			int				transFlag	:�摜�̓����x��L���ɂ��邩�H(TRUE:�L�� FALSE:����)
	����			int				turnFlag	:�摜�𔽓]�����邩?(TRUE:���]���� FALSE:���]���Ȃ�)
!*/
extern void Graphics_DrawSplit(GRAPHICS_RES* graphics,int posX,int posY,int u,int v,int splitSizeX,int splitSizeY,int transFlag,int trunFlag);

//�摜�̊�X�N���[�����W��ݒ肷��
extern void Graphics_SetBasePos(GRAPHICS_RES* graphics,int posX,int posY);

//�摜�̒��S���W��ݒ肷��
extern void Graphics_SetOffsetPos(GRAPHICS_RES* graphics,int posX,int posY);

//���W��ԋp����
extern int Graphics_GetPosX(GRAPHICS_RES graphics);
extern int Graphics_GetPosY(GRAPHICS_RES graphics);

//�摜�T�C�Y��ԋp����
extern int Graphics_GetWidth(GRAPHICS_RES graphics);
extern int Graphics_GetHeight(GRAPHICS_RES graphics);

