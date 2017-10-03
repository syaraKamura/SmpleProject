/*

		���ݎ�M�̃T���v�����쐬����

		�ڕW�@�ȈՃV���[�e�B���O�Q�[�����쐬����

		1.���@�ƓG�̍��W�𑗎�M���Ď󂯎��

			���WX
			���WY
			���ݑ̗�
			�e�̈З�
			
		2.�G�̍��W�́A��ʏ㕔�ֈڂ�悤�ɂ���

		3.�e�̏��͈ȉ��̏��𑗎�M����

			�e�����˂���
			
		4.�e�̏����󂯎������G�̒e�̂��̌�̋����͂��ׂĎ�M�����X�V����

		5.���s����p�f�[�^���󂯎��

			�t���O_����
			�t���O_����

		6.�^�C�g����

*/


#ifdef __MY_DEBUG__

#include "Common/GameCommon/GameCommon.h"
#include "TestCommunication.h"

enum eSubStep{

	eSubStep_Select,			//���M����M���ݒ�
	eSubStep_Transmission,		//���M
	eSubStep_Reception,			//��M
	eSubStep_InputIpAddress,	//Ip�A�h���X����

};

enum eStep{
	eStep_Init,
	eStep_Fade,
	eStep_Main,
	eStep_Exit,
	eStep_ExitDone,
};


typedef struct{

	int hp;
	int mp;
	int atk;
	int def;
	int spd;

	int posX;
	int posY;

	short shotFlag;

}TEST_PARAM_DATA;

typedef struct{
	int posX;
	int posY;
	bool isShot;
}TEST_SHOT_DATA;

typedef struct{
	int x;
	int y;
	char listName[256];
	eSubStep step;
}LIST_DATA_TBL;

typedef struct{ 
	
	eStep step;
	eSubStep subStep;
	int cnt;
	int selectY;
	SOCKAT_OBJ sockatTransmission;		//���M�\�P�b�g
	SOCKAT_OBJ sockatReception;			//��M�\�P�b�g
	TEST_PARAM_DATA* pReveptionData;	//��M�����f�[�^
	bool isTransimision;				//���M�������������H

	TEST_SHOT_DATA recepotionShot[100];	//��M���̃V���b�g�f�[�^

	KEY_INPUT_STRING_OBJ* keyInputObj;	//���������


}WORK_OBJ;


const LIST_DATA_TBL cList[] = {
	{20,40,"���M����",				eSubStep_Transmission				},
	{20,60,"��M����",				eSubStep_Reception					},
	{20,80,"IP�A�h���X����͂���",	eSubStep_InputIpAddress				},

};


//���M�f�[�^
TEST_PARAM_DATA testData = {100,20,10,5,4,200,400,0};

static WORK_OBJ* s_pWork;

/*
	�X�e�b�v�̐ݒ������
	WORK_OBJ*	ix
	eStep		step
*/
void _SetNextStep(WORK_OBJ* ix,eStep step){

	ix->step = step;
	ix->cnt = 0;

}


/*
	���M�X�V����
*/
static  void _TransmissionProc(WORK_OBJ* ix){

	
	if(Keyboard_Press(KEY_INPUT_X)){
		
		//�X�e�b�v�𑗎�M�I����
		ix->subStep = eSubStep_Select;
		
		//�ݒ肵���f�[�^���Ȃ���Ԃɂ���
		ix->sockatTransmission.pTrasmissionData = NULL;
		
		//�ڑ���؂�
		Communication_CloseNetWork(&ix->sockatTransmission);
		
		//�ڑ��J�n��Ԃֈڍs
		ix->cnt = 0;

		//�����艺�̏��������Ȃ��悤�Ɋ֐����甲����
		return ;
	}


	//�e��ł��Ă��Ȃ���Ԃɂ���
		testData.shotFlag = 0;
	if(Keyboard_Press(KEY_INPUT_Z)){
		//�e��ł��Ă����Ԃɂ���
		testData.shotFlag = 1;
	}

	if(Keyboard_On(KEY_INPUT_DOWN)){
		testData.posY ++;
		
	}else if(Keyboard_On(KEY_INPUT_UP)){
		testData.posY --;	
	}

	if(Keyboard_On(KEY_INPUT_RIGHT)){
		testData.posX ++;
		
	}else if(Keyboard_On(KEY_INPUT_LEFT)){
		testData.posX --;	
	}


	//�J�E���g��0 �܂��� �ڑ�������Ă��Ȃ�
	if(ix->cnt == 0 || Communicaition_GetCommunicationFlag(&ix->sockatTransmission) == false){
		//���M�f�[�^
		//TEST_PARAM_DATA testData = {10,20,30,5};
		//�ڑ��J�n
		Communication_ConnectNetWork(&ix->sockatTransmission);
		//���M����l��ݒ�
		Communication_SetTransmissionData(&ix->sockatTransmission,&testData,sizeof(TEST_PARAM_DATA));
		ix->cnt ++;
	}else{

		//���M����l���Đݒ肷��
		Communication_SetTransmissionData(&ix->sockatTransmission,&testData,sizeof(TEST_PARAM_DATA));

		//���M�J�n
		if(Communication_Transmission(&ix->sockatTransmission)){
			ix->isTransimision = true;
		}else{
			ix->isTransimision = false;
		}

		ix->cnt ++;
	}
}

/*
	��M�X�V����
	WORK_OBJ* ix
*/
void _ReceptionProc(WORK_OBJ* ix){

	if(Keyboard_Press(KEY_INPUT_X)){
		//����������
		ix->sockatReception.netHandle = -1;
			
		//�ڑ��҂���Ԃֈڍs
		ix->cnt = 0;

		//�f�[�^���Ȃ���Ԃɂ���
		//ix->pReveptionData = NULL;

		//�I����ʂֈڍs
		ix->subStep = eSubStep_Select;

		//�����艺�̏��������Ȃ��悤�Ɋ֐����甲����
		return ;
	}

	if(ix->cnt == 0 ){
		//�ڑ���t�J�n
		Communication_StartReception(&ix->sockatReception);
		ix->cnt++;
	}else if(ix->cnt == 1){

		//�ڑ���������܂ő҂�
		bool isReception = Communication_WaitReception(&ix->sockatReception);
		
		//�ڑ����������Ă���Ȃ�
		if(isReception == true){
			ix->cnt++;
		}
	}else{

		//�f�[�^���󂯎�����̂ł����
		if(Communication_IsNotAcquiredReception(&ix->sockatReception) == true){
			//�f�[�^���擾����
			ix->pReveptionData = (TEST_PARAM_DATA*)Communication_GetReceptionData(&ix->sockatReception);
		

			/*
				�ڑ����I�����������f����
			*/

			int lostNetWork = -1;
			//�ڑ����ؒf���ꂽ�l�b�g���[�N�n���h�����󂯎��
			lostNetWork = GetLostNetWork();

			//�ڑ����ؒf���ꂽ�l�b�g���[�N�n���h�������ݐڑ����Ă�l�b�g���[�N�n���h���ł���Ȃ��
			if(lostNetWork == ix->sockatReception.netHandle){

				//����������
				ix->sockatReception.netHandle = -1;
			
				//�ڑ��҂���Ԃֈڍs
				ix->cnt = 0;

				//�f�[�^���Ȃ���Ԃɂ���
				//ix->pReveptionData = NULL;

			}
			//�ڑ����ؒf����Ă��Ȃ��Ȃ��
			else{

				/*�󂯎�����f�[�^�����Ƃɒe���΂�*/

				//�V���b�g�t���O��1�ł���Ȃ�
				if(ix->pReveptionData->shotFlag == 1){
					//�g�p�\�Ȓe��T��
					for(int i = 0;i < 100;i++){
						if(ix->recepotionShot[i].isShot == false){
							//�����l��ݒ肷��
							ix->recepotionShot[i].posX = ix->pReveptionData->posX;
							ix->recepotionShot[i].posY = ix->pReveptionData->posY;
							//�ł��o�����ɐݒ�
							ix->recepotionShot[i].isShot = true;
							break;
						}
					}
				}


				for(int i = 0;i < 100;i++){
					//�ł��o�����̒e�������
					if(ix->recepotionShot[i].isShot == true){
						//������ɒe���ړ�����
						ix->recepotionShot[i].posY -= 8;
						//��ʊO�֏o�Ă��܂�����
						if(ix->recepotionShot[i].posY < -32){
							//�ł��o�����łȂ���Ԃɂ���
							ix->recepotionShot[i].isShot = false;
						}
					}
				}

			}

		}

	}

}

static void _SubProc(WORK_OBJ* ix){

	switch(ix->subStep){
	case eSubStep_Select:

		if(Keyboard_Press(KEY_INPUT_DOWN)){
			GameCommon_SelectClamp(&ix->selectY,1,0,3,eClampType_ClampLoop);
		}else if(Keyboard_Press(KEY_INPUT_UP)){
			GameCommon_SelectClamp(&ix->selectY,-1,0,3,eClampType_ClampLoop);
		}

		if(Keyboard_Press(KEY_INPUT_Z)){
			ix->subStep = cList[ix->selectY].step;
			if(cList[ix->selectY].step == eSubStep_InputIpAddress){
				//�������͂��A�N�e�B�u�ɂ���
				KeyInputString_KeyInputActive(ix->keyInputObj);
			}
		}

		//�O�̃V�[���֖߂�
		if(Keyboard_Press(KEY_INPUT_X)){
			Scene_Change(Scene_GetPrevSceneId());
		}


		break;
	case eSubStep_Transmission:
		_TransmissionProc(ix);
		break;
	case eSubStep_Reception:

		_ReceptionProc(ix);
		break;
	case eSubStep_InputIpAddress:
	

		//�������͂��I�����Ă���Ȃ�
		if(KeyInputString_IsEndKeyInput(ix->keyInputObj) == true){

			//���͂����������󂯎��


			//�T�u�X�e�b�v��I���X�e�b�v��
			ix->subStep = eSubStep_Select;

		}
		



		break;
	}

}

//�X�V����
static void _Updata(WORK_OBJ* ix){

	switch(ix->step){

	case eStep_Init:
		_SetNextStep(ix,eStep_Fade);
		break;
	case eStep_Fade:
		_SetNextStep(ix,eStep_Main);
		break;
	case eStep_Main:
		_SubProc(ix);
		break;
	case eStep_Exit:

		break;
	case eStep_ExitDone:

		break;
	}


}

//�`�揈��
static void _Draw(WORK_OBJ* ix){

	//���C���X�e�b�v�łȂ���Ώ����𔲂���
	if(ix->step != eStep_Main) return ;


	switch(ix->subStep){
	case eSubStep_Select:
	
		{
			DrawString(0,ix->selectY*20 + 40,"��",COLOR_WHITE);
		
			int length = sizeof(cList) / sizeof(cList[0]); 

			for(int i = 0;i < length;i++){
				DrawString(cList[i].x,cList[i].y,cList[i].listName,COLOR_WHITE);
			}
		}

		break;
	case eSubStep_Transmission:
		
		{
			
			//�f�[�^�����݂��Ă���Ȃ��
			if( ix->isTransimision ){
				DrawString(0,20,"���M�����I",COLOR_WHITE);

				DrawString(0,60 ,"��M��́��𑀍�ł����I",COLOR_WHITE);
				DrawString(0,80 ,"�\���L�[: �ړ�",COLOR_WHITE);
				DrawString(0,100,"Z�L�[   : ����ł�",COLOR_WHITE);
				
				ix->sockatTransmission.pTrasmissionData = NULL;
			}else{

				//�f�[�^���󂯎��
				const TEST_PARAM_DATA* pData = (TEST_PARAM_DATA*)ix->sockatTransmission.pTrasmissionData;

				DrawString(0,20,"���M��...",COLOR_WHITE);
				//�f�[�^���ݒ肠��Ȃ�`�悷��
				if(pData){
					DrawFormatString(0,40,COLOR_WHITE,"HP:%d MP:%d ATK:%d DEF:%d SPD:%d�𑗐M��",pData->hp,pData->mp,pData->atk,pData->def,pData->spd);
				}
			}

		}


		break;
	case eSubStep_Reception:
		
		//�f�[�^���ݒ肠��Ȃ�`�悷��
		if(ix->pReveptionData){
			DrawString(0,20,"��M�����I",COLOR_WHITE);
			DrawFormatString(0,40,COLOR_WHITE,"HP:%d MP:%d ATK:%d DEF:%d SPD:%d����M�I",ix->pReveptionData->hp,ix->pReveptionData->mp,ix->pReveptionData->atk,ix->pReveptionData->def,ix->pReveptionData->spd);
			
			//�e�̕`��
			for(int i = 0;i < 100;i++){
				//�ł��o�����̒e������Βe��`�悷��
				if(ix->recepotionShot[i].isShot == true){
					DrawString(ix->recepotionShot[i].posX,ix->recepotionShot[i].posY,"��",COLOR_RED);
				}
			}

			//�󂯎�������W�ʒu�ɕ`�悷��
			DrawString(ix->pReveptionData->posX,ix->pReveptionData->posY,"��",COLOR_WHITE);

		}else{
			DrawString(0,20,"��M��...",COLOR_WHITE);
		}

		break;
	}

}


void TestCommunication_Init(){

	WORK_OBJ* ix = (WORK_OBJ*)Memory_AllocZeroClear(sizeof(WORK_OBJ));

	if( ix != NULL ){

		//���M�\�P�b�g�̏�����	�g�p���Ă���p�\�R�����g�p���Ă���IP�A�h���X�łȂ���Ύ�M���邱�Ƃ��ł��Ȃ��̂ŗv���ӁI
		Communication_Initialize(&ix->sockatTransmission,Commuination_GetIPAddres(192,168,11,2),9850);

		//��M�\�P�b�g�̏������@
		memset(&ix->sockatReception,0,sizeof(SOCKAT_OBJ));
		//�|�[�g�ԍ��ݒ�
		ix->sockatReception.port = 9850;

		ix->selectY = 0;

		ix->pReveptionData = NULL;

		ix->isTransimision = false;

		ix->subStep = eSubStep_Select;
		ix->step = eStep_Init;

		//��������͐���
		ix->keyInputObj = KeyInputString_Create(100,300,eKeyInputStringType_SingCharOnly);

		s_pWork = ix;
	}

}

void TestCommunication_Updata(){
	_Updata(s_pWork);
}

void TestCommunication_Draw(){
	_Draw(s_pWork);
}

void TestCommunication_Finalize(){


	Communication_Finalize(&s_pWork->sockatTransmission);
	Communication_Finalize(&s_pWork->sockatReception);

	KeyInputString_Destroy(s_pWork->keyInputObj);

	//�������̊J��
	Memory_SafeFree(s_pWork);

}

#endif