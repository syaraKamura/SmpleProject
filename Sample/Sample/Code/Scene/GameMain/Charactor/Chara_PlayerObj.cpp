#include "Common/GameCommon/GameCommon.h"
#include "CharctorRes/CharComRes.h"

#include "Chara_PlayerObj.h"

static int hdl;
static int attachIdx;

//プレイヤーキャラクターの初期化
//キャラクターオブジェクト　座標　角度　モデルの種類(CharComRes の共用体参照)
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

//削除
void CharPlayerObj_Destory(CHARA_PLAYER_OBJ* ix){
	
	CharactorObj_Delete(ix->pCh);
	
	Memory_SafeFree(ix);

}

//更新処理
void CharPlayerObj_Updata(CHARA_PLAYER_OBJ* ix){

}

//描画処理
void CharPlayerObj_Draw(CHARA_PLAYER_OBJ* ix){

	//キャラクターモデルの取得
	MODEL_DATA_HANDLE* pHdl = CharactorObj_GetModelDataHdl(ix->pCh);


	VECTOR pos = CharactorOBj_GetPosition(ix->pCh);		//座標を取得
	VECTOR scal = CharactorObj_GetScal(ix->pCh);		//サイズを取得
	VECTOR rot = CharactorObj_GetRotate(ix->pCh);		//角度を取得

	Model_Draw(pHdl,pos,scal,rot);
		
}

//ステータスの設定
void CharPlayerObj_SetStatus(CHARA_PLAYER_OBJ* ix,int level,int exp,int hp,int attack,int defence,float moveSpeed){
	ix->level;
	ix->exp;
	CharactorObj_SetStatus(ix->pCh,hp,attack,defence,moveSpeed);
}

//座標設定
void CharPlayerObj_SetPosition(CHARA_PLAYER_OBJ* ix,VECTOR pos){
	CharactorObj_SetPosition(ix->pCh,pos);
}

//角度の設定
void CharPlayerObj_SetRotate(CHARA_PLAYER_OBJ* ix,VECTOR rot){
	CharactorObj_SetRotate(ix->pCh,rot);
}

//サイズの設定
void CharPlayerObj_SetScal(CHARA_PLAYER_OBJ* ix,VECTOR scal){
	CharactorObj_SetScal(ix->pCh,scal);
}

//サイズを返却する
VECTOR CharPlayerObj_GetScal(CHARA_PLAYER_OBJ* ix){
	return CharactorObj_GetScal(ix->pCh);
}

//角度を返却する
VECTOR CharPlayerObj_GetRotate(CHARA_PLAYER_OBJ* ix){
	return CharactorObj_GetRotate(ix->pCh);
}

//座標を返却する
VECTOR CharPlayerObj_GetPosition(CHARA_PLAYER_OBJ* ix){
	return CharactorOBj_GetPosition(ix->pCh);
}

//ステータスを返却する
STATUS_DATA* CharPlayerObj_GetStatus(CHARA_PLAYER_OBJ* ix){
	return CharactorObj_GatStatusData(ix->pCh);
}

