/*
				�t�@�C����		:Sound.cpp
				�쐬��			:
				�쐬����		:2017/08/16
				�\�[�X����		:�T�E���h�֌W
				
				
				���l
				
				
				
!*/

//	------- �C���N���[�h�錾

#include "DxLib.h"
#include "Sound.h"

//	------- �Œ�萔�錾

//	-------	�}�N����`

//	------- �񋓑�

//	------- �\����&���p��

//	------- �f�[�^�e�[�u��

//	------- �X�^�e�B�b�N�ϐ��錾

//	------- �O���[�o���ϐ��錾

//	------- �X�^�e�B�b�N�v���g�^�C�v�錾(�����֐�)

//	------- �v���g�^�C�v�錾���Ă��Ȃ��X�^�e�B�b�N�֐�(�����֐�)

//	------- �O���[�o���֐�

/*
	�T�E���h�f�[�^�ǂݍ���
	SOUND_DATA*		snd			:
	const char*		fileName	:�t�@�C����
	eSoundType		soundType	:�T�E���h�̎��
	*/
void Sound_LoadBase(SOUND_DATA* snd,const char* fileName,eSoundType soundType){

	snd->handle = LoadSoundMem(fileName);
	snd->valum = 255;
	snd->soundType = soundType;

}

/*
	�񓯊��ŃT�E���h�f�[�^�ǂݍ���
	SOUND_DATA*		snd			:
	const char*		fileName	:�t�@�C����
	eSoundType		soundType	:�T�E���h�̎��
*/
void Sound_ASyncLoad(SOUND_DATA* snd,const char* fileName,eSoundType soundType){
	SetUseASyncLoadFlag(TRUE);
	Sound_LoadBase(snd,fileName,soundType);
	SetUseASyncLoadFlag(FALSE);
}

/*
	�񓯊��ǂݍ��݂��I�����������f������
	SOUND_DATA*		snd
	return	true	:�񓯊��ǂݍ��݂��I������
			false	:�񓯊��ǂݍ��ݒ�
*/
bool Sound_IsEndASyncLoad(SOUND_DATA* snd){
	if(CheckHandleASyncLoad(snd->handle) == FALSE){
		return true;
	}
	return false;
}

/*
	�Đ�����
	SOUND_DATA*		snd
*/
void Sound_Play(SOUND_DATA* snd){

	//BGM�Đ�
	if(snd->soundType == eSoundType_BGM){
		PlaySoundMem(snd->handle,DX_PLAYTYPE_LOOP);
	}
	//���ʉ��Đ�
	else if(snd->soundType == eSoundType_SE){
		PlaySoundMem(snd->handle,DX_PLAYTYPE_BACK);
	}

}

/*
	�ꎞ��~����
	SOUND_DATA*		snd
*/
void Sound_Stop(SOUND_DATA* snd){
	StopSoundMem(snd->handle);
}

/*
	�폜����
	SOUND_DATA*		snd
*/
void Sound_Delete(SOUND_DATA* snd){
	DeleteSoundMem(snd->handle);
}

/*
	�Đ��������f����
	SOUND_DATA*		snd
	return	true	:�Đ���
			false	:�Œ��ł͂Ȃ�
*/
bool Sound_IsCheckPlaySound(SOUND_DATA* snd){

	if(CheckSoundMem(snd->handle) == FALSE){
		return false;
	}
	return true;
}

