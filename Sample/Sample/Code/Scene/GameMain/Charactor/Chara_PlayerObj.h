#pragma once

#include "CharactorObj.h"

typedef struct{
	int level;
	int exp;
	CHARA_OBJ* pCh;		//キャラクター
}CHARA_PLAYER_OBJ;


//プレイヤーキャラクターの初期化
//キャラクターオブジェクト　座標　角度　モデルの種類(CharComRes の共用体参照)
CHARA_PLAYER_OBJ* CharaPlayerObj_Create(VECTOR pos,VECTOR rot,int modelKind);
//削除
void CharPlayerObj_Destory(CHARA_PLAYER_OBJ* ix);
//更新処理
void CharPlayerObj_Updata(CHARA_PLAYER_OBJ* ix);
//描画処理
void CharPlayerObj_Draw(CHARA_PLAYER_OBJ* ix);

//ステータスの設定
//レベル　経験値　体力　攻撃力　防御力　移動スピード
void CharPlayerObj_SetStatus(CHARA_PLAYER_OBJ* ix,int level,int exp,int hp,int attack,int defence,float moveSpeed);
//座標設定
void CharPlayerObj_SetPosition(CHARA_PLAYER_OBJ* ix,VECTOR pos);
void CharPlayerObj_SetRotate(CHARA_PLAYER_OBJ* ix,VECTOR rot);
void CharPlayerObj_SetScal(CHARA_PLAYER_OBJ* ix,VECTOR scal);

VECTOR CharPlayerObj_GetScal(CHARA_PLAYER_OBJ* ix);
VECTOR CharPlayerObj_GetRotate(CHARA_PLAYER_OBJ* ix);
//座標を返却する
VECTOR CharPlayerObj_GetPosition(CHARA_PLAYER_OBJ* ix);
//ステータスを返却する
STATUS_DATA* CharPlayerObj_GetStatus(CHARA_PLAYER_OBJ* ix);