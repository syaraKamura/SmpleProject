/*

	ゲームで汎用的に使用するヘッダーファイルやコードをまとめた
	汎用ソースファイル


*/
#include "GameCommon.h"


/*
	選択クランプ
	int*			val			:変更する値
	int				add			:加算する値
	int				min			:最小値
	int				max			:最大値
	eClampType		clampType	:クランプの種類
*/
void GameCommon_SelectClamp(int* val,int add,int min,int max,eClampType clampType){

	int value = *val;

	//値の加算
	value += add;


	if(clampType == eClampType_ClampStop){
		//最小値より小さい
		if(value <= min){
			value = min;	//最小値に補正
		}else if(value >= max){
			value = max;	//最大値に補正
		}

	}else if(clampType == eClampType_ClampLoop){
		if(value < min){
			value = max-1;	//最大値に補正
		}else if(value >= max){
			value = min;	//最小値に補正
		}
	}
	*val = value;

}

/*
	選択クランプ(float型)
	float*		val			:変更する値
	float		add			:加算する値
	float		min			:最小値
	float		max			:最大値
	eClampType	clampType	:クランプの種類
*/
void GemeCommon_SelectClampF(float* val,float add,float min,float max,eClampType clampType){

	float value = *val;

	//値の加算
	value += add;


	if(clampType == eClampType_ClampStop){
		//最小値より小さい
		if(value < min){
			value = min;	//最小値に補正
		}else if(value >= max){
			value = max;	//最大値に補正
		}

	}else if(clampType == eClampType_ClampLoop){
		if(value <= min){
			value = max;	//最大値に補正
		}else if(value >= max){
			value = min;	//最小値に補正
		}
	}
	*val = value;

}