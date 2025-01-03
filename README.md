# FruitBasket
![](https://github.com/RyoyaMaejima/Fruit_Basket/blob/main/ReadmeSrc/Title.png)

## ゲーム概要
- フルーツを集めてフルーツジュースを作る3Dアクションゲーム
- プレイヤーはカゴを操作してフルーツを集め、ゴール地点にあるミキサーに入れればゲームクリア
- 制限時間を過ぎればゲームオーバー

![](https://github.com/RyoyaMaejima/Fruit_Basket/blob/main/ReadmeSrc/Ingame.png)

## 操作方法
![](https://github.com/RyoyaMaejima/Fruit_Basket/blob/main/ReadmeSrc/HowToPlay.png)

## プレイ動画
プレイ動画は下記リンクに記載しています  

https://youtu.be/C1QsEMtxZb0

## 実行ファイル
実行ファイルは下記リンクに記載しています  

https://drive.google.com/drive/folders/1w85yyZqWshpuGu3eDkSRUPvhT6seJpP5?usp=sharing

## 開発目的
- Unreal Engineを用いた開発を経験するため
- チーム開発の困難を経験するため

## 開発環境・体制
- 人数：３人
- 役割：プレイヤー、ステージ（自分）、UI
- 期間：３ヶ月
- 使用ツール：Unreal Engine 5

## ディレクトリ構成
Source内にソースコード一式を載せています  
Source/FruitBasket/Stage内に私が作成したコードが入っています  
以下が各ファイルの説明

- Dog：犬の挙動を管理するスクリプト
- Fire：焚火の挙動を管理するスクリプト
- Fruit：フルーツの挙動を管理するスクリプト
- FruitManager：フルーツの初期配置やプレイヤーが獲得したかなどを管理するスクリプト
- Goal：ゴールに到着した際の挙動を管理するスクリプト
- Human：人の挙動を管理するスクリプト
- Item：フルーツや薪などのプレイヤーが獲得できるアイテムの基底クラス
- Leaf：葉っぱの挙動を管理するスクリプト
- MyActor：全てのアクターの基底クラス
- Tree：木から葉っぱが舞う処理を行うスクリプト
- Wind：風の挙動を管理するスクリプト
- Wood：薪の挙動を管理するスクリプト

## こだわった点
- カゴが揺れるとフルーツが飛び出すゲーム性の追加
- 犬がフルーツを咥えて持っていくギミックの導入
- 風が吹くとフルーツが飛ばされる仕掛けの追加
- 視覚的な演出の追加
  - フルーツがカゴから出るとフルーツが点滅
  - 風が吹くと木から葉っぱが舞う
