#include "Common/GameCommon/GameCommon.h"

#include "CharctorRes/CharComRes.h"
#include "Chara_EnemyObj.h"

enum eMovePatternId{
	eMovePatternId_Right_to_Left,	//左右移動
	eMovePatternId_Targeting,		//追従
	eMovePatternId_Walk,			//歩行
	eMovePatternId_Dash,			//走る
	eMovePatternId_Rotate,			//回転する
	eMovePatternId_Max,				//最大数
};

typedef struct{
	void (*movePattern)(CHARA_ENEMY_OBJ*);
}MOVE_PATTERN_DATA;

static void _MovePattern000(CHARA_ENEMY_OBJ* ix);	//左右に動く
static void _MovePattern001(CHARA_ENEMY_OBJ* ix);
static void _MovePattern002(CHARA_ENEMY_OBJ* ix);
static void _MovePattern003(CHARA_ENEMY_OBJ* ix);
static void _MovePattern004(CHARA_ENEMY_OBJ* ix);

//行動パターンをテーブル化して登録をする
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


//更新処理
void CharEnemyObj_Updata(CHARA_ENEMY_OBJ* ix){

	if(ix == NULL) return ;

	//行動パターンテーブルから行動パターン関数を受け取る
	MOVE_PATTERN_DATA* pMovePtn =  &s_MovePatternTbl[ix->movePattaern];

	//行動パターン関数がNULLでなければ
	if(pMovePtn->movePattern != NULL){
		//行動パターンを実行
		pMovePtn->movePattern(ix);
	}

}

//描画処理
void CharEnemyObj_Draw(CHARA_ENEMY_OBJ* ix){

	//キャラクターモデルの取得
	MODEL_DATA_HANDLE* pHdl = CharactorObj_GetModelDataHdl(ix->pCh);


	VECTOR pos = CharactorOBj_GetPosition(ix->pCh);		//座標を取得
	VECTOR scal = CharactorObj_GetScal(ix->pCh);		//サイズを取得
	VECTOR rot = CharactorObj_GetRotate(ix->pCh);		//角度を取得

	Model_Draw(pHdl,pos,scal,rot);

}

//ステータスの設定
void CharEnemyObj_SetStatus(CHARA_ENEMY_OBJ* ix,int hp,int attack,int defence,float moveSpeed){
	CharactorObj_SetStatus(ix->pCh,hp,attack,defence,moveSpeed);
}

//座標設定
void CharEnemyObj_SetPosition(CHARA_ENEMY_OBJ* ix,VECTOR pos){
	CharactorObj_SetPosition(ix->pCh,pos);
}

//角度の設定
void CharEnemyObj_SetRotate(CHARA_ENEMY_OBJ* ix,VECTOR rot){
	CharactorObj_SetRotate(ix->pCh,rot);
}

//サイズの設定
void CharEnemyObj_SetScal(CHARA_ENEMY_OBJ* ix,VECTOR scal){
	CharactorObj_SetScal(ix->pCh,scal);
}

//目標地点を設定する
void CharEnemyObj_SetTargetPosintion(CHARA_ENEMY_OBJ* ix,VECTOR targetPos){
	ix-> targetPos = targetPos;
}

//サイズを返却する
VECTOR CharEnemyObj_GetScal(CHARA_ENEMY_OBJ* ix){
	return CharactorObj_GetScal(ix->pCh);
}

//角度を返却する
VECTOR CharEnemyObj_GetRotate(CHARA_ENEMY_OBJ* ix){
	return CharactorObj_GetRotate(ix->pCh);
}

//座標を返却する
VECTOR CharEnemyObj_GetPosition(CHARA_ENEMY_OBJ* ix){
	return CharactorOBj_GetPosition(ix->pCh);
}

//ステータスを返却する
STATUS_DATA* CharEnemyObj_GetStatus(CHARA_ENEMY_OBJ* ix){
	return CharactorObj_GatStatusData(ix->pCh);
}

//行動パターン
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