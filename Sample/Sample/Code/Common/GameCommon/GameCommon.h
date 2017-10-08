/*

	�Q�[���Ŕėp�I�Ɏg�p����w�b�_�[�t�@�C����R�[�h���܂Ƃ߂�
	�ėp�\�[�X�t�@�C��

	GameCommon���C���N���[�h���邱�Ƃ�MyLib�̃\�[�X���g�p�\�ɂȂ�

*/

#ifndef __GAME_COMMON_H__
#define __GAME_COMMON_H__

#if 0
#include "DxLib.h"
#include "MyLib/Graphics/Graphics.h"
#include "MyLib/Keyboard/Keyboard.h"
#include "MyLib/Touch/Touch.h"
#include "MyLib/Model/Model.h"
#include "MyLib/Debug/Debug.h"
#include "MyLib/Memory/Memory.h"
#include "MyLib/Task/Task.h"
#include "MyLib/Communication/Communication.h"
#include "MyLib/KeyInputString/KeyInputString.h"
#include "MyLib/Sound/Sound.h"
#include "MyLib/Figure/Figure.h"

#include "MyLib/Easing/Easing.h"

#include "MyLib/FontMgr/FontMgr.h"
#endif 

#include "../TDXLin/TDXLib.h"

#include "Scene/Scene.h"
#include <math.h>

#ifdef __WINDOWS__
	#include <crtdbg.h>
#endif	//__WINDOWS__


//	----- �悭�g���F�̒萔
#define COLOR_WHITE GetColor(255,255,255)	//��
#define COLOR_BLACK GetColor(0,0,0)			//��
#define COLOR_GRAY	GetColor(123,123,123)	//�D�F
#define COLOR_RED	GetColor(255,0,0)		//��
#define COLOR_GREEN	GetColor(0,255,0)		//��
#define COLOR_BLUE	GetColor(0,0,255)		//��
#define COLOR_YELLOW GetColor(255,255,0)	//���F


enum eClampType{
	eClampType_ClampStop,
	eClampType_ClampLoop,
};


/*
	�I���N�����v
	int*			val			:�ύX����l
	int				add			:���Z����l
	int				min			:�ŏ��l
	int				max			:�ő�l
	eClampType		clampType	:�N�����v�̎��
*/
void GameCommon_SelectClamp(int* val,int add,int min,int max,eClampType clampType);

/*
	�I���N�����v(float�^)
	float*		val			:�ύX����l
	float		add			:���Z����l
	float		min			:�ŏ��l
	float		max			:�ő�l
	eClampType	clampType	:�N�����v�̎��
*/
void GemeCommon_SelectClampF(float* val,float add,float min,float max,eClampType clampType);

#endif	//__GAME_COMMON_H__