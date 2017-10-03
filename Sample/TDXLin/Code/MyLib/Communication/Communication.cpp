/*

	通信関係
*/


//	------- インクルード宣言
#include "DxLib.h"
#include "Communication.h"
#include "MyLib/Memory/Memory.h"

#ifdef __WINDOWS__

//	------- 固定定数宣言

//	------- 列挙体

//	------- 構造体&共用体

//	------- データテーブル

//	------- スタティック変数

//	------- グローバル変数

//	------- スタティックプロトタイプ宣言

//	------- プロトタイプ宣言していないスタティック関数

//	------- グローバル関数



//	------- ユーザー使用関数

/*
	初期化
	SOCKAT_OBJ* ix
	IPDATA		ip
	int			protNum
*/
void Communication_Initialize(SOCKAT_OBJ* ix,IPDATA ip,int portNum){
	
	//IPアドレスの設定
	ix->ip = ip;

	//接続ポートの設定
	ix->port = portNum;

	//データの初期化
	ix->pTrasmissionData = NULL;

	ix->pReceptionData = NULL;

	//ネットワークハンドルの初期化
	ix->netHandle = -1;

	//受信データ量の初期化
	ix->dataLength = 0;

}

/*
	終了処理
	SOCKAT_OBJ* ix
*/
void Communication_Finalize(SOCKAT_OBJ* ix){
	
	Memory_SafeFree(ix->pTrasmissionData);
	Memory_SafeFree(ix->pReceptionData);

	//接続を切る
	Communication_CloseNetWork(ix);
	
}

/*
	接続を開始する
	SOCKAT_OBJ* ix
*/
void Communication_ConnectNetWork(SOCKAT_OBJ* ix){
	//通信を確立
	ix->netHandle = ConnectNetWork(ix->ip,ix->port);
}

/*
	接続を切断する
	SOCKAT_OBJ* ix
*/
void Communication_CloseNetWork(SOCKAT_OBJ* ix){
	//接続されていなければ処理を抜ける
	if(ix->netHandle == -1) return ;
	//接続を切断
	CloseNetWork(ix->netHandle);
	//接続していない状態に設定
	ix->netHandle = -1;
}

/*
	受信待ちを開始する
	SOCKAT_OBJ* ix
*/
void Communication_StartReception(SOCKAT_OBJ* ix){
	PreparationListenNetWork( ix->port ) ;
}

/*
	受信が来るまで待つ
	SOCAKT_OBJ* ix
	return true: 受信した	false: 受信待ち
*/
bool Communication_WaitReception(SOCKAT_OBJ* ix){
	
	//接続されたか？
	//true: 接続された	false: 接続されていない
	bool isReception = false;

	//新しく接続があったらそのネットワークハンドルを受け取る
	ix->netHandle = GetNewAcceptNetWork();
	if(ix->netHandle == -1){
		isReception = false;
	}else{
		// 接続の受付を終了する
		StopListenNetWork() ;
		//接続してきたPCのIPアドレスを受け取る
		GetNetWorkIP( ix->netHandle , &ix->ip ) ;
		isReception = true;
	}
	return isReception;
}

/*
	データの送信
	SOCKAT_OBJ* ix
*/
bool Communication_Transmission(SOCKAT_OBJ* ix){

	//送信されたか？
	//true:送信された false:送信されていない
	bool isTransmission = false;

	//接続されているなら
	if(ix->netHandle != -1){		
		//データがなければ処理を抜ける
		if(ix->pTrasmissionData == NULL){
			isTransmission = false;
		}
		//データがあるならデータの送信を行う
		else{
			//データの送信
			NetWorkSend(ix->netHandle,ix->pTrasmissionData,ix->dataLength);
			isTransmission = true;
		}
	}

	return isTransmission;
}

/*
	取得していない受信データの量を取得する
	SOCKAT_OBJ* ix
	return	true	:取得していない受信データ量が0でない
			false	:取得していない受信データ量が0である
*/
bool Communication_IsNotAcquiredReception(SOCKAT_OBJ* ix){

	//取得していない受信データの量を取得する
	ix->dataLength = GetNetWorkDataLength(ix->netHandle);

	//取得していない受信データ量が0であるならfalseを返す
	if(ix->dataLength == 0){
		return false;
	}
	return true;
}


//	------- セッター関係関数
/*
	送信するデータを設定する
	SOCKAT_OBJ* ix		:
	void*		pData	:データ
	size_t		size	:データサイズ
*/
void Communication_SetTransmissionData(SOCKAT_OBJ* ix,void* pData,size_t size){
	//データがなければ処理を抜ける
	if(pData == NULL) return ;

	//データを設定
	ix->pTrasmissionData = pData;
	//データサイズの設定
	ix->dataLength = size;

}

//	------- ゲッター関係関数

/*
	IPアドレスの値を入力しIPDATA構造体にして返却する
	unsigned char d1	:アドレス番号1 [000]
	unsigned char d2	:アドレス番号2 [000]
	unsigned char d3	:アドレス番号3 [ 0 ]
	unsigned char d4	:アドレス番号4 [000]
	return アドレス番号
*/
IPDATA Commuination_GetIPAddres(unsigned char d1,unsigned char d2,unsigned char d3,unsigned char d4){

	IPDATA ip = {};

	ip.d1 = d1;
	ip.d2 = d2;
	ip.d3 = d3;
	ip.d4 = d4;

	return ip;
}


/*
	取得した受信データの取得
	SOCKAT_OBJ* ix
	return データ取得
*/
void* Communication_GetReceptionData(SOCKAT_OBJ* ix){

	//データ量がなければ処理を抜ける
	if(ix->dataLength == 0) return NULL;

	if(ix->pReceptionData == NULL){
		//メモリ確保
		ix->pReceptionData = Memory_Alloc(ix->dataLength);
	}
	//受信データの取得
	NetWorkRecv(ix->netHandle,ix->pReceptionData,ix->dataLength);
	return ix->pReceptionData;
}

/*
	接続がされているか返却する
	SOCKACT_OBJ*	ix
	return true:接続している	false:接続していない
*/
bool Communicaition_GetCommunicationFlag(SOCKAT_OBJ* ix){
	return (ix->netHandle != -1);
}

//	------- プロトタイプ宣言したスティック関数の中身の記述

#endif //__WINDOWS__
