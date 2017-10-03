/*

	タスクの削除処理の実装

	タスクのリストの実装の再試行をして実装しなおす


*/

#include "Task.h"
#include "MyLib/Memory/Memory.h"
#include "DxLib.h"

typedef struct{

#ifdef __MY_DEBUG__
	char fileName[128];
	int line;
#endif
	int num;
	int size;
	FUNCTYPE Proc;
	FUNCTYPE Draw;
	FUNCTYPE Del;
	eTaskClassType ClassType;
	int eres_cnt;

	int waitCnt;
	bool isAddTask;

}TASK;

typedef struct TASK_LIST{
	TASK task;

	TASK_LIST* next;
	TASK_LIST* prev;
}TASK_LIST;

static TASK_LIST pEntory;	//登録用ポインタ変数
static TASK_LIST pEntoryTail;	//登録用ポインター末尾
static TASK_LIST pHead;
static TASK_LIST pTail;

//ユーザーのアドレスに変換する
static void* _TaskChangeUserAddress(void* ix){
	return (((TASK_LIST*)(unsigned int)ix) - sizeof(TASK_LIST));
}

//タスク分のアドレスに変換する
static void* _UserChangeTaskAddress(void* ix){
	return (((TASK_LIST*)(unsigned int)ix) + sizeof(TASK_LIST));
}

//リストの追加
static void _AddList(TASK_LIST* pData){
	
	//データがなければ処理を抜ける
	if(pData == NULL){
		return ;
	}
	
	//一つもデータが設定されていないなら
	if(pHead.next == NULL){
		pHead.next = pTail.next = pData;
	}else{

		pTail.next->next = pData;	//末尾にデータを設定する
		pData->prev = pTail.next;	//新規追加データのprevに末尾のデータを設定
		pTail.next = pData;			//新規データを末尾に設定する

	}

}

//条件付きでリストの追加を行う
static void _SortListAdd(TASK_LIST* pData){

	TASK_LIST* tmp = NULL;	//一時リスト

	//データがなければ処理を抜ける
	if(pData == NULL){
		return ;
	}
	
	//一つもデータが設定されていないなら
	if(pHead.next == NULL){
		pHead.next = pTail.next = pData;
	}else{

		tmp = pData;

		//データがなくなるまでループする
		while(tmp != NULL){

			//クラスタイプが小さいものが先に来るようにする
			if(pData->task.ClassType < tmp->task.ClassType){

				//メモリアドレスが同じであるなら先頭に登録をする
				if(tmp == pHead.next){
					pData->next = pHead.next;
					pHead.next->prev = pData;
					pHead.next = pData;
				}
				//メモリアドレスが異なるなら
				else{

					//リストの中間に登録を行う
					tmp->prev->next = pData;
					pData->prev = tmp->prev;

					pData->next = tmp;
					tmp->prev = pData;

				}
				break;
			}

			//データがあるなら次のデータへ
			if(tmp->next != NULL){
				tmp = tmp->next;
			}
			//データがないなら
			else{
				//リストの最後に登録を行う
				pTail.next->next = pData;
				pData->prev = pTail.next;
				pTail.next = pData;

				break;
			}
			
		}

	}

}

//リストの検索
//同じアドレスを検索する
//見つけた: タスクポインターを返却する 見つからなかった: NULLを返却する
static TASK_LIST* _SarchList(void* pAddress){

	TASK_LIST* head = pHead.next;

	TASK_LIST* tmp = head;

	while(tmp != NULL){
		if(tmp == pAddress){
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

//リストの削除
//メモリアドレスが同じものを削除する
static void _DeleteList(void* pAddress){

	TASK_LIST* del = _SarchList(pAddress);

	//処理を抜ける
	if(del == NULL){
		return ;
	}

	//メモリアドレスがリストの先頭と同じである
	if(del == pHead.next){

		//　削除対象のデータがリストの先頭
		pHead.next = pHead.next->next;

		//データが存在しているなら
		if(pHead.next != NULL){
			//リストのつながりを切る
			pHead.next->prev = NULL;
		}else{
			//すべて削除したならデータをNULLにする
			pHead.next = pTail.next = NULL;
		}
	}
	//メモリアドレスがリストの末尾と同じである
	else if(del == pTail.next){
		// 削除対象のデータがリストの末尾
		pTail.next = pTail.next->prev;
		pTail.next->next = NULL;
	}
	else{
		// 削除対象のデータがリストの中間
		del->prev->next = del->next;
		del->next->prev = del->prev;
	}

	Memory_SafeFree(del);

}

//すべて削除する
static void _AllDeleteList(){

	TASK_LIST* tmp = NULL;
	TASK_LIST* del = NULL;
	
	if(pHead.next != NULL){

		tmp = pHead.next;
		while(tmp){
			del = tmp;
			tmp = tmp->next;
			Memory_SafeFree(del);

		}
	}
	pHead.next = pTail.next = NULL;
}

//タスク登録リストに追加
static void _EntoryTaskListAdd(TASK_LIST* task){

	
	if(pEntory.next == NULL){
		pEntory.next = pEntoryTail.next = task;
	}else{

		pEntoryTail.next->next = task;
		task->prev = pEntoryTail.next;
		pEntoryTail.next = task;
	}


}

//タスク登録リストから削除すする
static void _EntoryTaskList_Delete(TASK_LIST*  task){

	TASK_LIST* tmp = pEntory.next;
	TASK_LIST* prev = NULL;

	while(tmp){

		if(tmp == task){
			if(tmp == pEntory.next){
				pEntory.next = pEntory.next->next;
			}else if(tmp == pEntoryTail.next){
				pEntoryTail.next = prev;
				pEntoryTail.next->next = NULL;
			}else{
				prev->next = tmp->next;
			}

			//tmp = NULL;
			return ;
		}

		prev = tmp;
		tmp = tmp->next;
	}

}


//タスクの追加
static void _TaskEntory(){

	TASK_LIST* entory = pEntory.next;

	if(!entory) return ;

	while(entory){
		if(entory->task.isAddTask){
			entory->task.waitCnt++;
			if(entory->task.waitCnt > 2){
				entory->task.isAddTask = false;
				_SortListAdd(entory);
			}
		}

		entory = entory->next;
	}

	

}

//タスクの登録終了処理
static void _TaskEndEntory(){
	
	TASK_LIST* entory = pEntory.next;

	if(!entory) return ;

	while(entory){
		//タスク追加処理が終了しているならば
		if(entory->task.isAddTask == false){
			_EntoryTaskList_Delete(entory);
		}

		entory = entory->next;
	}

}


#ifdef __MY_DEBUG__
void* Task_Create(FUNCTYPE Proc,FUNCTYPE Draw,FUNCTYPE Del,int FuncType,eTaskClassType ClassType,const char* fileName,int line)
#else
void* Task_Create(FUNCTYPE Proc,FUNCTYPE Draw,FUNCTYPE Del,int FuncType,eTaskClassType ClassType)
#endif
{


	if(pHead.task.num > 30) return NULL;

	unsigned int size = FuncType + sizeof(TASK_LIST);


	//新しく確保
	TASK_LIST* ix = (TASK_LIST*)Memory_Alloc(size);

	if(ix != NULL){

		pHead.task.num++;

		//データを入れる
		ix->task.size = FuncType;
		ix->task.ClassType = ClassType;
		ix->task.eres_cnt = 0;

		ix->task.num = 0;

		ix->task.isAddTask = true;
		ix->task.waitCnt = 0;
#ifdef __MY_DEBUG__
		strcpy_s(ix->task.fileName,fileName);
		ix->task.line = line;
#endif
		ix->task.Proc = Proc;
		ix->task.Draw = Draw;
		ix->task.Del  = Del ;

		//リストの接続先をない状態にする
		ix->next = NULL;
		ix->prev = NULL;

		_EntoryTaskListAdd(ix);

		//_SortListAdd(ix);

		void* user = _TaskChangeUserAddress(ix);

		
		if(user != NULL){
			//登録したユーザーワークの初期化
			memset(user,0,FuncType);
		}

		return user;
	}

	
	return NULL;
}


void Task_KillRequest(void* ix){

	TASK_LIST* task = (TASK_LIST*)_UserChangeTaskAddress(ix);
	
	task->task.eres_cnt = 1;

	//TASK_LIST* proc = pHead.next;//s_Task.next;
	//
	//for(int i = 0;proc!= NULL;i++){
	//	if(proc->task.Proc != NULL){
	//		//タスク削除依頼のメモリアドレスと同じなら
	//		if(proc == task){
	//			proc->task.eres_cnt = 1;	//削除依頼をする
	//		}
	//	}
	//	proc = proc->next;
	//}

	
}

void Task_Init(){

	pHead.next = NULL;
	pHead.prev = NULL;
	//データを入れる
	pHead.task.size = 0;
	pHead.task.ClassType = eTaskClassType_Class00;
	pHead.task.eres_cnt = 0;

	pHead.task.num = 0;
	pHead.task.isAddTask = false;

#ifdef __MY_DEBUG__
	strcpy_s(pHead.task.fileName,"");
	pHead.task.line = 0;
#endif
	pHead.task.Proc = NULL;
	pHead.task.Draw = NULL;
	pHead.task.Del  = NULL;

	pTail.next = NULL;
	pTail.prev = NULL;
	//データを入れる
	pTail.task.size = 0;
	pTail.task.ClassType = eTaskClassType_Class00;
	pTail.task.eres_cnt = 0;

	pTail.task.num = 0;
	pTail.task.isAddTask = false;

#ifdef __MY_DEBUG__
	strcpy_s(pTail.task.fileName,"");
	pTail.task.line = 0;
#endif
	pTail.task.Proc = NULL;
	pTail.task.Draw = NULL;
	pTail.task.Del  = NULL;

	pEntory.next = NULL;
	pEntory.prev = NULL;

	pEntoryTail.next = NULL;
	pEntoryTail.prev = NULL;


//	s_Task.task.num = 0;
//
//	s_Task.next = NULL;
//	s_Task.prev = NULL;
//	s_Task.task.Proc = NULL;
//	s_Task.task.Draw = NULL;
//	s_Task.task.Del = NULL;
//
//	s_Task.task.size = 0;
//
//#ifdef __MY_DEBUG__
//	s_Task.task.line = 0;
//	strcpy_s(s_Task.task.fileName,"");
//#endif	//__MY_DEBUG__

}

void Task_Finalize(){
	_AllDeleteList();
}

void Task_Entory(){
	_TaskEntory();
	_TaskEndEntory();
}

void Task_Updata(){

	

	TASK_LIST* proc = pHead.next;//s_Task.next;

	//メモリの確保がされていなければ処理を抜ける
	if(proc == NULL ) return;

	for(int i = 0;proc!= NULL;i++){
		if(proc->task.Proc != NULL){
			//タスクを生成中なら処理を飛ばす
			if(proc->task.isAddTask){
				proc = proc->next;
				continue;
			}
			if(proc->task.eres_cnt > 1) {
				proc = proc->next;
			}else{	
				void* address = _TaskChangeUserAddress(proc);
				proc->task.Proc(address);
				proc = proc->next;
			}
		}else{
			proc = proc->next;
		}
	}
}
	


void Task_Dalete(){

	//削除処理
	TASK_LIST* next =  pHead.next;//s_Task.next;

	//if(next == NULL)  return ;

	//削除処理が実行される
	for(int i = 0;next!= NULL;i++){
		if(next != NULL){
			if(next->task.isAddTask){
				next->task.isAddTask = false;
				next = next->next;
				continue;
			}
			if(next->task.eres_cnt == 0){
				next = next->next;
			}
			//削除処理を始める前に削除関数が存在していれば削除関数を実行する
			else if(next->task.eres_cnt == 1){
				if(next->task.Del){
					void* address = _TaskChangeUserAddress(next);
					next->task.Del(address);

				}
				next->task.eres_cnt++;
				next = next->next;
			}
			//タスク破棄処理を開始する
			else if(next->task.eres_cnt >= 2){
				//void* pAddress = next;
				_DeleteList(next);
				//next = NULL;
				pHead.task.num--;
				break;
				//next = next->next;
				
			}
		}
	}

	

}

void Task_Draw(){

	TASK_LIST* draw = pHead.next;//s_Task.next;

	//メモリの確保がされていなければ処理を抜ける
	if(draw == NULL) return ;

	for(int i = 0;draw != NULL;i++){

		if(draw->task.Draw != NULL){
			//タスクを生成中なら処理を飛ばす
			if(draw->task.isAddTask){
				draw = draw->next;
				continue;
			}
			if(draw->task.eres_cnt > 0){
				draw = draw->next;
			}else{
				void* address = _TaskChangeUserAddress(draw);
				draw->task.Draw(address);
				draw = draw->next;
			}
		}else{
			draw = draw->next;
		}
	}
}
