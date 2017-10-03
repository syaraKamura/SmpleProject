/*
				�t�@�C����		:Script.cpp
				�쐬��			:
				�쐬����		:2017/08/16
				�\�[�X����		:
				
				ADV���Đ����邽�߂̃X�N���v�g�v���O�������L�q���Ă���
				
				���l
				
				������
					
					���X�N���v�g�݌v�ɂ���
					
					���X�N���v�g�̋L�q�K��ɂ���

					���X�N���v�g�̊֐����X�g
						

						�ϐ���`���ł���悤�ɂ���
						�ϐ��̐錾���͕K��0�܂���false�̏�Ԃŏ������s����悤�ɂ���
						�ϐ��̌^ �ϐ��� 

						�ϐ��� = 0 �� �ϐ��� = �ϐ��� + 1�A�ϐ��� = true�@�Ƃ����悤��
						�܂��A�ϐ���1 = �ϐ���1 + �ϐ���2 * 4 / 2 �Ƃ����悤�ȋL�q�ɂ��Ή�������
						�������A�ϐ��͐����݂̂���������x�̂��̂��쐬����

						�Z�ϐ��̌^
							FLAG	:TRUE , FALSE ��2�l�݂̂�������@
							INTEGER	�������������Ƃ��ł���

						�Z�ϐ��̒�`�ɂ���
							FLAG isFlag
							INTEGER inInteger

						�Z�����ł̓���
							�v���O���������ł�List�Ő錾�����ϐ���ێ�����
							�錾���ɓ������O�̕ϐ������錾���ꂽ�ꍇ�̓G���[�Ƃ݂Ȃ�
							�X�N���v�g�̍Đ����I��������ێ������ϐ��̃f�[�^�͂��ׂĊJ������





						�L�q�ɑΉ����邱�Ƃ��ł���悤�ɍ쐬����


						��������`��
						MES	���b�Z�[�W						:���b�Z�[�W�̕`��
						TOLK �L�����N�^�[�� �b�����t		:�L�����N�^�[���b���Ă��邱�Ƃ�`�悷��
						
						���V�X�e���n
						IF	������							:������
						ELSEIF								:
						ENDIF								:
						GOTO ���x����						:�w��̃��x����T�����ă��x���̈ʒu�Ɉړ�����
						LABEL ���x����						:���x��
						FLAGS ID							:�w��̔ԍ��̃t���O���擾����


						�����\�[�X�ǂݍ���
						LOADGRAPHICS �t�@�C���� ID			:�摜�̓ǂݍ���
						DRAWGRAPHICS ID X���W Y���W			:�摜�̕`��
						DELETEGRAPHICS ID					:�摜���폜����
						LOADSOUND �t�@�C���� SoundType ID	:�T�E���h�̓ǂݍ���
						PLAYSOUDN ID						:�T�E���h�̍Đ�
						STOPSOUND ID						:�T�E���h���~�߂�
						DELETESOUND ID						:�T�E���h���폜����

						���L�����N�^�[�̈ړ�����
						MOVEPOSX ID �ړ���					:�w��ID�̃L�����N�^�[���ړ��ʂ���X�����ֈړ�������
						MOVEPOSY ID	�ړ���					:�w��ID�̃L�����N�^�[���ړ��ʂ���Y�����ֈړ�������




					����邱�ƃ��X�g
						
						


				
				
!*/

//	------- �C���N���[�h�錾
#include "Common/GameCommon/GameCommon.h"
#include "ScriptFlag.h"
#include "ScriptVariable.h"
#include "Script.h"


//	------- �Œ�萔�錾

const int SCRIPT_MAX_LINE = 1024;	//�X�N���v�g�̓ǂݍ��ݍő�s
const int SCRIPT_MAX_LENGTH = 256;	//�X�N���v�g�̓ǂݍ��ݍő啶����

const int WAIT_TIME = 2;

//	-------	�}�N����`

//	------- �񋓑�

enum eStep{
	eStep_Init,
	eStep_SetUp,
	eStep_Main,
	eStep_Exit,
	eStep_ExitDone,
};

//	------- �\����&���p��



typedef struct{
	VARIABLE_DATA* pFunction;							//���X�g������
	char script[SCRIPT_MAX_LINE][SCRIPT_MAX_LENGTH];	//�X�N���v�g
	int line;											//���݂̍s
	int maxLine;										//�ő�s��
	char fileName[SCRIPT_MAX_LENGTH];					//�t�@�C����
}SCRIPT_DATA;

typedef struct{
	SCRIPT_DATA* pScriptData;	//�X�N���v�g�f�[�^

	eStep step;					//���s�X�e�b�v
	int waitCnt;				//�҂�����
	
}SCRIPT_OBJ;

//	------- �f�[�^�e�[�u��

//	------- �X�^�e�B�b�N�ϐ��錾

static SCRIPT_OBJ* s_pHdl;

//	------- �O���[�o���ϐ��錾

//	------- �X�^�e�B�b�N�v���g�^�C�v�錾(�����֐�)

//	------- �v���g�^�C�v�錾���Ă��Ȃ��X�^�e�B�b�N�֐�(�����֐�)

/*
	���̃X�e�b�v��ݒ肷��
*/
void _SetNextStep(SCRIPT_OBJ* ix,eStep step){
	ix->waitCnt = 0;
	ix->step = step;
}

/*
	�X�V����
	SCRIPT_OBJ*		ix
*/
void _Updata(SCRIPT_OBJ* ix){

	switch(ix->step){
	case eStep_Init:

		_SetNextStep(ix,eStep_SetUp);
		break;
	case eStep_SetUp:

		_SetNextStep(ix,eStep_Main);
		break;
	case eStep_Main:

		break;
	case eStep_Exit:

		if(ix->waitCnt == 0){

		}

		ix->waitCnt ++;

		if(ix-> waitCnt > WAIT_TIME){

			Task_KillRequest(ix);
			_SetNextStep(ix,eStep_Exit);
		}

		break;
	case eStep_ExitDone:
		s_pHdl = NULL;
		break;
	}

}

/*
	�`�揈��
	SCRIPT_OBJ*		ix
*/
void _Draw(SCRIPT_OBJ* ix){

	//���C���X�e�b�v�łȂ���Ώ����𔲂���
	if(ix->step != eStep_Main) return ;


}

//	------- �O���[�o���֐�

/*
	�X�N���v�g�����̐���
	s32		scriptIdx	:�Đ�����X�N���v�g�ԍ�
*/
void Script_Creata(s32 scriptIdx){

	SCRIPT_OBJ* ix = Task_CreateBase(_Updata,_Draw,NULL,SCRIPT_OBJ,eTaskClassType_Class00);

	if(ix != NULL){
		
	
		s_pHdl = ix;
	}

}

/*
	�I���������H
	return	true	:���s�I������
			false	:���s��
*/
bool Script_IsEnd(){
	if(s_pHdl){
		return false;
	}else{
		return true;
	}
}
