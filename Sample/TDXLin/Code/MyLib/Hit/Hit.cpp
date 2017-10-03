/*

	�ėp�����蔻��


!*/

#include "DxLib.h"

#include "Hit.h"


//�l�p�`�Ɠ_�����蔻��

/*
	�l�p�`�Ǝl�p�`�̂����蔻��
	HIT_DATA rec1:�l�p�`1
	HIT_DATA rec2:�l�p�`2
	return	true	:�������Ă���
			false	:�������Ă��Ȃ�
*/
bool Hit2D_BoxToBox(HIT_DATA rec1,HIT_DATA rec2){

	if(((rec1.posX >= rec2.posX && rec1.posX <= rec2.posX + rec2.width) || 
		(rec1.posX + rec1.width >= rec2.posX && rec1.posX + rec1.width <= rec2.posX + rec2.width)) ||
		((rec1.posY >= rec2.posY && rec1.posY <= rec2.posY + rec2.height) || 
		(rec1.posY + rec1.height >= rec2.posY && rec1.posY + rec1.height <= rec2.posY + rec2.height))){
			return true;
	}
	return false;
}

/*
	�~�Ɠ_�̂����蔻��
	HIT_DATA circle	:�~
	HIT_DATA dot	:�_
	return	true	:�������Ă���
			false	:�������Ă��Ȃ�
*/
bool Hit2D_CircleToDot(HIT_DATA circle,HIT_DATA dot){

	//���S���W�ɏC��
	int centerX = circle.posX + circle.width / 2;
	int centerY = circle.posY + circle.height / 2;

	int x = centerX - dot.posX;
	int y = centerY - dot.posY;
	float r = circle.radius;

	if(x*x+y*y <= r*r){
		return true;
	}

	return false;
}

/*
	�~�Ɖ~�̂����蔻��
	HIT_DATA corcle1:�~1
	HIT_DATA corcle2:�~2
	return	true	:�������Ă���
			false	:�������Ă��Ȃ�
*/
bool Hit2D_CircleToCircle(HIT_DATA circle1,HIT_DATA circle2){

	//���S���W�ɏC��
	int centerX1 = circle1.posX + circle1.width / 2;
	int centerY1 = circle1.posY + circle1.height / 2;

	int centerX2 = circle2.posX + circle2.width / 2;
	int centerY2 = circle2.posY + circle2.height / 2;


	int x = centerX1 - centerX2;
	int y = centerY1 - centerY2;
	float r = circle1.radius + circle2.radius;

	if(x*x+y*y <= r*r){
		return true;
	}

	return false;
}

/*
	�q�b�g�f�[�^�\���̌^�ɂ��ĕԋp���܂�
	int posX		:X���W
	int posY		:Y���W
	int width		:����
	int height		:�c��
	float radius	:���a
	return HIT_DATA�^��ԋp
*/
HIT_DATA HIT2D_GetHitData(int posX,int posY,int width,int height,float radius){
	HIT_DATA data = {posX,posY,width,height,radius};
	return data;
}