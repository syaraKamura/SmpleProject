#include "Common/GameCommon/GameCommon.h"

#include "MapObj.h"


//マップオブジェクトの生成
MAP_OBJ* MapObj_Create(const char* fileName,VECTOR pos,bool isDisp){

	//メモリ確保
	MAP_OBJ* ix = (MAP_OBJ*)Memory_Alloc(sizeof(MAP_OBJ));

	if(ix != NULL){

		//モデル設定
		Model_Init(&ix->modle,(const TCHAR*)fileName);
		
		//座標の設定
		ix->pos = pos;

		//サイズの設定
		ix->scal = VGet(1.0f,1.0f,1.0f);
		
		//角度の設定
		ix->rot = VGet(0.0f,0.0f,0.0f);

		//モデルの表示設定
		Model_SetDispFlag(&ix->modle,isDisp);
		
		return ix;

	}
	return NULL;
}

//マップオブジェクト削除
void MapObj_Destory(MAP_OBJ* ix){
	
	Model_Finalize(&ix->modle);
	//メモリ開放
	Memory_SafeFree(ix);
}

//マップオブジェクト描画
void MapObj_Draw(MAP_OBJ* ix){
	Model_Draw(&ix->modle,ix->pos,ix->scal,ix->rot);
}

//座標の設定
void MapObj_SetPosition(MAP_OBJ* ix,VECTOR pos){
	ix->pos = pos;
}

//角度の設定
void MapObj_SetRotate(MAP_OBJ* ix,VECTOR rot){
	ix->rot = rot;
}

//サイズの設定
void MapObj_SetScal(MAP_OBJ* ix,VECTOR scal){
	ix->scal = scal;
}

