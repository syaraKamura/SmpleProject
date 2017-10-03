/*
				�t�@�C����		:ScriptFlag.h
				�쐬��			:
				�쐬����		:2017/08/20
				�\�[�X����		:�X�N���v�g�������t���O������
				


				
				���l
				
				
				
!*/

#ifndef __SCRIPT_FLAG_H__
#define __SCRIPT_FLAG_H__

//	------- �C���N���[�h�錾

//	------- �Œ�萔�錾

static const int FLAG_DATA_NUM = 4096;

//	-------	�}�N����`

//	------- �񋓑�

//	------- �\����&���p��

typedef struct{
	u8 flag[FLAG_DATA_NUM];
}SCRIPT_FLAG_DATA;

//	------- �O���[�o���֐�

/*
	�X�N���v�g�t���O������������
	SCRIPT_FLAG_DATA*	flag
*/
void ScriptFlag_Initialize(SCRIPT_FLAG_DATA* flag);
/*
	�t���O�f�[�^�̓ǂݍ��݂��s��
	SCRIPT_FLAG_DATA*	flag
*/
void ScriptFlag_Load(SCRIPT_FLAG_DATA* flag);
/*
	�t���O�f�[�^�̕ۑ����s��
	SCRIPT_FLAG_DATA*	flag		:
	const char*			path		:�ۑ���̃t�@�C�������܂߂��p�X����͂���(��. data/save/flags)
*/
bool ScriptFlag_Save(SCRIPT_FLAG_DATA* flag,const char* path);

/*
	�w��̃t���O�ԍ����I���ɂ���
	SCRIPT_FLAG_DATA*	flag	:
	s32					index	:�t���O�ԍ�
*/
void ScriptFlag_FlagOn(SCRIPT_FLAG_DATA* flag,s32 index);
/*
	�w��̃t���O�ԍ����I�t�ɂ���
	SCRIPT_FLAG_DATA*	flag	:
	s32					index	:�t���O�ԍ�
*/
void ScriptFlag_FlagOff(SCRIPT_FLAG_DATA* flag,s32 index);
/*
	�w��̃t���O�ԍ��̃t���O��Ԃ�ԋp����(�͈͊O�̏ꍇ�͕K���I�t��ԋp����)
	SCRIPT_FLAG_DATA*	flag	:
	s32					index	:�t���O�ԍ�
	return	0:�t���O�I�t
			1:�t���O�I��
*/
u8 ScriptFlag_GetFlag(SCRIPT_FLAG_DATA* flag,s32 index);

//	------- �C�����C���֐�(�w�b�_�[���֐�)

#endif	//__SCRIPT_FLAG_H__
