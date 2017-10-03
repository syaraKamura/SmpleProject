/*
				�t�@�C����		:GameData.cpp
				�쐬��			:
				�쐬����		:2017/08/22
				�\�[�X����		:
				
					�Q�[���f�[�^���Ǘ�����
					��Ƀf�[�^�̕ۑ���f�[�^�̓ǂݍ��ݓ����s��
				
				���l
				
				
				
!*/

//	------- �C���N���[�h�錾
#include "Common/GameCommon/GameCommon.h"
#include "GameData.h"
//	------- �Œ�萔�錾

//	-------	�}�N����`
#define HASH(S,A,V,E) ((S << 16) + (A << 8) + (V << 4) + (E << 1))
#define SAVE HASH('S','A','V','E')

#define FILE_NAME "SAVE.txt"

//	------- �񋓑�

//	------- �\����&���p��

//	------- �f�[�^�e�[�u��

//	------- �X�^�e�B�b�N�ϐ��錾
static GAME_DATA s_GameData;
//	------- �O���[�o���ϐ��錾

//	------- �X�^�e�B�b�N�v���g�^�C�v�錾(�����֐�)

//	------- �v���g�^�C�v�錾���Ă��Ȃ��X�^�e�B�b�N�֐�(�����֐�)

//	------- �O���[�o���֐�

/*
	�Q�[���f�[�^�̏�����
*/
void GameData_Initialize(){
	memset(&s_GameData,0,sizeof(GAME_DATA));
	s_GameData.hash = SAVE;
	strcpy_s(s_GameData.name,26,"���{��");
}

/*
	�Q�[���f�[�^�̓ǂݍ���
*/
void GameData_Load(){
	
	s64 hash = SAVE;
	GAME_DATA data;
	FILE* fp;

	fopen_s(&fp,FILE_NAME,"rb");

	if(fp == NULL){
		Debug_LogPrintf("SAVE�f�[�^���J���܂���ł����B\n");
		return ;
	}

	fread(&data,1,sizeof(GAME_DATA),fp);

	fclose(fp);
	
	if(data.hash != SAVE){
		Debug_LogPrintf("SAVE�f�[�^���s���ł��B\n");
		memset(&data,0,sizeof(GAME_DATA));
	}else{
		Debug_LogPrintf("SAVE�f�[�^�̓ǂݍ��݂ɐ������܂����B\n");
		s_GameData = data;
		Debug_LogPrintf("name:%s\n",data.name);

	}


}

/*
	�Q�[���f�[�^�̏�������
*/
void GameData_Save(){

	const GAME_DATA* pData = GameData_GetGameData();

	FILE* fp;

	fopen_s(&fp,FILE_NAME,"wb");

	if(fp == NULL){
		Debug_LogPrintf("SAVE�f�[�^���J���܂���ł����B\n");
		return ;
	}

	fwrite(pData,1,sizeof(GAME_DATA),fp);

	Debug_LogPrintf("SAVE�f�[�^�֕ۑ����ł��܂���\n");
	fclose(fp);

	Debug_LogPrintf("HASH = %d\n",SAVE);

}

// ----�Q�[���f�[�^�̎擾(��g)

/*
	�Q�[���f�[�^�S�̂�ԋp����
*/
const GAME_DATA* GameData_GetGameData(){
	return &s_GameData;
}



// ----�Q�[���f�[�^�̎擾(��)

/*
	�Q�[���̃t���O�̏�Ԃ�ԋp����
	s32	flagIdx	:�t���O�ԍ�
	return	true	:�t���O��ON
			false	:�t���O��OFF
*/
bool GameData_IsFlag(s32 flagIdx){

	//�t���O�͈̔͊O���w�肳�ꂽ��OFF�t���O��ԋp����
	if(flagIdx < 0 || flagIdx >= FLAGS_DATA_NUM){
		Debug_LogPrintf("Func: %s line:%d\n �t���O�͈̔͊O���w�肵�܂����B\n",__FUNCTION__,__LINE__);
		return false;
	}

	//0���傫�����true��ԋp����
	return s_GameData.gameFlag.flags[flagIdx] > 0;
}

/*
	�w��̃t���O�ԍ���ݒ肷��
	s32		flagIdx	:�t���O�ԍ�
	BOOL	flag	:�t���O��ݒ肷��
*/
void GameData_SetGameDataFlag(s32 flagIdx,BOOL flag){

	//�t���O�͈̔͊O���w�肳�ꂽ�珈���𔲂���
	if(flagIdx < 0 || flagIdx >= FLAGS_DATA_NUM){
		Debug_LogPrintf("Func: %s line:%d\n �t���O�͈̔͊O�ɐݒ肵�悤�Ƃ��܂����B\n",__FUNCTION__,__LINE__);	
		return;
	}
	s_GameData.gameFlag.flags[flagIdx] = flag;

}


#ifdef __MY_DEBUG__




#endif //__MY_DEBUG__