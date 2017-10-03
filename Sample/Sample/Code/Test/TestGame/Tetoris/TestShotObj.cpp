#include "Common/GameCommon/GameCommon.h"
#include "Common/CommonRes/CommonRes.h"

#include "TestShotObj.h"

const int WAIT_TIME = 2;

enum eStep{
	eStep_Init,
	eStep_Main,
	eStep_Exit,
	eStep_ExitDone,

	eStep_None,

};

typedef struct{
	int posX;			//X座標
	int posY;			//Y座標
	GRAPHICS_RES res;	//画像
	int step;
	int cnt;
	int pad;			//パディング
}TEST_SHOT_OBJ;			//24byte


static void _SetNextStep(TEST_SHOT_OBJ* ix,eStep step){
	ix->step = step;
	ix->cnt = 0;
}

//移動処理
static eStep _MoveProc(TEST_SHOT_OBJ* ix){
	eStep ret = eStep_None;

	//ix->posY -= 8;
	ix->cnt ++;
	if(ix->cnt > 60 * 3){
	//if(ix->posX > WINDOW_WIDTH || ix->posX < 0 ||
	//	ix->posY > WINDOW_HEIGHT || ix->posY < -32){
			ret = eStep_Exit;
	}
	
	return ret;
}


static void _Updata(TEST_SHOT_OBJ* ix){

	eStep ret = eStep_None;

	switch(ix->step){
	case eStep_Init:
		ix->cnt ++;
		if(ix->cnt > WAIT_TIME){
			_SetNextStep(ix,eStep_Main);
		}
		break;
	case eStep_Main:
		ret = _MoveProc(ix);
		if(ret != eStep_None){
			_SetNextStep(ix,ret);
		}

		break;
	case eStep_Exit:
		if(ix->cnt == 0){
			//Graphics_Delete(&ix->res);
		}
		ix->cnt ++;
		if(ix->cnt > WAIT_TIME){
			Task_KillRequest(ix);
			_SetNextStep(ix,eStep_ExitDone);
		}
		break;
	case eStep_ExitDone:
		break;
	}

}

static void _Draw(TEST_SHOT_OBJ* ix){
	//メインステップでなければ処理を抜ける
	if(ix->step != eStep_Main) return ;

	//if(ix->res){
		Graphics_Draw(ComRes_GetGraphics(eComResID_IMG_SHOT),ix->posX,ix->posY,TRUE);
	//}
}

static void _Del(TEST_SHOT_OBJ* ix){
	//ix = NULL;
}

//生成
void TestShotObj_Create(int posX,int posY){
	
	TEST_SHOT_OBJ* ix = Task_CreateBase(_Updata,_Draw,_Del,TEST_SHOT_OBJ,eTaskClassType_Class00);
	ASSERT_MES(ix != NULL,"メモリの確保に失敗",ix);
	if(ix != NULL){
		
		//ix->res = ComRes_GetGraphics(eComResID_IMG_SHOT);

		//Graphics_Load(&ix->res,"Data/Graphic/Common/shot.png");

		ix->posX = posX;
		ix->posY = posY;
		
		ix->cnt = 0;
		ix->step = eStep_Init;

		ix->pad = 0;

	}
}
