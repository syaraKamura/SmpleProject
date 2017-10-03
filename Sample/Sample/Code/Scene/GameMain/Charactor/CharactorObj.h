/*
	
	CharactorObj.h

	�L�����N�^�[�̊�{���\�z����

	�L�����N�^�[�̐���

	�L�����N�^�[�̍폜

	���L�����N�^�[�����X�e�[�^�X

		//���ʃf�[�^
		�L�����N�^�[���W
		�L�����N�^�[�p�x
		�L�����N�^�[�T�C�Y
		���f���f�[�^
		�A�j���[�V�����f�[�^

		//�X�e�[�^�X�f�[�^
		�L�����N�^�[�̗�
		�L�����N�^�[�U����
		�L�����N�^�[�h���
		�L�����N�^�[�ړ����x

		//�v���C���[�ŗL�f�[�^
		���x��


		//�G�ŗL�f�[�^
		�s��AI
		�U��AI



*/

typedef struct{
	int hp;
	int maxHp;
	int Attack;
	int Defence;
	float moveSpeed;
}STATUS_DATA;

typedef struct{
	VECTOR pos;
	VECTOR rot;
	VECTOR scal;
	MODEL_DATA_HANDLE* model;
	STATUS_DATA status;
}CHARA_OBJ;


CHARA_OBJ* CharactorObj_Create(int modelKind);
void CharactorObj_Delete(CHARA_OBJ* ix);

//- �`�F���W���[--------------------------------

//���f����ւ���
void CharactorObj_ChangeModel(CHARA_OBJ* ix,int modelKind);

//- �Z�b�^�[ ---------------------------------

//�X�e�[�^�X�̐ݒ�
void CharactorObj_SetStatus(CHARA_OBJ* ix,int hp,int attack,int defence,float moveSpeed);
void CharactorObj_SetPosition(CHARA_OBJ* ix,VECTOR pos);
void CharactorObj_SetRotate(CHARA_OBJ* ix,VECTOR rot);
void CharactorObj_SetScal(CHARA_OBJ* ix,VECTOR scal);
//- �Q�b�^�[ ---------------------------------


//�X�e�[�^�X���擾����
STATUS_DATA* CharactorObj_GatStatusData(CHARA_OBJ* ix);
//���f���f�[�^���擾����
MODEL_DATA_HANDLE* CharactorObj_GetModelDataHdl(CHARA_OBJ* ix);

VECTOR CharactorObj_GetScal(CHARA_OBJ* ix);

VECTOR CharactorObj_GetRotate(CHARA_OBJ* ix);

VECTOR CharactorOBj_GetPosition(CHARA_OBJ* ix);
