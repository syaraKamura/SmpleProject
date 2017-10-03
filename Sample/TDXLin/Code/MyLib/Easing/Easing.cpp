/*
				ファイル名		:Easing.cpp
				作成者			:
				作成日時		:2017/08/26
				ソース説明		:
					
					アニメーションイージング処理
				
				備考
				
	
				
				
!*/

//	------- インクルード宣言
#include "DxLib.h"

#include <math.h>

#include "Easing.h"
//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

//	------- 構造体&共用体

typedef struct{
	float (*easing)(float time,float totalTime,float startPos,float endPos);
}EASING_FUNC_DATA;




//	------- スタティック変数宣言

//	------- グローバル変数宣言

//	------- スタティックプロトタイプ宣言(内部関数)

//	------- プロトタイプ宣言していないスタティック関数(内部関数)


// -- Quadratic

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos	:初期位置
	float			endPos		:終了位置

	return　成功:計算結果を返却する
*/
static float _Quadratic_In(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;
	return endPos * time* time + startPos;
}

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos			:初期位置
	float			endPos			:終了位置

	return　成功:計算結果を返却する
*/
static float _Quadratic_Out(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;
	return -endPos * time* time + startPos;

}

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos			:初期位置
	float			endPos			:終了位置

	return　成功:計算結果を返却する
*/
static float _Quadratic_InOut(float time,float totalTime,float startPos,float endPos){

	time /= (totalTime/ 2.0f);

	if(time < 1.0f){
		return endPos / 2.0f * time* time + startPos;
	}

	time = time - 1.0f;
	
	return -endPos / 2.0f * (time * (time - 2.0f) - 1.0f) + startPos;
}

// -- Cubic

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos			:初期位置
	float			endPos			:終了位置

	return　成功:計算結果を返却する
*/
static float _Cubic_In(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;
	return endPos * time * time * time + startPos;
	
	/*
					
		time : 時間(進行度)
		endPos : 開始の値(開始時の座標やスケールなど)
		startPos : 開始と終了の値の差分
		totalTiem : Tween(トゥイーン)の合計時間

	*/


}

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos			:初期位置
	float			endPos			:終了位置

	return　成功:計算結果を返却する
*/
static float _Cubic_Out(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;
	time = time - 1.0f;
	return endPos * time * time * time + startPos;
}

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos	:初期位置
	float			endPos		:終了位置

	return　成功:計算結果を返却する
*/
static float _Cubic_InOut(float time,float totalTime,float startPos,float endPos){

	time /= (totalTime/ 2.0f);

	if(time < 1.0f){
		return endPos / 2.0f * time* time * time + startPos;
	}

	time = time - 2.0f;
	
	return endPos / 2.0f * (time * time* time + 2.0f) + startPos;

	return 0.0f;
}

// -- Quartic

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos	:初期位置
	float			endPos		:終了位置

	return　成功:計算結果を返却する
*/
static float _Quartic_In(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;

	return endPos * time * time * time * time + startPos;

}

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos			:初期位置
	float			endPos			:終了位置

	return　成功:計算結果を返却する
*/
static float _Quartic_Out(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;
	time = time - 1.0f;

	return -endPos * (time * time * time * time - 1.0f) + startPos;
}

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos			:初期位置
	float			endPos			:終了位置

	return　成功:計算結果を返却する
*/
static float _Quartic_InOut(float time,float totalTime,float startPos,float endPos){

	time /= totalTime / 2.0f;

	if( time < 1.0f ){

		return endPos / 2.0f * time * time * time * time + startPos;
	}

	return -endPos / 2.0f * (time * time * time * time - 2.0f) + startPos;
}

// -- Quintic

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos			:初期位置
	float			endPos			:終了位置

	return　成功:計算結果を返却する
*/
static float _Quintic_In(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;

	return endPos * time * time * time * time * time + startPos;

}

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos			:初期位置
	float			endPos			:終了位置

	return　成功:計算結果を返却する
*/
static float _Quintic_Out(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;

	time = time - 1.0f;

	return endPos * (time * time * time * time * time + 1) + startPos;

}

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos			:初期位置
	float			endPos			:終了位置

	return　成功:計算結果を返却する
*/
static float _Quintic_InOut(float time,float totalTime,float startPos,float endPos){

	time /= totalTime / 2.0f;

	if(time < 1.0f){
		return endPos / 2.0f * time * time * time * time * time + startPos; 
	}

	time = time - 2.0f;

	return endPos / 2.0f * (time * time * time * time * time + 2.0f) + startPos;
}

// -- Sinusoidal

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos			:初期位置
	float			endPos			:終了位置

	return　成功:計算結果を返却する
*/
static float _Sinusoidal_In(float time,float totalTime,float startPos,float endPos){

	return -endPos * cos(time / totalTime * (DX_PI_F / 2.0f)) + endPos + startPos;
}

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos			:初期位置
	float			endPos			:終了位置

	return　成功:計算結果を返却する
*/
static float _Sinusoidal_Out(float time,float totalTime,float startPos,float endPos){

	return endPos * sin(time / totalTime * (DX_PI_F / 2.0f)) + startPos;
}

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos			:初期位置
	float			endPos			:終了位置

	return　成功:計算結果を返却する
*/
static float _Sinusoidal_InOut(float time,float totalTime,float startPos,float endPos){

	return -endPos / 2.0f * (cos(DX_PI_F * time / totalTime) - 1.0f) + startPos;
}

// -- Exponential

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos			:初期位置
	float			endPos			:終了位置

	return　成功:計算結果を返却する
*/
static float _Exponential_In(float time,float totalTime,float startPos,float endPos){

	return endPos * 2.0f * (10.0f * (time / totalTime - 1.0f)) *  (10.0f * (time / totalTime - 1.0f)) + startPos;
}

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos			:初期位置
	float			endPos			:終了位置

	return　成功:計算結果を返却する
*/
static float _Exponential_Out(float time,float totalTime,float startPos,float endPos){

	return endPos * (-(2.0f * (-10.0f * time/totalTime) * (-10.0f * time/totalTime)) + 1.0f) + startPos;
}

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos			:初期位置
	float			endPos			:終了位置

	return　成功:計算結果を返却する
*/
static float _Exponential_InOut(float time,float totalTime,float startPos,float endPos){

	time /= time / 2.0f;

	if( time < 1.0f){
		return endPos / 2.0f * 2.0f * (10.0f * (time - 1.0f)) * (10.0f * (time - 1.0f)) + startPos;
	}

	return endPos / 2.0f * (-(2.0f * (-10.0f * time) * (-10.0f * time)) + 2.0f) + startPos;
}

// -- Circular

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos	:初期位置
	float			endPos		:終了位置

	return　成功:計算結果を返却する
*/
static float _Circular_In(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;
	return -endPos * (sqrt(1.0f - time * time) - 1.0f) + startPos;
	
}

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos	:初期位置
	float			endPos		:終了位置

	return　成功:計算結果を返却する
*/
static float _Circular_Out(float time,float totalTime,float startPos,float endPos){

	time /= totalTime;

	time = time - 1.0f;

	return endPos * sqrt(1.0f - time * time ) + startPos;
}

/*
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos	:初期位置
	float			endPos		:終了位置

	return　成功:計算結果を返却する
*/
static float _Circular_InOut(float time,float totalTime,float startPos,float endPos){

	time /= time / 2.0f;
	
	if(time < 1.0f){
		return -endPos / 2.0f * (sqrt(1.0f - time * time) -1.0f); 
	}

	time = time - 2.0f;

	return endPos / 2.0f * (sqrt(1.0f - time + time) + 1.0f) + startPos;
}



//	------- グローバル関数



//	------- データテーブル
static EASING_FUNC_DATA s_EasingFuncTbl[eEasingType_Max][eEasingInOut_Max] = {
	
	//	IN					OUT					INOUT
	{	_Quadratic_In,		_Quadratic_Out,		_Quadratic_InOut	},		//Quadratic
    {	_Cubic_In,			_Cubic_Out,			_Cubic_InOut		},		//Cubic
    {	_Quartic_In,		_Quartic_Out,		_Quartic_InOut		},		//Quartic
    {	_Quintic_In,		_Quintic_Out,		_Quintic_InOut		},		//Quintic
    {	_Sinusoidal_In,		_Sinusoidal_Out,	_Sinusoidal_InOut	},		//Sinusoidal
    {	_Exponential_In,	_Exponential_Out,	_Exponential_InOut	},		//Exponential
    {	_Circular_In,		_Circular_Out,		_Circular_InOut		},		//Circular

};


/*
	イージング処理を行う
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos			:初期位置
	float			endPos			:終了位置

	return　成功:計算結果を返却する
			失敗:必ず0.0fを返却する

*/
float Easing(eEasingType type,eEasingInOut inOut,float time,float totalTime,float startPos,float endPos){
	
	//範囲外が指定されたら処理をしない
	if(type >= eEasingType_Max || type < eEasingType_Quadratic) return 0.0f;
	if(inOut >= eEasingInOut_Max || inOut < eEasingInOut_In)	return 0.0f;

	EASING_FUNC_DATA* easing = &s_EasingFuncTbl[type][inOut];

	//関数ポインターがNULLなら処理を抜ける
	if(easing == NULL) return 0.0f;
	return easing->easing(time,totalTime,startPos,endPos);

}
