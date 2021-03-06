/*!


				作成日		:2017/09/07

				TDXLibの本体　これを読み込めばすべてのファイルを参照できるようにする


				
*/




#ifndef __TDXLIB_H__
#define __TDXLIB_H__


#include "DxLib.h"
#include "Code/MyLib/Graphics/Graphics.h"
#include "Code/MyLib/Keyboard/Keyboard.h"
#include "Code/MyLib/Touch/Touch.h"
#include "Code/MyLib/Model/Model.h"
#include "Code/MyLib/Debug/Debug.h"
#include "Code/MyLib/Memory/Memory.h"
#include "Code/MyLib/Task/Task.h"
#include "Code/MyLib/Communication/Communication.h"
#include "Code/MyLib/KeyInputString/KeyInputString.h"
#include "Code/MyLib/Sound/Sound.h"
#include "Code/MyLib/Figure/Figure.h"

#include "Code/MyLib/Easing/Easing.h"

#include "Code/MyLib/FontMgr/FontMgr.h"

#include "Code/MyLib/Array2D/Array2D.h"

#include "Code/MyLib/Framework/Framework.h"



//変数型宣言
typedef long			s64;	//long型		8byte
typedef int				s32;	//int型			4byte
typedef short			s16;	//short型		2byte
typedef char			s8;		//char型		1byte
								
typedef unsigned long	u64;	//unsigned　long型		8byte
typedef unsigned int	u32;	//unsigned　int型		4byte
typedef unsigned short	u16;	//unsigned　short型		2byte
typedef unsigned char	u8;		//unsigned　char型		1byte
								
typedef double			f64;	//double型	8byte
typedef float			f32;	//float型	4byte




#endif //__TDXLIB_H__