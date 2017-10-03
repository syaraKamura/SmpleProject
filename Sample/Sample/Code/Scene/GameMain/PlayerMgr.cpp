
//------------------------------------------------- �C���N���[�h
#include "Common/GameCommon/GameCommon.h"
#include "Charactor/CharctorRes/CharComRes.h"

#include "PlayerMgr.h"
#include "Camera/CameraObj.h"

//------------------------------------------------- �萔��`(define & const)
const float CAMERA_DICETANSE = 50.0f;
const float CAMREA_ROT_SPEED = 1.0f;
//------------------------------------------------- �񋓑̒�`

//------------------------------------------------- �\���̒�`(structer & union)
typedef struct{
	CHARA_PLAYER_OBJ* player;	//�v���C���[
	CAMERA_OBJ* cam;			//�J����
	float rot;
	bool isHit;					//�G�ꂽ
}PLAYER_MGR;
//------------------------------------------------- �e�[�u����`
//------------------------------------------------- �X�^�e�B�b�N�ϐ���`
static PLAYER_MGR* s_pCh;
//------------------------------------------------- �O���[�o���ϐ���`

//------------------------------------------------- �v���g�^�C�v�錾
//------------------------------------------------- �X�^�e�B�b�N��`

//�v���C���[����
static void _ControlProc(PLAYER_MGR* ix){
	
	

	//�ړ��p�x�N�g����ݒ�
	VECTOR moveVec = VGet(0,0,0);

	//���݂̍��W���擾
	VECTOR pos = CharPlayerObj_GetPosition(ix->player);
	//���݂̊p�x���擾
	VECTOR rot = CharPlayerObj_GetRotate(ix->player);
	
	//�J������Y�����S�̊p�x���擾
	float hRot = CameraObj_GetHAngle(ix->cam);
	float vRot = CameraObj_GetVAngle(ix->cam);

	//�v���C���[�̈ړ����x
	float MoveSpeed = CharPlayerObj_GetStatus(ix->player)->moveSpeed;

	//�s���t���O��ݒ�
	bool isMove = false;

	if(Keyboard_On(KEY_INPUT_D)){
		
		hRot += CAMREA_ROT_SPEED;
		if(hRot >= 180.0f){
			hRot -= 360.0f;
		}

	}
	else if(Keyboard_On(KEY_INPUT_A)){
		hRot -= CAMREA_ROT_SPEED;
		if(hRot <= -180.0f){
			hRot += 360.0f;
		}
	}

	if(Keyboard_On(KEY_INPUT_W)){
		
		vRot += CAMREA_ROT_SPEED;
		if(vRot >= 80.0f){
			vRot = 80.0f;
		}

	}
	else if(Keyboard_On(KEY_INPUT_S)){
		vRot -= CAMREA_ROT_SPEED;
		if(vRot <= 0.0f){
			vRot = 0.0f;
		}
	}

	if(Keyboard_On(KEY_INPUT_LEFT)){
		isMove = true;
		rot.y = -90.0f - hRot;
		moveVec.x = -MoveSpeed;
	}else if(Keyboard_On(KEY_INPUT_RIGHT)){
		isMove = true;
		rot.y = 90.0f - hRot;
		moveVec.x = MoveSpeed;
	}

	if(Keyboard_On(KEY_INPUT_UP)){
		isMove = true;
		rot.y = 0.0f - hRot;
		moveVec.z = MoveSpeed;
	}else if(Keyboard_On(KEY_INPUT_DOWN)){
		isMove = true;
		rot.y = 160.0f - hRot;
		moveVec.z = -MoveSpeed;
	}


	//�ړ�������
	if(isMove){
	
		
		VECTOR tmpVec;
		float sinParam;
		float cosParam;
	
		sinParam = sin(hRot / 180.0f * DX_PI_F);
		cosParam = -cos(hRot / 180.0f * DX_PI_F);
		tmpVec.x = moveVec.x * cosParam - moveVec.z * sinParam;
		tmpVec.y = 0.0f;
		tmpVec.z = moveVec.x * sinParam + moveVec.z * cosParam;
		
		//�ړ��ʂ����Z
		pos = VAdd(pos,tmpVec);
		
		//�f�b�O�ɕϊ�����
		rot.y = rot.y / 180.0f * DX_PI_F;
	
	}

	
	CharPlayerObj_SetRotate(ix->player,rot);
	CharPlayerObj_SetPosition(ix->player,pos);

	CameraObj_SetVAngle(ix->cam,vRot);
	CameraObj_SetHAngle(ix->cam,hRot);
	CameraObj_SetCameraTargetPosition(ix->cam,pos);

	//�J�����̍��W�Ƀv���C���[�̍��W�𒍎��_�Ƃ��đ��
	//CameraMgr_SetTargetPos(pos);

}

static void _Updata(PLAYER_MGR* ix){
	_ControlProc(ix);
	

	CharPlayerObj_Updata(ix->player);
	CameraObj_Updata(ix->cam);

}

static void _Draw(PLAYER_MGR* ix){

	//DrawCapsule3D(PlayerObj_GetPosition(ix->player),PlayerObj_GetPosition(ix->player),10.0f,40,GetColor(0,0,0),GetColor(0,255,0),TRUE);
	CharPlayerObj_Draw(ix->player);

}

//------------------------------------------------- �O���[�o����`

void PlayerMgr_Init(){

	//�������̊m��
	PLAYER_MGR* ix = (PLAYER_MGR*)Memory_Alloc(sizeof(PLAYER_MGR));

	if(ix != NULL){

		ix->player = CharaPlayerObj_Create(VGet(0,0,0),VGet(0,0,0),eCharComResId_Charactor);
		CharPlayerObj_SetStatus(ix->player,1,0,20,10,5,5.0f);

		//�J�����̏�����
		ix->cam = CameraObj_Init(VGet(0,0,0),40.0f);
		CameraObj_SetCameraTargetPosition(ix->cam,VGet(0,0,100));


		ix->rot = 0.0;
		
		s_pCh = ix;

	}

}

//�X�V
void PlayerMgr_Updata(){
	_Updata(s_pCh);
}

//�`��
void PlayerMgr_Draw(){
	_Draw(s_pCh);
}

void PlayerMgr_Finalize(){

	CharPlayerObj_Destory(s_pCh->player);
	CameraObj_Finalize(s_pCh->cam);
	//�������̊J��
	Memory_SafeFree(s_pCh);
	
}


//�Q�b�^�[

//���W��ԋp����
VECTOR PlayerMgr_GetPosition(){
	if(s_pCh != NULL) return VGet(0,0,0);
	return CharPlayerObj_GetPosition(s_pCh->player);
}

//�v���C���[�f�[�^��ԋp����
CHARA_PLAYER_OBJ* PlayerMgr_GetPlayer(){
	if(s_pCh != NULL) return NULL;
	return s_pCh->player;
}

