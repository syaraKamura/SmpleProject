#include "Common/GameCommon/GameCommon.h"

#include "CharctorRes/CharComRes.h"
#include "Chara_EnemyObj.h"

enum eMovePatternId{
	eMovePatternId_Right_to_Left,	//���E�ړ�
	eMovePatternId_Targeting,		//�Ǐ]
	eMovePatternId_Walk,			//���s
	eMovePatternId_Dash,			//����
	eMovePatternId_Rotate,			//��]����
	eMovePatternId_Max,				//�ő吔
};

typedef struct{
	void (*movePattern)(CHARA_ENEMY_OBJ*);
}MOVE_PATTERN_DATA;

static void _MovePattern000(CHARA_ENEMY_OBJ* ix);	//���E�ɓ���
static void _MovePattern001(CHARA_ENEMY_OBJ* ix);
static void _MovePattern002(CHARA_ENEMY_OBJ* ix);
static void _MovePattern003(CHARA_ENEMY_OBJ* ix);
static void _MovePattern004(CHARA_ENEMY_OBJ* ix);

//�s���p�^�[�����e�[�u�������ēo�^������
static MOVE_PATTERN_DATA s_MovePatternTbl[eMovePatternId_Max] = {
	_MovePattern000,
	_MovePattern001,
	_MovePattern002,
	_MovePattern003,
	_MovePattern004,
};

CHARA_ENEMY_OBJ* CharEnemyObj_Creata(int id,VECTOR pos,VECTOR rot,int modelKind,int movePattern,int attackPattern){

	CHARA_ENEMY_OBJ* ix = (CHARA_ENEMY_OBJ*)Memory_Alloc(sizeof(CHARA_ENEMY_OBJ));

	if(ix != NULL){

		ix->id = id;

		ix->pCh = CharactorObj_Create(modelKind);

		CharactorObj_SetPosition(ix->pCh,pos);
		CharactorObj_SetRotate(ix->pCh,rot);

		ix->movePattaern = movePattern;
		ix->attackPattern = attackPattern;

		return ix;

	}
	return NULL;
}

void CharEnemyObj_Destory(CHARA_ENEMY_OBJ* ix){
	CharactorObj_Delete(ix->pCh);
	Memory_SafeFree(ix);
}


//�X�V����
void CharEnemyObj_Updata(CHARA_ENEMY_OBJ* ix){

	if(ix == NULL) return ;

	//�s���p�^�[���e�[�u������s���p�^�[���֐����󂯎��
	MOVE_PATTERN_DATA* pMovePtn =  &s_MovePatternTbl[ix->movePattaern];

	//�s���p�^�[���֐���NULL�łȂ����
	if(pMovePtn->movePattern != NULL){
		//�s���p�^�[�������s
		pMovePtn->movePattern(ix);
	}

}

//�`�揈��
void CharEnemyObj_Draw(CHARA_ENEMY_OBJ* ix){

	//�L�����N�^�[���f���̎擾
	MODEL_DATA_HANDLE* pHdl = CharactorObj_GetModelDataHdl(ix->pCh);


	VECTOR pos = CharactorOBj_GetPosition(ix->pCh);		//���W���擾
	VECTOR scal = CharactorObj_GetScal(ix->pCh);		//�T�C�Y���擾
	VECTOR rot = CharactorObj_GetRotate(ix->pCh);		//�p�x���擾

	Model_Draw(pHdl,pos,scal,rot);

}

//�X�e�[�^�X�̐ݒ�
void CharEnemyObj_SetStatus(CHARA_ENEMY_OBJ* ix,int hp,int attack,int defence,float moveSpeed){
	CharactorObj_SetStatus(ix->pCh,hp,attack,defence,moveSpeed);
}

//���W�ݒ�
void CharEnemyObj_SetPosition(CHARA_ENEMY_OBJ* ix,VECTOR pos){
	CharactorObj_SetPosition(ix->pCh,pos);
}

//�p�x�̐ݒ�
void CharEnemyObj_SetRotate(CHARA_ENEMY_OBJ* ix,VECTOR rot){
	CharactorObj_SetRotate(ix->pCh,rot);
}

//�T�C�Y�̐ݒ�
void CharEnemyObj_SetScal(CHARA_ENEMY_OBJ* ix,VECTOR scal){
	CharactorObj_SetScal(ix->pCh,scal);
}

//�ڕW�n�_��ݒ肷��
void CharEnemyObj_SetTargetPosintion(CHARA_ENEMY_OBJ* ix,VECTOR targetPos){
	ix-> targetPos = targetPos;
}

//�T�C�Y��ԋp����
VECTOR CharEnemyObj_GetScal(CHARA_ENEMY_OBJ* ix){
	return CharactorObj_GetScal(ix->pCh);
}

//�p�x��ԋp����
VECTOR CharEnemyObj_GetRotate(CHARA_ENEMY_OBJ* ix){
	return CharactorObj_GetRotate(ix->pCh);
}

//���W��ԋp����
VECTOR CharEnemyObj_GetPosition(CHARA_ENEMY_OBJ* ix){
	return CharactorOBj_GetPosition(ix->pCh);
}

//�X�e�[�^�X��ԋp����
STATUS_DATA* CharEnemyObj_GetStatus(CHARA_ENEMY_OBJ* ix){
	return CharactorObj_GatStatusData(ix->pCh);
}

//�s���p�^�[��
static void _MovePattern000(CHARA_ENEMY_OBJ* ix){

#ifdef __MY_DEBUG__
	printfDx("EnemyMovePattern 0 \n");
#endif

	VECTOR pos = CharactorOBj_GetPosition(ix->pCh);
	VECTOR rot = CharactorObj_GetRotate(ix->pCh);
	STATUS_DATA* pStatus = CharactorObj_GatStatusData(ix->pCh);

	pos.x -= pStatus->moveSpeed;

	if(pos.x > 100.0f || pos.x < -100.0f){
		rot.y = -rot.y;
		//rot.y = rot.y / DX_PI_F * 180.f;
		pStatus->moveSpeed *= -1;
	}

	CharactorObj_SetPosition(ix->pCh,pos);
	CharactorObj_SetRotate(ix->pCh,rot);
	CharactorObj_SetStatus(ix->pCh,pStatus->hp,pStatus->Attack,pStatus->Defence,pStatus->moveSpeed);


}

static void _MovePattern001(CHARA_ENEMY_OBJ* ix){


}

static void _MovePattern002(CHARA_ENEMY_OBJ* ix){

}

static void _MovePattern003(CHARA_ENEMY_OBJ* ix){

}

static void _MovePattern004(CHARA_ENEMY_OBJ* ix){

}