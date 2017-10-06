/*�����̃��C���ł��قƂ�ǂ�����Ȃ����炻�̂܂܂��ȁH*/


#include"Common/GameCommon/GameCommon.h"
#include "Code\Scene\Scene.h"

static void _Initialize();
static void _Finalize();
static void _Updata();
static void _Draw();

static FRAMEWORK_DATA s_Framework = {
	_Initialize,
	_Finalize,
	_Updata,
	_Draw,
};


int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	
	SetWindowText("Sample");
	SetGraphMode(WINDOW_WIDTH,WINDOW_HEIGHT,32);

//�f�o�b�O���͂����Ɠ����悤�ɂ��Ă���
#ifdef __MY_DEBUG__
		SetAlwaysRunFlag(TRUE);
		DxSetAllocPrintFlag(FALSE);
		SetDoubleStartValidFlag(TRUE);

		//���������[�N�̏󋵂��Q�[���I�����ɏo�͂���
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#endif 

    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

		// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D( TRUE ) ;

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D( TRUE ) ;

	//_Initialize();

	Framework_Init(s_Framework);

    // while( ����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A, )
	while( ProcessMessage()==0 && Keyboard_Off(KEY_INPUT_ESCAPE)){
		
		clsDx();

		//�L�[���͍X�V�@���@��ԍŏ��Ɏ����Ă���
		Keyboard_Updata();	
		Touch_Updata();

		//_Updata();
		//_Draw();

		Framework_UpdataBgin();
		Framework_Draw();
		Framework_UpdataEnd();

	}

	//_Finalize();
	
	Framework_Finalize();

    DxLib_End(); // DX���C�u�����I������
    return 0;
}


static bool isDebugMenuDisp = false;

/*
	������
*/
static void _Initialize(){

#ifdef __MY_DEBUG__
	Debug_Initialize();
#endif //__MY_DEBUG__

	Task_Init();
	Scene_Init();

}

/*
	�I������
*/
static void _Finalize(){

	Task_Finalize();

	Scene_Finalize();
	
#ifdef __MY_DEBUG__
	Debug_Finalize();
#endif

}

/*
	�@�X�V
*/
static void _Updata(){

#ifdef __MY_DEBUG__
	
	if(Keyboard_On(KEY_INPUT_LCONTROL) && Keyboard_Press(KEY_INPUT_N)){
		isDebugMenuDisp = isDebugMenuDisp ? false : true;
	}
	
	if(isDebugMenuDisp){
		Debug_Updata();

	}else{
		Task_Entory();

		Scene_Updata();
		
		Task_Updata();
	}

	

#else 

	Task_Entory();

	Scene_Updata();
		
	Task_Updata();

#endif	//__MY_DEBUG__
	
		

}

/*
	�`��
*/
static void _Draw(){

#ifdef __MY_DEBUG__

	Scene_Draw();

	Task_Draw();
	
	Task_Dalete();

	if(isDebugMenuDisp){
		Debug_Draw();
	}


#else 
	
	Scene_Draw();

	Task_Draw();
	
	Task_Dalete();
	
#endif	//__MY_DEBUG__


}
