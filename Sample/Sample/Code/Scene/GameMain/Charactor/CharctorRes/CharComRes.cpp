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

	//���f��
	{"Data/Model/Charactor/00/Ki���`���m100.pmd",eDataType_Model},	//�v���C���[
	{"Data/Model/Charactor/01/�����~�N_�A�m�}��5th.pmx",eDataType_Model},	//�G1
	{"Data/Model/Charactor/00/Ki���`���m100.pmd",eDataType_Model},	//�G2
	{"Data/Model/Old Town/Old Town.pmx"			,eDataType_Model},	//�}�b�v

	//�摜
	{"Data/Graphic/Common/HpGage.png"			,eDataType_Graphics},	//�}�b�v

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

	//�t�@�C���T�C�Y���擾
	ix->csv.size = FileRead_size((const TCHAR*)s_cDataTbl[charComResId].fileName);
		
	//�T�C�Y���̃��������m�ۂ���
	ix->csv.text = Memory_Alloc(sizeof(ix->csv.size));

	//�񓯊��ǂݍ��݂Ńt�@�C�����J���n���h�����擾����
	ix->csv.fileHndle = FileRead_open((const TCHAR*)s_cDataTbl[charComResId].fileName,TRUE);

	//�t�@�C���̓ǂݍ���
	FileRead_read(ix->csv.text,ix->csv.size,ix->csv.fileHndle);
	
	//�t�@�C�������
	FileRead_close(ix->csv.fileHndle );

	
}

static void _Delete_Csv(LOAD_DATA* ix){
	Memory_SafeFree(ix->csv.text);
}


//�������̊m��
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

//�ǂݍ��݃��N�G�X�g
void CharComRes_LoadRequest(){

	//�񓯊��ǂݍ��݂��J�n����
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


	//�񓯊��ǂݍ��݂��I������
	SetUseASyncLoadFlag(FALSE);

}

//�ǂݍ��݂��I�����������f����
//true:�ǂݍ��ݏI�� false:�ǂݍ��ݒ�
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

//�f�[�^��ԋp����
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
