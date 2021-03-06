//////////////////////////////////////////////////////////////////////////////////////////
/*
		File :  ReadMe.txt
		Title:	Sampleプロジェクトについて
		Name :	T.Kidokoro
		Day	 :	2017/6/30
		Note :  プロジェクトについての説明を記述します
!*/
//////////////////////////////////////////////////////////////////////////////////////////

★Sampleプロジェクトの設定について
	
	基本的にはDxLibを使用する際の設定で行っている。

	プロジェクトオプションの
	プリプロセッサの設定でDebugでのみ有効な __MY_DEBUG__ というものを設定している
	なので、Debug中にのみ行いたい処理を以下のように記述するとReleseでは実行されないようになる

	例1.
	#ifdef __MY_DEBUG__	//__MY_DEBUG__が宣言されているか？　宣言されているとき有効
		void Func(){
			// ~何かしらの処理
		}
	#enif

	例2.

	void Func(){
		
	#ifdef __MY_DEBUG__
		
		//~ここで行わせたい処理

	#endif
		
		//~通常処理


	} 


	上記の例以外にも、プログラム中で記述している場所があると思うので探してみてください。

	今回は、フィルター分けに対応してフォルダーを作成してその中にソースファイルを作っている

	本来であればすこし、まどろっこしい記述方法をしないとインクルードできないソースファイルも出てくるが
	今回は、Codeファイルを追加インクルードファイルとして読み込みしているので

	例えば
	SceneフォルダのTitleフォルダのTitle.hからMyLibのGrahics.hをインクルードしたい場合
	#include "../../MyLib/Graphics.h"と記述しなければならないが
	追加インクルードファイルでCodeファイルを設定しているので
	#include "MyLib/Graphics.h"と記述すれば読み込みを行うことができる

	ちなみに
	｢../｣は人前の階層に戻るという記述です。

	実はDxLibも上記の理由で#include "DxLib.h"と書くだけでインクルードができてしまうのです。


★MyLibフォルダーのソース群について

	DxLibをラッピングしたり楽に多くのデータを設定、取得できるようにしたものです。
	考え方的にはもう少し楽にデータの設定や取得ができるようにする
	メモリの取得と同時にメモリの中を初期化したい
	メモリの開放時にNULLで初期化できるようにしたい
	キーボード入力をもう少し場合分けをして簡単に使用できるようにしたい
	などという考えのもとに機能を実装したものを自分自身のライブラリと言い張っているだけモノ

★フォルダー階層
	Codeフォルダーをコードファイルの頂点として
	機能やシーンといった感じでファイル分けをしています。

	MyLib: DxLibをラッピングしてもう少し楽にデータを取得できるようにしようという考えのもとに
		   実装をした自作ライブラリ(言い張っていたいだけ)
		   ここに機能を実装していくと次回の開発時に流用して楽にゲーム開発ができるようになるかも？

	Common: 汎用的や共通で使用するものや機能を追加していく。
			ここに機能を実装していくと次回の開発時に流用することが可能となる



	Scene:	各シーンごとのファイルやフォルダーを作成していく
			いつものフォルダー


	Test:	テストを行うためのフォルダー
			実装をする前にお試しで機能を構築したり実験を行うためのフォルダー


★蛇足

	プロジェクトのバージョン管理って大変だよね
	トータスSVNを使用すると意外と簡単にバージョンの管理が行えるようになるので興味があれば使用してみるといいかも

