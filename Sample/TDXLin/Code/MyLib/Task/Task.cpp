/*

	�^�X�N�̍폜�����̎���

	�^�X�N�̃��X�g�̎����̍Ď��s�����Ď������Ȃ���


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

static TASK_LIST pEntory;	//�o�^�p�|�C���^�ϐ�
static TASK_LIST pEntoryTail;	//�o�^�p�|�C���^�[����
static TASK_LIST pHead;
static TASK_LIST pTail;

//���[�U�[�̃A�h���X�ɕϊ�����
static void* _TaskChangeUserAddress(void* ix){
	return (((TASK_LIST*)(unsigned int)ix) - sizeof(TASK_LIST));
}

//�^�X�N���̃A�h���X�ɕϊ�����
static void* _UserChangeTaskAddress(void* ix){
	return (((TASK_LIST*)(unsigned int)ix) + sizeof(TASK_LIST));
}

//���X�g�̒ǉ�
static void _AddList(TASK_LIST* pData){
	
	//�f�[�^���Ȃ���Ώ����𔲂���
	if(pData == NULL){
		return ;
	}
	
	//����f�[�^���ݒ肳��Ă��Ȃ��Ȃ�
	if(pHead.next == NULL){
		pHead.next = pTail.next = pData;
	}else{

		pTail.next->next = pData;	//�����Ƀf�[�^��ݒ肷��
		pData->prev = pTail.next;	//�V�K�ǉ��f�[�^��prev�ɖ����̃f�[�^��ݒ�
		pTail.next = pData;			//�V�K�f�[�^�𖖔��ɐݒ肷��

	}

}

//�����t���Ń��X�g�̒ǉ����s��
static void _SortListAdd(TASK_LIST* pData){

	TASK_LIST* tmp = NULL;	//�ꎞ���X�g

	//�f�[�^���Ȃ���Ώ����𔲂���
	if(pData == NULL){
		return ;
	}
	
	//����f�[�^���ݒ肳��Ă��Ȃ��Ȃ�
	if(pHead.next == NULL){
		pHead.next = pTail.next = pData;
	}else{

		tmp = pData;

		//�f�[�^���Ȃ��Ȃ�܂Ń��[�v����
		while(tmp != NULL){

			//�N���X�^�C�v�����������̂���ɗ���悤�ɂ���
			if(pData->task.ClassType < tmp->task.ClassType){

				//�������A�h���X�������ł���Ȃ�擪�ɓo�^������
				if(tmp == pHead.next){
					pData->next = pHead.next;
					pHead.next->prev = pData;
					pHead.next = pData;
				}
				//�������A�h���X���قȂ�Ȃ�
				else{

					//���X�g�̒��Ԃɓo�^���s��
					tmp->prev->next = pData;
					pData->prev = tmp->prev;

					pData->next = tmp;
					tmp->prev = pData;

				}
				break;
			}

			//�f�[�^������Ȃ玟�̃f�[�^��
			if(tmp->next != NULL){
				tmp = tmp->next;
			}
			//�f�[�^���Ȃ��Ȃ�
			else{
				//���X�g�̍Ō�ɓo�^���s��
				pTail.next->next = pData;
				pData->prev = pTail.next;
				pTail.next = pData;

				break;
			}
			
		}

	}

}

//���X�g�̌���
//�����A�h���X����������
//������: �^�X�N�|�C���^�[��ԋp���� ������Ȃ�����: NULL��ԋp����
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

//���X�g�̍폜
//�������A�h���X���������̂��폜����
static void _DeleteList(void* pAddress){

	TASK_LIST* del = _SarchList(pAddress);

	//�����𔲂���
	if(del == NULL){
		return ;
	}

	//�������A�h���X�����X�g�̐擪�Ɠ����ł���
	if(del == pHead.next){

		//�@�폜�Ώۂ̃f�[�^�����X�g�̐擪
		pHead.next = pHead.next->next;

		//�f�[�^�����݂��Ă���Ȃ�
		if(pHead.next != NULL){
			//���X�g�̂Ȃ����؂�
			pHead.next->prev = NULL;
		}else{
			//���ׂč폜�����Ȃ�f�[�^��NULL�ɂ���
			pHead.next = pTail.next = NULL;
		}
	}
	//�������A�h���X�����X�g�̖����Ɠ����ł���
	else if(del == pTail.next){
		// �폜�Ώۂ̃f�[�^�����X�g�̖���
		pTail.next = pTail.next->prev;
		pTail.next->next = NULL;
	}
	else{
		// �폜�Ώۂ̃f�[�^�����X�g�̒���
		del->prev->next = del->next;
		del->next->prev = del->prev;
	}

	Memory_SafeFree(del);

}

//���ׂč폜����
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

//�^�X�N�o�^���X�g�ɒǉ�
static void _EntoryTaskListAdd(TASK_LIST* task){

	
	if(pEntory.next == NULL){
		pEntory.next = pEntoryTail.next = task;
	}else{

		pEntoryTail.next->next = task;
		task->prev = pEntoryTail.next;
		pEntoryTail.next = task;
	}


}

//�^�X�N�o�^���X�g����폜������
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


//�^�X�N�̒ǉ�
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

//�^�X�N�̓o�^�I������
static void _TaskEndEntory(){
	
	TASK_LIST* entory = pEntory.next;

	if(!entory) return ;

	while(entory){
		//�^�X�N�ǉ��������I�����Ă���Ȃ��
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


	//�V�����m��
	TASK_LIST* ix = (TASK_LIST*)Memory_Alloc(size);

	if(ix != NULL){

		pHead.task.num++;

		//�f�[�^������
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

		//���X�g�̐ڑ�����Ȃ���Ԃɂ���
		ix->next = NULL;
		ix->prev = NULL;

		_EntoryTaskListAdd(ix);

		//_SortListAdd(ix);

		void* user = _TaskChangeUserAddress(ix);

		
		if(user != NULL){
			//�o�^�������[�U�[���[�N�̏�����
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
	//		//�^�X�N�폜�˗��̃������A�h���X�Ɠ����Ȃ�
	//		if(proc == task){
	//			proc->task.eres_cnt = 1;	//�폜�˗�������
	//		}
	//	}
	//	proc = proc->next;
	//}

	
}

void Task_Init(){

	pHead.next = NULL;
	pHead.prev = NULL;
	//�f�[�^������
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
	//�f�[�^������
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

	//�������̊m�ۂ�����Ă��Ȃ���Ώ����𔲂���
	if(proc == NULL ) return;

	for(int i = 0;proc!= NULL;i++){
		if(proc->task.Proc != NULL){
			//�^�X�N�𐶐����Ȃ珈�����΂�
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

	//�폜����
	TASK_LIST* next =  pHead.next;//s_Task.next;

	//if(next == NULL)  return ;

	//�폜���������s�����
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
			//�폜�������n�߂�O�ɍ폜�֐������݂��Ă���΍폜�֐������s����
			else if(next->task.eres_cnt == 1){
				if(next->task.Del){
					void* address = _TaskChangeUserAddress(next);
					next->task.Del(address);

				}
				next->task.eres_cnt++;
				next = next->next;
			}
			//�^�X�N�j���������J�n����
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

	//�������̊m�ۂ�����Ă��Ȃ���Ώ����𔲂���
	if(draw == NULL) return ;

	for(int i = 0;draw != NULL;i++){

		if(draw->task.Draw != NULL){
			//�^�X�N�𐶐����Ȃ珈�����΂�
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
