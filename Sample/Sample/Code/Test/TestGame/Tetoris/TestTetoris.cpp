/*!

		☆メモ

			テトリス仕様について


			フィールド


			ブロック

			ブロックの回転

			ブロックのあたり判定

			ブロックの揃った判定

			ブロックの消滅処理

			ゲームオーバー処理



*/


#include "Common/GameCommon/GameCommon.h"
#include "Common/CommonRes/CommonRes.h"

#include "TestAnim.h"
#include "TestShotObj.h"

#include "TestTetoris.h"

const int BLOCK_WIDHT = 5;
const int BLOCK_HEIGHT = 5;
const int BLOCK_SIZE = BLOCK_WIDHT * BLOCK_HEIGHT;

const int FIELD_HEIGHT = 21;
const int FIELD_WIDHT = 12;

enum eFiled{
	eFiled_Space,
	eFiled_Wall = 99,
};

enum eStep{
	eStep_Init,
	eStep_Main,
	eStep_Exit,
	eStep_ExitDone,
};

typedef struct{
	int block[BLOCK_SIZE];
}BLOCK_DATA_TBL;


typedef struct{
	GRAPHICS_RES* pGraph;
	TEST_ANIM_OBJ* pAnimObj[4];
	int graphPosY;
	int posX;
	int posY;
	int field[FIELD_HEIGHT][FIELD_WIDHT];			//フィールドデータ
	int bufferField[FIELD_HEIGHT][FIELD_WIDHT];	//一時記憶用フィールド
	BLOCK_DATA_TBL block;
	int blockKind;
	eStep step;
	int waitCnt;
	int mdelHdl;
	int animHdl;
	int attactIdx;
	f32 toalTime;
	f32 playTime;
}WORK_OBJ;

static WORK_OBJ* s_pWork;

const BLOCK_DATA_TBL s_BlockTbl[] = {

	{
		0,0,0,0,0,
		0,0,1,0,0,
		0,1,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0,
	},

	{
		0,0,0,0,0,
		0,1,0,0,0,
		0,1,0,0,0,
		0,1,1,0,0,
		0,0,0,0,0,
	},

	{
		0,0,0,0,0,
		0,0,0,1,0,
		0,0,0,1,0,
		0,0,1,1,0,
		0,0,0,0,0,
	},

	{
		0,0,0,0,0,
		0,1,1,0,0,
		0,0,1,1,0,
		0,0,0,0,0,
		0,0,0,0,0,
	},

	{
		0,0,0,0,0,
		0,0,1,1,0,
		0,1,1,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
	},

	{
		0,0,0,0,0,
		0,1,1,0,0,
		0,1,1,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
	},

	{
		0,0,0,0,0,
		0,0,0,0,0,
		1,1,1,1,1,
		0,0,0,0,0,
		0,0,0,0,0,
	},
};

static void _AnimProc(WORK_OBJ* ix){

	if(ix->playTime >= ix->toalTime){
		return ;
	}

	ix->playTime +=1.0f;

	MV1SetAttachAnimTime(ix->mdelHdl,ix->attactIdx,ix->playTime);


}

static eStep _MainProc(WORK_OBJ* ix){

	if(Keyboard_Press(KEY_INPUT_X)){
		ix->waitCnt = 0;
		return eStep_Exit;
	}
	
	if(Keyboard_Press(KEY_INPUT_Z)){
		TestAnimObj_ChangeAnim(ix->pAnimObj[0],eAnimKind_In);
	}

	if(Keyboard_Press(KEY_INPUT_A)){
		TestAnimObj_ChangeAnim(ix->pAnimObj[0],eAnimKind_Out);
	}

	if(Keyboard_Press(KEY_INPUT_Q)){
		TestAnimObj_SetPosition(ix->pAnimObj[0],100,100);
		TestAnimObj_ChangeAnim(ix->pAnimObj[0],eAnimKind_Rot);
	}

	if(Keyboard_Press(KEY_INPUT_W)){
		TestAnimObj_ChangeAnim(ix->pAnimObj[0],eAnimKind_RandomMove);
	}

	if(Keyboard_Repeat(KEY_INPUT_C)){
		for(int i = 0;i < 5;i++)
		TestShotObj_Create(GetRand(630),GetRand(450));
	}

	if(Keyboard_Press(KEY_INPUT_SPACE)){
		ix->playTime = 0.0f;
	}


	_AnimProc(ix);

	int posY = ix->posY;
	int blockKind = ix->blockKind;

	ix->graphPosY = ix->graphPosY > WINDOW_HEIGHT ? 0 : ix->graphPosY + 10;

	int x = 3+BLOCK_WIDHT/2;
	int y = posY+BLOCK_HEIGHT/2+1;

	if(ix->field[y][x] > eFiled_Space){
		ix->posY = 0;
		for(int i = 0;i < FIELD_HEIGHT;i++){
			for(int j = 1;j < FIELD_WIDHT-1;j++){
				ix->bufferField[i][j] = ix->field[i][j];
			}
		}
		ix->blockKind = GetRand(3);
		return eStep_Main;
	}

	for(int i = 0;i < FIELD_HEIGHT;i++){
		for(int j = 0;j < FIELD_WIDHT;j++){
			ix->field[i][j] = ix->bufferField[i][j];
		}
	}

	for(int i = 0;i < BLOCK_HEIGHT;i++){
		for(int j = 0;j < BLOCK_WIDHT;j++){
			if(s_BlockTbl[blockKind].block[j + i * BLOCK_WIDHT] != 0){
				if(ix->field[i+posY][j+3] == eFiled_Space){
					ix->field[i+posY][j+3] += s_BlockTbl[blockKind].block[j + i * BLOCK_WIDHT]; 
				}
			}
		}
	}
	


	if(ix->waitCnt % 60 == 0){	
		ix->posY++;
	}

	ix->waitCnt++;

	return eStep_Main;
}

static void _Updata(WORK_OBJ* ix){
	
	switch(ix->step){

	case eStep_Init:
		ix->step = eStep_Main;
		break;
	case eStep_Main:

		ix->step = _MainProc(ix);

		break;
	case eStep_Exit:
		
		if(ix->waitCnt == 0){
			for(int i = 0;i < 4;i++){
				if(ix->pAnimObj[i] != NULL){
					TestAnimObj_Destroy(ix->pAnimObj[i]);
					ix->pAnimObj[i] = NULL;
				}
			}
			MV1DeleteModel(ix->mdelHdl);
			MV1DeleteModel(ix->animHdl);
		}
		ix->waitCnt++;
		if(ix->waitCnt > 2){
			ix->step = eStep_ExitDone;
		}
		break;
	case eStep_ExitDone:
		Task_KillRequest(ix);
		break;
	}

}

static void _Draw(WORK_OBJ* ix){

	if(ix->step != eStep_Main) return ;

	for(int i = 0;i < FIELD_HEIGHT;i++){
		for(int j = 0;j < FIELD_WIDHT;j++){
			if(ix->field[i][j] == eFiled_Wall){
				DrawString(j * 20,i * 20,"■",GetColor(255,255,255));
			}else if(ix->field[i][j] == eFiled_Space){
				DrawString(j * 20,i * 20,"□",GetColor(255,255,255));
			}else{
				DrawString(j * 20,i * 20,"☆",GetColor(255,255,255));
			}
		}
	}
	
	Graphics_Draw(ix->pGraph,ix->posX,ix->graphPosY,TRUE);

	DrawFormatString(300,10,GetColor(255,255,255),"starPosY:%d",ix->graphPosY);

	DrawString(300,30,"Zキー:INアニメーション",GetColor(255,255,255));
	DrawString(300,50,"Aキー:Outアニメーション",GetColor(255,255,255));
	DrawString(300,70,"Qキー:回転アニメーション",GetColor(255,255,255));
	DrawString(300,90,"Wキー:ランダム移動",GetColor(255,255,255));


	MV1SetPosition( ix->mdelHdl, VGet( 320.0f, 0.0f, 600.0f ) ) ;
	MV1DrawModel(ix->mdelHdl);
	VECTOR pos = MV1GetPosition(ix->mdelHdl);
	DrawFormatString(0,0,COLOR_RED,"%.1f %.1f %.1f",pos.x,pos.y,pos.z);
	SetCameraPositionAndTarget_UpVecY(VGet(0,0,0),VAdd(pos,VGet(0,0,-1)));

}

static void _Del(WORK_OBJ* ix){
	//Scene_Change(Scene_GetPrevSceneId());
	s_pWork = NULL;
}

void TestTetoris_Init(){

	WORK_OBJ* ix = Task_CreateBase(_Updata,_Draw,_Del,WORK_OBJ,eTaskClassType_Class00);

	ASSERT_MES(ix != NULL,"メモリの確保に失敗",ix);

	if(ix != NULL){
	
		for(int i = 0;i < FIELD_HEIGHT;i++){
			for(int j = 0;j < FIELD_WIDHT;j++){
				if(i == FIELD_HEIGHT-1 || j == FIELD_WIDHT - 1 || j == 0){
					ix->bufferField[i][j] = ix->field[i][j] = eFiled_Wall;
				}else{
					ix->bufferField[i][j] = ix->field[i][j] = eFiled_Space;
				}
			}
		}

		ix->pGraph = ComRes_GetGraphics(eComResID_UI_Star);
		ix->graphPosY = 0;

		ix->posX = 0;
		ix->posY = 0;



		ix->blockKind = 0;
		ix->block = s_BlockTbl[ix->blockKind];

		ix->waitCnt = 0;
		ix->step = eStep_Init;

		//タスクなので最後に登録したものが最前面に来る
		ix->pAnimObj[0] = TestAnimObj_Create("Data/Graphic/Common/HpGage.png",0,0,1.0,0.0,eAnimKind_Rot);
		ix->pAnimObj[1] = TestAnimObj_Create("Data/Graphic/Common/Player0.png",100,300,1.0,0.0,eAnimKind_RandomMove);
		ix->pAnimObj[2] = TestAnimObj_Create("Data/Graphic/Common/Player1.png",300,400,2.5,0.0,eAnimKind_RandomMove);
		ix->pAnimObj[3] = TestAnimObj_Create("Data/Graphic/Common/Telop.png",0,0,1.0,0.0,eAnimKind_In);
		
		ix->mdelHdl = MV1LoadModel("Data/Model/Charactor/02/Modle.mv1");
		ix->animHdl = MV1LoadModel("Data/Model/Charactor/02/AnimA.mv1");
		ix->attactIdx = MV1AttachAnim(ix->mdelHdl,0,ix->animHdl);

		

		ix->toalTime = MV1GetAttachAnimTotalTime( ix->mdelHdl, ix->attactIdx ) ;
		ix->playTime = 0;
		MV1SetScale(ix->mdelHdl,VGet(15,15,15));
		SetCameraNearFar(10,1000);
		VECTOR pos = MV1GetPosition(ix->mdelHdl);
		//SetCameraPositionAndTargetAndUpVec(VGet(0,0,0),VAdd(pos,VGet(0,0,-10)) ,VGet(0,0,-20));
		SetCameraPositionAndTarget_UpVecY(VGet(0,0,0),VAdd(pos,VGet(0,1,-10)));
		s_pWork = ix;
	}

}

void TestTetoris_Finalize(){
}

void TestTetoris_Updata(){	
}

void TestTetoris_Draw(){
}


/*
	終了判定
	return	true	:終了
			false	:実行中
*/
bool TestTetoris_IsEnd(){

	if(s_pWork){
		return false;
	}else{
		return true;
	}
}