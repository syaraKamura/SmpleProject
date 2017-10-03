/*
				ファイル名		:GraphcisAnimationPlayer.cpp
				作成者			:
				作成日時		:2017/09/01
				ソース説明		:
					
					アニメーションをながす
				
				備考
				
				
				
!*/

//	------- インクルード宣言
#include "DxLib.h"

#include "GraphcisAnimationPlayer.h"

//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

//	------- 構造体&共用体

typedef struct{
	int keyFream;		//キーフレーム
	int offsetPosX;		//描画座標
	int offsetPosY;
	float scalX;		//画像サイズ
	float scalY;
	int alpah;			//アルファブレンド
	int graphicsKind;	//画像の種類
	int graphicsDivKind;//graphicsKindを参照した分割した画像の種類
}GRAPHICS_ANIMATION_INFO;

typedef struct{
	
	int setKeyFreamNum;		//キーフレームの設定数
	int nowKeyFrameNum;		//現在のキーフレーム番号

	int keyFrameMax;		//最大キーフレーム
	bool isLoop;			//ループ再生を行うか？
	GRAPHICS_ANIMATION_INFO* pGraphicsAnimationInfo;
	int frameCnt;			//キーフレームカウンター
}GRAPHICS_ANIMATION_DATA;

typedef struct{
	int animationDataNum;	//アニメーションデータの数
	int playAnmationDataNum;	//再生しているアニメーション番号
	GRAPHICS_ANIMATION_DATA* pAnimData;	//アニメーションデータ
}GRAPHICS_ANIMATION_PLAYER;

//	------- データテーブル

static GRAPHICS_ANIMATION_INFO infoTbl[] = {
	{0,20,100,1.0f,1.0f,255,0,0},
};

static GRAPHICS_ANIMATION_DATA animTbl[] = {
	{1,0,60,true,infoTbl,0},
};

static GRAPHICS_ANIMATION_PLAYER playerTbl[] = {

	{1,0,animTbl,}


};

//	------- スタティック変数宣言

//	------- グローバル変数宣言

//	------- スタティックプロトタイプ宣言(内部関数)

/*
	指定のアニメーション番号のアニメーションをする
*/
static void _PlayAnimation(GRAPHICS_ANIMATION_DATA* pData)
{
	//データがなければ処理をしない
	if(pData == NULL) return;

	
	//現在のキーフレーム番号
	int keyFrameNum = pData->nowKeyFrameNum;

	if(pData->setKeyFreamNum <= pData->nowKeyFrameNum){
		if(pData->isLoop == true){
			//キーフレームを0にし処理をいったん抜ける
			pData->frameCnt = 0;
			pData->nowKeyFrameNum = 0;
			return ;
		}else{
			//最大キーフレームなら処理を抜ける
			if(pData->keyFrameMax >= pData->frameCnt){
				return ;
			}
		}

	}
	//設定したキーフレームの数より少ない
	else if(pData->setKeyFreamNum > pData->nowKeyFrameNum){
		//次に設定されているキーフレーム以上キーフレームカウントがたくなったら
		if(pData->pGraphicsAnimationInfo[keyFrameNum+1].keyFream <= pData->frameCnt){
			//今のキーフレームを加算する
			pData->nowKeyFrameNum++;
		}
	}

	//キーフレーム加算
	pData->frameCnt++;
}

//	------- プロトタイプ宣言していないスタティック関数(内部関数)

//	------- グローバル関数

/*
	再生するアニメーション番号の設定を行う
*/
void GraphicsAnimationPlayer_Initialize(GRAPHICS_ANIMATION_PLAYER* pData,int animId){

	//データがなければ処理をしない
	if(pData == NULL) return;
	
	//アニメーション番号が範囲外なら処理処理を抜ける
	if(animId >= pData->animationDataNum || animId < 0) return ;


	//再生するアニメーション番号を設定する
	pData->playAnmationDataNum = animId;

}

void GraphicsAnimationPlayer_Updata(GRAPHICS_ANIMATION_PLAYER* pData){

	//データがなければ処理をしない
	if(pData == NULL) return;
	
	int animId = pData->playAnmationDataNum;

	//アニメーション番号が範囲外なら処理処理を抜ける
	if(animId >= pData->animationDataNum || animId < 0) return ;

	GRAPHICS_ANIMATION_DATA* pAnimData = &pData->pAnimData[animId];

	_PlayAnimation(pAnimData);


}

void GraphicsAnimationPlayer_Draw(GRAPHICS_ANIMATION_PLAYER* pData,int posX,int posY){

	//データがなければ処理をしない
	if(pData == NULL) return;

}




void GraphicsAnimationPlayer_TestUpdata(){
	
	GraphicsAnimationPlayer_Updata(&playerTbl[0]);

}