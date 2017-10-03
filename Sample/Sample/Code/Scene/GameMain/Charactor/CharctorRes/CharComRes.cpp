#include "Common/GameCommon/GameCommon.h"

#include "CharComRes.h"



enum eDataType{
	eDataType_Model,
	eDataType_Graphics,
	eDataType_Csv,
};

typedef struct{
	int fileHndle;
	int size;
	void* text;
}LOAD_CSV_FILE;

typedef struct{
	char fileName[128];
	eDataType dataType;
	GRAPHICS_RES* pGraph;
	MODEL_DATA_HANDLE* pModel;
	LOAD_CSV_FILE csv;
}LOAD_DATA;

static LOAD_DATA s_cDataTbl[eCharComResId_Max] = {

	//モデル
	{"Data/Model/Charactor/00/Ki式チルノ100.pmd",eDataType_Model},	//プレイヤー
	{"Data/Model/Charactor/01/初音ミク_アノマロ5th.pmx",eDataType_Model},	//敵1
	{"Data/Model/Charactor/00/Ki式チルノ100.pmd",eDataType_Model},	//敵2
	{"Data/Model/Old Town/Old Town.pmx"			,eDataType_Model},	//マップ

	//画像
	{"Data/Graphic/Common/HpGage.png"			,eDataType_Graphics},	//マップ

	//CSV

};

//static LOAD_DATA* s_pHdl;

static void _Load_Model(LOAD_DATA* ix,eCharComResId charComResId){

	ix->pModel = (MODEL_DATA_HANDLE*)Memory_Alloc(sizeof(MODEL_DATA_HANDLE));
	Model_Init(ix->pModel,(const TCHAR*)s_cDataTbl[charComResId].fileName);
	
}

static void _Delete_Model(LOAD_DATA* ix){
	Model_Finalize(ix->pModel);
	Memory_SafeFree(ix->pModel);
}

static void _Load_Graphics(LOAD_DATA* ix,eCharComResId charComResId){
	ix->pGraph = (GRAPHICS_RES*)Memory_Alloc(sizeof(GRAPHICS_RES));
	Graphics_ASyncLoad(ix->pGraph,s_cDataTbl[charComResId].fileName);
}

static void _Delete_Graphics(LOAD_DATA* ix){
	Graphics_Delete(ix->pGraph);
	Memory_SafeFree(ix->pGraph);
}


static void _Load_Csv(LOAD_DATA* ix,eCharComResId charComResId){

	//ファイルサイズを取得
	ix->csv.size = FileRead_size((const TCHAR*)s_cDataTbl[charComResId].fileName);
		
	//サイズ分のメモリを確保する
	ix->csv.text = Memory_Alloc(sizeof(ix->csv.size));

	//非同期読み込みでファイルを開きハンドルを取得する
	ix->csv.fileHndle = FileRead_open((const TCHAR*)s_cDataTbl[charComResId].fileName,TRUE);

	//ファイルの読み込み
	FileRead_read(ix->csv.text,ix->csv.size,ix->csv.fileHndle);
	
	//ファイルを閉じる
	FileRead_close(ix->csv.fileHndle );

	
}

static void _Delete_Csv(LOAD_DATA* ix){
	Memory_SafeFree(ix->csv.text);
}


//メモリの確保
void CharComRes_Init(){
	//s_pHdl = (LOAD_DATA*)Memory_Alloc(sizeof(LOAD_DATA) * eCharComResId_Max);
}

void CharComRes_Finalize(){

	LOAD_DATA* pHdl = &s_cDataTbl[0];
	for(int i = 0;i < eCharComResId_Max;i++){
		if(pHdl->dataType == eDataType_Model){
			_Delete_Model(pHdl);
		}else if(pHdl->dataType == eDataType_Graphics){
			_Delete_Graphics(pHdl);
		}else if(pHdl->dataType == eDataType_Csv){
			_Delete_Csv(pHdl);
		}
		pHdl++;
	}
	
	//Memory_SafeFree(s_pHdl);

}

//読み込みリクエスト
void CharComRes_LoadRequest(){

	//非同期読み込みを開始する
	SetUseASyncLoadFlag(TRUE);

	LOAD_DATA* pHdl = &s_cDataTbl[0];
	for(int i = 0;i < eCharComResId_Max;i++){
		if(pHdl->dataType == eDataType_Model){
			_Load_Model(pHdl,(eCharComResId)i);
		}else if(pHdl->dataType == eDataType_Graphics){
			_Load_Graphics(pHdl,(eCharComResId)i);
		}else if(pHdl->dataType == eDataType_Csv){
			_Load_Csv(pHdl,(eCharComResId)i);
		}
		pHdl++;
	}


	//非同期読み込みを終了する
	SetUseASyncLoadFlag(FALSE);

}

//読み込みが終了したか判断する
//true:読み込み終了 false:読み込み中
bool CharComRes_IsLoadEnd(){
	
	bool isGraphicsLoadEnd = false;

	LOAD_DATA* pHdl = &s_cDataTbl[0];
	for(int i = 0;i < eCharComResId_Max;i++){
		if(pHdl->dataType == eDataType_Graphics){
			if(Graphics_IsASyncLoadEnd(pHdl->pGraph)){
				isGraphicsLoadEnd = true;
			}else{
				isGraphicsLoadEnd = false;
			}
		}
		pHdl++;
	}
	if(!isGraphicsLoadEnd || GetASyncLoadNum() > 0){
		return false;
	}
	return true;
}


MODEL_DATA_HANDLE* CharComRes_GetModelData(eCharComResId idx){
	LOAD_DATA* pHdl = &s_cDataTbl[idx];
	if(pHdl->dataType != eDataType_Model) return NULL;
	return pHdl->pModel;
}

//データを返却する
GRAPHICS_RES* CharComRes_GetGraphics(eCharComResId idx){
	LOAD_DATA* pHdl = &s_cDataTbl[idx];
	if(pHdl->dataType != eDataType_Graphics) return NULL;
	return pHdl->pGraph;
}

int CharComRes_GetCsvDataSize(eCharComResId idx){
	LOAD_DATA* pHdl = &s_cDataTbl[idx];
	if(pHdl->dataType != eDataType_Model) return 0;
	return pHdl->csv.size;
}

const char* CharComRes_GetCsvData(eCharComResId idx){
	LOAD_DATA* pHdl = &s_cDataTbl[idx];
	if(pHdl->dataType != eDataType_Model) return "";
	return (const char*)pHdl->csv.text;
}
