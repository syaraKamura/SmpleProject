#pragma once

typedef struct{
	VECTOR pos;			//座標
	VECTOR rotate;		//向き
	VECTOR scal;		//サイズ
	MATRIX matrix;		//行列
	MODEL_DATA_HANDLE model;
}PLAYER_OBJ;


//生成
PLAYER_OBJ* PlayerObj_Create(const TCHAR* fileName);
//削除
void PlayerObj_Destroy(PLAYER_OBJ* ix);

//更新
void PlayerObj_Updata(PLAYER_OBJ* ix);
//描画
void PlayerObj_Draw(PLAYER_OBJ* ix);

//座標の設定
void PlayerObj_SetPositon(PLAYER_OBJ* ix,float x,float y,float z);
void PlayerObj_SetPositon(PLAYER_OBJ* ix,VECTOR pos);

//角度の設定
void PlayerObj_SetRotate(PLAYER_OBJ* ix,VECTOR rot);

//サイズ変更
void PlayerObj_SetScal(PLAYER_OBJ* ix,VECTOR scal);

//角度取得
VECTOR PlayerObj_GetRoate(PLAYER_OBJ* ix);
//座標の取得
VECTOR PlayerObj_GetPosition(PLAYER_OBJ* ix);