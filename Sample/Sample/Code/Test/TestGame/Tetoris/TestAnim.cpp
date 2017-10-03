
#include "TestAnim.h"

const int WAIT_CNT = 2;		//遅延カウンタ

enum {
	eStep_Init,
	eStep_Main,
	eStep_Exit,
	eStep_ExitDone,
};

static void _SetNextStep(TEST_ANIM_OBJ* ix,int step){
	ix->cnt = 0;
	ix->step = step;
}

static void _AnimIn(TEST_ANIM_OBJ* ix){
	if(ix->cnt == 0){
		ix->posX = WINDOW_WIDTH;
		ix->posY = 0;
	}

	if(ix->cnt < 60){

		//ix->posX = (int)Easing(eEasingType_Circular,eEasingInOut_Out,(float)ix->cnt,60.0f,(float)0.0f,(float)Graphics_GetWidth(ix->res));
		ix->posX -= Graphics_GetWidth(ix->res) / 60;
	}
	ix->cnt++;

}

static void _AnimOut(TEST_ANIM_OBJ* ix){
	if(ix->cnt < 60){
		ix->posX += WINDOW_WIDTH / 60;
	}
	ix->cnt++;
}

static void _AnimRandomMove(TEST_ANIM_OBJ* ix){

	if(ix->cnt % 60 == 0){
		ix->dir = GetRand(3);
	}

	switch(ix->dir){
	case 0:
		if(ix->posX < WINDOW_WIDTH - Graphics_GetWidth(ix->res)){
			ix->posX += 4;
			ix->rot = DX_PI / 2;
		}
		break;
	case 1:
		if(ix->posX > 0){
			ix->posX -= 4;
			ix->rot = -(DX_PI / 2);
		}
		break;
	case 2:
		if(ix->posY < WINDOW_HEIGHT - Graphics_GetHeight(ix->res)){
			ix->posY += 4;
			ix->rot = DX_PI;
		}
		break;
	case 3:
		if(ix->posY > 0){
			ix->posY -= 4;
			ix->rot = 0;
		}
		break;
	}

	ix->cnt++;
}

void _AnimRot(TEST_ANIM_OBJ* ix){
	ix->rot += 0.1;
}

static void _AnimProc(TEST_ANIM_OBJ* ix){

	void (*animTbl[])(TEST_ANIM_OBJ*)={
		_AnimIn,
		_AnimOut,
		_AnimRot,
		_AnimRandomMove,
	};


	if(animTbl[ix->anim] != NULL){
		animTbl[ix->anim](ix);
	}

#if 0
	switch(ix->anim){
	case eAnimKind_In:
		_AnimIn(ix);
		break;
	case eAnimKind_Out:
		_AnimOut(ix);
		break;
	case eAnimKind_Rot:
		ix->rot += 0.1;
		break;
	case eAnimKind_RandomMove:
		_AnimRandomMove(ix);
		break;
	}
#endif

}

static void _Updata(TEST_ANIM_OBJ* ix){

	switch(ix->step){
	case eStep_Init:
		_SetNextStep(ix,eStep_Main);
		break;
	case eStep_Main:

		_AnimProc(ix);

		break;
	case eStep_Exit:

		if(ix->cnt == 0){
			Graphics_Delete(&ix->res);
		}
		ix->cnt++;

		if(ix->cnt > WAIT_CNT){
			ix->step =	eStep_ExitDone;
		}

		break;
	case eStep_ExitDone:
		Task_KillRequest(ix);
		break;
	}

}

static void _Draw(TEST_ANIM_OBJ* ix){
	
	if(ix->step != eStep_Main) return ;

	int width = Graphics_GetWidth(ix->res);
	int height = Graphics_GetHeight(ix->res);
	Graphics_DrawBase(&ix->res,ix->posX,ix->posY,0,0,width,height,width/2,height/2,ix->scal,ix->rot,TRUE,FALSE);

}

//----------------------- 設定関数 -----------------------

//アニメーションを変更する
void TestAnimObj_ChangeAnim(TEST_ANIM_OBJ* ix,eAnimKind anim){
	ix->anim = anim;
	ix->cnt = 0;
}

//座標を設定する
void TestAnimObj_SetPosition(TEST_ANIM_OBJ* ix,int posX,int posY){
	ix->posX = posX;
	ix->posY = posY;
}


//--------------------　タスクの生成　---------------------

/*
アニメションの生成
	
	@pram fileName	:	読み込む画像のパス
	@pram PosX		:	X座標
	@pram PosY		:	Y座標
	@pram Scal		:	サイズ
	@pram rot		:	角度
	@pram anim		:	アニメーションの種類
	


	@return	
*/
TEST_ANIM_OBJ* TestAnimObj_Create(const char* fileName,int posX,int posY,double scal,double rot,eAnimKind anim){

	TEST_ANIM_OBJ* ix = Task_CreateBase(_Updata,_Draw,NULL,TEST_ANIM_OBJ,eTaskClassType_Class08);
	
	if(ix != NULL){

		Graphics_Load(&ix->res,fileName);

		ix->posX = posX;
		ix->posY = posY;
		ix->rot = rot;
		ix->scal = scal;
		ix->anim = anim;
		ix->cnt = 0;
		ix->dir = 0;
		ix->step = eStep_Init;
		return ix;
	}

	return NULL;
}

//アニメーションの削除
void TestAnimObj_Destroy(TEST_ANIM_OBJ* ix){
	_SetNextStep(ix,eStep_Exit);
}

