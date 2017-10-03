/*
				ファイル名		:Array2D.cpp
				作成者			:
				作成日時		:2017/09/09
				ソース説明		:
				
				
				備考
				
				
				
!*/

//	------- インクルード宣言
#include "Array2D.h"

//	------- 固定定数宣言

//	-------	マクロ定義

//	------- 列挙体

//	------- 構造体&共用体

//	------- データテーブル

//	------- スタティック変数宣言

//	------- グローバル変数宣言

//	------- スタティックプロトタイプ宣言(内部関数)

//	------- プロトタイプ宣言していないスタティック関数(内部関数)

//	------- グローバル関数

#if 0
template <typename T> Array2D<T>::Array2D(){
	 m_ArrayData = NULL;
	 m_Width = 0;
	 m_Height = 0;
}

template <typename T> Array2D<T>::Array2D(int width,int height){

	 int idx = widht * height;

	 m_Width = wdith;
	 m_Height = height;
	 
	 m_ArrayData = new T[idx];

 }

template <typename T> Array2D<T>::~Array2D(){
	 Delete();
 }

template <typename T>Array2D<T> Array2D<T>::ToCopy(){
	return this;
}


template <typename T>void Array2D<T>::CopyTo(Array2D val){
	
	if(m_ArrayData != nullptr){
		Delete();
	}

	this = val;
}

template <typename T> void Array2D<T>::Create(int width,int heigh){
	
	if(m_ArrayData != nullptr){
		Delete();
	}

	Array2D(width,height);

}

template <typename T> void Array2D<T>::Delete(){
	m_Width = 0;
	m_Height = 0;

	delete[] m_ArrayData;
}

template <typename T> void Array2D<T>::SetValue(int x,int y,T val){
	
	//範囲外なら処理を抜ける
	if(x < 0 || x >= m_Width) return ;
	if(y < 0 || y >= m_Height) return ;

	SetValueToIdx(x + m_Width * y) = val;
}

template <typename T> void Array2D<T>::SetValueToIdx(int idx,T val){
	
	//範囲外なら処理を抜ける
	if(idx < 0 || idx >= GetIdx()) return ;
	m_ArrayData[idx] = val;
}

template <typename T> T Array2D<T>::GetArray(int x,int y){

	//範囲外なら処理を抜ける
	if(x < 0 || x >= m_Width) return ;
	if(y < 0 || y >= m_Height) return ;

	return GetArrayToIdx(x + m_Width * y);

}

template <typename T> T Array2D<T>::GetArrayToIdx(int idx){

	//範囲外なら処理を抜ける
	if(idx < 0 || idx >= GetIdx()) return ;
	return m_ArrayData[idx];

}

template <typename T> int Array2D<T>::GetWidth(){
	return m_Width;
}

template <typename T> int Array2D<T>::GetHeight(){
	return m_Height;
}

template <typename T> int Array2D<T>::GetSize(){
	return m_Width * m_Height;
}

#endif