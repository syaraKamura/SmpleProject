/*

	__MY_DEBUG__ : �f�o�b�O�ł̂ݎ��s��������������
				�@ #ifdef #endif�@�Ȃǂň͂ނƃ����[�X���ɂ͎��s���Ȃ��悤�ɂȂ�

*/


#include "DxLib.h"

#include "MyLib/Memory/Memory.h"
#include "MyLib/Keyboard/Keyboard.h"

#include "Debug.h"

const int DEBUG_MESSAGE_LIST_NUM = 100;
const int DEBUG_DATA_MAX = 100;	//�f�o�b�O�f�[�^�̓o�^�ł���ő吔


typedef struct{
	int id;
	char str[256];
}DEBUG_MES_LIST;


static DEBUG_DATA s_debugData[DEBUG_DATA_MAX];
static int s_page = 0;
static int s_PageMax = 0;
static int s_cursor = 0;

static DEBUG_MES_LIST  debugList[DEBUG_MESSAGE_LIST_NUM];

void _Entory_DebugString(DEBUG_MES_LIST* ix,const char* str){


	int i = 0;

	for(i = 0;i < DEBUG_MESSAGE_LIST_NUM;i++){

		//���b�Z�[�W���X�g���k���ł͂Ȃ� ���� ���łɂ��郁�b�Z�[�W���e�Ɠ����Ȃ珈�����΂�
		if(strcmp(ix[i].str,"") != 0 && strcmp(ix[i].str,str) == 0) continue;

		if(ix[i].id == 0){
			ix[i].id = i + 1;
			strcpy_s(ix[i].str,str);
			break;
		}
	}
	
}

void Debug_DrawString(){

	clsDx();

	for(int i = 0;i < DEBUG_MESSAGE_LIST_NUM;i++){
		if(debugList[i].id == 0) continue;
		printfDx("%s",debugList[i].str);
	}

}

//
void Debug_Print(const char* str,...){

	
#ifdef __MY_DEBUG__
	va_list ap;
	char buffer[256];
	va_start(ap,str);
	vsprintf_s(buffer,str,ap);
	va_end(ap);

	_Entory_DebugString(debugList,buffer);
#endif
}

#ifdef __MY_DEBUG__

//���s�t������������`��
void Debug_Println(const char* str,...){


	va_list ap;

	char buffer[256];
	va_start(ap,str);
	vsprintf_s(buffer,str,ap);
	va_end(ap);

	printfDx("%s\n",buffer);


}

#else

void Debug_Println(const char* str,...){}

#endif


/*
	�����t��������̕`����s��
	���W�𕶎��̃T�C�Y���|���ĕ\�����s���B
	posX��0�Ƃ���0
	posX��1����1*GetFontSize()�̍��W�֕`����s��
*/
void Debug_Printf(int posX,int posY,unsigned int color,const char* str,...){

	va_list ap;
	char buffer[256];
	int x = posX * GetFontSize();
	int y = posY * GetFontSize();

	va_start(ap,str);
	vsprintf_s(buffer,str,ap);
	va_end(ap);

	DrawString(x,y,buffer,color);


}

#ifdef __MY_DEBUG__

/*
	�o�̓E�B���h�E�ɏo�͂���(�����t��)
	const char*		str
					...
*/
void Debug_LogPrintf(const char* str,...){
	


	va_list ap;
	char buffer[256];

	va_start(ap,str);
	vsprintf_s(buffer,str,ap);
	va_end(ap);
#ifdef __WINDOWS__
	OutputDebugString(buffer);
#elif __ANDROID__
	
#endif	// __WINDOWS__

}

#else

void Debug_LogPrintf(const char* str,...){}

#endif	// __MY_DEBUG__


#ifdef __MY_DEBUG__
/*
	���łɓ����I�u�W�F�N�g���̃f�o�b�O���ڂ����݂��Ă��邩���f����
	return	true	:���݂��Ă���
			false	:���݂��Ă��Ȃ�
*/
static bool _IsExsistDebuObject(const char* objectName){

	DEBUG_DATA* pData = &s_debugData[0];

	bool isFind = false;

	//�������O�̃f�o�b�O�I�u�W�F�N�g�������݂��Ă��邩
	for(int i = 0;i < DEBUG_DATA_MAX;i++){
		if(strcmp(pData->objectName,objectName) == 0){
			isFind =  true;
			break;
		}
		pData++;
	}
	return isFind;
}

/*
	�f�o�b�O���ڂ�o�^����
*/
static void _AddDebug(DEBUG_FUNC_DATA* debugData,const char* objectName,size_t size){

	DEBUG_DATA* pData = &s_debugData[0];
	
	//�󂢂Ă���ꏊ����������
	for(int i = 0;i < DEBUG_DATA_MAX;i++){
		if(strcmp(pData->objectName,"") == 0){
			break;
		}
		pData++;
	}

	//�f�o�b�O�I�u�W�F�N�g�����R�s�[
	strcpy_s(pData->objectName,objectName);

	//�f�o�b�O���ڂ̌����Z�b�g
	pData->debugFuncNum = size/sizeof(DEBUG_FUNC_DATA);
	

	//�f�o�b�O���ڂ̓o�^
	pData->pdebuFunc = (DEBUG_FUNC_DATA*)Memory_AllocZeroClear(sizeof(DEBUG_FUNC_DATA) * pData->debugFuncNum);

	DEBUG_FUNC_DATA* func = &pData->pdebuFunc[0];
	DEBUG_FUNC_DATA* debug = debugData;
	for(int i = 0;i < pData->debugFuncNum;i++){
		
		strcpy_s(func->debugName,debug->debugName);
		func->debugType		= debug->debugType;
		func->FuncUpdata	= debug->FuncUpdata;
		func->FuncDraw		= debug->FuncDraw;
		func->FuncFlagOn	= debug->FuncFlagOn;
		func->FuncFlagOff	= debug->FuncFlagOff;
		func->isFlag		= debug->isFlag;

		debug++;
		func++;
	}

}

/*
	�f�o�b�O���ڂ̓o�^
	DEBUG_FUNC_DATA*	debugData	:�f�o�b�O�f�[�^
	const char*			objectName	:�f�o�b�O���ږ�
	size_t				size		:�f�[�^�T�C�Y
*/
void Debug_Entory(DEBUG_FUNC_DATA* debugData,const char* objectName,size_t size){

	
	//�������O���������̂œo�^����߂�
	if(_IsExsistDebuObject(objectName) == true) return ;

	_AddDebug(debugData,objectName,size);

	s_PageMax++;

}

/*
	�f�o�b�O�t���O�̏�Ԃ��擾����
	const char* objectName	:�f�o�b�O���ږ�
	const char* debugName	:�f�o�b�O��
	return	true	:�t���O���I��
			false	:�t���O���I�t
*/
bool Debug_IsFlag(const char* objectName,const char* debugName){

	bool isFlag = false;

	DEBUG_DATA* pData = &s_debugData[0];

	for(int i = 0;i < s_PageMax;i++){
		//�f�o�b�O���ږ�������
		if(strcmp(pData->objectName,objectName) == 0){
			for(int j = 0;j < pData->debugFuncNum;j++){
				DEBUG_FUNC_DATA* debug= &pData->pdebuFunc[j];
				if(strcmp(debug->debugName,debugName) == 0){
					isFlag = debug->isFlag;
					break;
				}
			}
		}

		pData++;

	}

	return isFlag;
}

/*
	������
*/
void Debug_Initialize(){
	memset(s_debugData,0,sizeof(DEBUG_DATA) * DEBUG_DATA_MAX);
	
	/*
		�e�\�[�X�ō쐬�����f�o�b�O���ڂ̓o�^�֐��������ɋL�q����
		�ォ�珇�ԂɃy�[�W�����Z����Ă���
	*/

	
}

/*
	�I������
*/
void Debug_Finalize(){

	DEBUG_DATA* pData = &s_debugData[0];

	for(int i = 0;i < DEBUG_DATA_MAX;i++){
		if(strcmp(pData->objectName,"") == 0){
			pData++;
			continue;
		}
		Memory_SafeFree(pData->pdebuFunc);
		pData++;
	}

}

/*
	�X�V
*/
void Debug_Updata(){

	//�o�^����Ă��Ȃ���Ώ����𔲂���
	if(s_PageMax == 0)	return ;

	DEBUG_DATA* pData = &s_debugData[s_page];

	if(s_cursor == -1){
		if(Keyboard_Press(KEY_INPUT_RIGHT)){
			s_page = (s_page + 1) % s_PageMax;
		}else if(Keyboard_Press(KEY_INPUT_LEFT)){
			s_page = (s_page + (s_PageMax - 1)) % s_PageMax;
		}
	}else{
		
		DEBUG_FUNC_DATA* debug= &pData->pdebuFunc[s_cursor];

		if(debug == NULL) return;

		if(debug->debugType == eDebugType_Flag){

			if(Keyboard_Press(KEY_INPUT_RIGHT) || Keyboard_Press(KEY_INPUT_LEFT)){
				debug->isFlag = debug->isFlag ? false : true; 
			}

			if(debug->isFlag == true){

				//NULL�łȂ���Ύ��s����
				if(debug->FuncFlagOn != NULL){
					debug->FuncFlagOn();
				}

			}else{

				//NULL�łȂ���Ύ��s����
				if(debug->FuncFlagOff != NULL){
					debug->FuncFlagOff();
				}
			}

		}else{

			DEBUG_FUNC_DATA* debug= &pData->pdebuFunc[s_cursor];

			if(Keyboard_Press(KEY_INPUT_Z)){
				
			}

		}


	}

	if(Keyboard_Press(KEY_INPUT_UP)){
		if(s_cursor > -1){
			s_cursor --;
		}
	}else if(Keyboard_Press(KEY_INPUT_DOWN)){
		if(s_cursor < pData->debugFuncNum-1){
			s_cursor ++;
		}
	}

}

/*
	�`��
*/
void Debug_Draw(){
	
	//�o�^����Ă��Ȃ���Ώ����𔲂���
	if(s_PageMax == 0)	return ;

	//�ő�y�[�W���ȏ�Ȃ�`����s��Ȃ�
	if(s_page >= s_PageMax) return ;

	DEBUG_DATA* pData = &s_debugData[s_page];

	DrawBox(0,0,320,40 + 20 * pData->debugFuncNum,GetColor(120,120,120),TRUE);

	DrawString(0,s_cursor * 20 + 40,"��",GetColor(255,255,255));

	DrawString(0,0,pData->objectName,GetColor(0,255,0));
	DrawFormatString(20,20,GetColor(0,255,0),"Page:%d",s_page);

	for(int i = 0;i < pData->debugFuncNum;i++){
		DEBUG_FUNC_DATA* debug= &pData->pdebuFunc[i];
		int strlen = strlenDx(debug->debugName);
		
		if(debug->debugType == eDebugType_Flag){
			DrawString(20,(i+2)*20,debug->debugName,GetColor(255,255,255));
			DrawFormatString(20 + strlen * 20,(i+2)*20,GetColor(255,255,0),"%s",debug->isFlag ? "ON" : "OFF");
		}else if(debug->debugType == eDebugType_Func){
			DrawString(20,(i+2)*20,debug->debugName,GetColor(0,255,0));
		}
	}

}

#endif	// __MY_DEBUG__