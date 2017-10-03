#include "Common/GameCommon/GameCommon.h"
#include "CharctorRes\CharComRes.h"

#include "CharactorObj.h"

//生成
CHARA_OBJ* CharactorObj_Create(int modelKind){

	//メモリを確保し初期化を行う
	CHARA_OBJ* ix =(CHARA_OBJ*) Memory_Alloc(sizeof(CHARA_OBJ));

	if(ix != NULL){

		ix->model = CharComRes_GetModelData((eCharComResId)modelKind);

		CharactorObj_SetScal(ix,VGet(1,1,1));

		return ix;
	}
	return NULL;
}

//削除
void CharactorObj_Delete(CHARA_OBJ* ix){
	//メモリの開放
	Memory_SafeFree(ix);
}


//モデルを替える
void CharactorObj_ChangeModel(CHARA_OBJ* ix,int modelKind){
	ix->model = CharComRes_GetModelData((eCharComResId)modelKind);
}


//ステータスの設定
void CharactorObj_SetStatus(CHARA_OBJ* ix,int hp,int attack,int defence,float moveSpeed){
	ix->status.hp = hp;
	ix->status.maxHp = hp;
	ix->status.Attack = attack;
	ix->status.Defence = defence;
	ix->status.moveSpeed = moveSpeed;
}

void CharactorObj_SetPosition(CHARA_OBJ* ix,VECTOR pos){
	ix->pos = pos;
}

void CharactorObj_SetRotate(CHARA_OBJ* ix,VECTOR rot){
	ix->rot = rot;
}

void CharactorObj_SetScal(CHARA_OBJ* ix,VECTOR scal){
	ix->scal = scal;
}

VECTOR CharactorObj_GetScal(CHARA_OBJ* ix){
	return ix->scal;
}

VECTOR CharactorObj_GetRotate(CHARA_OBJ* ix){
	return ix->rot;
}

VECTOR CharactorOBj_GetPosition(CHARA_OBJ* ix){
	return ix->pos;
}

//ステータスを取得する
STATUS_DATA* CharactorObj_GatStatusData(CHARA_OBJ* ix){
	return &ix->status;
}

//モデルデータを取得する
MODEL_DATA_HANDLE* CharactorObj_GetModelDataHdl(CHARA_OBJ* ix){
	return ix->model;
}

