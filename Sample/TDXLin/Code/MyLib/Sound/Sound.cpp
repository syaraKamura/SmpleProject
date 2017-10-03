/*
				ファイル名		:Sound.cpp
				作成者			:
				作成日時		:2017/08/16
				ソース説明		:サウンド関係
				
				
				備考
				
				
				
!*/

//	------- インクルード宣言

#include "DxLib.h"
#include "Sound.h"

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

/*
	サウンドデータ読み込み
	SOUND_DATA*		snd			:
	const char*		fileName	:ファイル名
	eSoundType		soundType	:サウンドの種類
	*/
void Sound_LoadBase(SOUND_DATA* snd,const char* fileName,eSoundType soundType){

	snd->handle = LoadSoundMem(fileName);
	snd->valum = 255;
	snd->soundType = soundType;

}

/*
	非同期でサウンドデータ読み込み
	SOUND_DATA*		snd			:
	const char*		fileName	:ファイル名
	eSoundType		soundType	:サウンドの種類
*/
void Sound_ASyncLoad(SOUND_DATA* snd,const char* fileName,eSoundType soundType){
	SetUseASyncLoadFlag(TRUE);
	Sound_LoadBase(snd,fileName,soundType);
	SetUseASyncLoadFlag(FALSE);
}

/*
	非同期読み込みが終了したか判断をする
	SOUND_DATA*		snd
	return	true	:非同期読み込みが終了した
			false	:非同期読み込み中
*/
bool Sound_IsEndASyncLoad(SOUND_DATA* snd){
	if(CheckHandleASyncLoad(snd->handle) == FALSE){
		return true;
	}
	return false;
}

/*
	再生する
	SOUND_DATA*		snd
*/
void Sound_Play(SOUND_DATA* snd){

	//BGM再生
	if(snd->soundType == eSoundType_BGM){
		PlaySoundMem(snd->handle,DX_PLAYTYPE_LOOP);
	}
	//効果音再生
	else if(snd->soundType == eSoundType_SE){
		PlaySoundMem(snd->handle,DX_PLAYTYPE_BACK);
	}

}

/*
	一時停止する
	SOUND_DATA*		snd
*/
void Sound_Stop(SOUND_DATA* snd){
	StopSoundMem(snd->handle);
}

/*
	削除する
	SOUND_DATA*		snd
*/
void Sound_Delete(SOUND_DATA* snd){
	DeleteSoundMem(snd->handle);
}

/*
	再生中か判断する
	SOUND_DATA*		snd
	return	true	:再生中
			false	:最中ではない
*/
bool Sound_IsCheckPlaySound(SOUND_DATA* snd){

	if(CheckSoundMem(snd->handle) == FALSE){
		return false;
	}
	return true;
}

