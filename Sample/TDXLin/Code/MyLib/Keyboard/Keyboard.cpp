#include "DxLib.h"
#include "Keyboard.h"

//-------------------------- �Œ�萔
static const int KEY_MAX_NUM = 256;
static const int PAD_MAX_NUM = 32;

//-------------------------- �X�^�e�B�b�N�ϐ���`
static int s_ReleseCount[KEY_MAX_NUM] = {0};	//�L�[���J������Ă���ԃJ�E���g����
static int s_KeyInputCount[KEY_MAX_NUM];		//�L�[��������Ă���ԃJ�E���g����


/*
	�L�[���͂����͂���Ă��鎞�Ԃ�ԋp����
	int		keyCode	:���͂��Ă���L�[�R�[�h�ԍ�
*/
static int _CheckHitKey(int keyCode){
	return s_KeyInputCount[keyCode];
}

/*
	�L�[�����͂���Ă���
	return	true	:	�L�[�����͂���Ă���
			false	:	�L�[�����͂���Ă��Ȃ�
*/
bool Keyboard_On(int keyCode){
	return _CheckHitKey(keyCode) > 0;
}

/*
	�L�[�����͂���Ă��Ȃ�
	return	true	:�L�[�����͂���Ă��Ȃ�
			false	:�L�[�����͂���Ă���
*/
bool Keyboard_Off(int keyCode){
	return _CheckHitKey(keyCode) == 0;
}

/*
	�L�[���J�����ꂽ
	return	true	:�L�[���J�����ꂽ
			false	:�L�[���J������Ă��Ȃ�
*/
bool Keyboard_Relese(int keyCode){
	if(_CheckHitKey(keyCode) > 0){
		s_ReleseCount[keyCode] = 0;
		return false;
	}
	s_ReleseCount[keyCode]++;
	return  s_ReleseCount[keyCode] == 1;
}

/*
	�L�[�����s�[�g����Ă���
	return	true	:�L�[��������Ă���
			false	:�L�[��������Ă��Ȃ�
*/	
bool Keyboard_Repeat(int keyCode){
	return _CheckHitKey(keyCode) == 1 || (_CheckHitKey(keyCode) > 4 && _CheckHitKey(keyCode) % 20 == 0);
}

/*
	�L�[��������Ă���
	return	true	:�L�[�������ꂽ
			false	:�L�[��������Ă��Ȃ�
*/
bool Keyboard_Press(int keyCode){
	return _CheckHitKey(keyCode) == 1;
}



/*
	�L�[���͍X�V
*/
void Keyboard_Updata(){

	char key[KEY_MAX_NUM] = {};
	GetHitKeyStateAll(key);

	for(int i = 0;i < KEY_MAX_NUM;i++){
		if(key[i] != 0){
			s_KeyInputCount[i]++;
		}else{
			s_KeyInputCount[i] = 0;
		}
	}
}