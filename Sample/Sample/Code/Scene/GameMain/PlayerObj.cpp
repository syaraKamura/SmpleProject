//------------------------------------------------- インクルード
#include "Common/GameCommon/GameCommon.h"

#include "GameMain.h"
#include "PlayerObj.h"
//------------------------------------------------- 定数定義(define & const)

//------------------------------------------------- 列挙体定義

//------------------------------------------------- 構造体定義(structer & union)

//------------------------------------------------- テーブル定義
//------------------------------------------------- スタティック変数定義
//------------------------------------------------- グローバル変数定義
//------------------------------------------------- プロトタイプ宣言
//------------------------------------------------- スタティック定義
//------------------------------------------------- グローバル定義

//生成
PLAYER_OBJ* PlayerObj_Create(const char* fileName){

	PLAYER_OBJ* ix = (PLAYER_OBJ*)Memory_AllocZeroClear(sizeof(PLAYER_OBJ));
	
	//メモリが確保できているなら
	if(ix != NULL){
		
		//モデルデータの読み込み
		Model_Init(&ix->model,fileName);
	

		PlayerObj_SetScal(ix,VGet(1.0f,1.0f,1.0f));
		PlayerObj_SetRotate(ix,VGet(0,0,0));

		ix->matrix = MGetIdent();	//単位行列を取得する

		return ix;
	}
	return NULL;
}

//削除
void PlayerObj_Destroy(PLAYER_OBJ* ix){
	if(ix == NULL) return ;
	
	Model_Finalize(&ix->model);
	
	Memory_SafeFree(ix);
}

void PlayerObj_Updata(PLAYER_OBJ* ix){

	//ix->matrix = MGetIdent();								//単位行列を取得
	//ix->matrix = MMult(ix->matrix,MGetRotX(ix->rotate.x));	//回転
	//ix->matrix = MMult(ix->matrix,MGetRotY(ix->rotate.y));
	//ix->matrix = MMult(ix->matrix,MGetRotZ(ix->rotate.z));
	//ix->matrix = MMult(ix->matrix,MGetTranslate(ix->pos));	//平行移動
	//ix->matrix = MMult(ix->matrix,MGetScale(ix->scal));		//スケーリング


}

//描画
void PlayerObj_Draw(PLAYER_OBJ* ix){

	Model_Draw(&ix->model,ix->pos,ix->scal,ix->rotate);
	//Model_Draw(&ix->model,ix->matrix);

}

//座標の設定
void PlayerObj_SetPositon(PLAYER_OBJ* ix,float x,float y,float z){
	ix->pos.x = x;
	ix->pos.y = y;
	ix->pos.z = z;
}

void PlayerObj_SetPositon(PLAYER_OBJ* ix,VECTOR pos){
	ix->pos = pos;
}

//サイズ変更
void PlayerObj_SetScal(PLAYER_OBJ* ix,VECTOR scal){
	ix->scal = scal;
}

//角度の設定
void PlayerObj_SetRotate(PLAYER_OBJ* ix,VECTOR rot){
	ix->rotate = rot;
}

//角度の取得
VECTOR PlayerObj_GetRoate(PLAYER_OBJ* ix){
	return ix->rotate;
}

//座標の取得
VECTOR PlayerObj_GetPosition(PLAYER_OBJ* ix){
	return ix->pos;
}

