/*
				�t�@�C����		:Sound.h
				�쐬��			:
				�쐬����		:2017/08/16
				�\�[�X����		:
				
				
				���l
				
				
				
!*/

#ifndef __SOUND_H__
#define __SOUND_H__

//	------- �C���N���[�h�錾

//	------- �Œ�萔�錾

//	-------	�}�N����`

//	------- �񋓑�

enum eSoundType{
	eSoundType_BGM,
	eSoundType_SE,
	eSoundType_NONE,
};

//	------- �\����&���p��

typedef struct{
	int handle;				//�T�E���h�n���h��
	int valum;				//����
	int startPos;			//�Đ��J�n�ʒu
	int endPos;				//�Đ��I���ʒu
	eSoundType soundType;	//�T�E���h�̎��
}SOUND_DATA;

//	------- �O���[�o���֐�

/*
	�T�E���h�f�[�^�ǂݍ���
	SOUND_DATA*		snd			:
	const char*		fileName	:�t�@�C����
	eSoundType		soundType	:�T�E���h�̎��
	*/
extern void Sound_LoadBase(SOUND_DATA* snd,const char* fileName,eSoundType soundType);

/*
	�񓯊��ŃT�E���h�f�[�^�ǂݍ���
	SOUND_DATA*		snd			:
	const char*		fileName	:�t�@�C����
	eSoundType		soundType	:�T�E���h�̎��
*/
extern void Sound_ASyncLoad(SOUND_DATA* snd,const char* fileName,eSoundType soundType);

/*
	�񓯊��ǂݍ��݂��I�����������f������
	SOUND_DATA*		snd
	return	true	:�񓯊��ǂݍ��݂��I������
			false	:�񓯊��ǂݍ��ݒ�
*/
extern bool Sound_IsEndASyncLoad(SOUND_DATA* snd);

/*
	�Đ�����
	SOUND_DATA*		snd
*/
extern void Sound_Play(SOUND_DATA* snd);

/*
	�ꎞ��~����
	SOUND_DATA*		snd
*/
extern void Sound_Stop(SOUND_DATA* snd);
/*
	�폜����
	SOUND_DATA*		snd
*/
extern void Sound_Delete(SOUND_DATA* snd);
/*
	�Đ��������f����
	SOUND_DATA*		snd
	return	true	:�Đ���
			false	:�Œ��ł͂Ȃ�
*/
extern bool Sound_IsCheckPlaySound(SOUND_DATA* snd);

//	------- �C�����C���֐�(�w�b�_�[���֐�)

#endif	//__SOUND_H__