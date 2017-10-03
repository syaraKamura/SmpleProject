#pragma once 

#include "CharactorObj.h"

typedef struct{
	int id;				//ID
	int movePattaern;	//移動パターン
	int attackPattern;	//攻撃パターン
	VECTOR targetPos;
	CHARA_OBJ* pCh;
}CHARA_ENEMY_OBJ;


CHARA_ENEMY_OBJ* CharEnemyObj_Creata(int id,VECTOR pos,VECTOR rot,int modelKind,int movePattern = 0,int attackPattern = 0);
void CharEnemyObj_Destory(CHARA_ENEMY_OBJ* ix);

//更新処理
void CharEnemyObj_Updata(CHARA_ENEMY_OBJ* ix);
//描画処理
void CharEnemyObj_Draw(CHARA_ENEMY_OBJ* ix);
//ステータスの設定
void CharEnemyObj_SetStatus(CHARA_ENEMY_OBJ* ix,int hp,int attack,int defence,float moveSpeed);
//座標設定
void CharEnemyObj_SetPosition(CHARA_ENEMY_OBJ* ix,VECTOR pos);
//角度の設定
void CharEnemyObj_SetRotate(CHARA_ENEMY_OBJ* ix,VECTOR rot);
//サイズの設定
void CharEnemyObj_SetScal(CHARA_ENEMY_OBJ* ix,VECTOR scal);
//サイズを返却する
VECTOR CharEnemyObj_GetScal(CHARA_ENEMY_OBJ* ix);
//角度を返却する
VECTOR CharEnemyObj_GetRotate(CHARA_ENEMY_OBJ* ix);
//座標を返却する
VECTOR CharEnemyObj_GetPosition(CHARA_ENEMY_OBJ* ix);
//ステータスを返却する
STATUS_DATA* CharEnemyObj_GetStatus(CHARA_ENEMY_OBJ* ix);