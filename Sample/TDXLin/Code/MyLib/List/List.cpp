/*
				ファイル名		:List
				作成者			:
				作成日時		:2017/10/10
				ソース説明		:
				
				リスト
				
				備考
				
				
				
!*/

//	------- インクルード宣言
#include "DxLib.h"
#include "../Memory/Memory.h"
#include "List.h"
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
	リスト初期化処理
	必ず初期化をしなければならない
	LIST_DATA* ix
	int nodeMax		:ノードの最大個数を設定する(0の場合は無限に設定できる)
*/
void List_Initialize(LIST_DATA* ix,int nodeMax/* = 0*/){

	
	ix->isInitialize = false;

	ix->nodeCnt = 0;

	ix->pPrev = ix->pNext = NULL;
	ix->node = NULL;
	ix->nodeMax = nodeMax;

#if 0
	//ノードの上限が設定されているならば
	if(0 < nodeMax){

		int memorySize = sizeof(int);
		int allocSize = nodeMax * memorySize;
		
		ix->node = (NODE_DATA*)Memory_Alloc(sizeof(NODE_DATA)*allocSize);
		
	}else{
		ix->node = (NODE_DATA*)Memory_Alloc(sizeof(NODE_DATA));
	}
#endif


	ix->isInitialize = true;
	
}

/*
	削除
*/
void List_Finalize(LIST_DATA* ix){
	
	List_RemoveAllTile(ix);
	

}


/*
	ノードを先頭に追加する
	LIST_DATA* ix
	void* pNode		:リストに追加するデータ
*/
void List_AddHead(LIST_DATA* ix,void* pNode){

}

/*
	ノードを最後に追加する
	LIST_DATA* ix
	void* pNode		:リストに追加するデータ
*/
void List_AddTile(LIST_DATA* ix,void* pNode){

}

/*
	ノードを指定のノードの次に追加する
	LIST_DATA* ix
	void* pNode		:このノードの次にノードを追加する
	void* pAddNode	:追加するノード
*/
void List_AddSelectNext(LIST_DATA* ix, void* pNode,void* pAddNode){

}

/*
	ノードを指定のノードの前に追加する
	LIST_DATA* ix
	void* pNode		:このノードの前にノードを追加する
	void* pAddNode	:追加するノード
*/
void List_AddSelectPrev(LIST_DATA* ix, void* pNode,void* pAddNode){

}

/*
	指定のノードを削除する
*/
void List_Remove(LIST_DATA* ix,void* pNode){

}

/*
	すべてのノードを先頭から削除する
*/
void List_RemoveAllHead(LIST_DATA* ix){

}

/*
	すべてのノートを最後から削除する
*/
void List_RemoveAllTile(LIST_DATA* ix){

}


