/*
	�ʐM�֌W
	
*/

#pragma once

#ifdef __WINDOWS__

typedef struct{
	int netHandle;			//�l�b�g���[�N�n���h��
	IPDATA ip;				//IP�A�h���X 000.000.0.000
	int port;				//�|�[�g�ԍ�

	bool isTransmission;	//�f�[�^�𑗐M�������H


	int dataLength;			//�f�[�^��
	void* pTrasmissionData;	//���M�f�[�^
	void* pReceptionData;	//��M�f�[�^

}SOCKAT_OBJ;


/*
	������
	SOCKAT_OBJ* ix
	IPDATA		ip
	int			protNum
*/
extern void Communication_Initialize(SOCKAT_OBJ* ix,IPDATA ip,int portNum);
/*
	�I������
	SOCKAT_OBJ* ix
*/
extern void Communication_Finalize(SOCKAT_OBJ* ix);
/*
	�ڑ����J�n����
	SOCKAT_OBJ* ix
*/
extern void Communication_ConnectNetWork(SOCKAT_OBJ* ix);

/*
	�ڑ���ؒf����
	SOCKAT_OBJ* ix
*/
extern void Communication_CloseNetWork(SOCKAT_OBJ* ix);

/*
	��M�҂����J�n����
	SOCKAT_OBJ* ix
*/
extern void Communication_StartReception(SOCKAT_OBJ* ix);
/*
	��M������܂ő҂�
	SOCAKT_OBJ* ix
	return true: ��M����	false: ��M�҂�
*/
extern bool Communication_WaitReception(SOCKAT_OBJ* ix);

/*
	�f�[�^�̑��M
	SOCKAT_OBJ* ix
*/
extern bool Communication_Transmission(SOCKAT_OBJ* ix);

/*
	�擾���Ă��Ȃ���M�f�[�^�̗ʂ��擾����
	SOCKAT_OBJ* ix
	return true:�擾���Ă��Ȃ���M�f�[�^�ʂ�0�łȂ� false:�擾���Ă��Ȃ���M�f�[�^�ʂ�0�ł���
*/
extern bool Communication_IsNotAcquiredReception(SOCKAT_OBJ* ix);

//	------- �Z�b�^�[�֌W�֐�
/*
	���M����f�[�^��ݒ肷��
	SOCKAT_OBJ* ix		:
	void*		pData	:�f�[�^
	size_t		size	:�f�[�^�T�C�Y
*/
extern void Communication_SetTransmissionData(SOCKAT_OBJ* ix,void* pData,size_t size);

//	------- �Q�b�^�[�֌W�֐�

/*
	IP�A�h���X�̒l����͂�IPDATA�\���̂ɂ��ĕԋp����
	unsigned char d1	:�A�h���X�ԍ�1 [000]
	unsigned char d2	:�A�h���X�ԍ�2 [000]
	unsigned char d3	:�A�h���X�ԍ�3 [ 0 ]
	unsigned char d4	:�A�h���X�ԍ�4 [000]
	return �A�h���X�ԍ�
*/
extern IPDATA Commuination_GetIPAddres(unsigned char d1,unsigned char d2,unsigned char d3,unsigned char d4);

/*
	�擾������M�f�[�^�̎擾
	SOCKAT_OBJ* ix
	return �f�[�^�擾
*/
extern void* Communication_GetReceptionData(SOCKAT_OBJ* ix);


/*
	�ڑ�������Ă��邩�ԋp����
	SOCKACT_OBJ*	ix
	return true:�ڑ����Ă���	false:�ڑ����Ă��Ȃ�
*/
extern bool Communicaition_GetCommunicationFlag(SOCKAT_OBJ* ix);

#endif //__WINDOWS__
