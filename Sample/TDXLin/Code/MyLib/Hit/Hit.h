#pragma once

//�����蔻��Ƃ�

typedef struct{
	int posX;		//���W
	int posY;
	int width;		//�T�C�Y
	int height;
	float radius;	//���a
}HIT_DATA;

//�l�p�`�Ɠ_�����蔻��

/*
	�l�p�`�Ǝl�p�`�̂����蔻��
	HIT_DATA rec1:�l�p�`1
	HIT_DATA rec2:�l�p�`2
	return	true	:�������Ă���
			false	:�������Ă��Ȃ�
*/
extern bool Hit2D_BoxToBox(HIT_DATA rec1,HIT_DATA rec2);

/*
	�~�Ɠ_�̂����蔻��
	HIT_DATA circle	:�~
	HIT_DATA dot	:�_
	return	true	:�������Ă���
			false	:�������Ă��Ȃ�
*/

extern bool Hit2D_CircleToDot(HIT_DATA circle,HIT_DATA dot);
/*
	�~�Ɖ~�̂����蔻��
	HIT_DATA corcle1:�~1
	HIT_DATA corcle2:�~2
	return	true	:�������Ă���
			false	:�������Ă��Ȃ�
*/
extern bool Hit2D_CircleToCircle(HIT_DATA circle1,HIT_DATA circle2);

/*
	�q�b�g�f�[�^�\���̌^�ɂ��ĕԋp���܂�
	int posX		:X���W
	int posY		:Y���W
	int width		:����
	int height		:�c��
	float radius	:���a
	return HIT_DATA�^��ԋp
*/
extern HIT_DATA HIT2D_GetHitData(int posX,int posY,int width,int height,float radius);