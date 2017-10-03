#include "Common/GameCommon/GameCommon.h"
#include "CharctorRes/CharComRes.h"

#include "Chara_EnemyObj.h"
#include "EnemyMgr.h"

const int ENEMY_CREATE_MAX_NUM = 100;

typedef struct{
	int enemyCreateNum;			//ìGÇÃê∂ê¨êî
	CHARA_ENEMY_OBJ* enemy[ENEMY_CREATE_MAX_NUM];
}ENEMY_MGR_OBJ;

static ENEMY_MGR_OBJ* s_pWork;

static void _Updata(ENEMY_MGR_OBJ* ix){

	
	for(int i = 0;i < ix->enemyCreateNum;i++){
		CharEnemyObj_Updata(ix->enemy[i]);
	}
}

static void _Draw(ENEMY_MGR_OBJ* ix){
	
	for(int i = 0;i < ix->enemyCreateNum;i++){
		CharEnemyObj_Draw(ix->enemy[i]);
	}
}

//num: ìGÇÃê∂ê¨êî
void EnemyMgr_Init(int num){

	
	if(num <= 0){
		return ;
	}

	ENEMY_MGR_OBJ* ix = (ENEMY_MGR_OBJ*)Memory_Alloc(sizeof(ENEMY_MGR_OBJ));

	if(ix != NULL){
		
		ix->enemyCreateNum = num;

		
		for(int i = 0;i < ix->enemyCreateNum;i++){
			ix->enemy[i] = CharEnemyObj_Creata(i,VGet(GetRand(200) - 100,0,GetRand(300) - 150),VGet(0,40,0),eCharComResId_Enemy1 + i % 2);
			CharEnemyObj_SetStatus(ix->enemy[i],100,10,3,2.5f);
		}

		s_pWork = ix;
	}

}

void EnemyMgr_Finalize(){

	for(int i = 0;i < s_pWork->enemyCreateNum;i++){
		CharEnemyObj_Destory(s_pWork->enemy[i]);
	}
	Memory_SafeFree(s_pWork);

}

void EnemyMgr_Updata(){
	_Updata(s_pWork);
}

void EnemyMgr_Draw(){
	_Draw(s_pWork);
}


int EnemyMgr_EnemyNum(){
	if(s_pWork == NULL)	return 0;
	return s_pWork->enemyCreateNum;
}

CHARA_ENEMY_OBJ* EnemyMgr_GetEnemy(int num){
	if(s_pWork == NULL)	return NULL;
	if(num < 0 || num >= s_pWork->enemyCreateNum) return NULL;
	return s_pWork->enemy[num];
}