/*
	
	CharactorObj.h

	キャラクターの基本を構築する

	キャラクターの生成

	キャラクターの削除

	★キャラクターが持つステータス

		//共通データ
		キャラクター座標
		キャラクター角度
		キャラクターサイズ
		モデルデータ
		アニメーションデータ

		//ステータスデータ
		キャラクター体力
		キャラクター攻撃力
		キャラクター防御力
		キャラクター移動速度

		//プレイヤー固有データ
		レベル


		//敵固有データ
		行動AI
		攻撃AI



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

//- チェンジャー--------------------------------

//モデルを替える
void CharactorObj_ChangeModel(CHARA_OBJ* ix,int modelKind);

//- セッター ---------------------------------

//ステータスの設定
void CharactorObj_SetStatus(CHARA_OBJ* ix,int hp,int attack,int defence,float moveSpeed);
void CharactorObj_SetPosition(CHARA_OBJ* ix,VECTOR pos);
void CharactorObj_SetRotate(CHARA_OBJ* ix,VECTOR rot);
void CharactorObj_SetScal(CHARA_OBJ* ix,VECTOR scal);
//- ゲッター ---------------------------------


//ステータスを取得する
STATUS_DATA* CharactorObj_GatStatusData(CHARA_OBJ* ix);
//モデルデータを取得する
MODEL_DATA_HANDLE* CharactorObj_GetModelDataHdl(CHARA_OBJ* ix);

VECTOR CharactorObj_GetScal(CHARA_OBJ* ix);

VECTOR CharactorObj_GetRotate(CHARA_OBJ* ix);

VECTOR CharactorOBj_GetPosition(CHARA_OBJ* ix);
