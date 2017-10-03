#ifdef __MY_DEBUG__

#include "Common/GameCommon/GameCommon.h"

#include "Scene/GameMain/PlayerObj.h"
#include "Scene/GameMain/Charactor/CharctorRes/CharComRes.h"
#include "Scene/Scene.h"
#include "Scene/GameMain/Camera/CameraObj.h"

#include "Test.h"


const float PLAYER_MOVE_SPEED = 3.0f;
const float CAMREA_ROT_SPEED = 1.0f;

typedef struct {
	MODEL_DATA_HANDLE model;
}MAP_DATA;

typedef struct{
	MAP_DATA map;
	MODEL_DATA_HANDLE model;
	CAMERA_OBJ* cam;
	PLAYER_OBJ* ch;
	int cnt;
}WORK_OBJ;

static WORK_OBJ* s_pWork;

//描画処理
static void _Draw(WORK_OBJ* ix){
	//マップの描画
	Model_Draw(&ix->map.model,VGet(0,0,0),VGet(1,1,1),VGet(0,0,0));
	
	//キャラクターの描画
	PlayerObj_Draw(ix->ch);

	DrawCapsule3D(VGet(0,0,0),VGet(0,0,0),10,40,GetColor(255,0,0),GetColor(255,0,0),TRUE);

	if(CharComRes_IsLoadEnd()){
		GRAPHICS_RES* pHdl = CharComRes_GetGraphics(eCharComResId_UI_HpGage);
		Graphics_Draw(pHdl,200,20,TRUE);
		Model_Draw(CharComRes_GetModelData(eCharComResId_Charactor),VGet(0,0,12),VGet(1,1,1),VGet(0,0,0));
	}else{
		DrawString(0,100,"非同期読み込み中",GetColor(0,255,0));
	}

	DrawString(0,0,"X Key To Back",GetColor(255,255,255));
	DrawFormatString(0,20,GetColor(255,255,255),"cnt:%d",ix->cnt);


}

//更新処理
static void _Updata(WORK_OBJ* ix){

	VECTOR moveVec = {};
	bool isMove = false;
	
	float cameraHRot = CameraObj_GetHAngle(ix->cam);
	float cameraVRot = CameraObj_GetVAngle(ix->cam);

	VECTOR chPos = PlayerObj_GetPosition(ix->ch);
	VECTOR chRot = PlayerObj_GetRoate(ix->ch);

	clsDx();
	printfDx("Angle %f %f %f\n",chRot.x,chRot.y,chRot.z);
	
	if(Keyboard_On(KEY_INPUT_D)){
		cameraHRot +=CAMREA_ROT_SPEED;
		if(cameraHRot  >= 180.0){
			cameraHRot -= 360.0f;
		}
	}else if(Keyboard_On(KEY_INPUT_A)){
		cameraHRot -=CAMREA_ROT_SPEED;
		if(cameraHRot  <= -180.0){
			cameraHRot += 360.0f;
		}
	}

	if(Keyboard_On(KEY_INPUT_W)){
		cameraVRot +=CAMREA_ROT_SPEED;
		if(cameraVRot  >= 80.0){
			cameraVRot = 80.0f;
		}
	}else if(Keyboard_On(KEY_INPUT_S)){
		cameraVRot -=CAMREA_ROT_SPEED;
		if(cameraVRot  <= 0.0){
			cameraVRot = 0.0f;
		}
	}


	if(Keyboard_On(KEY_INPUT_RIGHT)){
		isMove = true;
		chRot.y = 90.0f - cameraHRot;
		moveVec.x = PLAYER_MOVE_SPEED;
	}else if(Keyboard_On(KEY_INPUT_LEFT)){
		isMove = true;
		chRot.y = -90.0f - cameraHRot;
		moveVec.x = -PLAYER_MOVE_SPEED;
	}

	if(Keyboard_On(KEY_INPUT_UP)){
		isMove = true;
		chRot.y = 0.0f - cameraHRot;
		moveVec.z = PLAYER_MOVE_SPEED;
	}else if(Keyboard_On(KEY_INPUT_DOWN)){
		isMove = true;
		chRot.y = 160.0f - cameraHRot;
		moveVec.z = -PLAYER_MOVE_SPEED;
	}

	
	//前の画面へ戻る
	if(Keyboard_Press(KEY_INPUT_X)){
		Scene_Change(Scene_GetPrevSceneId());
	}


	//移動中である
	if(isMove){
		VECTOR tmpMoveVec;
		float sinParam;
		float cosParam;
		
		//カメラが向いている方向が進行方向になるように計算
		sinParam = sin(cameraHRot / 180.0f * DX_PI_F);
		cosParam = -cos(cameraHRot / 180.0f * DX_PI_F);
		tmpMoveVec.x = moveVec.x * cosParam - moveVec.z * sinParam;
		tmpMoveVec.y = 0.0f;
		tmpMoveVec.z = moveVec.x * sinParam + moveVec.z * cosParam;
		chPos = VAdd(chPos,tmpMoveVec);
		
		//デッグに変換する
		chRot.y = chRot.y / 180.0f * DX_PI_F;
	}


	
	//プレイヤーの座標を設定する
	PlayerObj_SetPositon(ix->ch,chPos);

	//プレイヤーの角度を設定する
	PlayerObj_SetRotate(ix->ch,chRot);
	
	
	CameraObj_SetHAngle(ix->cam,cameraHRot);
	CameraObj_SetVAngle(ix->cam,cameraVRot);
	CameraObj_SetCameraTargetPosition(ix->cam,chPos);
	CameraObj_Updata(ix->cam);
	

	ix->cnt++;
}

void Test_Init(){

	WORK_OBJ* ix = (WORK_OBJ*)Memory_Alloc(sizeof(WORK_OBJ));

	//メモリの確保ができているなら
	if(ix != NULL){

		// 背景の色を灰色にする
		SetBackgroundColor( 128, 128, 128 ) ;

		//プレイヤーの生成
		ix->ch = PlayerObj_Create("Data/Model/Charactor/00/Ki式チルノ100.pmd");

		PlayerObj_SetPositon(ix->ch,VGet(0,0,0));
		PlayerObj_SetRotate(ix->ch,VGet(0,0,0));
		PlayerObj_SetScal(ix->ch,VGet(1,1,1));


		//マップ読み込み
		Model_Init(&ix->map.model,"Data/Model/Old Town/Old Town.pmx");

		//カメラオブジェクトの生成
		ix->cam = CameraObj_Init(VGet(0,0,0),40.0f);
		CameraObj_SetCameraTargetPosition(ix->cam,VGet(0,0,100));

		CharComRes_Init();
		CharComRes_LoadRequest();

		ix->cnt = 0;

		s_pWork = ix;
	}


}

void Test_Updata(){
	_Updata(s_pWork);
}

void Test_Draw(){
	_Draw(s_pWork);
}

void Test_Finalize(){
	
	// 背景の色を黒色にする
	SetBackgroundColor( 0, 0, 0 ) ;

	Model_Finalize(&s_pWork->map.model);

	CameraObj_Finalize(s_pWork->cam);
	PlayerObj_Destroy(s_pWork->ch);

	//リソースの削除
	CharComRes_Finalize();

	//メモリの開放
	Memory_SafeFree(s_pWork);
}

#endif