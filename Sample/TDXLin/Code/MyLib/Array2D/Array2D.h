/*
				ファイル名		:Array2D.h
				作成者			:
				作成日時		:2017/09/09
				ソース説明		:
				
				
				備考
				
				
				
!*/

#ifndef __ARRAY2D_H__
#define __ARRAY2D_H__

template <typename T>

class  Array2D{

private:

	T *m_ArrayData;
	int m_Width;		//横幅
	int m_Height;		//高さ

public :
	
	/* コンストラクタ */
	Array2D(){

		 this->m_ArrayData = NULL;
		 this->m_Width = 0;
		 this->m_Height = 0;

	}

	Array2D(int width,int height){

		int idx = width * height;

		 this->m_Width = width;
		 this->m_Height = height;
	 
		 this->m_ArrayData = new T[idx];
	}
	
	/* デストラクタ */
	~Array2D(){
		Delete();
	}

	//コピーする
	Array2D ToCopy(){
		return this;
	}

	//引数のデータをコピーする
	void CopyTo(Array2D val){
		if(m_ArrayData != nullptr){
			Delete();
		}

		this = val;
	}

	//生成する
	void Create(int width,int height){
		if(m_ArrayData != nullptr){
			Delete();
		}

		Array2D(width,height);
	}

	//削除する
	void Delete(){
		this->m_Width = 0;
		this->m_Height = 0;

		delete[] m_ArrayData;
	}

	//値を座標値で設定する
	void SetValue(int x,int y,T val){
		//範囲外なら処理を抜ける
		if(IsOutOfRange(x,y)) return (T)-1;
		SetValueToIdx(x + m_Width * y) = val;
	}

	//値をインデックス番号で設定する
	void SetValueToIdx(int idx,T val){
		//範囲外なら処理を抜ける
		if(idx < 0 || idx >= GetSize()) return ;
		this->m_ArrayData[idx] = val;
	}

	//値を座標値で返却する
	T GetArray(int x,int y){
		//範囲外なら処理を抜ける
		if(IsOutOfRange(x,y)) return (T)-1;
		return GetArrayToIdx(x + m_Width * y);
	}

	//値をインデックス番号で返却する
	T GetArrayToIdx(int idx){
		//範囲外なら処理を抜ける
		if(idx < 0 || idx >= GetSize()) return (T)-1;
		return this->m_ArrayData[idx];
	}

	//横幅を返却する
	int GetWidth(){
		return this->m_Width;
	}

	//縦幅を返却する
	int GetHeight(){
		return this->m_Height;
	}
	
	//全体のサイズを返却する
	int GetSize(){
		return this->m_Width * this->m_Height;
	}

	//範囲外か判断する
	bool IsOutOfRange(int x,int y){
		if(x < 0 || x >= this->m_Width) return true;
		if(y < 0 || y >= this->m_Height) return true;
		return false;
	}

};

#endif // __ARRAY2D_H__