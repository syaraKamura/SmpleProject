/*
	通信関係
	
*/

#pragma once

#ifdef __WINDOWS__

typedef struct{
	int netHandle;			//ネットワークハンドル
	IPDATA ip;				//IPアドレス 000.000.0.000
	int port;				//ポート番号

	bool isTransmission;	//データを送信したか？


	int dataLength;			//データ量
	void* pTrasmissionData;	//送信データ
	void* pReceptionData;	//受信データ

}SOCKAT_OBJ;


/*
	初期化
	SOCKAT_OBJ* ix
	IPDATA		ip
	int			protNum
*/
extern void Communication_Initialize(SOCKAT_OBJ* ix,IPDATA ip,int portNum);
/*
	終了処理
	SOCKAT_OBJ* ix
*/
extern void Communication_Finalize(SOCKAT_OBJ* ix);
/*
	接続を開始する
	SOCKAT_OBJ* ix
*/
extern void Communication_ConnectNetWork(SOCKAT_OBJ* ix);

/*
	接続を切断する
	SOCKAT_OBJ* ix
*/
extern void Communication_CloseNetWork(SOCKAT_OBJ* ix);

/*
	受信待ちを開始する
	SOCKAT_OBJ* ix
*/
extern void Communication_StartReception(SOCKAT_OBJ* ix);
/*
	受信が来るまで待つ
	SOCAKT_OBJ* ix
	return true: 受信した	false: 受信待ち
*/
extern bool Communication_WaitReception(SOCKAT_OBJ* ix);

/*
	データの送信
	SOCKAT_OBJ* ix
*/
extern bool Communication_Transmission(SOCKAT_OBJ* ix);

/*
	取得していない受信データの量を取得する
	SOCKAT_OBJ* ix
	return true:取得していない受信データ量が0でない false:取得していない受信データ量が0である
*/
extern bool Communication_IsNotAcquiredReception(SOCKAT_OBJ* ix);

//	------- セッター関係関数
/*
	送信するデータを設定する
	SOCKAT_OBJ* ix		:
	void*		pData	:データ
	size_t		size	:データサイズ
*/
extern void Communication_SetTransmissionData(SOCKAT_OBJ* ix,void* pData,size_t size);

//	------- ゲッター関係関数

/*
	IPアドレスの値を入力しIPDATA構造体にして返却する
	unsigned char d1	:アドレス番号1 [000]
	unsigned char d2	:アドレス番号2 [000]
	unsigned char d3	:アドレス番号3 [ 0 ]
	unsigned char d4	:アドレス番号4 [000]
	return アドレス番号
*/
extern IPDATA Commuination_GetIPAddres(unsigned char d1,unsigned char d2,unsigned char d3,unsigned char d4);

/*
	取得した受信データの取得
	SOCKAT_OBJ* ix
	return データ取得
*/
extern void* Communication_GetReceptionData(SOCKAT_OBJ* ix);


/*
	接続がされているか返却する
	SOCKACT_OBJ*	ix
	return true:接続している	false:接続していない
*/
extern bool Communicaition_GetCommunicationFlag(SOCKAT_OBJ* ix);

#endif //__WINDOWS__
