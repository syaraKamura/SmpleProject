/*
	�ėp���\�[�X

	�Q�[���S�̂��n�܂�O�ɓǂݍ��݂��s���B
	�Q�[�����I������Ƃ��Ƀ��\�[�X���J������

!*/

#pragma once

#include "MyLib/Graphics/Graphics.h"
#include "MyLib/Model/Model.h"

enum eComResID{
	eComResID_UI_Star,
	eComResID_IMG_SHOT,

	eComResID_MAX,
};

//������
void ComRes_Init();
//�����
void ComRes_Finalize();

//���\�[�X�̓ǂݍ��݂��I���������H
bool ComRes_IsLoadEnd();

//�摜�f�[�^��ԋp����
GRAPHICS_RES* ComRes_GetGraphics(eComResID comResID);