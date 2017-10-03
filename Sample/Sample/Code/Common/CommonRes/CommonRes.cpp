#include "DxLib.h"
#include "MyLib/Memory/Memory.h"

#include "CommonRes.h"

enum eResType{

	eResType_Graphics,
	eResType_Model,
	eResType_Csv,

};


typedef struct{

	char fileName[128];	//�t�@�C����
	eResType resType;	//���\�[�X�̎��
	GRAPHICS_RES* graph;
	MODEL_DATA_HANDLE* model;

}COMMON_RES;


static COMMON_RES s_ComResTbl[eComResID_MAX] = {

	// -- �摜 -------------------------------------------------------------------

	{"Data/Graphic/Common/Star.png" ,eResType_Graphics},
	{"Data/Graphic/Common/shot.png" ,eResType_Graphics},

	// -- ���f�� ------------------------------------------------------------------

	// -- �t�@�C�� ----------------------------------------------------------------

};



void ComRes_Init(){
	
	COMMON_RES* pData = &s_ComResTbl[0];

	if(eComResID_MAX == 0) return ;

	//�񓯊��ǂݍ��݊J�n
	//SetUseASyncLoadFlag(TRUE);

	for(int i = 0;i < eComResID_MAX;i++){
		if(pData->resType == eResType_Graphics){
			//�������̊m��
			pData->graph = (GRAPHICS_RES*)Memory_AllocZeroClear(sizeof(GRAPHICS_RES));
			//�摜�ǂݍ���
			Graphics_ASyncLoad(pData->graph,pData->fileName);
		}
		pData++;
	}
	//�񓯊��ǂݍ��ݏI��
	//SetUseASyncLoadFlag(FALSE);
}


void ComRes_Finalize(){
	
	COMMON_RES* pData = &s_ComResTbl[0];

	if(eComResID_MAX == 0) return ;

	for(int i = 0;i < eComResID_MAX;i++){
		if(pData->resType == eResType_Graphics){
			
			//�摜�̊J��
			Graphics_Delete(pData->graph);
			//�������̊J��
			Memory_SafeFree(pData->graph);

		}
		pData++;
	}


}

//���\�[�X�̓ǂݍ��݂��I���������H
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

//�摜�f�[�^��ԋp����
GRAPHICS_RES* ComRes_GetGraphics(eComResID comResID){
	COMMON_RES* pData = &s_ComResTbl[comResID];
	if(pData->resType != eResType_Graphics) return NULL;
	return pData->graph;
}

