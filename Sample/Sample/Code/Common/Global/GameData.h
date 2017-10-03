/*
				�t�@�C����		:GameData.h
				�쐬��			:
				�쐬����		:2017/08/22
				�\�[�X����		:
				
					�Q�[���f�[�^���Ǘ�����
					��Ƀf�[�^�̕ۑ���f�[�^�̓ǂݍ��ݓ����s��
				
				���l
				
				
				
!*/

#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__

//	------- �C���N���[�h�錾

#include "Common/GameCommon/GameCommon.h"

//	------- �Œ�萔�錾
static const int FLAGS_DATA_NUM = 4096;
//	-------	�}�N����`

//	------- �񋓑�

//	------- �\����&���p��
typedef struct{
	s8 flags[FLAGS_DATA_NUM];
}GAME_FLAGS_DATA;

typedef struct{
	s32 hash;					//�n�b�V�� �����l���قȂ�ꍇ�s���ȃZ�[�u�f�[�^�Ƃ���
	GAME_FLAGS_DATA gameFlag;
	char name[26];
}GAME_DATA;
//	------- �O���[�o���֐�

/*
	�Q�[���f�[�^�̏�����
*/
void GameData_Initialize();
/*
	�Q�[���f�[�^�̓ǂݍ���
*/
void GameData_Load();
/*
	�Q�[���f�[�^�̏�������
*/
void GameData_Save();

// ----�Q�[���f�[�^�̎擾(��g)

/*
	�Q�[���f�[�^�S�̂�ԋp����
*/
const GAME_DATA* GameData_GetGameData();


// ----�Q�[���f�[�^�̎擾(��)

/*
	�Q�[���̃t���O�̏�Ԃ�ԋp����
	s32	flagIdx	:�t���O�ԍ�
	return	true	:�t���O��ON
			false	:�t���O��OFF
*/
bool GameData_IsFlag(s32 flagIdx);

/*
	�w��̃t���O�ԍ���ݒ肷��
	s32		flagIdx	:�t���O�ԍ�
	BOOL	flag	:�t���O��ݒ肷��
*/
void GameData_SetGameDataFlag(s32 flagIdx,BOOL flag);

//	------- �C�����C���֐�(�w�b�_�[���֐�)


#endif	//__GAME_DATA_H__
