#pragma once


//キー入力されている
extern bool Keyboard_On(int keyCode);

//キー入力されていない
extern bool Keyboard_Off(int keyCode);

//キーが押された状態から解放された
extern bool Keyboard_Relese(int keyCode);

//キーが押され続けている
extern bool Keyboard_Repeat(int keyCode);

//キーが押された
extern bool Keyboard_Press(int keyCode);


extern void Keyboard_Updata();