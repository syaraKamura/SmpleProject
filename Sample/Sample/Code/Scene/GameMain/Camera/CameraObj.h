#pragma once

typedef struct{
	VECTOR cameraPos;			//�J�����̍��W
	VECTOR cameraTargetPos;		//�J�����̒����_���W
	float vRot;					//�J�����̊p�x(X��)
	float hRot;					//�J�����̊p�x(Y��)
	float tRot;					//�J�����̊p�x(Z��)
}CAMERA_OBJ;


CAMERA_OBJ* CameraObj_Init(VECTOR pos = VGet(0,0,0),float vRot = 0.0f,float hRot = 0.0f,float tRot = 0.0f);
void CameraObj_Finalize(CAMERA_OBJ* ix);
void CameraObj_Updata(CAMERA_OBJ* ix);

//�����_���W�ɂ���ڕW�̍��W��ݒ肷��
void CameraObj_SetCameraTargetPosition(CAMERA_OBJ* ix,VECTOR targetPos);
//�p�x�̐ݒ�
void CameraObj_SetVAngle(CAMERA_OBJ* ix,float vRot);
void CameraObj_SetHAngle(CAMERA_OBJ* ix,float hRot);
void CameraObj_SetTAngle(CAMERA_OBJ* ix,float tRot);
//�p�x�̐ݒ�
float CameraObj_GetVAngle(CAMERA_OBJ* ix);
float CameraObj_GetHAngle(CAMERA_OBJ* ix);
float CameraObj_GetTAngle(CAMERA_OBJ* ix);