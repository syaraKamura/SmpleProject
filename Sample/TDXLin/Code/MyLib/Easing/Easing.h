/*
				ファイル名		:Easing.h
				作成者			:
				作成日時		:2017/08/26
				ソース説明		:
				
					アニメーションイージング処理
				
				備考
				
				
    
				
!*/

#ifndef __EASING_H__
#define __EASING_H__

//	------- インクルード宣言

//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

enum eEasingType{

	eEasingType_Quadratic,
	eEasingType_Cubic,
	eEasingType_Quartic,
	eEasingType_Quintic,
	eEasingType_Sinusoidal,
	eEasingType_Exponential,
	eEasingType_Circular,

	eEasingType_Max,
};

enum eEasingInOut{
	eEasingInOut_In,
	eEasingInOut_Out,
	eEasingInOut_InOut,
	eEasingInOut_Max,
};


//	------- 構造体&共用体

//	------- グローバル関数

/*
	イージング処理を行う
	eEasingType		type		:イージングの種類
	eEasingInOut	inOut		:イージングがどの方向か
	float			time		:時間
	float			totalTime	:終了時間
	float			startPos	:初期位置
	float			endPos		:終了位置

	return　成功:計算結果を返却する
			失敗:必ず0.0fを返却する

*/
extern float Easing(eEasingType type,eEasingInOut inOut,float time,float totalTime,float startPos,float endPos);

//	------- インライン関数(ヘッダー内関数)


#endif // __EASING_H__