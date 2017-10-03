/*

	�ʐM�֌W
*/


//	------- �C���N���[�h�錾
#include "DxLib.h"
#include "Communication.h"
#include "MyLib/Memory/Memory.h"

#ifdef __WINDOWS__

//	------- �Œ�萔�錾

//	------- �񋓑�

//	------- �\����&���p��

//	------- �f�[�^�e�[�u��

//	------- �X�^�e�B�b�N�ϐ�

//	------- �O���[�o���ϐ�

//	------- �X�^�e�B�b�N�v���g�^�C�v�錾

//	------- �v���g�^�C�v�錾���Ă��Ȃ��X�^�e�B�b�N�֐�

//	------- �O���[�o���֐�



//	------- ���[�U�[�g�p�֐�

/*
	������
	SOCKAT_OBJ* ix
	IPDATA		ip
	int			protNum
*/
void Communication_Initialize(SOCKAT_OBJ* ix,IPDATA ip,int portNum){
	
	//IP�A�h���X�̐ݒ�
	ix->ip = ip;

	//�ڑ��|�[�g�̐ݒ�
	ix->port = portNum;

	//�f�[�^�̏�����
	ix->pTrasmissionData = NULL;

	ix->pReceptionData = NULL;

	//�l�b�g���[�N�n���h���̏�����
	ix->netHandle = -1;

	//��M�f�[�^�ʂ̏�����
	ix->dataLength = 0;

}

/*
	�I������
	SOCKAT_OBJ* ix
*/
void Communication_Finalize(SOCKAT_OBJ* ix){
	
	Memory_SafeFree(ix->pTrasmissionData);
	Memory_SafeFree(ix->pReceptionData);

	//�ڑ���؂�
	Communication_CloseNetWork(ix);
	
}

/*
	�ڑ����J�n����
	SOCKAT_OBJ* ix
*/
void Communication_ConnectNetWork(SOCKAT_OBJ* ix){
	//�ʐM���m��
	ix->netHandle = ConnectNetWork(ix->ip,ix->port);
}

/*
	�ڑ���ؒf����
	SOCKAT_OBJ* ix
*/
void Communication_CloseNetWork(SOCKAT_OBJ* ix){
	//�ڑ�����Ă��Ȃ���Ώ����𔲂���
	if(ix->netHandle == -1) return ;
	//�ڑ���ؒf
	CloseNetWork(ix->netHandle);
	//�ڑ����Ă��Ȃ���Ԃɐݒ�
	ix->netHandle = -1;
}

/*
	��M�҂����J�n����
	SOCKAT_OBJ* ix
*/
void Communication_StartReception(SOCKAT_OBJ* ix){
	PreparationListenNetWork( ix->port ) ;
}

/*
	��M������܂ő҂�
	SOCAKT_OBJ* ix
	return true: ��M����	false: ��M�҂�
*/
bool Communication_WaitReception(SOCKAT_OBJ* ix){
	
	//�ڑ����ꂽ���H
	//true: �ڑ����ꂽ	false: �ڑ�����Ă��Ȃ�
	bool isReception = false;

	//�V�����ڑ����������炻�̃l�b�g���[�N�n���h�����󂯎��
	ix->netHandle = GetNewAcceptNetWork();
	if(ix->netHandle == -1){
		isReception = false;
	}else{
		// �ڑ��̎�t���I������
		StopListenNetWork() ;
		//�ڑ����Ă���PC��IP�A�h���X���󂯎��
		GetNetWorkIP( ix->netHandle , &ix->ip ) ;
		isReception = true;
	}
	return isReception;
}

/*
	�f�[�^�̑��M
	SOCKAT_OBJ* ix
*/
bool Communication_Transmission(SOCKAT_OBJ* ix){

	//���M���ꂽ���H
	//true:���M���ꂽ false:���M����Ă��Ȃ�
	bool isTransmission = false;

	//�ڑ�����Ă���Ȃ�
	if(ix->netHandle != -1){		
		//�f�[�^���Ȃ���Ώ����𔲂���
		if(ix->pTrasmissionData == NULL){
			isTransmission = false;
		}
		//�f�[�^������Ȃ�f�[�^�̑��M���s��
		else{
			//�f�[�^�̑��M
			NetWorkSend(ix->netHandle,ix->pTrasmissionData,ix->dataLength);
			isTransmission = true;
		}
	}

	return isTransmission;
}

/*
	�擾���Ă��Ȃ���M�f�[�^�̗ʂ��擾����
	SOCKAT_OBJ* ix
	return	true	:�擾���Ă��Ȃ���M�f�[�^�ʂ�0�łȂ�
			false	:�擾���Ă��Ȃ���M�f�[�^�ʂ�0�ł���
*/
bool Communication_IsNotAcquiredReception(SOCKAT_OBJ* ix){

	//�擾���Ă��Ȃ���M�f�[�^�̗ʂ��擾����
	ix->dataLength = GetNetWorkDataLength(ix->netHandle);

	//�擾���Ă��Ȃ���M�f�[�^�ʂ�0�ł���Ȃ�false��Ԃ�
	if(ix->dataLength == 0){
		return false;
	}
	return true;
}


//	------- �Z�b�^�[�֌W�֐�
/*
	���M����f�[�^��ݒ肷��
	SOCKAT_OBJ* ix		:
	void*		pData	:�f�[�^
	size_t		size	:�f�[�^�T�C�Y
*/
void Communication_SetTransmissionData(SOCKAT_OBJ* ix,void* pData,size_t size){
	//�f�[�^���Ȃ���Ώ����𔲂���
	if(pData == NULL) return ;

	//�f�[�^��ݒ�
	ix->pTrasmissionData = pData;
	//�f�[�^�T�C�Y�̐ݒ�
	ix->dataLength = size;

}

//	------- �Q�b�^�[�֌W�֐�

/*
	IP�A�h���X�̒l����͂�IPDATA�\���̂ɂ��ĕԋp����
	unsigned char d1	:�A�h���X�ԍ�1 [000]
	unsigned char d2	:�A�h���X�ԍ�2 [000]
	unsigned char d3	:�A�h���X�ԍ�3 [ 0 ]
	unsigned char d4	:�A�h���X�ԍ�4 [000]
	return �A�h���X�ԍ�
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
	�擾������M�f�[�^�̎擾
	SOCKAT_OBJ* ix
	return �f�[�^�擾
*/
void* Communication_GetReceptionData(SOCKAT_OBJ* ix){

	//�f�[�^�ʂ��Ȃ���Ώ����𔲂���
	if(ix->dataLength == 0) return NULL;

	if(ix->pReceptionData == NULL){
		//�������m��
		ix->pReceptionData = Memory_Alloc(ix->dataLength);
	}
	//��M�f�[�^�̎擾
	NetWorkRecv(ix->netHandle,ix->pReceptionData,ix->dataLength);
	return ix->pReceptionData;
}

/*
	�ڑ�������Ă��邩�ԋp����
	SOCKACT_OBJ*	ix
	return true:�ڑ����Ă���	false:�ڑ����Ă��Ȃ�
*/
bool Communicaition_GetCommunicationFlag(SOCKAT_OBJ* ix){
	return (ix->netHandle != -1);
}

//	------- �v���g�^�C�v�錾�����X�e�B�b�N�֐��̒��g�̋L�q

#endif //__WINDOWS__
