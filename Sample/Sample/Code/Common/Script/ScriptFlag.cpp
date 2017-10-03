/*
				�t�@�C����		:ScripFlag.cpp
				�쐬��			:
				�쐬����		:2071/08/20
				�\�[�X����		:�X�N���v�g�������t���O������
				
				
				���l
				
				
				
!*/

//	------- �C���N���[�h�錾
#include "Common/GameCommon/GameCommon.h"
#include "ScriptFlag.h"

//	------- �Œ�萔�錾

static const u8 FLAG_ON = 1;
static const u8 FLAG_OFF = 0;

//	-------	�}�N����`

//	------- �񋓑�

//	------- �\����&���p��



//	------- �f�[�^�e�[�u��

//	------- �X�^�e�B�b�N�ϐ��錾

//	------- �O���[�o���ϐ��錾

//	------- �X�^�e�B�b�N�v���g�^�C�v�錾(�����֐�)

//	------- �v���g�^�C�v�錾���Ă��Ȃ��X�^�e�B�b�N�֐�(�����֐�)

//	------- �O���[�o���֐�

/*
	�X�N���v�g�t���O������������
	SCRIPT_FLAG_DATA*	flag
*/
void ScriptFlag_Initialize(SCRIPT_FLAG_DATA* flag){
	
	//���ׂẴt���O��0�ɂ���
	for(int i = 0;i < FLAG_DATA_NUM;i++){
		flag->flag[i] = 0;
	}
}

/*
	�t���O�f�[�^�̓ǂݍ��݂��s��
	SCRIPT_FLAG_DATA*	flag
*/
void ScriptFlag_Load(SCRIPT_FLAG_DATA* flag){

	/*
		������

			�������ɂ���
				�f�[�^�����݂��Ă���Ȃ�΃t���O�f�[�^�̓ǂݍ��݂��s��
				�f�[�^�����݂��Ă��Ȃ��Ȃ�Ή������Ȃ��B

			���ǂݍ��݃f�[�^�ɂ���
				�ǂݍ��݃f�[�^�̊g���q�́u.svf�v
				�ǂݍ��݃f�[�^�̃t�@�C�����́uflagments�v
	*/

}

/*
	�t���O�f�[�^�̕ۑ����s��
	SCRIPT_FLAG_DATA*	flag		:
	const char*			path		:�ۑ���̃t�@�C�������܂߂��p�X����͂���(��. data/save/flags)
*/
bool ScriptFlag_Save(SCRIPT_FLAG_DATA* flag,const char* path){
	
	/*
		������

			���ۑ��f�[�^�ɂ���
				�ۑ��f�[�^�̊g���q�́u.svf�v
				�ۑ��f�[�^�̃t�@�C�����́uflagments�v

	*/
	return true;
}

/*
	�w��̃t���O�ԍ����I���ɂ���
	SCRIPT_FLAG_DATA*	flag	:
	s32					index	:�t���O�ԍ�
*/
void ScriptFlag_FlagOn(SCRIPT_FLAG_DATA* flag,s32 index){
	
	//�͈͊O�Ȃ珈���𔲂���
	if(index < 0 || index >= FLAG_DATA_NUM) return ;
	
	flag->flag[index] = FLAG_ON;
}

/*
	�w��̃t���O�ԍ����I�t�ɂ���
	SCRIPT_FLAG_DATA*	flag	:
	s32					index	:�t���O�ԍ�
*/
void ScriptFlag_FlagOff(SCRIPT_FLAG_DATA* flag,s32 index){
	//�͈͊O�Ȃ珈���𔲂���
	if(index < 0 || index >= FLAG_DATA_NUM) return ;
	
	flag->flag[index] = FLAG_OFF;
}

/*
	�w��̃t���O�ԍ��̃t���O��Ԃ�ԋp����(�͈͊O�̏ꍇ�͕K���I�t��ԋp����)
	SCRIPT_FLAG_DATA*	flag	:
	s32					index	:�t���O�ԍ�
	return	0:�t���O�I�t
			1:�t���O�I��
*/
u8 ScriptFlag_GetFlag(SCRIPT_FLAG_DATA* flag,s32 index){
	//�͈͊O�Ȃ珈���𔲂���
	if(index < 0 || index >= FLAG_DATA_NUM) return FLAG_OFF;
	return flag->flag[index];
}
