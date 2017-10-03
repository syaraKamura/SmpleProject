/*

	��������͊֌W


!*/


#include "DxLib.h"
#include "KeyInputString.h"
#include "MyLib/Task/Task.h"

#ifdef __WINDOWS__

const int WAIT_TIME = 2;


enum eStep{
	eStep_Init,
	eStep_Main,
	eStep_Exit,
	eStep_ExitDone,
};


/*
	���̃X�e�b�v��ݒ肷��
	KEY_INPUT_STRING_OBJ*	ix
	eStep					step	:���̃X�e�b�v
*/
static void _SetNextStep(KEY_INPUT_STRING_OBJ* ix,eStep step){
	ix->step = step;
	ix->cnt = 0;
}

/*
	�`��
	KEY_INPUT_STRING_OBJ* ix
*/
static void _Draw(KEY_INPUT_STRING_OBJ* ix){

	if(ix->step != eStep_Main) return ;

	//�������͂��I�����Ă��Ȃ��Ȃ�
	if(CheckKeyInput(ix->handle) == 0){
		//���͒��̕�����`�悷��
		DrawKeyInputString( ix->posX , ix->posY , ix->handle );
	}
}

static void _KeyInputProc(KEY_INPUT_STRING_OBJ* ix){

	//�������͂��I�����Ă��Ȃ��Ȃ珈���𔲂���
	if(CheckKeyInput(ix->handle) == 0) return ;
	
	//���͂����������󂯎��
	if(ix->keyInputStringType == eKeyInputStringType_NumCharOnly){
		//���͂��ꂽ������󂯎��
		ix->inputNumber = GetKeyInputNumber(ix->handle);
	}else{
		//���͂�����������󂯎��
		GetKeyInputString(ix->inputString,ix->handle);
	}
	
	//�������͂��A�N�e�B�u�ɂ���
	ix->isKeyInputActive = false;

	//�������͂��I������
	ix->isEndKeyInput = true;

}


/*
	�X�V
	KEY_INPUT_STRING_OBJ* ix
*/
static void _Updata(KEY_INPUT_STRING_OBJ* ix){

	switch(ix->step){
	case eStep_Init:

		_SetNextStep(ix,eStep_Main);
		break;
	case eStep_Main:

		_KeyInputProc(ix);

		break;
	case eStep_Exit:

		if(ix->cnt == 0){
			//��������̓n���h�����J������
			DeleteKeyInput(ix->handle);
			ix->handle = 0;
		}

		ix->cnt ++ ;

		if(ix->cnt > WAIT_TIME){
			Task_KillRequest(ix);
			ix->step = eStep_ExitDone;
		}

		break;
	case eStep_ExitDone:
		break;
	}

}


/*
	��������͂̐���
	int					drawPosX			:�`����WX
	int					drawPosY			:�`����WY
	eKeyInputStringType keyInputStringType	:�������̓^�C�v
*/
KEY_INPUT_STRING_OBJ* KeyInputString_Create(int drawPosX,int drawPosY,eKeyInputStringType keyInputStringType){

	KEY_INPUT_STRING_OBJ* ix = Task_CreateBase(_Updata,_Draw,NULL,KEY_INPUT_STRING_OBJ,eTaskClassType_Class00);

	//�^�X�N�m�ۂ��ł��Ă���Ȃ�
	if(ix != NULL){

		//�������0�ŏ���������
		memset(ix->inputString,0,INPUT_STRING_LENGTH+1);
		
		//���͂������������������
		ix->inputNumber = 0;

		//��������̓^�C�v��ݒ肷��
		ix->keyInputStringType = keyInputStringType;

		if(keyInputStringType == eKeyInputStringType_All){
			//���ׂĂ̕����^�̓��͂��󂯕t����
			ix->handle =  MakeKeyInput(INPUT_STRING_LENGTH,TRUE,FALSE,FALSE);
		}else if(keyInputStringType == eKeyInputStringType_SingCharOnly){
			//���p�����݂̂̓��͂��󂯂���
			ix->handle =  MakeKeyInput(INPUT_STRING_LENGTH,TRUE,TRUE,FALSE);
		}else{
			//�������݂̂̓��͂��󂯂���
			ix->handle =  MakeKeyInput(INPUT_STRING_LENGTH,TRUE,FALSE,TRUE);
		}

		//�`����W��ݒ�
		ix->posX = drawPosX;
		ix->posY = drawPosY;

		//�ŏ��̃X�e�b�v��ݒ肷��
		ix->step = eStep_Init;

		//�J�E���^�[�̏�����
		ix->cnt = 0;

		//�������͂��A�N�e�B�u�łȂ���Ԃɂ���
		ix->isKeyInputActive = false;

		//�������͂��I�����Ă��Ȃ���Ԃɂ���
		ix->isEndKeyInput = false;

		return ix;
	}
	return NULL;
}

/*
	�j��
*/
void KeyInputString_Destroy(KEY_INPUT_STRING_OBJ* ix){
	_SetNextStep(ix,eStep_Exit);
}


//------------ ���[�U�[�g�p�֐�

/*
	�������͂��A�N�e�B�u����
	KEY_INPUT_STRING_OBJ* ix
*/
void KeyInputString_KeyInputActive(KEY_INPUT_STRING_OBJ* ix){
	//�L�[���͂��A�N�e�B�u�ɂ���
	SetActiveKeyInput(ix->handle);

	ix->isKeyInputActive = true;

	//�������͂��I�����Ă��Ȃ���Ԃɂ���
	ix->isEndKeyInput = false;

	//�������0�ŏ���������
	memset(ix->inputString,0,INPUT_STRING_LENGTH+1);

	//���͂������������������
	ix->inputNumber = 0;

}

//------------- �Q�b�^�[�֐�

/*
	�������͂��A�N�e�B�u�ɂȂ��Ă��邩���f����
	KEY_INPUT_STRING_OBJ* ix
	return	true	:�������͂��A�N�e�B�u�ɂȂ��Ă���
			false	:�������͂��A�N�e�B�u�ɂȂ��Ă��Ȃ�
*/
bool KeyInputString_GetKeyInputActiveFlag(KEY_INPUT_STRING_OBJ* ix){
	return ix->isKeyInputActive;
}

/*
	�������͂��I���������ԋp����
	KEY_INPUT_STRING_OBJ* ix
	return	true	:�������͂��I�����Ă���
			false	:�������͂��I�����Ă��Ȃ�
*/
bool KeyInputString_IsEndKeyInput(KEY_INPUT_STRING_OBJ* ix){
	return ix->isEndKeyInput;
}

/*
	���͂����������ԋp����
	KEY_INPUT_STRING_OBJ* ix
	return ���͂���������
*/
const char* KeyInputString_GetKeyInputString(KEY_INPUT_STRING_OBJ* ix){
	return ix->inputString;
}

/*
	���͂��������ԋp����
	KEY_INPUT_STRING_OBJ* ix
	return ���͂��������ԋp����
*/
int KeyInputString_GetKeyInputNumber(KEY_INPUT_STRING_OBJ* ix){
	return ix->inputNumber;
}

#endif //__WINDOWS__
