#include "Common/GameCommon/GameCommon.h"

#include "CameraObj.h"

const float CAMERA_FAR_DICETANSE = 10.0f;
const float CAMERA_NEAR_DICETANSE = 8000.0f;

const float CAMERA_HEIGHT = 100.0f;		//カメラの高さ
const float CAMREA_DEPTH = 100.0f;		//カメラの奥行

//初期化
CAMERA_OBJ* CameraObj_Init(VECTOR pos,float vRot,float hRot,float tRot){

	//メモリーの確保
	CAMERA_OBJ* ix = (CAMERA_OBJ*)Memory_Alloc(sizeof(CAMERA_OBJ));

	if(ix != NULL){
		
		ix->cameraPos = pos;
		ix->cameraTargetPos = VGet(0,0,0);

		ix->vRot = vRot;
		ix->hRot = hRot;
		ix->tRot = tRot;

		SetCameraNearFar(CAMERA_FAR_DICETANSE,CAMERA_NEAR_DICETANSE);
		
		return ix;
	}
	return NULL;
}

//終了処理
void CameraObj_Finalize(CAMERA_OBJ* ix){
	//メモリーの開放
	Memory_SafeFree(ix);
}


void CameraObj_Updata(CAMERA_OBJ* ix){

	float sinParam;
	float cosParam;
	VECTOR tmpPos1;
	VECTOR tmpPos2;
	VECTOR cameraLockAtPos;

	cameraLockAtPos = ix->cameraTargetPos;
	cameraLockAtPos.y += 50;

	sinParam = sin(ix->vRot / 180.0f * DX_PI_F);
	cosParam = cos(ix->vRot / 180.0f * DX_PI_F);

	tmpPos1.x = 0.0f;
	tmpPos1.y = sinParam * CAMERA_HEIGHT;
	tmpPos1.z = -cosParam * CAMREA_DEPTH;

	sinParam = sin(ix->hRot / 180.0f * DX_PI_F);
	cosParam = cos(ix->hRot / 180.0f * DX_PI_F);
		
	tmpPos2.x = cosParam * tmpPos1.x - sinParam * tmpPos1.z;
	tmpPos2.y = tmpPos1.y;
	tmpPos2.z = sinParam * tmpPos1.x - cosParam * tmpPos1.z;

	ix->cameraPos = VAdd(tmpPos2,cameraLockAtPos);

	SetCameraPositionAndTarget_UpVecY(ix->cameraPos,cameraLockAtPos);


}

//注視点座標にする目標の座標を設定する
void CameraObj_SetCameraTargetPosition(CAMERA_OBJ* ix,VECTOR targetPos){
	ix->cameraTargetPos = targetPos;
}

//角度の設定
void CameraObj_SetVAngle(CAMERA_OBJ* ix,float vRot){
	ix->vRot = vRot;
}

void CameraObj_SetHAngle(CAMERA_OBJ* ix,float hRot){
	ix->hRot = hRot;
}

void CameraObj_SetTAngle(CAMERA_OBJ* ix,float tRot){
	ix->tRot = tRot;
}

//角度の設定
float CameraObj_GetVAngle(CAMERA_OBJ* ix){
	return ix->vRot;
}

float CameraObj_GetHAngle(CAMERA_OBJ* ix){
	return ix->hRot;
}

float CameraObj_GetTAngle(CAMERA_OBJ* ix){
	return ix->tRot;
}