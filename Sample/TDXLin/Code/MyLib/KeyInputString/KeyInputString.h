/*

	��������͊֌W

*/

#pragma once

#ifdef __WINDOWS__

const int INPUT_STRING_LENGTH = 200;	//���{���100������


enum eKeyInputStringType{
	eKeyInputStringType_All,				//���ׂĂ̕����^�̓��͂�������
	eKeyInputStringType_SingCharOnly,		//���p�����^�̂ݓ��͂�������
	eKeyInputStringType_NumCharOnly,		//�������͂̂݋�����
};

typedef struct{

	int step;
	int cnt;

	int handle;									//��������͗p�n���h��
	eKeyInputStringType	keyInputStringType;		//��������̓^�C�v
	char inputString[INPUT_STRING_LENGTH + 1];	//���͂��ꂽ������
	int inputNumber;							//���͂��ꂽ������󂯎��
	bool isKeyInputActive;						//�������͂��A�N�e�B�u�ɂȂ��Ă��邩�H
	bool isEndKeyInput;							//�������͂��I���������H

	int posX;	//�`����W
	int posY;

}KEY_INPUT_STRING_OBJ;


/*
	��������͂̐���
	int					drawPosX			:�`����WX
	int					drawPosY			:�`����WY
	eKeyInputStringType keyInputStringType	:�������̓^�C�v
*/
extern KEY_INPUT_STRING_OBJ* KeyInputString_Create(int drawPosX,int drawPosY,eKeyInputStringType keyInputStringType);

/*
	�j��
*/
extern void KeyInputString_Destroy(KEY_INPUT_STRING_OBJ* ix);

//------------ ���[�U�[�g�p�֐�

/*
	�������͂��A�N�e�B�u����
	KEY_INPUT_STRING_OBJ* ix
*/
extern void KeyInputString_KeyInputActive(KEY_INPUT_STRING_OBJ* ix);
//------------- �Q�b�^�[�֐�

/*
	�������͂��A�N�e�B�u�ɂȂ��Ă��邩���f����
	KEY_INPUT_STRING_OBJ* ix
	return	true	:�������͂��A�N�e�B�u�ɂȂ��Ă���
			false	:�������͂��A�N�e�B�u�ɂȂ��Ă��Ȃ�
*/
extern bool KeyInputString_GetKeyInputActiveFlag(KEY_INPUT_STRING_OBJ* ix);

/*
	�������͂��I���������ԋp����
	KEY_INPUT_STRING_OBJ* ix
	return	true	:�������͂��I�����Ă���
			false	:�������͂��I�����Ă��Ȃ�
*/
extern bool KeyInputString_IsEndKeyInput(KEY_INPUT_STRING_OBJ* ix);

/*
	���͂����������ԋp����
	KEY_INPUT_STRING_OBJ* ix
	return ���͂���������
*/
extern const char* KeyInputString_GetKeyInputString(KEY_INPUT_STRING_OBJ* ix);

/*
	���͂��������ԋp����
	KEY_INPUT_STRING_OBJ* ix
	return ���͂��������ԋp����
*/
extern int KeyInputString_GetKeyInputNumber(KEY_INPUT_STRING_OBJ* ix);

#endif //__WINDOWS__
