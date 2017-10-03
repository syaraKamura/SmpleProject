/*

		相互受信のサンプルを作成する

		目標　簡易シューティングゲームを作成する

		1.自機と敵の座標を送受信して受け取る

			座標X
			座標Y
			現在体力
			弾の威力
			
		2.敵の座標は、画面上部へ移るようにする

		3.弾の情報は以下の情報を送受信する

			弾が発射した
			
		4.弾の情報を受け取ったら敵の弾のその後の挙動はすべて受信側が更新する

		5.勝敗判定用データを受け取る

			フラグ_勝ち
			フラグ_負け

		6.タイトルへ

*/


#ifdef __MY_DEBUG__

#include "Common/GameCommon/GameCommon.h"
#include "TestCommunication.h"

enum eSubStep{

	eSubStep_Select,			//送信か受信か設定
	eSubStep_Transmission,		//送信
	eSubStep_Reception,			//受信
	eSubStep_InputIpAddress,	//Ipアドレス入力

};

enum eStep{
	eStep_Init,
	eStep_Fade,
	eStep_Main,
	eStep_Exit,
	eStep_ExitDone,
};


typedef struct{

	int hp;
	int mp;
	int atk;
	int def;
	int spd;

	int posX;
	int posY;

	short shotFlag;

}TEST_PARAM_DATA;

typedef struct{
	int posX;
	int posY;
	bool isShot;
}TEST_SHOT_DATA;

typedef struct{
	int x;
	int y;
	char listName[256];
	eSubStep step;
}LIST_DATA_TBL;

typedef struct{ 
	
	eStep step;
	eSubStep subStep;
	int cnt;
	int selectY;
	SOCKAT_OBJ sockatTransmission;		//送信ソケット
	SOCKAT_OBJ sockatReception;			//受信ソケット
	TEST_PARAM_DATA* pReveptionData;	//受信したデータ
	bool isTransimision;				//送信が成功したか？

	TEST_SHOT_DATA recepotionShot[100];	//受信側のショットデータ

	KEY_INPUT_STRING_OBJ* keyInputObj;	//文字列入力


}WORK_OBJ;


const LIST_DATA_TBL cList[] = {
	{20,40,"送信する",				eSubStep_Transmission				},
	{20,60,"受信する",				eSubStep_Reception					},
	{20,80,"IPアドレスを入力する",	eSubStep_InputIpAddress				},

};


//送信データ
TEST_PARAM_DATA testData = {100,20,10,5,4,200,400,0};

static WORK_OBJ* s_pWork;

/*
	ステップの設定をする
	WORK_OBJ*	ix
	eStep		step
*/
void _SetNextStep(WORK_OBJ* ix,eStep step){

	ix->step = step;
	ix->cnt = 0;

}


/*
	送信更新処理
*/
static  void _TransmissionProc(WORK_OBJ* ix){

	
	if(Keyboard_Press(KEY_INPUT_X)){
		
		//ステップを送受信選択へ
		ix->subStep = eSubStep_Select;
		
		//設定したデータがない状態にする
		ix->sockatTransmission.pTrasmissionData = NULL;
		
		//接続を切る
		Communication_CloseNetWork(&ix->sockatTransmission);
		
		//接続開始状態へ移行
		ix->cnt = 0;

		//これより下の処理をしないように関数から抜ける
		return ;
	}


	//弾を打っていない状態にする
		testData.shotFlag = 0;
	if(Keyboard_Press(KEY_INPUT_Z)){
		//弾を打っている状態にする
		testData.shotFlag = 1;
	}

	if(Keyboard_On(KEY_INPUT_DOWN)){
		testData.posY ++;
		
	}else if(Keyboard_On(KEY_INPUT_UP)){
		testData.posY --;	
	}

	if(Keyboard_On(KEY_INPUT_RIGHT)){
		testData.posX ++;
		
	}else if(Keyboard_On(KEY_INPUT_LEFT)){
		testData.posX --;	
	}


	//カウントが0 または 接続がされていない
	if(ix->cnt == 0 || Communicaition_GetCommunicationFlag(&ix->sockatTransmission) == false){
		//送信データ
		//TEST_PARAM_DATA testData = {10,20,30,5};
		//接続開始
		Communication_ConnectNetWork(&ix->sockatTransmission);
		//送信する値を設定
		Communication_SetTransmissionData(&ix->sockatTransmission,&testData,sizeof(TEST_PARAM_DATA));
		ix->cnt ++;
	}else{

		//送信する値を再設定する
		Communication_SetTransmissionData(&ix->sockatTransmission,&testData,sizeof(TEST_PARAM_DATA));

		//送信開始
		if(Communication_Transmission(&ix->sockatTransmission)){
			ix->isTransimision = true;
		}else{
			ix->isTransimision = false;
		}

		ix->cnt ++;
	}
}

/*
	受信更新処理
	WORK_OBJ* ix
*/
void _ReceptionProc(WORK_OBJ* ix){

	if(Keyboard_Press(KEY_INPUT_X)){
		//初期化する
		ix->sockatReception.netHandle = -1;
			
		//接続待ち状態へ移行
		ix->cnt = 0;

		//データをない状態にする
		//ix->pReveptionData = NULL;

		//選択画面へ移行
		ix->subStep = eSubStep_Select;

		//これより下の処理をしないように関数から抜ける
		return ;
	}

	if(ix->cnt == 0 ){
		//接続受付開始
		Communication_StartReception(&ix->sockatReception);
		ix->cnt++;
	}else if(ix->cnt == 1){

		//接続完了するまで待つ
		bool isReception = Communication_WaitReception(&ix->sockatReception);
		
		//接続が完了しているなら
		if(isReception == true){
			ix->cnt++;
		}
	}else{

		//データを受け取ったのであれば
		if(Communication_IsNotAcquiredReception(&ix->sockatReception) == true){
			//データを取得する
			ix->pReveptionData = (TEST_PARAM_DATA*)Communication_GetReceptionData(&ix->sockatReception);
		

			/*
				接続が終了したか判断する
			*/

			int lostNetWork = -1;
			//接続が切断されたネットワークハンドルを受け取る
			lostNetWork = GetLostNetWork();

			//接続が切断されたネットワークハンドルが現在接続してるネットワークハンドルであるならば
			if(lostNetWork == ix->sockatReception.netHandle){

				//初期化する
				ix->sockatReception.netHandle = -1;
			
				//接続待ち状態へ移行
				ix->cnt = 0;

				//データをない状態にする
				//ix->pReveptionData = NULL;

			}
			//接続が切断されていないならば
			else{

				/*受け取ったデータをもとに弾を飛ばす*/

				//ショットフラグが1であるなら
				if(ix->pReveptionData->shotFlag == 1){
					//使用可能な弾を探し
					for(int i = 0;i < 100;i++){
						if(ix->recepotionShot[i].isShot == false){
							//初期値を設定する
							ix->recepotionShot[i].posX = ix->pReveptionData->posX;
							ix->recepotionShot[i].posY = ix->pReveptionData->posY;
							//打ち出し中に設定
							ix->recepotionShot[i].isShot = true;
							break;
						}
					}
				}


				for(int i = 0;i < 100;i++){
					//打ち出し中の弾があれば
					if(ix->recepotionShot[i].isShot == true){
						//上方向に弾を移動させ
						ix->recepotionShot[i].posY -= 8;
						//画面外へ出てしまったら
						if(ix->recepotionShot[i].posY < -32){
							//打ち出し中でない状態にする
							ix->recepotionShot[i].isShot = false;
						}
					}
				}

			}

		}

	}

}

static void _SubProc(WORK_OBJ* ix){

	switch(ix->subStep){
	case eSubStep_Select:

		if(Keyboard_Press(KEY_INPUT_DOWN)){
			GameCommon_SelectClamp(&ix->selectY,1,0,3,eClampType_ClampLoop);
		}else if(Keyboard_Press(KEY_INPUT_UP)){
			GameCommon_SelectClamp(&ix->selectY,-1,0,3,eClampType_ClampLoop);
		}

		if(Keyboard_Press(KEY_INPUT_Z)){
			ix->subStep = cList[ix->selectY].step;
			if(cList[ix->selectY].step == eSubStep_InputIpAddress){
				//文字入力をアクティブにする
				KeyInputString_KeyInputActive(ix->keyInputObj);
			}
		}

		//前のシーンへ戻る
		if(Keyboard_Press(KEY_INPUT_X)){
			Scene_Change(Scene_GetPrevSceneId());
		}


		break;
	case eSubStep_Transmission:
		_TransmissionProc(ix);
		break;
	case eSubStep_Reception:

		_ReceptionProc(ix);
		break;
	case eSubStep_InputIpAddress:
	

		//文字入力が終了しているなら
		if(KeyInputString_IsEndKeyInput(ix->keyInputObj) == true){

			//入力した文字を受け取る


			//サブステップを選択ステップへ
			ix->subStep = eSubStep_Select;

		}
		



		break;
	}

}

//更新処理
static void _Updata(WORK_OBJ* ix){

	switch(ix->step){

	case eStep_Init:
		_SetNextStep(ix,eStep_Fade);
		break;
	case eStep_Fade:
		_SetNextStep(ix,eStep_Main);
		break;
	case eStep_Main:
		_SubProc(ix);
		break;
	case eStep_Exit:

		break;
	case eStep_ExitDone:

		break;
	}


}

//描画処理
static void _Draw(WORK_OBJ* ix){

	//メインステップでなければ処理を抜ける
	if(ix->step != eStep_Main) return ;


	switch(ix->subStep){
	case eSubStep_Select:
	
		{
			DrawString(0,ix->selectY*20 + 40,"◇",COLOR_WHITE);
		
			int length = sizeof(cList) / sizeof(cList[0]); 

			for(int i = 0;i < length;i++){
				DrawString(cList[i].x,cList[i].y,cList[i].listName,COLOR_WHITE);
			}
		}

		break;
	case eSubStep_Transmission:
		
		{
			
			//データが存在しているならば
			if( ix->isTransimision ){
				DrawString(0,20,"送信成功！",COLOR_WHITE);

				DrawString(0,60 ,"受信先の◇を操作できるよ！",COLOR_WHITE);
				DrawString(0,80 ,"十字キー: 移動",COLOR_WHITE);
				DrawString(0,100,"Zキー   : 球を打つ",COLOR_WHITE);
				
				ix->sockatTransmission.pTrasmissionData = NULL;
			}else{

				//データを受け取る
				const TEST_PARAM_DATA* pData = (TEST_PARAM_DATA*)ix->sockatTransmission.pTrasmissionData;

				DrawString(0,20,"送信中...",COLOR_WHITE);
				//データが設定あるなら描画する
				if(pData){
					DrawFormatString(0,40,COLOR_WHITE,"HP:%d MP:%d ATK:%d DEF:%d SPD:%dを送信中",pData->hp,pData->mp,pData->atk,pData->def,pData->spd);
				}
			}

		}


		break;
	case eSubStep_Reception:
		
		//データが設定あるなら描画する
		if(ix->pReveptionData){
			DrawString(0,20,"受信成功！",COLOR_WHITE);
			DrawFormatString(0,40,COLOR_WHITE,"HP:%d MP:%d ATK:%d DEF:%d SPD:%dを受信！",ix->pReveptionData->hp,ix->pReveptionData->mp,ix->pReveptionData->atk,ix->pReveptionData->def,ix->pReveptionData->spd);
			
			//弾の描画
			for(int i = 0;i < 100;i++){
				//打ち出し中の弾があれば弾を描画する
				if(ix->recepotionShot[i].isShot == true){
					DrawString(ix->recepotionShot[i].posX,ix->recepotionShot[i].posY,"◎",COLOR_RED);
				}
			}

			//受け取った座標位置に描画する
			DrawString(ix->pReveptionData->posX,ix->pReveptionData->posY,"◇",COLOR_WHITE);

		}else{
			DrawString(0,20,"受信中...",COLOR_WHITE);
		}

		break;
	}

}


void TestCommunication_Init(){

	WORK_OBJ* ix = (WORK_OBJ*)Memory_AllocZeroClear(sizeof(WORK_OBJ));

	if( ix != NULL ){

		//送信ソケットの初期化	使用しているパソコンが使用しているIPアドレスでなければ受信することができないので要注意！
		Communication_Initialize(&ix->sockatTransmission,Commuination_GetIPAddres(192,168,11,2),9850);

		//受信ソケットの初期化　
		memset(&ix->sockatReception,0,sizeof(SOCKAT_OBJ));
		//ポート番号設定
		ix->sockatReception.port = 9850;

		ix->selectY = 0;

		ix->pReveptionData = NULL;

		ix->isTransimision = false;

		ix->subStep = eSubStep_Select;
		ix->step = eStep_Init;

		//文字列入力生成
		ix->keyInputObj = KeyInputString_Create(100,300,eKeyInputStringType_SingCharOnly);

		s_pWork = ix;
	}

}

void TestCommunication_Updata(){
	_Updata(s_pWork);
}

void TestCommunication_Draw(){
	_Draw(s_pWork);
}

void TestCommunication_Finalize(){


	Communication_Finalize(&s_pWork->sockatTransmission);
	Communication_Finalize(&s_pWork->sockatReception);

	KeyInputString_Destroy(s_pWork->keyInputObj);

	//メモリの開放
	Memory_SafeFree(s_pWork);

}

#endif