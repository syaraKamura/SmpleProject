/*!/////////////////////////////////////////////////////////////////////////////////////////
	

				������
					�t�@�C���V�X�e���ɂ���


					�t�@�C���̓ǂݍ���
						
						Hedder�@FILE:�t�@�C���̎�� �o�[�W����1.0
						TBL���X�g
							LabelName:
							LabelName:
						�f�[�^1
							LabelName1:
						�f�[�^2
							LabelName2:
							�f�[�^�T�C�Y�ŋL�q

						�g���q��myfile
					�t�@�C���̏����o��


					�t�@�C���̎�ށ@�t�@�C���̃o�[�W����
					�t�@�C���̃f�[�^�e�[�u���ꗗ

					�t�@�C���f�[�^�̒��g
					�����͉�






*////////////////////////////////////////////////////////////////////////////////////////////


#include "DxLib.h"
#include "File.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>



//�摜�̊�{���
typedef struct{
	int id;
	char fileName[256];
	int handle;				//�O���t�B�b�N�n���h��
}GRAPHICS_INFO;

typedef struct{
	int graphicID;	//�摜�ԍ�
	int posX;
	int posY;
	int u1;		//�摜�����W ����
	int v1;
	int u2;		//�摜�����W �E��
	int v2;
}GRAPHICS_UV_DATA;

typedef struct{
	GRAPHICS_INFO info;	//��{���
	GRAPHICS_UV_DATA graphicsUvData;
}GRAPHICS_SHEET_DATA;


typedef struct{
	char fileName[256];
	int line;				//�ő�s��
	char str[][64];			//������f�[�^
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
	
	//�t�@�C�����當������擾����

	char ch = '\0';
	char str[1024][64] = {""};
	int pos = 0;
	int line = 0;

	while(feof(fp) == 0){
		
		ch = fgetc(fp);

		if(ch == '\t'){
			continue;
		}else if(ch == ' ' || ch == '\n'){
			str[line][pos] = '\0';	//�k��������ݒ�
			pos = 0;
			line ++;
			continue;
		}

		str[line][pos] = ch;

		pos++;
	}

	//�󔒍s�A�^�u�A���p�X�y�[�X��ǂݔ�΂�

	//�t�@�C���̎�ނ̓ǂݎ��

	//�t�@�C���̃o�[�W�����ǂݎ��

	//�X�N���v�g�֐��̓ǂݎ��

	fclose(fp);

	//�����̕����ǂݍ��݊J�n




}
