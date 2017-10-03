/*

	�Q�[���Ŕėp�I�Ɏg�p����w�b�_�[�t�@�C����R�[�h���܂Ƃ߂�
	�ėp�\�[�X�t�@�C��


*/
#include "GameCommon.h"


/*
	�I���N�����v
	int*			val			:�ύX����l
	int				add			:���Z����l
	int				min			:�ŏ��l
	int				max			:�ő�l
	eClampType		clampType	:�N�����v�̎��
*/
void GameCommon_SelectClamp(int* val,int add,int min,int max,eClampType clampType){

	int value = *val;

	//�l�̉��Z
	value += add;


	if(clampType == eClampType_ClampStop){
		//�ŏ��l��菬����
		if(value <= min){
			value = min;	//�ŏ��l�ɕ␳
		}else if(value >= max){
			value = max;	//�ő�l�ɕ␳
		}

	}else if(clampType == eClampType_ClampLoop){
		if(value < min){
			value = max-1;	//�ő�l�ɕ␳
		}else if(value >= max){
			value = min;	//�ŏ��l�ɕ␳
		}
	}
	*val = value;

}

/*
	�I���N�����v(float�^)
	float*		val			:�ύX����l
	float		add			:���Z����l
	float		min			:�ŏ��l
	float		max			:�ő�l
	eClampType	clampType	:�N�����v�̎��
*/
void GemeCommon_SelectClampF(float* val,float add,float min,float max,eClampType clampType){

	float value = *val;

	//�l�̉��Z
	value += add;


	if(clampType == eClampType_ClampStop){
		//�ŏ��l��菬����
		if(value < min){
			value = min;	//�ŏ��l�ɕ␳
		}else if(value >= max){
			value = max;	//�ő�l�ɕ␳
		}

	}else if(clampType == eClampType_ClampLoop){
		if(value <= min){
			value = max;	//�ő�l�ɕ␳
		}else if(value >= max){
			value = min;	//�ŏ��l�ɕ␳
		}
	}
	*val = value;

}