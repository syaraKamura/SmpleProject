/*
				�t�@�C����		:Touch.cpp
				�쐬��			:
				�쐬����		:
				�\�[�X����		:
				
				
				���l
				
				
				
!*/

//	------- �C���N���[�h�錾
#include "DxLib.h"

#include "Touch.h"

//	------- �Œ�萔�錾
const int TOUCH_MAX_NUM = 10;		//�^�b�`�f�[�^�̍ő吔
//	-------	�}�N����`

//	------- �񋓑�

//	------- �\����&���p��


typedef struct {
	int touchNum;	//�^�b�`��
	TOUCH_DATA touchData[TOUCH_MAX_NUM];
}TOUCH_MGR;

//	------- �f�[�^�e�[�u��

//	------- �X�^�e�B�b�N�ϐ��錾
static TOUCH_MGR s_touch;
//	------- �O���[�o���ϐ��錾

//	------- �X�^�e�B�b�N�v���g�^�C�v�錾(�����֐�)

//	------- �v���g�^�C�v�錾���Ă��Ȃ��X�^�e�B�b�N�֐�(�����֐�)

static int _TouchProc() {
	
	s_touch.touchNum = GetTouchInputNum();

	if (s_touch.touchNum >= TOUCH_MAX_NUM) {
		s_touch.touchNum = TOUCH_MAX_NUM;
	}

	for (int i = 0; i < TOUCH_MAX_NUM; i++) {
		TOUCH_DATA* touch = &s_touch.touchData[i];
		if (GetTouchInput(i, &touch->posX, &touch->posY, NULL, &touch->device) == 0) {
			touch->id = i;
		}
		else {
			touch->id = -1;
		}
	}

	for (int i = 0; i < TOUCH_MAX_NUM; i++) {
		TOUCH_DATA* touch = &s_touch.touchData[i];
		if (touch->id == i) {
			touch->touchCnt++;
		}
		else {
			touch->touchCnt = 0;
			touch->posX = 0;
			touch->posY = 0;
			touch->oldPosX = 0;
			touch->oldPosY = 0;
			touch->releseCnt = 0;
		}
	}

#if 0
#ifdef __MY_DEBUG__
	printfDx("TouchNum:%d\n", s_touch.touchNum);
	
	for (int i = 0; i < TOUCH_MAX_NUM; i++) {
		TOUCH_DATA* touch = &s_touch.touchData[i];
		printfDx("ID:%d device:%d posX:%d posY:%d cnt:%d\n", touch->id, touch->device, touch->posX, touch->posY, touch->touchCnt);
	}
#endif // __MY_DEBUG__
#endif // 0
	return 0;
}

//	------- �O���[�o���֐�

/*
	�^�b�`���Ă��鐔�𐔂���
*/
int Touch_GetTouchNum() {
	return s_touch.touchNum;
}

/*
	�^�b�`���Ă���
	int		num	:�^�b�`�ԍ�
	return	true	:�^�b�`���Ă���
			false	:�^�b�`���Ă��Ȃ�
*/
bool Touch_On(int num) {
	return s_touch.touchData[num].touchCnt > 0;
}

/*
	�^�b�`���Ă��Ȃ�
	int		num	:�^�b�`�ԍ�
	return	true	:�^�b�`���Ă��Ȃ�
			false	:�^�b�`���Ă��Ă���
*/
bool Touch_Off(int num) {
	return s_touch.touchData[num].touchCnt > 0;
}

/*
	�X�N���[�����^�b�`���ꂽ
	int		num		:�^�b�`�ԍ�
	return	true	:�^�b�`���ꂽ
			false	:�^�b�`����Ă��Ȃ�
*/
bool Touch_Press(int num) {
	return s_touch.touchData[num].touchCnt == 1;
}

/*
	�X�N���[�����^�b�`���ꑱ���Ă���
	int		num		:�^�b�`�ԍ�
	return	true	:�^�b�`���ꂽ
			false	:�^�b�`����Ă��Ȃ�
*/
bool Touch_Repeat(int num) {
	return s_touch.touchData[num].touchCnt > 0 && s_touch.touchData[num].touchCnt % 20 == 0;
}

/*
	�X�N���[������w�������ꂽ
	int		num		:�^�b�`�ԍ�
	return	true	:�w�������ꂽ
			false	:�^�b�`����Ă���
*/
bool Touch_Relese(int num) {

	if (s_touch.touchData[num].touchCnt > 0) {
		s_touch.touchData[num].releseCnt = 0;
	}
	else {
		s_touch.touchData[num].releseCnt ++;
	}

	return s_touch.touchData[num].releseCnt == 1;
}

/*
	�t���b�N���삳�ꂽ��(�㉺)
	int		num		:�^�b�`�ԍ�
	return	0		:�t���b�N����Ă��Ȃ�
			1�ȏ�	:������Ƀt���b�N���ꂽ
			-1�ȉ�	:�������Ƀt���b�N���ꂽ
*/
int Touch_FulickUpDown(int num) {

	TOUCH_DATA* touch = &s_touch.touchData[num];

	int dir = 0;

	if (Touch_Press(num) == true) {
		touch->oldPosY = touch->posY;
	}
	else if (Touch_Relese(num) == true) {

		dir = touch->oldPosY - touch->posY;

	}

	return dir;

}

/*
	�t���b�N���삳�ꂽ��(���E)
	int		num		:�^�b�`�ԍ�
	return	0		:�t���b�N����Ă��Ȃ�
	1�ȏ�	:�������Ƀt���b�N���ꂽ
	-1�ȉ�	:�E�����Ƀt���b�N���ꂽ
*/
int Touch_FulickLeftRight(int num) {

	TOUCH_DATA* touch = &s_touch.touchData[num];

	int dir = 0;

	if (Touch_Press(num) == true) {
		touch->oldPosX = touch->posX;
	}
	else if (Touch_Relese(num) == true) {

		dir = touch->oldPosX - touch->posX;

	}
	return dir;
}

/*
	�w��̃^�b�`�ԍ��̃f�[�^��ԋp����
	int num	:�^�b�`�ԍ�
	return TOUCH_DATA�|�C���^�ϐ�
*/
const TOUCH_DATA* Touch_GetParamData(int num){
	const TOUCH_DATA* touch = &s_touch.touchData[num];
	return touch;
}


/*
	�^�b�`�p�b�h�G�~�����[�^�̏�����
*/
void TouchPadEmuletor_Initialize(){
	
	//�V�X�e���Ńp�b�h�����g�p����ݒ�Ȃ��,�������������s��

	//�摜�̓ǂݍ���

	//�摜���Ȃ����BOX�̕`�������悤�ɐݒ肷��

}

/*
	�^�b�`�p�b�h�G�~�����[�^�̏I������
*/
void TouchPadEmuletor_Finalize(){

	//�V�X�e���Ńp�b�h�����g�p����ݒ�Ȃ��,�������������s��

	//�摜�̍폜

	//�摜���Ȃ����BOX�̍폜�������s��Ȃ�


}

/*
	�^�b�`�p�b�h�G�~�����[�^�̍X�V����
*/
void TouchPadEmuletor_Updata(){

	//�V�X�e���Ńp�b�h�����g�p����ݒ�Ȃ��,�X�V�������s��


	//�^�b�`�����̍X�V

}

/*
	�^�b�`�p�b�h�G�~�����[�^�̕`�揈��
*/
void TouchPadEmuletor_Draw(){

	//�V�X�e���Ńp�b�h�����g�p����ݒ�Ȃ��,�摜�`����s��


	//�摜���Ȃ����BOX��`�悷��


}


/*
	�^�b�`�����̍X�V
*/
void Touch_Updata() {
	_TouchProc();
}

