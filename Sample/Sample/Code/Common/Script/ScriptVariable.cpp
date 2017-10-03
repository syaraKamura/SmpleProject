/*
				�t�@�C����		:ScriptVariable.cpp
				�쐬��			:
				�쐬����		:2017/08/20
				�\�[�X����		:�X�N���v�g�ň����ϐ��̊Ǘ����s��
				
				
				���l
				
				
				
!*/

//	------- �C���N���[�h�錾
#include "Common/GameCommon/GameCommon.h"
#include "ScriptVariable.h"

//	------- �Œ�萔�錾

//	-------	�}�N����`

//	------- �񋓑�

//	------- �\����&���p��

typedef struct _tag_VARIABLE_LIST{
	VARIABLE_DATA* variable;
	_tag_VARIABLE_LIST* pNext;
}VARIABLE_LIST;

//���X�g�̐擪�Ɩ������L�����Ă����\����
typedef struct{
	VARIABLE_LIST* pTop;		//�擪�̃|�C���^�[
	VARIABLE_LIST* pBottom;		//�����̃|�C���^�[
}BUFFER_MEMORISE;

//	------- �f�[�^�e�[�u��

//	------- �X�^�e�B�b�N�ϐ��錾
static VARIABLE_LIST s_Var;			//�ϐ����X�g
static BUFFER_MEMORISE s_Memorise;	//�L���p
//	------- �O���[�o���ϐ��錾

//	------- �X�^�e�B�b�N�v���g�^�C�v�錾(�����֐�)

//	------- �v���g�^�C�v�錾���Ă��Ȃ��X�^�e�B�b�N�֐�(�����֐�)

/*
	���łɓ������O�̕ϐ������݂��Ă��邩���f����
	VARIABLE_DATA*	pVarData
	return	true	:���݂��Ă���
			false	:���݂��Ă��Ȃ�
*/
static bool _IsExitVarialbleName(VARIABLE_DATA* pVarData){
	//���łɑ��݂��Ă��邩�H
	//true:���݂��Ă���	false:���݂��Ă��Ȃ�
	bool isExist = false;

	//���߂Ă̕ϐ��o�^�łȂ���Δ��f������
	if(s_Memorise.pTop != NULL){
		
		for(VARIABLE_LIST* pData = s_Memorise.pTop;pData != s_Memorise.pBottom;pData = s_Memorise.pTop->pNext){
			if(strcmp(pData->variable->variableName,pVarData->variableName) == 0){
					isExist = true;
					break;
			}
		}

	}
	return isExist;
}

//	------- �O���[�o���֐�

/*
	����������(�K���X�N���v�g�g�p���ɌĂ΂Ȃ���΂Ȃ�Ȃ�)
*/
void ScriptVariable_Initalize(){
	
	s_Var.variable = NULL;
	s_Var.pNext = NULL;

	//�f�[�^�̐擪�Ɩ�����ݒ�
	s_Memorise.pTop = s_Memorise.pBottom = s_Var.pNext;
	
}

/*
	�I������(�K���X�N���v�g���I������ۂɌĂ΂Ȃ���΂Ȃ�Ȃ�)
*/
void ScriptVariable_Finalize(){
	
	VARIABLE_LIST* pNowData = s_Memorise.pTop;
	VARIABLE_LIST* pDelData = NULL;

	//���ׂẴf�[�^���폜����
	while(pNowData != NULL){
		pDelData = pNowData;
		Memory_SafeFree(pDelData);
		pNowData = pNowData->pNext;
	}


}

/*
	�ϐ��̒ǉ�
	VARIABLE_DATA*	pVarData	:�o�^����f�[�^
	return	true	:�o�^����
			false	:�o�^���s
*/
bool ScriptVariable_Add(VARIABLE_DATA* pVarData){
	
	//�������O�̕ϐ������݂��Ă�����o�^�����Ȃ�
	if(_IsExitVarialbleName(pVarData) == true) return false;
	
	
	//�������̊m��
	VARIABLE_LIST* pNewData = (VARIABLE_LIST*)Memory_Alloc(sizeof(VARIABLE_LIST));
	
	//�������̊m�ۂɎ��s����
	if(pNewData == NULL){
		return false;
	}
	
	pNewData->pNext = NULL;
	
	//�V�����f�[�^��ݒ�
	s_Memorise.pBottom->variable = pVarData;
	s_Memorise.pBottom = pNewData;
	s_Memorise.pBottom->pNext = NULL;
	
	return true;

}

/*
	�w��̖��O�̕ϐ��̒l��ԋp����
	const char*		variableName	:�ϐ��̖��O
	return	NULL�ȊO:�w��̕ϐ����̃f�[�^��ԋp����
			NULL	:�w��̕ϐ������������Ȃ�����
*/
VARIABLE_DATA* ScriptVariable_GetVariable(const char* variableName){

	//�������f�[�^���i�[����
	VARIABLE_DATA* pVarData = NULL;

	//���߂Ă̕ϐ��o�^�łȂ���Δ��f������
	if(s_Memorise.pTop != NULL){
		
		for(VARIABLE_LIST* pData = s_Memorise.pTop;pData != s_Memorise.pBottom;pData = s_Memorise.pTop->pNext){
			if(strcmp(pData->variable->variableName,variableName) == 0){
				pVarData = pData->variable;
				break;
			}
		}
	}
	return pVarData;
}

/*
	�w��̖��O�̕ϐ��̒l���X�V����
	VARIABLE_DATA*	pVarData	:�ݒ肷��ϐ��f�[�^
*/
void ScriptVariabl_SetUpVariable(VARIABLE_DATA* pVarData){

	//���߂Ă̕ϐ��o�^�łȂ���Δ��f������
	if(s_Memorise.pTop != NULL){
		
		//�ϐ��������������H
		bool isFindVariable = false;
		VARIABLE_LIST* pTmp = NULL;


		for(VARIABLE_LIST* pData = s_Memorise.pTop;pData != s_Memorise.pBottom;pData = s_Memorise.pTop->pNext){
			if(strcmp(pData->variable->variableName,pVarData->variableName) == 0 &&
				pData->variable->variableKind == pVarData->variableKind){
				pData->variable = pVarData;
				pTmp = pData;
				pTmp->pNext = NULL;
				isFindVariable = true;
				break;
			}
		}

		//������ꂽ
		if(isFindVariable == true){

			//�ύX���ꂽ�A�f�[�^���Ō���ֈړ�����B



		}

	}

}