/*
				ファイル名		:Sound.h
				作成者			:
				作成日時		:2017/08/16
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __SOUND_H__
#define __SOUND_H__

//	------- インクルード宣言

//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

enum eSoundType{
	eSoundType_BGM,
	eSoundType_SE,
	eSoundType_NONE,
};

//	------- 構造体&共用体

typedef struct{
	int handle;				//サウンドハンドル
	int valum;				//音量
	int startPos;			//再生開始位置
	int endPos;				//再生終了位置
	eSoundType soundType;	//サウンドの種類
}SOUND_DATA;

//	------- グローバル関数

/*
	サウンドデータ読み込み
	SOUND_DATA*		snd			:
	const char*		fileName	:ファイル名
	eSoundType		soundType	:サウンドの種類
	*/
extern void Sound_LoadBase(SOUND_DATA* snd,const char* fileName,eSoundType soundType);

/*
	非同期でサウンドデータ読み込み
	SOUND_DATA*		snd			:
	const char*		fileName	:ファイル名
	eSoundType		soundType	:サウンドの種類
*/
extern void Sound_ASyncLoad(SOUND_DATA* snd,const char* fileName,eSoundType soundType);

/*
	非同期読み込みが終了したか判断をする
	SOUND_DATA*		snd
	return	true	:非同期読み込みが終了した
			false	:非同期読み込み中
*/
extern bool Sound_IsEndASyncLoad(SOUND_DATA* snd);

/*
	再生する
	SOUND_DATA*		snd
*/
extern void Sound_Play(SOUND_DATA* snd);

/*
	一時停止する
	SOUND_DATA*		snd
*/
extern void Sound_Stop(SOUND_DATA* snd);
/*
	削除する
	SOUND_DATA*		snd
*/
extern void Sound_Delete(SOUND_DATA* snd);
/*
	再生中か判断する
	SOUND_DATA*		snd
	return	true	:再生中
			false	:最中ではない
*/
extern bool Sound_IsCheckPlaySound(SOUND_DATA* snd);

//	------- インライン関数(ヘッダー内関数)

#endif	//__SOUND_H__