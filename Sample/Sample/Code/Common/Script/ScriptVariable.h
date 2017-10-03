/*
				�t�@�C����		:ScriptVariable.h
				�쐬��			:
				�쐬����		:2017/08/20
				�\�[�X����		:�X�N���v�g�ň����ϐ��̊Ǘ����s��
				
				
				���l
				
				
				
!*/

#ifndef __SCRIPT_VARIABLE_H__
#define __SCRIPT_VARIABLE_H__

//	------- �C���N���[�h�錾

//	------- �Œ�萔�錾

//	-------	�}�N����`

//	------- �񋓑�

enum eVariable{
	eVariable_Integer,	//int�^
	eVariable_Boolean,	//bool�^
	eVariable_None,		//�����Ȃ�
};


//	------- �\����&���p��

typedef struct{
	char variableName[64];
	int val;
	eVariable variableKind;		//�ϐ��̎��
}VARIABLE_DATA;

//	------- �O���[�o���֐�

//	------- �C�����C���֐�(�w�b�_�[���֐�)

#endif	//__SCRIPT_VARIABLE_H__