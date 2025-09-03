#include "scene/SceneManager.h"
#include "scene/TitleScene.h"
#include "scene/GameScene.h"

#include <KamataEngine.h>
#include <Windows.h>

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	Initialize(L"3042_swim");

	// DirectXCommonのインスタンスを取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	SceneManager sceneManager;

	// シーン登録
	sceneManager.RegisterScene(SceneName::Title, []() { return std::make_unique<TitleScene>(); });
	sceneManager.RegisterScene(SceneName::Game, []() { return std::make_unique<GameScene>(); });

	// 初期シーンをタイトルに設定
	sceneManager.ChangeScene(SceneName::Title);

	// メインループ
	while (true) {
		// エンジンの更新
		if (Update()) {
			break;
		}

		// シーン更新
		sceneManager.Update();

		// 描画開始
		dxCommon->PreDraw();

		// シーンの描画
		sceneManager.Draw();

		// 描画終了
		dxCommon->PostDraw();
	}

	// エンジンの終了処理
	Finalize();

	return 0;
}
//テーマ「境界」
//水上と水中をの間の水面を境界線として解釈
//
//ゲーム内容
//水中にあるお宝を集めてポイントを稼ぐ縦スクロールゲーム
//
//プレイヤーの操作
//S : 潜行
//A : 左移動
//D : 右移動
//W : 浮上
//
//酸素ゲージ
//水中にいる間徐々に減る
//水上に浮上すると回復
//途中でなくなるとその時点のスコアで終了
//
//実装内容
//・酸素ゲージ
//本ゲームのレベルデザインの1つ
//酸素の減る量で水中にいられる時間を縛る
//
//・スコアシステム
//獲ったお宝は水上に浮上するとスコアに加算
//水深によってお宝のスコア量の変動
//
//本ゲームの売り
//深く潜らないとたどり着けない場所がある
//そこにあるのは高スコアのお宝
//
//酸素ゲージを意識しながら
//浅いところでコツコツスコアを稼ぐか
//深いところに行きハイリスクハイリターンを目指すか