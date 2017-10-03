#include "Common/GameCommon/GameCommon.h"

#include "../Scene.h"
#include "Title.h"

const int CRSOL_MOVE_TIME = 20;	//カーソルが移動にかかる時間
const int MOVE_DISTANCE_Y = 40;	//移動距離(項目間の距離)

typedef struct{
	int cnt;
	float posY;			//◆の描画Y座標
	int distanceY;		//Y座標の移動距離
	float oldPosY;		//前回のY座標
	int crsolMoveCnt;	//カーソル移動用カウント
	bool crsolMoveFlag;	//カーソルが移動しているか？
	int select;			//選択
}WORK_OBJ;

static WORK_OBJ* s_pWork;

static void _Updata(WORK_OBJ* ix){

#ifdef __MY_DEBUG__
	ix->cnt++;
#endif
	
	//カーソルが移動中は入力を受け付けない
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
				//キーコンフィグ
			}
			else if(ix->select == 2){
				//ゲーム終了
#ifdef __MY_DEBUG__
				Scene_Change(eSceneId_TestMenu);	//テストメニューへ移動
#endif
			}
		}
	}
	//カーソルが移動中
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

		
	DrawString(240,(int)ix->posY,"◆",GetColor(255,255,255));
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