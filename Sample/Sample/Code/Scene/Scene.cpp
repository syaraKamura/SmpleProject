#include "Common/GameCommon/GameCommon.h"

#include "Scene.h"
#include "Boot/Boot.h"
#include "GameMain/GameMain.h"
#include "Title/Title.h"

#ifdef __MY_DEBUG__

#include "Test/Test.h"
#include "Test/TestMenu/TestMenu.h"
#include "Test/TestGame/TestGameMgr.h"
#include "Test/TestCommunication/TestCommunication.h"

#endif


typedef struct{

	void (*Init)(void);		//�֐��|�C���^�[(������)
	void (*Update)(void);	//�֐��|�C���^�[(�X�V)
	void (*Draw)(void);		//�֐��|�C���^�[(�`��)
	void (*Finalize)(void);	//�֐��|�C���^�[(�I������)

	eSceneId eScene;
	char sceneName[64];

}SCENE;

//�V�[���̓o�^
static  SCENE s_ScnTbl[eSceneID_Max] = {

	//������						�X�V										�`��						�I������						//�V�[���ԍ�					//�V�[���̖��O
	{Boot_Init,						Boot_Updata,								NULL,						NULL,							eSceneId_Boot,					"Boot"				},
	{Title_Init,					Title_Updata,								Title_Draw,					Title_Finalize,					eSceneId_Title,					"Title"				},
	{GameMain_Init,					GameMain_UpData,							GameMain_Draw,				GameMmain_Finalize,				eSceneId_GameMain,				"GameMain"			},

#ifdef __MY_DEBUG__
	//�f�o�b�O���̂ݎg�p����V�[��
	{TestMenu_Init,					TestMenu_Updata,							TestMenu_Draw,				TestMenu_Finalize,				eSceneId_TestMenu,				"TestMenu"			},
	{Test_Init,						Test_Updata,								Test_Draw,					Test_Finalize,					eSceneId_Test,					"Test"				},
	{TestGameMgr_Init,				TestGameMgr_Updata,							TestGameMgr_Draw,			TestGameMgr_Finalize,			eSceneId_TestGames,				"TestGames"			},
	{TestCommunication_Init,		TestCommunication_Updata,					TestCommunication_Draw,		TestCommunication_Finalize,		eSceneId_TestCommunication,		"TestCommunication"	},
#endif

};

//�v���g�^�C�v�錾

#ifdef __MY_DEBUG__
	static void _Dbg_InfoDraw();	//�f�o�b�O���
#endif


static eSceneId s_PrevScene = eSceneId_None;		//�O��̃V�[��
static eSceneId s_NowScene = eSceneId_Boot;			//���̃V�[��
static eSceneId s_NextScene = eSceneId_None;		//���̃V�[��

static bool _SceneChangeProc(){

	
	if(s_NextScene != eSceneId_None){
		SCENE* pScn = &s_ScnTbl[s_NowScene];
		//�I�������֐������݂���Ȃ�
		if(pScn->Finalize){
			//�I���������s��
			pScn->Finalize();
		}
		
		s_PrevScene = s_NowScene;		//�O��̃V�[����ݒ�
		s_NowScene = s_NextScene;		//���̃V�[����ݒ�
		s_NextScene = eSceneId_None;	//���̃V�[�����Ȃ���Ԃɐݒ�
		
		//�V�[����؂�ւ����̂ł�����x�󂯎��
		pScn = &s_ScnTbl[s_NowScene];

		//�������֐������݂���Ȃ�
		if(pScn->Init){
			//�������������s��
			pScn->Init();
		}
		return false;
	}

	return true;

}

//���̃V�[���̐ݒ�
void Scene_Change(eSceneId next){
	s_NextScene = next;
}

//�O�̃V�[����ԋp����
eSceneId Scene_GetPrevSceneId(){
	return s_PrevScene;
}

//���̃V�[����ԋp����
eSceneId Scene_GetNowSceneId(){
	return s_NowScene;
}

void Scene_Init(){

#ifdef __MY_DEBUG__
	dbg_Scene_DebugEntory();
#endif 

	SCENE* pScn = &s_ScnTbl[s_NowScene];

	if(!pScn->Init) return;
	pScn->Init();
}

void Scene_Updata(){

	SCENE* pScn = &s_ScnTbl[s_NowScene];

	if( !_SceneChangeProc() || !pScn->Update) return;
	
	pScn->Update();
	
}

void Scene_Draw(){

	SCENE* pScn = &s_ScnTbl[s_NowScene];

	if(!pScn->Draw){		
		return;
	}

	pScn->Draw();

	
#ifdef __MY_DEBUG__
	_Dbg_InfoDraw();
#endif

}

void Scene_Finalize(){
	
	//�u�[�g�͕K���I��������������
	Boot_Finalize();
	
	SCENE* pScn = &s_ScnTbl[s_NowScene];

	if(!pScn->Finalize) return;
	
	pScn->Finalize();
}


#ifdef __MY_DEBUG__

	DEBUG_FUNC_DATA debug[] = {
		{"DispInfo",eDebugType_Flag,NULL,NULL,NULL,NULL,false},
	};

	//�f�o�b�O���
	static void _Dbg_InfoDraw(){

		if(Debug_IsFlag("Scene","DispInfo") == false ) return ;

		SCENE* pScn = &s_ScnTbl[s_NowScene];

		int drawPosX = WINDOW_WIDTH - 240;

		DrawBox(drawPosX,0,drawPosX + 180,100,GetColor(123,123,123),TRUE);
		DrawFormatString(drawPosX,0,GetColor(255,0,0), "SceneID    :%d",pScn->eScene);
		DrawFormatString(drawPosX,20,GetColor(255,0,0),"SceneName  :%s",pScn->sceneName);
		DrawFormatString(drawPosX,40,GetColor(255,0,0),"DxAlloc:%d",DxGetAllocSize());
		DrawFormatString(drawPosX,60,GetColor(255,0,0),"DxAllocNum:%d",DxGetAllocNum());
		DrawFormatString(drawPosX,80,GetColor(255,0,0),"MyAllocNum:%d",Memory_GetAllocNum());

	}

	void dbg_Scene_DebugEntory(){
		Debug_Entory(debug,"Scene",sizeof(debug));
	}

#endif