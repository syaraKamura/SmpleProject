/*!/////////////////////////////////////////////////////////////////////////////////////////
	

				☆メモ
					ファイルシステムについて


					ファイルの読み込み
						
						Hedder　FILE:ファイルの種類 バージョン1.0
						TBLリスト
							LabelName:
							LabelName:
						データ1
							LabelName1:
						データ2
							LabelName2:
							データサイズで記述

						拡張子はmyfile
					ファイルの書き出し


					ファイルの種類　ファイルのバージョン
					ファイルのデータテーブル一覧

					ファイルデータの中身
					ここは可変






*////////////////////////////////////////////////////////////////////////////////////////////


#include "DxLib.h"
#include "File.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>



//画像の基本情報
typedef struct{
	int id;
	char fileName[256];
	int handle;				//グラフィックハンドル
}GRAPHICS_INFO;

typedef struct{
	int graphicID;	//画像番号
	int posX;
	int posY;
	int u1;		//画像内座標 左上
	int v1;
	int u2;		//画像内座標 右下
	int v2;
}GRAPHICS_UV_DATA;

typedef struct{
	GRAPHICS_INFO info;	//基本情報
	GRAPHICS_UV_DATA graphicsUvData;
}GRAPHICS_SHEET_DATA;


typedef struct{
	char fileName[256];
	int line;				//最大行数
	char str[][64];			//文字列データ
}FILE_LOADER_DATA;


static void _GraphicsLoadData(FILE_LOADER_DATA FileData){
	
	int line = 0;

	GRAPHICS_SHEET_DATA graphicsSheetData = {};

	while(line < FileData.line){

		char* str = FileData.str[line];


		if(strcmp(str,"FILE") == 0){
			
		}else if(strcmp(str,"VERSION") == 0){


		}else if(strcmp(str,"PASH") == 0){
			
			strcpy_s(graphicsSheetData.info.fileName, FileData.str[1]);
			


		}else if(strcmp(str,"VERSION") == 0){


		}else if(strcmp(str,"VERSION") == 0){


		}

	}

}

void File_Wirte(void* data,size_t size){

	FILE* fp;

	fopen_s(&fp,"testFile.txt","wb");

	if(fp == NULL){
		return ;
	}

	fwrite("FILE: VERSION:1.0\n",1,sizeof("FILE: VERSION:1.0\n"),fp);
	fwrite("TABLE{",1,sizeof("TABLE{"),fp);
	fwrite("Pram",1,sizeof("Pram"),fp);
	fwrite("}",1,sizeof("}"),fp);
	fwrite("Pram{",1,sizeof("Pram{"),fp);
	
	fwrite("}",1,sizeof("}"),fp);

	fclose(fp);

	
}


void File_Read(){

	FILE* fp;
	bool isFlag = true;

	fopen_s(&fp,"testFile.txt","rb");

	if(fp == NULL){
		return ;
	}
	
	//ファイルから文字列を取得する

	char ch = '\0';
	char str[1024][64] = {""};
	int pos = 0;
	int line = 0;

	while(feof(fp) == 0){
		
		ch = fgetc(fp);

		if(ch == '\t'){
			continue;
		}else if(ch == ' ' || ch == '\n'){
			str[line][pos] = '\0';	//ヌル文字を設定
			pos = 0;
			line ++;
			continue;
		}

		str[line][pos] = ch;

		pos++;
	}

	//空白行、タブ、半角スペースを読み飛ばす

	//ファイルの種類の読み取り

	//ファイルのバージョン読み取り

	//スクリプト関数の読み取り

	fclose(fp);

	//文字の分割読み込み開始




}
