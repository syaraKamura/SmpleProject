/*
				ファイル名		:Framework.cpp
				作成者			:
				作成日時		:2017/09/30
				ソース説明		:
				
				
				備考
				
				
				
!*/

//	------- インクルード宣言
#include "DxLib.h"

#include "Framework.h"
//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

//	------- 構造体&共用体

//	------- データテーブル

//	------- スタティック変数宣言

//	------- グローバル変数宣言

//	------- スタティックプロトタイプ宣言(内部関数)

//	------- プロトタイプ宣言していないスタティック関数(内部関数)

//	------- グローバル関数


class FPS {

private:

	float m_FrameRate;
	int m_Counter;
	int m_StartTime;
	int m_Fps;
	int m_smpleNum;
	bool m_IsframeSkip;

public :

	/*
		コンストラクタ
	*/
	FPS(){
		m_FrameRate = 0;
		m_Counter= 0;
		m_StartTime = 0;
		m_IsframeSkip = false;
		m_Fps = 60;
		m_smpleNum = 60;
	}

	/*
		コンストラクタ
		フレームレート設定版
	*/
	FPS(int fps){
		m_FrameRate = 0;
		m_Counter= 0;
		m_StartTime = 0;
		m_IsframeSkip = false;
		m_Fps = fps;
		m_smpleNum = 60;
	}

	/*
		コンストラクタ
		フレームレート、フレームレートのサンプル数設定版
	*/
	FPS(int fps,int sampleNum){
		m_FrameRate = 0;
		m_Counter= 0;
		m_StartTime = 0;
		m_IsframeSkip = false;
		m_Fps = fps;
		m_smpleNum = sampleNum;
	}

	~FPS(){

	}

	/*
		フレームレート計算処理
	*/
	bool Updata(){

		if(m_Counter == 0){
			m_StartTime = GetNowCount();
		}
		if(m_Counter == m_smpleNum){
			int t = GetNowCount();
			m_FrameRate = 1000.0f / ((t - m_StartTime) / (float)(m_Fps));
			m_Counter = 0;
			m_StartTime = t;

		}
		m_Counter++;
		return true;
	}

	/*
		待ち時間
	*/
	void Wait(){

		int tookTime = GetNowCount() - m_StartTime;				//かかった時間
		int waitTime = m_Counter * 1000.f / m_Fps - tookTime;	//待つべき時間

		if(waitTime > 0){
			m_IsframeSkip = false;
			Sleep(waitTime);
		}else {
			m_IsframeSkip = true;
		}

	}

	/*
		フレームレートを返却する
	*/
	float GetFps(){
		return m_FrameRate;
	}

	/*
		設定されているフレームレートの値を返却する
	*/
	int GetUserSetFps(){
		return m_Fps;
	}

	/*
		スキップするか返却する
		return	true	:スキップする
				false	:スキップしない
	*/
	bool IsSkip(){
		return m_IsframeSkip;
	}

};


static FPS s_fps;
static FRAMEWORK_DATA s_Framework;

/*
	framework初期化
	const FRAMEWORK_DATA cFramework	:frameworkを設定
	int fps							:フレームレートを設定(設定がなければ60fps)
	int fpsSample					:フレームレートのサンプル数を設定(設定がなければサンプル数60)
*/
void Framework_Init(const FRAMEWORK_DATA cFramework,int fps /*= 60*/,int fpsSample /*= 60*/){
	s_fps = FPS(fps,fpsSample);
	s_Framework = cFramework;

	if(s_Framework.InitFunc){
		s_Framework.InitFunc();
	}


}

/*
	framework終了処理
*/
void Framework_Finalize(){

	if(s_Framework.FinalzieFunc){
		s_Framework.FinalzieFunc();
	}

} 

/*
	更新処理開始
*/
void Framework_UpdataBgin(){

	if(!s_fps.IsSkip()){
		ClearDrawScreen();
	}
	s_fps.Updata();

	if(s_Framework.UpdataFunc){
		s_Framework.UpdataFunc();
	}


}

/*
	描画処理
*/
void Framework_Draw(){

	//スキップするなら処理を抜ける
	if(s_fps.IsSkip()) return;

	if(s_Framework.DrawFunc){
		s_Framework.DrawFunc();
	}

	int posX = WINDOW_WIDTH - 80;
	int posY = WINDOW_HEIGHT - 20;
	float anderLineFps = s_fps.GetUserSetFps() * 0.8f;

	unsigned int color = GetColor(255,255,255);

	if(s_fps.GetFps() > anderLineFps && s_fps.GetFps() <= s_fps.GetUserSetFps() - 0.5f){
		color = GetColor(255,255,0);
	}else if(s_fps.GetFps() < anderLineFps){
		color = GetColor(255,0,0);
	}

	DrawFormatString(posX,posY,color,"FPS:%0.1f",s_fps.GetFps());

}

/*
	更新処理終了
*/
void Framework_UpdataEnd(){

	if(!s_fps.IsSkip()){
		ScreenFlip();
	}
	s_fps.Wait();
}