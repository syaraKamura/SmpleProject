#pragma once


typedef struct{
	MODEL_DATA_HANDLE modle;	//モデル読み込み
	VECTOR pos;					//座標
	VECTOR rot;					//角度
	VECTOR scal;				//サイズ
}MAP_OBJ;

//マップオブジェクトの生成
MAP_OBJ* MapObj_Create(const char* fileName,VECTOR pos,bool isDisp);
//マップオブジェクト削除
void MapObj_Destory(MAP_OBJ* ix);
//マップオブジェクト描画
void MapObj_Draw(MAP_OBJ* ix);
//座標の設定
void MapObj_SetPosition(MAP_OBJ* ix,VECTOR pos);
//角度の設定
void MapObj_SetRotate(MAP_OBJ* ix,VECTOR rot);
//サイズの設定
void MapObj_SetScal(MAP_OBJ* ix,VECTOR scal);