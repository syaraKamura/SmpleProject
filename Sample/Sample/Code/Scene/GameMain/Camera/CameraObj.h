#pragma once

typedef struct{
	VECTOR cameraPos;			//カメラの座標
	VECTOR cameraTargetPos;		//カメラの注視点座標
	float vRot;					//カメラの角度(X軸)
	float hRot;					//カメラの角度(Y軸)
	float tRot;					//カメラの角度(Z軸)
}CAMERA_OBJ;


CAMERA_OBJ* CameraObj_Init(VECTOR pos = VGet(0,0,0),float vRot = 0.0f,float hRot = 0.0f,float tRot = 0.0f);
void CameraObj_Finalize(CAMERA_OBJ* ix);
void CameraObj_Updata(CAMERA_OBJ* ix);

//注視点座標にする目標の座標を設定する
void CameraObj_SetCameraTargetPosition(CAMERA_OBJ* ix,VECTOR targetPos);
//角度の設定
void CameraObj_SetVAngle(CAMERA_OBJ* ix,float vRot);
void CameraObj_SetHAngle(CAMERA_OBJ* ix,float hRot);
void CameraObj_SetTAngle(CAMERA_OBJ* ix,float tRot);
//角度の設定
float CameraObj_GetVAngle(CAMERA_OBJ* ix);
float CameraObj_GetHAngle(CAMERA_OBJ* ix);
float CameraObj_GetTAngle(CAMERA_OBJ* ix);