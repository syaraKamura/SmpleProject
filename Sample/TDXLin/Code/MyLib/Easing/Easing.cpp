/*
				�t�@�C����		:Easing.cpp
				�쐬��			:
				�쐬����		:2017/08/26
				�\�[�X����		:
					
					�A�j���[�V�����C�[�W���O����
				
				���l
				
	
				
				
!*/

//	------- �C���N���[�h�錾
#include "DxLib.h"

#include <math.h>

#include "Easing.h"
//	------- �Œ�萔�錾

//	-------	�}�N����`

//	------- �񋓑�

//	------- �\����&���p��

typedef struct{
	float (*easing)(float time,float totalTime,float startPos,float endPos);
}EASING_FUNC_DATA;




//	------- �X�^�e�B�b�N�ϐ��錾

//	------- �O���[�o���ϐ��錾

//	------- �X�^�e�B�b�N�v���g�^�C�v�錾(�����֐�)

//	------- �v���g�^�C�v�錾���Ă��Ȃ��X�^�e�B�b�N�֐�(�����֐�)


// -- Quadratic

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos	:�����ʒu
	float			endPos		:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Quadratic_In(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;
	return endPos * time* time + startPos;
}

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos			:�����ʒu
	float			endPos			:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Quadratic_Out(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;
	return -endPos * time* time + startPos;

}

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos			:�����ʒu
	float			endPos			:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Quadratic_InOut(float time,float totalTime,float startPos,float endPos){

	time /= (totalTime/ 2.0f);

	if(time < 1.0f){
		return endPos / 2.0f * time* time + startPos;
	}

	time = time - 1.0f;
	
	return -endPos / 2.0f * (time * (time - 2.0f) - 1.0f) + startPos;
}

// -- Cubic

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos			:�����ʒu
	float			endPos			:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Cubic_In(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;
	return endPos * time * time * time + startPos;
	
	/*
					
		time : ����(�i�s�x)
		endPos : �J�n�̒l(�J�n���̍��W��X�P�[���Ȃ�)
		startPos : �J�n�ƏI���̒l�̍���
		totalTiem : Tween(�g�D�C�[��)�̍��v����

	*/


}

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos			:�����ʒu
	float			endPos			:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Cubic_Out(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;
	time = time - 1.0f;
	return endPos * time * time * time + startPos;
}

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos	:�����ʒu
	float			endPos		:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Cubic_InOut(float time,float totalTime,float startPos,float endPos){

	time /= (totalTime/ 2.0f);

	if(time < 1.0f){
		return endPos / 2.0f * time* time * time + startPos;
	}

	time = time - 2.0f;
	
	return endPos / 2.0f * (time * time* time + 2.0f) + startPos;

	return 0.0f;
}

// -- Quartic

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos	:�����ʒu
	float			endPos		:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Quartic_In(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;

	return endPos * time * time * time * time + startPos;

}

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos			:�����ʒu
	float			endPos			:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Quartic_Out(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;
	time = time - 1.0f;

	return -endPos * (time * time * time * time - 1.0f) + startPos;
}

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos			:�����ʒu
	float			endPos			:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Quartic_InOut(float time,float totalTime,float startPos,float endPos){

	time /= totalTime / 2.0f;

	if( time < 1.0f ){

		return endPos / 2.0f * time * time * time * time + startPos;
	}

	return -endPos / 2.0f * (time * time * time * time - 2.0f) + startPos;
}

// -- Quintic

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos			:�����ʒu
	float			endPos			:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Quintic_In(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;

	return endPos * time * time * time * time * time + startPos;

}

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos			:�����ʒu
	float			endPos			:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Quintic_Out(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;

	time = time - 1.0f;

	return endPos * (time * time * time * time * time + 1) + startPos;

}

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos			:�����ʒu
	float			endPos			:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Quintic_InOut(float time,float totalTime,float startPos,float endPos){

	time /= totalTime / 2.0f;

	if(time < 1.0f){
		return endPos / 2.0f * time * time * time * time * time + startPos; 
	}

	time = time - 2.0f;

	return endPos / 2.0f * (time * time * time * time * time + 2.0f) + startPos;
}

// -- Sinusoidal

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos			:�����ʒu
	float			endPos			:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Sinusoidal_In(float time,float totalTime,float startPos,float endPos){

	return -endPos * cos(time / totalTime * (DX_PI_F / 2.0f)) + endPos + startPos;
}

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos			:�����ʒu
	float			endPos			:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Sinusoidal_Out(float time,float totalTime,float startPos,float endPos){

	return endPos * sin(time / totalTime * (DX_PI_F / 2.0f)) + startPos;
}

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos			:�����ʒu
	float			endPos			:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Sinusoidal_InOut(float time,float totalTime,float startPos,float endPos){

	return -endPos / 2.0f * (cos(DX_PI_F * time / totalTime) - 1.0f) + startPos;
}

// -- Exponential

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos			:�����ʒu
	float			endPos			:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Exponential_In(float time,float totalTime,float startPos,float endPos){

	return endPos * 2.0f * (10.0f * (time / totalTime - 1.0f)) *  (10.0f * (time / totalTime - 1.0f)) + startPos;
}

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos			:�����ʒu
	float			endPos			:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Exponential_Out(float time,float totalTime,float startPos,float endPos){

	return endPos * (-(2.0f * (-10.0f * time/totalTime) * (-10.0f * time/totalTime)) + 1.0f) + startPos;
}

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos			:�����ʒu
	float			endPos			:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Exponential_InOut(float time,float totalTime,float startPos,float endPos){

	time /= time / 2.0f;

	if( time < 1.0f){
		return endPos / 2.0f * 2.0f * (10.0f * (time - 1.0f)) * (10.0f * (time - 1.0f)) + startPos;
	}

	return endPos / 2.0f * (-(2.0f * (-10.0f * time) * (-10.0f * time)) + 2.0f) + startPos;
}

// -- Circular

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos	:�����ʒu
	float			endPos		:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Circular_In(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;
	return -endPos * (sqrt(1.0f - time * time) - 1.0f) + startPos;
	
}

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos	:�����ʒu
	float			endPos		:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Circular_Out(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;

	time = time - 1.0f;

	return endPos * sqrt(1.0f - time * time ) + startPos;
}

/*
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos	:�����ʒu
	float			endPos		:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
*/
static float _Circular_InOut(float time,float totalTime,float startPos,float endPos){

	time /= time / 2.0f;
	
	if(time < 1.0f){
		return -endPos / 2.0f * (sqrt(1.0f - time * time) -1.0f); 
	}

	time = time - 2.0f;

	return endPos / 2.0f * (sqrt(1.0f - time + time) + 1.0f) + startPos;
}



//	------- �O���[�o���֐�



//	------- �f�[�^�e�[�u��
static EASING_FUNC_DATA s_EasingFuncTbl[eEasingType_Max][eEasingInOut_Max] = {
	
	//	IN					OUT					INOUT
	{	_Quadratic_In,		_Quadratic_Out,		_Quadratic_InOut	},		//Quadratic
    {	_Cubic_In,			_Cubic_Out,			_Cubic_InOut		},		//Cubic
    {	_Quartic_In,		_Quartic_Out,		_Quartic_InOut		},		//Quartic
    {	_Quintic_In,		_Quintic_Out,		_Quintic_InOut		},		//Quintic
    {	_Sinusoidal_In,		_Sinusoidal_Out,	_Sinusoidal_InOut	},		//Sinusoidal
    {	_Exponential_In,	_Exponential_Out,	_Exponential_InOut	},		//Exponential
    {	_Circular_In,		_Circular_Out,		_Circular_InOut		},		//Circular

};


/*
	�C�[�W���O�������s��
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos			:�����ʒu
	float			endPos			:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
			���s:�K��0.0f��ԋp����

*/
float Easing(eEasingType type,eEasingInOut inOut,float time,float totalTime,float startPos,float endPos){
	
	//�͈͊O���w�肳�ꂽ�珈�������Ȃ�
	if(type >= eEasingType_Max || type < eEasingType_Quadratic) return 0.0f;
	if(inOut >= eEasingInOut_Max || inOut < eEasingInOut_In)	return 0.0f;

	EASING_FUNC_DATA* easing = &s_EasingFuncTbl[type][inOut];

	//�֐��|�C���^�[��NULL�Ȃ珈���𔲂���
	if(easing == NULL) return 0.0f;
	return easing->easing(time,totalTime,startPos,endPos);

}
