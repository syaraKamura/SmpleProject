#pragma once


enum eSceneId{
	eSceneId_None = -1,
	eSceneId_Boot,
	eSceneId_Title,
	eSceneId_GameMain,

#ifdef __MY_DEBUG__
	
	eSceneId_TestMenu,
	eSceneId_Test,
	eSceneId_TestGames,
	eSceneId_TestCommunication,

#endif

	eSceneID_Max,

};

//�V�[���؂�ւ�
void Scene_Change(eSceneId next);

//�O��̃V�[�����擾����
eSceneId Scene_GetPrevSceneId();

//���̃V�[�����擾����
eSceneId Scene_GetNowSceneId();

void Scene_Init();
void Scene_Updata();
void Scene_Draw();
void Scene_Finalize();

#ifdef __MY_DEBUG__
	void dbg_Scene_DebugEntory();
#endif