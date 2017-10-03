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

//�`�揈��
static void _Draw(WORK_OBJ* ix){
	//�}�b�v�̕`��
	Model_Draw(&ix->map.model,VGet(0,0,0),VGet(1,1,1),VGet(0,0,0));
	
	//�L�����N�^�[�̕`��
	PlayerObj_Draw(ix->ch);

	DrawCapsule3D(VGet(0,0,0),VGet(0,0,0),10,40,GetColor(255,0,0),GetColor(255,0,0),TRUE);

	if(CharComRes_IsLoadEnd()){
		GRAPHICS_RES* pHdl = CharComRes_GetGraphics(eCharComResId_UI_HpGage);
		Graphics_Draw(pHdl,200,20,TRUE);
		Model_Draw(CharComRes_GetModelData(eCharComResId_Charactor),VGet(0,0,12),VGet(1,1,1),VGet(0,0,0));
	}else{
		DrawString(0,100,"�񓯊��ǂݍ��ݒ�",GetColor(0,255,0));
	}

	DrawString(0,0,"X Key To Back",GetColor(255,255,255));
	DrawFormatString(0,20,GetColor(255,255,255),"cnt:%d",ix->cnt);


}

//�X�V����
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

	
	//�O�̉�ʂ֖߂�
	if(Keyboard_Press(KEY_INPUT_X)){
		Scene_Change(Scene_GetPrevSceneId());
	}


	//�ړ����ł���
	if(isMove){
		VECTOR tmpMoveVec;
		float sinParam;
		float cosParam;
		
		//�J�����������Ă���������i�s�����ɂȂ�悤�Ɍv�Z
		sinParam = sin(cameraHRot / 180.0f * DX_PI_F);
		cosParam = -cos(cameraHRot / 180.0f * DX_PI_F);
		tmpMoveVec.x = moveVec.x * cosParam - moveVec.z * sinParam;
		tmpMoveVec.y = 0.0f;
		tmpMoveVec.z = moveVec.x * sinParam + moveVec.z * cosParam;
		chPos = VAdd(chPos,tmpMoveVec);
		
		//�f�b�O�ɕϊ�����
		chRot.y = chRot.y / 180.0f * DX_PI_F;
	}


	
	//�v���C���[�̍��W��ݒ肷��
	PlayerObj_SetPositon(ix->ch,chPos);

	//�v���C���[�̊p�x��ݒ肷��
	PlayerObj_SetRotate(ix->ch,chRot);
	
	
	CameraObj_SetHAngle(ix->cam,cameraHRot);
	CameraObj_SetVAngle(ix->cam,cameraVRot);
	CameraObj_SetCameraTargetPosition(ix->cam,chPos);
	CameraObj_Updata(ix->cam);
	

	ix->cnt++;
}

void Test_Init(){

	WORK_OBJ* ix = (WORK_OBJ*)Memory_Alloc(sizeof(WORK_OBJ));

	//�������̊m�ۂ��ł��Ă���Ȃ�
	if(ix != NULL){

		// �w�i�̐F���D�F�ɂ���
		SetBackgroundColor( 128, 128, 128 ) ;

		//�v���C���[�̐���
		ix->ch = PlayerObj_Create("Data/Model/Charactor/00/Ki���`���m100.pmd");

		PlayerObj_SetPositon(ix->ch,VGet(0,0,0));
		PlayerObj_SetRotate(ix->ch,VGet(0,0,0));
		PlayerObj_SetScal(ix->ch,VGet(1,1,1));


		//�}�b�v�ǂݍ���
		Model_Init(&ix->map.model,"Data/Model/Old Town/Old Town.pmx");

		//�J�����I�u�W�F�N�g�̐���
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
	
	// �w�i�̐F�����F�ɂ���
	SetBackgroundColor( 0, 0, 0 ) ;

	Model_Finalize(&s_pWork->map.model);

	CameraObj_Finalize(s_pWork->cam);
	PlayerObj_Destroy(s_pWork->ch);

	//���\�[�X�̍폜
	CharComRes_Finalize();

	//�������̊J��
	Memory_SafeFree(s_pWork);
}

#endif