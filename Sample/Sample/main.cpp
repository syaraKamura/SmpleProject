/*処理のメインでもほとんどいじらないからそのままかな？*/


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

//デバッグ時はずっと動くようにしておく
#ifdef __MY_DEBUG__
		SetAlwaysRunFlag(TRUE);
		DxSetAllocPrintFlag(FALSE);
		SetDoubleStartValidFlag(TRUE);

		//メモリリークの状況をゲーム終了時に出力する
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#endif 

    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定

		// Ｚバッファを有効にする
	SetUseZBuffer3D( TRUE ) ;

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D( TRUE ) ;

	//_Initialize();

	Framework_Init(s_Framework);

    // while( 裏画面を表画面に反映, メッセージ処理, 画面クリア, )
	while( ProcessMessage()==0 && Keyboard_Off(KEY_INPUT_ESCAPE)){
		
		clsDx();

		//キー入力更新　←　一番最初に持ってくる
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

    DxLib_End(); // DXライブラリ終了処理
    return 0;
}


static bool isDebugMenuDisp = false;

/*
	初期化
*/
static void _Initialize(){

#ifdef __MY_DEBUG__
	Debug_Initialize();
#endif //__MY_DEBUG__

	Task_Init();
	Scene_Init();

}

/*
	終了処理
*/
static void _Finalize(){

	Task_Finalize();

	Scene_Finalize();
	
#ifdef __MY_DEBUG__
	Debug_Finalize();
#endif

}

/*
	　更新
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
	描画
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
