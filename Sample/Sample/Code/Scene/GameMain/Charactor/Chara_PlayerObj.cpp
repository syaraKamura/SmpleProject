#include "Common/GameCommon/GameCommon.h"
#include "CharctorRes/CharComRes.h"

#include "Chara_PlayerObj.h"

static int hdl;
static int attachIdx;

//�v���C���[�L�����N�^�[�̏�����
//�L�����N�^�[�I�u�W�F�N�g�@���W�@�p�x�@���f���̎��(CharComRes �̋��p�̎Q��)
CHARA_PLAYER_OBJ* CharaPlayerObj_Create(VECTOR pos,VECTOR rot,int modelKind){
	
	CHARA_PLAYER_OBJ* ix = (CHARA_PLAYER_OBJ*)Memory_AllocZeroClear(sizeof(CHARA_PLAYER_OBJ));

	if(ix != NULL){

		ix->pCh = CharactorObj_Create(modelKind);

		CharactorObj_SetPosition(ix->pCh,pos);
		CharactorObj_SetRotate(ix->pCh,rot);
		
		return ix;

	}
	return NULL;
}

//�폜
void CharPlayerObj_Destory(CHARA_PLAYER_OBJ* ix){
	
	CharactorObj_Delete(ix->pCh);
	
	Memory_SafeFree(ix);

}

//�X�V����
void CharPlayerObj_Updata(CHARA_PLAYER_OBJ* ix){

}

//�`�揈��
void CharPlayerObj_Draw(CHARA_PLAYER_OBJ* ix){

	//�L�����N�^�[���f���̎擾
	MODEL_DATA_HANDLE* pHdl = CharactorObj_GetModelDataHdl(ix->pCh);


	VECTOR pos = CharactorOBj_GetPosition(ix->pCh);		//���W���擾
	VECTOR scal = CharactorObj_GetScal(ix->pCh);		//�T�C�Y���擾
	VECTOR rot = CharactorObj_GetRotate(ix->pCh);		//�p�x���擾

	Model_Draw(pHdl,pos,scal,rot);
		
}

//�X�e�[�^�X�̐ݒ�
void CharPlayerObj_SetStatus(CHARA_PLAYER_OBJ* ix,int level,int exp,int hp,int attack,int defence,float moveSpeed){
	ix->level;
	ix->exp;
	CharactorObj_SetStatus(ix->pCh,hp,attack,defence,moveSpeed);
}

//���W�ݒ�
void CharPlayerObj_SetPosition(CHARA_PLAYER_OBJ* ix,VECTOR pos){
	CharactorObj_SetPosition(ix->pCh,pos);
}

//�p�x�̐ݒ�
void CharPlayerObj_SetRotate(CHARA_PLAYER_OBJ* ix,VECTOR rot){
	CharactorObj_SetRotate(ix->pCh,rot);
}

//�T�C�Y�̐ݒ�
void CharPlayerObj_SetScal(CHARA_PLAYER_OBJ* ix,VECTOR scal){
	CharactorObj_SetScal(ix->pCh,scal);
}

//�T�C�Y��ԋp����
VECTOR CharPlayerObj_GetScal(CHARA_PLAYER_OBJ* ix){
	return CharactorObj_GetScal(ix->pCh);
}

//�p�x��ԋp����
VECTOR CharPlayerObj_GetRotate(CHARA_PLAYER_OBJ* ix){
	return CharactorObj_GetRotate(ix->pCh);
}

//���W��ԋp����
VECTOR CharPlayerObj_GetPosition(CHARA_PLAYER_OBJ* ix){
	return CharactorOBj_GetPosition(ix->pCh);
}

//�X�e�[�^�X��ԋp����
STATUS_DATA* CharPlayerObj_GetStatus(CHARA_PLAYER_OBJ* ix){
	return CharactorObj_GatStatusData(ix->pCh);
}

