/*
				�t�@�C����		:Easing.h
				�쐬��			:
				�쐬����		:2017/08/26
				�\�[�X����		:
				
					�A�j���[�V�����C�[�W���O����
				
				���l
				
				
    
				
!*/

#ifndef __EASING_H__
#define __EASING_H__

//	------- �C���N���[�h�錾

//	------- �Œ�萔�錾

//	-------	�}�N����`

//	------- �񋓑�

enum eEasingType{

	eEasingType_Quadratic,
	eEasingType_Cubic,
	eEasingType_Quartic,
	eEasingType_Quintic,
	eEasingType_Sinusoidal,
	eEasingType_Exponential,
	eEasingType_Circular,

	eEasingType_Max,
};

enum eEasingInOut{
	eEasingInOut_In,
	eEasingInOut_Out,
	eEasingInOut_InOut,
	eEasingInOut_Max,
};


//	------- �\����&���p��

//	------- �O���[�o���֐�

/*
	�C�[�W���O�������s��
	eEasingType		type		:�C�[�W���O�̎��
	eEasingInOut	inOut		:�C�[�W���O���ǂ̕�����
	float			time		:����
	float			totalTime	:�I������
	float			startPos	:�����ʒu
	float			endPos		:�I���ʒu

	return�@����:�v�Z���ʂ�ԋp����
			���s:�K��0.0f��ԋp����

*/
extern float Easing(eEasingType type,eEasingInOut inOut,float time,float totalTime,float startPos,float endPos);

//	------- �C�����C���֐�(�w�b�_�[���֐�)


#endif // __EASING_H__