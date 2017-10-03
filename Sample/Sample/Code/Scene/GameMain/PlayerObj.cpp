//------------------------------------------------- �C���N���[�h
#include "Common/GameCommon/GameCommon.h"

#include "GameMain.h"
#include "PlayerObj.h"
//------------------------------------------------- �萔��`(define & const)

//------------------------------------------------- �񋓑̒�`

//------------------------------------------------- �\���̒�`(structer & union)

//------------------------------------------------- �e�[�u����`
//------------------------------------------------- �X�^�e�B�b�N�ϐ���`
//------------------------------------------------- �O���[�o���ϐ���`
//------------------------------------------------- �v���g�^�C�v�錾
//------------------------------------------------- �X�^�e�B�b�N��`
//------------------------------------------------- �O���[�o����`

//����
PLAYER_OBJ* PlayerObj_Create(const char* fileName){

	PLAYER_OBJ* ix = (PLAYER_OBJ*)Memory_AllocZeroClear(sizeof(PLAYER_OBJ));
	
	//���������m�ۂł��Ă���Ȃ�
	if(ix != NULL){
		
		//���f���f�[�^�̓ǂݍ���
		Model_Init(&ix->model,fileName);
	

		PlayerObj_SetScal(ix,VGet(1.0f,1.0f,1.0f));
		PlayerObj_SetRotate(ix,VGet(0,0,0));

		ix->matrix = MGetIdent();	//�P�ʍs����擾����

		return ix;
	}
	return NULL;
}

//�폜
void PlayerObj_Destroy(PLAYER_OBJ* ix){
	if(ix == NULL) return ;
	
	Model_Finalize(&ix->model);
	
	Memory_SafeFree(ix);
}

void PlayerObj_Updata(PLAYER_OBJ* ix){

	//ix->matrix = MGetIdent();								//�P�ʍs����擾
	//ix->matrix = MMult(ix->matrix,MGetRotX(ix->rotate.x));	//��]
	//ix->matrix = MMult(ix->matrix,MGetRotY(ix->rotate.y));
	//ix->matrix = MMult(ix->matrix,MGetRotZ(ix->rotate.z));
	//ix->matrix = MMult(ix->matrix,MGetTranslate(ix->pos));	//���s�ړ�
	//ix->matrix = MMult(ix->matrix,MGetScale(ix->scal));		//�X�P�[�����O


}

//�`��
void PlayerObj_Draw(PLAYER_OBJ* ix){

	Model_Draw(&ix->model,ix->pos,ix->scal,ix->rotate);
	//Model_Draw(&ix->model,ix->matrix);

}

//���W�̐ݒ�
void PlayerObj_SetPositon(PLAYER_OBJ* ix,float x,float y,float z){
	ix->pos.x = x;
	ix->pos.y = y;
	ix->pos.z = z;
}

void PlayerObj_SetPositon(PLAYER_OBJ* ix,VECTOR pos){
	ix->pos = pos;
}

//�T�C�Y�ύX
void PlayerObj_SetScal(PLAYER_OBJ* ix,VECTOR scal){
	ix->scal = scal;
}

//�p�x�̐ݒ�
void PlayerObj_SetRotate(PLAYER_OBJ* ix,VECTOR rot){
	ix->rotate = rot;
}

//�p�x�̎擾
VECTOR PlayerObj_GetRoate(PLAYER_OBJ* ix){
	return ix->rotate;
}

//���W�̎擾
VECTOR PlayerObj_GetPosition(PLAYER_OBJ* ix){
	return ix->pos;
}

