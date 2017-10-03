#include "Common/GameCommon/GameCommon.h"

#include "../Scene.h"
#include "Title.h"

const int CRSOL_MOVE_TIME = 20;	//�J�[�\�����ړ��ɂ����鎞��
const int MOVE_DISTANCE_Y = 40;	//�ړ�����(���ڊԂ̋���)

typedef struct{
	int cnt;
	float posY;			//���̕`��Y���W
	int distanceY;		//Y���W�̈ړ�����
	float oldPosY;		//�O���Y���W
	int crsolMoveCnt;	//�J�[�\���ړ��p�J�E���g
	bool crsolMoveFlag;	//�J�[�\�����ړ����Ă��邩�H
	int select;			//�I��
}WORK_OBJ;

static WORK_OBJ* s_pWork;

static void _Updata(WORK_OBJ* ix){

#ifdef __MY_DEBUG__
	ix->cnt++;
#endif
	
	//�J�[�\�����ړ����͓��͂��󂯕t���Ȃ�
	if(ix->crsolMoveFlag == false){
		if(Keyboard_Press(KEY_INPUT_UP)){
			if(ix->select > 0){
				ix->select --;
				ix->distanceY = -MOVE_DISTANCE_Y;	
				ix->crsolMoveCnt = 0;
				ix->crsolMoveFlag = true;
			}
		}else if(Keyboard_Press(KEY_INPUT_DOWN)){
			if(ix->select < 2){
				ix->select ++;
				ix->distanceY = MOVE_DISTANCE_Y; 
				ix->crsolMoveCnt = 0;
				ix->crsolMoveFlag = true;
			}
		}

		if(Keyboard_Press(KEY_INPUT_Z)){
			if(ix->select == 0){
				Scene_Change(eSceneId_GameMain);
			}
			else if(ix->select == 1){
				//�L�[�R���t�B�O
			}
			else if(ix->select == 2){
				//�Q�[���I��
#ifdef __MY_DEBUG__
				Scene_Change(eSceneId_TestMenu);	//�e�X�g���j���[�ֈړ�
#endif
			}
		}
	}
	//�J�[�\�����ړ���
	else {

		ix->posY = ix->oldPosY + sin(DX_PI_F/2/CRSOL_MOVE_TIME * ix->crsolMoveCnt) * ix->distanceY;
		
		if(ix->crsolMoveCnt < CRSOL_MOVE_TIME){
			ix->crsolMoveCnt++;
		}else{
			ix->oldPosY = ix->posY;
			ix->crsolMoveFlag = false;
		}
		
	}


}

static void _Draw(WORK_OBJ* ix){

	#ifdef __MY_DEBUG__
	DrawString(0,0,"X Key To Back",GetColor(255,255,255));
	DrawFormatString(0,20,GetColor(255,255,255),"cnt:%d",ix->cnt);
#endif

		
	DrawString(240,(int)ix->posY,"��",GetColor(255,255,255));
	DrawString(300,200,"Login",GetColor(255,255,255));
	DrawString(300,240,"Key Config",GetColor(255,255,255));
	DrawString(300,280,"Exit",GetColor(255,255,255));

}

void Title_Init(){

	WORK_OBJ* ix = (WORK_OBJ*)Memory_Alloc(sizeof(WORK_OBJ));

	if(ix != NULL){

		ix->cnt = 0;
		ix->posY = 200;
		ix->distanceY = MOVE_DISTANCE_Y;
		ix->oldPosY = ix->posY;
		ix->select = 0;
		ix->crsolMoveCnt = 0;
		ix->crsolMoveFlag = false;
		s_pWork = ix;
	}

}

void Title_Updata(){

	_Updata(s_pWork);

}

void Title_Draw(){

	_Draw(s_pWork);

}

void Title_Finalize(){

	Memory_SafeFree(s_pWork);

}