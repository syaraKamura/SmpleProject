
//------------------------------------------------- �C���N���[�h
#include "Common/GameCommon/GameCommon.h"
#include "Common/CommonRes/CommonRes.h"
#include "Charactor/CharctorRes/CharComRes.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Charactor/EnemyMgr.h"
//------------------------------------------------- �萔��`(define & const)

//------------------------------------------------- �񋓑̒�`

enum eStep{
	eStep_Init,
	eStep_SetUp,
	eStep_Main,
};

//------------------------------------------------- �\���̒�`(structer & union)

typedef struct{
	int step;
	int cnt;
}WORK_OBJ;

//------------------------------------------------- �e�[�u����`
const char* strTbl[] = {
	"Now Loading",
	"Now Loading.",
	"Now Loading..",
	"Now Loading...",
	"Now Loading..",
	"Now Loading.",
};

//------------------------------------------------- �X�^�e�B�b�N�ϐ���`
//------------------------------------------------- �O���[�o���ϐ���`
static WORK_OBJ* s_pWork; 
//------------------------------------------------- �v���g�^�C�v�錾
//------------------------------------------------- �X�^�e�B�b�N��`
//------------------------------------------------- �O���[�o����`

static void _Updata(WORK_OBJ* ix){


	switch(ix->step){
	case eStep_Init:
		CharComRes_LoadRequest();
		ix->step = eStep_SetUp;
		break;
	case eStep_SetUp:
		if(CharComRes_IsLoadEnd()){
			PlayerMgr_Init();
			EnemyMgr_Init(10);
			ix->step = eStep_Main;
		}
		ix->cnt++;
		break;
	case eStep_Main:
	
		PlayerMgr_Updata();
		EnemyMgr_Updata();

#ifdef __MY_DEBUG__
		if(Keyboard_Press(KEY_INPUT_X)){
			//�O�̉�ʂ֖߂�
			Scene_Change(Scene_GetPrevSceneId());
		}
#endif 

		break;
	}

}

static void _Draw(WORK_OBJ* ix){
	
	if(ix->step != eStep_Main){
		//NowLoading�̕\�L
		int changeTiming = (ix->cnt / 20 )% 6;
		double rot = (double)(ix->cnt / 10.0);
		DrawString(0,460,strTbl[changeTiming],GetColor(255,255,255));
		Graphics_DrawRot(ComRes_GetGraphics(eComResID_UI_Star),0,0,rot,TRUE);
		return;
	}
	
	Model_Draw(CharComRes_GetModelData(eCharComResId_Map),VGet(0,0,0),VGet(1,1,1),VGet(0,0,0));

	PlayerMgr_Draw();
	EnemyMgr_Draw();
}

void GameMain_Init(){
	
	WORK_OBJ* ix = (WORK_OBJ*)Memory_Alloc(sizeof(WORK_OBJ));

	if(ix != NULL){

		ix->step = eStep_Init;
		ix->cnt = 0;

		CharComRes_Init();
		s_pWork = ix;
	}
}

void GameMain_UpData(){
	_Updata(s_pWork);	
}
void GameMain_Draw(){
	_Draw(s_pWork);
}

void GameMmain_Finalize(){

	PlayerMgr_Finalize();
	EnemyMgr_Finalize();

	CharComRes_Finalize();

	Memory_SafeFree(s_pWork);

}