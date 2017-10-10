/*
				ファイル名		:List.h
				作成者			:
				作成日時		:201/10/10
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __LIST_H__
#define __LIST_H__

//	------- インクルード宣言

//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

//	------- 構造体&共用体

typedef struct NODE_DATA{
	void *pData;
	NODE_DATA* pNext;
	NODE_DATA* pPrev;
}NODE_DATA;

typedef struct LIST_DATA{

	NODE_DATA* node;
	int nodeCnt;
	int nodeMax;
	bool isInitialize;	//初期化処理を行ったか？

	LIST_DATA* pNext;
	LIST_DATA* pPrev;

}LIST_DATA;

//	------- グローバル関数

/*
	リスト初期化処理
	必ず初期化をしなければならない
	LIST_DATA* ix
	int nodeMax		:ノードの最大個数を設定する(0の場合は無限に設定できる)
*/
void List_Initialize(LIST_DATA* ix,int nodeMax = 0);

/*
	削除
*/
void List_Finalize(LIST_DATA* ix);


/*
	ノードを先頭に追加する
	LIST_DATA* ix
	void* pNode		:リストに追加するデータ
*/
void List_AddHead(LIST_DATA* ix,void* pNode);

/*
	ノードを最後に追加する
	LIST_DATA* ix
	void* pNode		:リストに追加するデータ
*/
void List_AddTile(LIST_DATA* ix,void* pNode);

/*
	ノードを指定のノードの次に追加する
	LIST_DATA* ix
	void* pNode		:このノードの次にノードを追加する
	void* pAddNode	:追加するノード
*/
void List_AddSelectNext(LIST_DATA* ix, void* pNode,void* pAddNode);

/*
	ノードを指定のノードの前に追加する
	LIST_DATA* ix
	void* pNode		:このノードの前にノードを追加する
	void* pAddNode	:追加するノード
*/
void List_AddSelectPrev(LIST_DATA* ix, void* pNode,void* pAddNode);


/*
	指定のノードを削除する
*/
void List_Remove(LIST_DATA* ix,void* pNode);

/*
	すべてのノードを先頭から削除する
*/
void List_RemoveAllHead(LIST_DATA* ix);

/*
	すべてのノートを最後から削除する
*/
void List_RemoveAllTile(LIST_DATA* ix);


//	------- インライン関数(ヘッダー内関数)


#endif // __LIST_H__