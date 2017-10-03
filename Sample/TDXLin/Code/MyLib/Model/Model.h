#pragma once

#include "DxLib.h"

typedef struct{
	int frameIndex;
	int XDivNum;
	int YDivNum;
	int ZDivNum;
}MODEL_COLLISTION_DATA;

typedef struct{
	VECTOR pos;			//座標
	VECTOR rot;			//角度
	VECTOR scale;		//スケール
	bool isDispFlag;	//表示非表示を設定する
}MODEL_DATA;

typedef struct{
	int mhandle;							//モデルハンドル
	MODEL_DATA modleData;					//モデルデータ
	MODEL_COLLISTION_DATA modelCollData;	//モデルのコリジョンデータ
	int animNum;							//アニメーションの数
	int animIndex;							//アニメーション番号
	int AnimScrMHadel;						//アタッチするアニメーションを持っているモデルハンドル
}MODEL_DATA_HANDLE;


//モデル初期化
extern void Model_Init(MODEL_DATA_HANDLE* pHdl,const TCHAR* fileName);

//モデル描画
extern void Model_Draw(MODEL_DATA_HANDLE* pHdl,VECTOR pos,VECTOR scal,VECTOR rot);
//行列を使用してモデルを描画する
extern void Model_Draw(MODEL_DATA_HANDLE* pHdl,MATRIX matrix);

//モデル終了処理
extern void Model_Finalize(MODEL_DATA_HANDLE* pHdl);

//Setter

//モデルの表示、非表示の設定を行う
extern void Model_SetDispFlag(MODEL_DATA_HANDLE* pHdl,bool isDisp);

//コリジョン情報を構築する
extern void Model_SetCollisitionInfomation(MODEL_DATA_HANDLE* pHdl,int frameIndex = -1,int XDivNum = 32,int YDivNum = 8,int ZDivNum = 32);
//コリジョン情報を削除する
extern void Model_DestoryCollisionInfomation(MODEL_DATA_HANDLE* pHdl);

//コリジョン情報を更新する
extern void Model_UpdataCollisitionInfomation(MODEL_DATA_HANDLE* pHdl);

//Getter

//モデルのデータを返却する
extern const MODEL_DATA Model_GetData(MODEL_DATA_HANDLE* pHdl);

