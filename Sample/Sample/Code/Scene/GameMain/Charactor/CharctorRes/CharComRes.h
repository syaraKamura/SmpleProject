#pragma once

/*

	�L�����N�^�[���g�p����f�[�^�̓ǂݍ��݂��s��

	�Q�[�����C���Ɉڍs�����ۂɃf�[�^�̓ǂݍ��݂��s��

		���񓯊��ǂݍ��݂��]�܂����B

	

*/


enum eCharComResId{

	//���f��
	eCharComResId_Charactor,	//�L�����N�^�[
	eCharComResId_Enemy1,		//�G
	eCharComResId_Enemy2,		//�G2
	eCharComResId_Map,			//�}�b�v
	//�摜
	eCharComResId_UI_HpGage,	//�̗̓Q�[�W

	//csv�f�[�^
	
	eCharComResId_Max,
};

//�������̊m��
void CharComRes_Init();

void CharComRes_Finalize();

//�ǂݍ��݃��N�G�X�g
void CharComRes_LoadRequest();

//�ǂݍ��݂��I�����������f����
//true:�ǂݍ��ݏI�� false:�ǂݍ��ݒ�
bool CharComRes_IsLoadEnd();

//�f�[�^��ԋp����
MODEL_DATA_HANDLE* CharComRes_GetModelData(eCharComResId idx);

//�f�[�^��ԋp����
GRAPHICS_RES* CharComRes_GetGraphics(eCharComResId idx);

int CharComRes_GetCsvDataSize(eCharComResId idx);

const char* CharComRes_GetCsvData(eCharComResId idx);