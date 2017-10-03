#include "Model.h"

//モデル初期化
//モデルの読み込みを行う
void Model_Init(MODEL_DATA_HANDLE* pHdl,const TCHAR* fileName){

	pHdl->mhandle = MV1LoadModel(fileName);
	
	if(pHdl->mhandle != -1){
		pHdl->modleData.isDispFlag = true;		//表示状態
		pHdl->modleData.pos = MV1GetPosition(pHdl->mhandle);
		pHdl->modleData.rot = MV1GetRotationXYZ(pHdl->mhandle);
		pHdl->modleData.scale = MV1GetScale(pHdl->mhandle);

		pHdl->animNum = MV1GetAnimNum(pHdl->mhandle);	//アニメーションの数を取得する

	}else{
		pHdl->mhandle = 0;
	}

}

/*
	モデルのアニメーションデータを読み込む
*/

/*
	モデルのアニメーションを設定する
*/

/*
	モデルアニメーションの再生
	MODEL_DATA_HANDLE* pHdl
*/

/*
	モデルアニメーションシュル用判定を返す
	MODEL_DATA_HANDLE* pHdl
	return	true	:終了
			false	:アニメーション中
*/		

//モデル描画
void Model_Draw(MODEL_DATA_HANDLE* pHdl,VECTOR pos,VECTOR scal,VECTOR rot){
	
	if(!pHdl->modleData.isDispFlag) return ;

	MV1SetRotationXYZ(pHdl->mhandle,rot);
	MV1SetPosition(pHdl->mhandle,pos);
	MV1SetScale(pHdl->mhandle,scal);
		
	MV1DrawModel(pHdl->mhandle);
}

//行列を使用してモデルを描画する
void Model_Draw(MODEL_DATA_HANDLE* pHdl,MATRIX matrix){
	if(!pHdl->modleData.isDispFlag) return ;

	MV1SetMatrix(pHdl->mhandle,matrix);
	MV1DrawModel(pHdl->mhandle);

}

//モデルの表示、非表示の設定を行う
void Model_SetDispFlag(MODEL_DATA_HANDLE* pHdl,bool isDisp){
	pHdl->modleData.isDispFlag = isDisp;
}

//コリジョン情報を構築する
void Model_SetCollisitionInfomation(MODEL_DATA_HANDLE* pHdl,int frameIndex/* = -1*/,int XDivNum/*= 32*/,int YDivNum/* = 8*/,int ZDivNum/* = 32*/){
	
	pHdl->modelCollData.frameIndex = frameIndex;
	pHdl->modelCollData.XDivNum = XDivNum;
	pHdl->modelCollData.YDivNum = YDivNum;
	pHdl->modelCollData.ZDivNum = ZDivNum;

	MV1SetupCollInfo(pHdl->mhandle,frameIndex,XDivNum,YDivNum,ZDivNum);
}

//コリジョン情報を更新する
void Model_UpdataCollisitionInfomation(MODEL_DATA_HANDLE* pHdl){
	MV1RefreshCollInfo(pHdl->mhandle,pHdl->modelCollData.frameIndex);
}

//コリジョン情報を削除する
void Model_DestoryCollisionInfomation(MODEL_DATA_HANDLE* pHdl){
	MV1TerminateCollInfo(pHdl->mhandle,pHdl->modelCollData.frameIndex);
}

//モデルのデータを返却する
const MODEL_DATA Model_GetData(MODEL_DATA_HANDLE* pHdl){
	pHdl->modleData.rot = MV1GetRotationXYZ(pHdl->mhandle);
	pHdl->modleData.pos = MV1GetPosition(pHdl->mhandle);
	pHdl->modleData.scale = MV1GetScale(pHdl->mhandle);
	return pHdl->modleData;
}

int Model_GetAnimNum(MODEL_DATA_HANDLE* pHdl){
	return pHdl->animNum;
}

//モデル終了処理
void Model_Finalize(MODEL_DATA_HANDLE* pHdl){
	MV1DeleteModel(pHdl->mhandle);
}