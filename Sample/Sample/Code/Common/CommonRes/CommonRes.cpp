#include "DxLib.h"
#include "MyLib/Memory/Memory.h"

#include "CommonRes.h"

enum eResType{

	eResType_Graphics,
	eResType_Model,
	eResType_Csv,

};


typedef struct{

	char fileName[128];	//ファイル名
	eResType resType;	//リソースの種類
	GRAPHICS_RES* graph;
	MODEL_DATA_HANDLE* model;

}COMMON_RES;


static COMMON_RES s_ComResTbl[eComResID_MAX] = {

	// -- 画像 -------------------------------------------------------------------

	{"Data/Graphic/Common/Star.png" ,eResType_Graphics},
	{"Data/Graphic/Common/shot.png" ,eResType_Graphics},

	// -- モデル ------------------------------------------------------------------

	// -- ファイル ----------------------------------------------------------------

};



void ComRes_Init(){
	
	COMMON_RES* pData = &s_ComResTbl[0];

	if(eComResID_MAX == 0) return ;

	//非同期読み込み開始
	//SetUseASyncLoadFlag(TRUE);

	for(int i = 0;i < eComResID_MAX;i++){
		if(pData->resType == eResType_Graphics){
			//メモリの確保
			pData->graph = (GRAPHICS_RES*)Memory_AllocZeroClear(sizeof(GRAPHICS_RES));
			//画像読み込み
			Graphics_ASyncLoad(pData->graph,pData->fileName);
		}
		pData++;
	}
	//非同期読み込み終了
	//SetUseASyncLoadFlag(FALSE);
}


void ComRes_Finalize(){
	
	COMMON_RES* pData = &s_ComResTbl[0];

	if(eComResID_MAX == 0) return ;

	for(int i = 0;i < eComResID_MAX;i++){
		if(pData->resType == eResType_Graphics){
			
			//画像の開放
			Graphics_Delete(pData->graph);
			//メモリの開放
			Memory_SafeFree(pData->graph);

		}
		pData++;
	}


}

//リソースの読み込みが終了したか？
bool ComRes_IsLoadEnd(){

	if(eComResID_MAX == 0) return true;

	bool isGraphicsLoadEnd = false;

	COMMON_RES* pData = &s_ComResTbl[0];

	for(int i = 0;i < eComResID_MAX;i++){
		if(pData->resType == eResType_Graphics){
			if(Graphics_IsASyncLoadEnd(pData->graph)){
				isGraphicsLoadEnd = true;
			}else{
				isGraphicsLoadEnd = false;
			}
		}
		pData++;
	}
	if(!isGraphicsLoadEnd || GetASyncLoadNum() > 0){
		return false;
	}
	return true;
}

//画像データを返却する
GRAPHICS_RES* ComRes_GetGraphics(eComResID comResID){
	COMMON_RES* pData = &s_ComResTbl[comResID];
	if(pData->resType != eResType_Graphics) return NULL;
	return pData->graph;
}

