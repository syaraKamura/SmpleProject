#include "Common/GameCommon/GameCommon.h"
#include "Common/Global/GameData.h"

#include "Scene/Scene.h"
#include "TestMenu.h"

#include "MyLib/GraphcisAnimationPlayer/GraphcisAnimationPlayer.h"

#ifdef __MY_DEBUG__

#define TEST_SCENE_NUM (sizeof(s_SceneTbl)/sizeof(s_SceneTbl[0]))

typedef struct{
	char sceneName[128];
	eSceneId scene;
}TEST_MENU_TBL;

static TEST_MENU_TBL  s_SceneTbl[] = {

	{"Title"				,eSceneId_Title				},
	{"GameMain"				,eSceneId_GameMain			},
	{"Test"					,eSceneId_Test				},
	{"TestGames"			,eSceneId_TestGames			},
	{"TestCommunication"	,eSceneId_TestCommunication	},


};

static int s_select;

void TestMenu_Init(){
	s_select = 0;
	
	//ÉeÉXÉgêÈåæÇ…Ç¬Ç´å„Ç≈è¡Ç∑ÇÊ
	//int* ix = Task_CreateBase(NULL,NULL,NULL,int,eTaskClassType_Class00);

}

void TestMenu_Updata(){

	if(Keyboard_Press(KEY_INPUT_UP)){
		s_select = (s_select + (TEST_SCENE_NUM-1)) % TEST_SCENE_NUM;
	}
	else if(Keyboard_Press(KEY_INPUT_DOWN)){
		s_select = (s_select + 1) % TEST_SCENE_NUM;
	}
	else if(Keyboard_Press(KEY_INPUT_Z)){
		Scene_Change(s_SceneTbl[s_select].scene);

	}


}

void TestMenu_Draw(){

	int x = 2;
	int y = 5;

	Debug_Printf(x,y++,GetColor(255,255,255),"-- TEST MENU SELECT --");
	y++;
	Debug_Printf(x,y + s_select,GetColor(255,255,255),"Å†");
	x+= 2;

	for(int i = 0;i < TEST_SCENE_NUM;i++){
		Debug_Printf(x,y++,GetColor(255,255,255),s_SceneTbl[i].sceneName);
	}
	
	y++;

	GameData_Save();
	GameData_Load();

}

void TestMenu_Finalize(){

}

#endif
