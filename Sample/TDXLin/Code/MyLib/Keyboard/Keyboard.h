#pragma once


//�L�[���͂���Ă���
extern bool Keyboard_On(int keyCode);

//�L�[���͂���Ă��Ȃ�
extern bool Keyboard_Off(int keyCode);

//�L�[�������ꂽ��Ԃ��������ꂽ
extern bool Keyboard_Relese(int keyCode);

//�L�[�������ꑱ���Ă���
extern bool Keyboard_Repeat(int keyCode);

//�L�[�������ꂽ
extern bool Keyboard_Press(int keyCode);


extern void Keyboard_Updata();