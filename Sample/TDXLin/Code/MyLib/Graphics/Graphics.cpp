#include "DxLib.h"
#include "Graphics.h"
#include "MyLib/Debug/Debug.h"

static void _ZeroClear(GRAPHICS_RES* graphics){
	
	graphics->graphicHandle = 0;
	graphics->width = 0;
	graphics->height = 0;
	graphics->offsetPosX = 0;
	graphics->offsetPosY = 0;
	graphics->basePosX = 0;
	graphics->basePosY = 0;
	graphics->drawPosX = 0;
	graphics->drawPosY = 0;

}


//�摜�ǂݍ���
//true:�摜�ǂݍ��ݐ��� false:�摜�ǂݍ��ݎ��s
bool Graphics_LoadBase(GRAPHICS_RES* graphics,const char* fileName,int offsetPosX/* = 0*/,int offsetPosY/* = 0*/,int basePosX/* = 0*/,int basePosY/* = 0*/){

	graphics->graphicHandle = LoadGraph(fileName);

	if(graphics->graphicHandle == -1){
		Debug_Print("�摜�ǂݍ��݂Ɏ��s���܂����B(%s)\n",fileName);
		return false;
	}

	//�摜�T�C�Y�擾
	GetGraphSize(graphics->graphicHandle,&graphics->width,&graphics->height);

	graphics->offsetPosX = offsetPosX;
	graphics->offsetPosY = offsetPosY;

	graphics->basePosX = basePosX;
	graphics->basePosY = basePosY;

	graphics->drawPosX = 0;
	graphics->drawPosY = 0;

	//graphics->pad = 0;
	
	return true;
}

bool Graphics_Load(GRAPHICS_RES* graphics,const char* fileName){
	return Graphics_LoadBase(graphics,fileName);
}

//�摜�̔񓯊��ǂݍ��݊��
void Graphics_ASyncLoadBase(GRAPHICS_RES* graphics,const char*fileName,int offsetPosX/* = 0*/,int offsetPosY/* = 0*/,int basePosX/* = 0*/,int basePosY/* = 0*/){
	SetUseASyncLoadFlag(TRUE);
	Graphics_LoadBase(graphics,fileName,offsetPosX,offsetPosY,basePosX,basePosY);
	SetUseASyncLoadFlag(FALSE);
}

//�摜�̔񓯊��ǂݍ���
void Graphics_ASyncLoad(GRAPHICS_RES* graphics,const char* fileName){
	Graphics_ASyncLoadBase(graphics,fileName);
}


//�摜�̔񓯊��ǂݍ��݂��I�����Ă��邩�H
bool Graphics_IsASyncLoadEnd(GRAPHICS_RES* graphics){

	//�񓯊��ǂݍ��݂��I�����Ă��邩�H
	if(CheckHandleASyncLoad(graphics->graphicHandle) == FALSE){
		//�摜�T�C�Y�擾(�񓯊��ǂݍ��ݒ��ł͉摜�T�C�Y�̎擾���ł��Ȃ�����)
		GetGraphSize(graphics->graphicHandle,&graphics->width,&graphics->height);
		return true;
	}
	return false;
}

void Graphics_Delete(GRAPHICS_RES* graphics){
	
	if(graphics->graphicHandle == 0){
		return ;
	}

	DeleteGraph(graphics->graphicHandle);
	
	_ZeroClear(graphics);
}
/*
	�����ɂ���	�摜�`��K��
	�֐���			Graphics_DrawBase
	����			GRAPHICS_RES*	graphics	:�O���t�B�b�N���\�[�X�\����
	����			int				posX		:X���W
	����			int				posY		:Y���W
	����			int				scrX		:�`����s���摜���ł̍���̍��WU(100�Ȃ� �摜�����W100����width�܂ł͈̔͂�`�悷��)
	����			int				scrY		:�`����s���摜���ł̍���̍��WV(100�Ȃ� �摜�����W100����height�܂ł͈̔͂�`�悷��)
	����			int				width		:�摜�T�C�Y
	����			int				heihgt		:�摜�T�C�Y
	����			int				centerX		:��]�̒��S���WX
	����			int				centerY		:��]�̒��S���WY
	����			double			ExtRate		:�g�嗦(1.0���ʏ�T�C�Y)
	����			double			angle		:�`��p�x
	����			int				transFlag	:�摜�̓����x��L���ɂ��邩�H(TRUE:�L�� FALSE:����)
	����			int				turnFlag	:�摜�𔽓]�����邩?(TRUE:���]���� FALSE:���]���Ȃ�)
!*/
void Graphics_DrawBase(GRAPHICS_RES* graphics,int posX,int posY,int scrX,int scrY,int width,int heihgt,int centerX,int centerY,double ExtRate,double angle,int transFlag,int turnFlag){
	if(graphics == NULL || graphics->graphicHandle == 0){
		return ;
	}

	graphics->drawPosX = graphics->basePosX - graphics->offsetPosX + posX + centerX;
	graphics->drawPosY = graphics->basePosY - graphics->offsetPosY + posY + centerY;


	DrawRectRotaGraph2(graphics->drawPosX,graphics->drawPosY,scrX,scrY,width,heihgt,centerX,centerY,ExtRate,angle,graphics->graphicHandle ,transFlag, turnFlag);
}

/*
	�����ɂ���	�摜�`��
	�֐���			Graphics_DrawBase
	����			GRAPHICS_RES*	graphics	:�O���t�B�b�N���\�[�X�\����
	����			int				posX		:X���W
	����			int				posY		:Y���W
	����			int				transFlag	:�摜�̓����x��L���ɂ��邩�H(TRUE:�L�� FALSE:����)
	����			int				turnFlag	:�摜�𔽓]�����邩?(TRUE:���]���� FALSE:���]���Ȃ�)
!*/
void Graphics_Draw(GRAPHICS_RES* graphics,int posX,int posY,int transFlag,int turnFlag/* = FALSE*/){
	Graphics_DrawBase(graphics,posX,posY,0,0,graphics->width,graphics->height,0,0,1.0,0.0,transFlag,turnFlag);
}

/*
	�����ɂ���	�摜�`��(�摜�̒��S���N�_�ɉ�]������)
	�֐���			Graphics_DrawRot
	����			GRAPHICS_RES*	graphics	:�O���t�B�b�N���\�[�X�\����
	����			int				posX		:X���W
	����			int				posY		:Y���W
	����			double			angle		:�`��p�x
	����			int				transFlag	:�摜�̓����x��L���ɂ��邩�H(TRUE:�L�� FALSE:����)
	����			int				turnFlag	:�摜�𔽓]�����邩?(TRUE:���]���� FALSE:���]���Ȃ�)
!*/
void Graphics_DrawRot(GRAPHICS_RES* graphics,int posX,int posY,double angle,int transFlag,int turnFlag){

	int width = graphics->width;
	int height = graphics->height;
	int centerX = width / 2;
	int centerY = height / 2;
	Graphics_DrawBase(graphics,posX,posY,0,0,width,height,centerX,centerY,1.0,angle,transFlag,turnFlag);
}

/*

	�����ɂ���	�摜�𕪊����ĕ`��
	�֐���			Graphics_DrawRot
	����			GRAPHICS_RES*	graphics	:�O���t�B�b�N���\�[�X�\����
	����			int				posX		:X���W
	����			int				posY		:Y���W
	����			int				scrX		:U1���W(����)
	����			int				scrY		:V1���W
	����			int				width		:U2���W(�E��)
	����			int				height		:V2���W
	����			int				transFlag	:�摜�̓����x��L���ɂ��邩�H(TRUE:�L�� FALSE:����)
	����			int				turnFlag	:�摜�𔽓]�����邩?(TRUE:���]���� FALSE:���]���Ȃ�)

!*/
void Graphics_DrawDiv(GRAPHICS_RES* graphcis,int posX,int posY,int scrX,int scrY,int width,int height,int transFlag,int trunFlag){

	Graphics_DrawBase(graphcis,posX,posY,scrX,scrY,width,height,0,0,1.0,0.0,transFlag,trunFlag);

}

/*
	
	�����ɂ���	�摜���w�肵���T�C�Y�ŕ������`�悷��
	�֐���			Graphics_DrawRot
	����			GRAPHICS_RES*	graphics	:�O���t�B�b�N���\�[�X�\����
	����			int				posX		:X���W
	����			int				posY		:Y���W
	����			int				scrX		:U���W
	����			int				scrY		:V���W
	����			int				transFlag	:�摜�̓����x��L���ɂ��邩�H(TRUE:�L�� FALSE:����)
	����			int				turnFlag	:�摜�𔽓]�����邩?(TRUE:���]���� FALSE:���]���Ȃ�)
!*/
void Graphics_DrawSplit(GRAPHICS_RES* graphics,int posX,int posY,int u,int v,int splitSizeX,int splitSizeY,int transFlag,int trunFlag){

	if(splitSizeX <= 0 || splitSizeX > graphics->width) return ;
	if(splitSizeY <= 0 || splitSizeY > graphics->height) return ;

	int splitXNum = graphics->width / splitSizeX;
	int splitYNum = graphics->height / splitSizeY;

	if(u < 0 || u > splitXNum) return ;
	if(v < 0 || v > splitYNum) return ;

	int u1 = u * splitSizeX;
	int v1 = v * splitSizeY;
	int u2 = u1 + splitSizeX;
	int v2 = v1 + splitSizeY;


	Graphics_DrawDiv(graphics,posX,posY,u1,v1,u2,v2,transFlag,trunFlag);

}


//�摜�̊�X�N���[�����W��ݒ肷��
void Graphics_SetBasePos(GRAPHICS_RES* graphics,int posX,int posY){
	if(graphics == NULL) return ;
	graphics->basePosX = posX;
	graphics->basePosY = posY;
}

//�摜�̒��S���W��ݒ肷��
void Graphics_SetOffsetPos(GRAPHICS_RES* graphics,int posX,int posY){
	if(graphics == NULL) return ;
	graphics->offsetPosX = posX;
	graphics->offsetPosY = posY;
}

//���W��ԋp����
int Graphics_GetPosX(GRAPHICS_RES graphics){
	if(graphics.graphicHandle == 0){
		return 0;
	}
	return graphics.drawPosX;
}

int Graphics_GetPosY(GRAPHICS_RES graphics){
	if(graphics.graphicHandle == 0){
		return graphics.drawPosY;
	}
	return graphics.drawPosY;
}

//�摜�T�C�Y��ԋp����
int Graphics_GetWidth(GRAPHICS_RES graphics){
	if(graphics.graphicHandle == 0){
		return 0;
	}
	return graphics.width;
}

int Graphics_GetHeight(GRAPHICS_RES graphics){
	if(graphics.graphicHandle == 0){
		return 0;
	}
	return graphics.height;

}

