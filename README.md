# TopDownRPG
- ゲームエンジン：Unreal Engine 5.6
- 開発IDE：Rider

## Game Overview
本ゲームはUnreal EngineおよびC++で開発しています。主にUnreal EngineのGameplay Ability System（GAS）フレームワークを使用し、俯瞰視点のRPGデモを制作しました。戦闘、経験値、レベルアップ、敵AI、魔法（スキル）、メニュー、セーブ／ロードなどの機能を実装しています。

## Features  
- AAA品質を意識したアーキテクチャ  
	- OOP（継承・責務分離）に基づくキャラクター階層設計  
	- SOLID 原則を意識した、拡張・保守しやすい構成  
	- 「C++ で実装すべき領域」と「Blueprint で表現すべき領域」を実例で整理（約 50% / 50%）  
- GAS コアの実戦導入（マルチプレイを見据えた設計）  
	- カスタム AbilitySystemComponent / AttributeSet  
	- Attribute の複製（Replication）と GAS 各種設定  
	- Gameplay Tags を中心にした「識別可能で拡張しやすい」設計  
- RPGステータス＆属性システム（例）  
	- Primary Attributes：Strength / Intelligence / Resilience / Vigor  
	- Secondary Attributes：Armor / Armor Penetration / Block Chance / Critical 系 / Regeneration / Max Health・Mana など  
	- Vital Attributes：Health / Mana（他属性に依存して変化）  
- ダメージ＆戦闘パイプライン（RPGらしい戦闘）  
	- 複数 DamageType、耐性（Resistance）、デバフ（Debuff）を含む計算  
	- クリティカル、ブロック、ノックバック、スタン、燃焼など  
	- すべての戦闘結果を「視覚的フィードバック」で表示（浮きダメージ文字・色分け等）  
- アビリティ＆スペル（GAS の中心要素）  
	- コスト＆クールダウン（例：Mana 消費）  
	- オフェンス系スペル（例：FireBolt / Electrocute / Arcane Shards / FireBlast）  
	- パッシブスペル（装備中に常時有効）  
	- Ability Task / Async Task など中級テクニックも扱う  
- UI（大規模 RPG を破綻なく作るためのUI設計）  
	- HUD：装備中スペル／クールダウンタイマー／XP・レベル表示  
	- Attribute Menu / Spell Menu：能力ツリー、ロック解除、段階的強化、ポイント消費  
	- MVC / MVVM（UE ViewModel）などの UI パラダイムも紹介  
- 入力割り当て（Spell Menu から自由に差し替え）  
	- 例：FireBolt を「1キー」、Electrocute を「左クリック」へ割り当て、交換も可能  
- 敵AI（Behavior Tree / EQS）  
	- 近接・遠距離・エレメンタル系などタイプ別の行動  
	- 敵がスペルを使用、AIミニオン召喚など  
- トップダウン特有の快適性  
	- 選択アウトライン（敵/アイテムの選択）  
	- カメラ遮蔽物のフェード（視界確保）  
- 経験値＆レベルアップ  
	- 敵撃破で XP 付与、閾値でレベルアップ  
	- レベルアップで Attribute Point / Spell Point を獲得  
	- レベルアップ時に HP/Mana の補充、演出・メッセージ表示  
- セーブ／レベル遷移  
	- 進行状況保存、レベルトランジションに対応
## How To Play
- 左右移動：A／Dキー
- 前後移動：W／Sキー
- 魔法（スキル）：左クリック、右クリック、1、2、3、4キー
- メニューの移動、選択:マウス

## Topics Covered（学習内容）  
- Top-Down プロジェクトのセットアップ（ゼロから）  
- 選択アウトライン（敵・アイテム）  
- GAS の基礎と主要クラス（ASC / AttributeSet / GE / GA / Tags）  
- Attribute 設計（Primary/Secondary/Vital）と複製  
- Gameplay Effects による属性変更・戦闘計算の体系化  
- UI 設計（HUD、属性/スペルメニュー、MVC/MVVM）  
- 役割別クラス（Ranger / Warrior / Elementalist などの拡張可能な実装）  
- ダメージタイプ、耐性、デバフ、ノックバック、スタン、燃焼  
- 敵AI（Behavior Tree / EQS）、召喚  
- コスト＆クールダウン、装備スペル表示  
- 入力割当の付け替え（Spell Menu から）  
- XP＆レベルアップとポイント消費  
- セーブ＆レベル遷移  
- 中〜上級 UE トピック：  
- Async Task / Ability Task、Asset Manager、シングルトンの扱いどころ  
- Custom GameplayEffectContext、Net Serialization、Struct Traits  
- C++ Lambda、ゲームメカニクスのアルゴリズム など
