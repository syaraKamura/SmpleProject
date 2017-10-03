/*

	”Ä—p‚ ‚½‚è”»’è


!*/

#include "DxLib.h"

#include "Hit.h"


//ŽlŠpŒ`‚Æ“_‚ ‚½‚è”»’è

/*
	ŽlŠpŒ`‚ÆŽlŠpŒ`‚Ì‚ ‚½‚è”»’è
	HIT_DATA rec1:ŽlŠpŒ`1
	HIT_DATA rec2:ŽlŠpŒ`2
	return	true	:“–‚½‚Á‚Ä‚¢‚é
			false	:“–‚½‚Á‚Ä‚¢‚È‚¢
*/
bool Hit2D_BoxToBox(HIT_DATA rec1,HIT_DATA rec2){

	if(((rec1.posX >= rec2.posX && rec1.posX <= rec2.posX + rec2.width) || 
		(rec1.posX + rec1.width >= rec2.posX && rec1.posX + rec1.width <= rec2.posX + rec2.width)) ||
		((rec1.posY >= rec2.posY && rec1.posY <= rec2.posY + rec2.height) || 
		(rec1.posY + rec1.height >= rec2.posY && rec1.posY + rec1.height <= rec2.posY + rec2.height))){
			return true;
	}
	return false;
}

/*
	‰~‚Æ“_‚Ì‚ ‚½‚è”»’è
	HIT_DATA circle	:‰~
	HIT_DATA dot	:“_
	return	true	:“–‚½‚Á‚Ä‚¢‚é
			false	:“–‚½‚Á‚Ä‚¢‚È‚¢
*/
bool Hit2D_CircleToDot(HIT_DATA circle,HIT_DATA dot){

	//’†SÀ•W‚ÉC³
	int centerX = circle.posX + circle.width / 2;
	int centerY = circle.posY + circle.height / 2;

	int x = centerX - dot.posX;
	int y = centerY - dot.posY;
	float r = circle.radius;

	if(x*x+y*y <= r*r){
		return true;
	}

	return false;
}

/*
	‰~‚Æ‰~‚Ì‚ ‚½‚è”»’è
	HIT_DATA corcle1:‰~1
	HIT_DATA corcle2:‰~2
	return	true	:“–‚½‚Á‚Ä‚¢‚é
			false	:“–‚½‚Á‚Ä‚¢‚È‚¢
*/
bool Hit2D_CircleToCircle(HIT_DATA circle1,HIT_DATA circle2){

	//’†SÀ•W‚ÉC³
	int centerX1 = circle1.posX + circle1.width / 2;
	int centerY1 = circle1.posY + circle1.height / 2;

	int centerX2 = circle2.posX + circle2.width / 2;
	int centerY2 = circle2.posY + circle2.height / 2;


	int x = centerX1 - centerX2;
	int y = centerY1 - centerY2;
	float r = circle1.radius + circle2.radius;

	if(x*x+y*y <= r*r){
		return true;
	}

	return false;
}

/*
	ƒqƒbƒgƒf[ƒ^\‘¢‘ÌŒ^‚É‚µ‚Ä•Ô‹p‚µ‚Ü‚·
	int posX		:XÀ•W
	int posY		:YÀ•W
	int width		:‰¡•
	int height		:c•
	float radius	:”¼Œa
	return HIT_DATAŒ^‚ð•Ô‹p
*/
HIT_DATA HIT2D_GetHitData(int posX,int posY,int width,int height,float radius){
	HIT_DATA data = {posX,posY,width,height,radius};
	return data;
}