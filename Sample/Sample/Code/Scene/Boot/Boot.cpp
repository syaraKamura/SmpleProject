#include "Scene/Scene.h"
#include "Common/CommonRes/CommonRes.h"
#include "Common/Global/GameData.h"

#include "Boot.h"

#ifdef __MY_DEBUG__
eSceneId scene = eSceneId_TestMenu;
#else
eSceneId scene = eSceneId_Title;
#endif


void Boot_Init(){

	//�Q�[���f�[�^�̏�����
	GameData_Initialize();

	ComRes_Init();
}

void Boot_Finalize(){
	ComRes_Finalize();
}

void Boot_Updata(){
	if(ComRes_IsLoadEnd()){
		Scene_Change(scene);
	}
}
