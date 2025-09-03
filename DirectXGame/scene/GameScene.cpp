#include "GameScene.h"

using namespace KamataEngine;

// コンストラクタ
GameScene::GameScene() {
}

// デストラクタ
GameScene::~GameScene() {
	delete player_;
	delete stage_;
	delete graph_;
	delete score_;

	for (Treasure* treasure : lowTreasures_) {
		delete treasure;
	}
	lowTreasures_.clear();

	for (Treasure* treasure : midlleTreasures_) {
		delete treasure;
	}
	midlleTreasures_.clear();

	for (Treasure* treasure : highTreasures_) {
		delete treasure;
	}
	highTreasures_.clear();
}

void GameScene::Initialize() {
	// DirectXCommonインスタンスの取得
	dxCommon_ = DirectXCommon::GetInstance();
	// Inputインスタンスの取得
	input_ = Input::GetInstance();
	// Audioインスタンスの取得
	audio_ = Audio::GetInstance();

	// カメラの初期化
	camera_.Initialize();

	// プレイヤーの初期化
	player_ = new Player();
	player_->Initialize();

	// ステージの初期化
	stage_ = new Stage();
	stage_->Initialize();

	// グラフの初期化
	graph_ = new Graph2D();
	graph_->Initialize();

	// スコアの初期化
	score_ = new Score();
	score_->Initialize();
	score_->SetNumber(0);

	// 乱数初期化（Initialize() の最初で一度だけ）
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// 低い宝（上側：Y 0～6）
	for (int i = 0; i < 1; i++) {
		Treasure* treasure = new Treasure();
		treasure->Initialize();

		float x = static_cast<float>(rand() % 501 - 250) / 10.0f; // -25 ~ +25
		float y = static_cast<float>(rand() % 7);                  // 0 ~ 6
		float z = 0.0f;

		treasure->SetPosition({ x, y, z });
		lowTreasures_.push_back(treasure);
	}

	// 中くらいの宝（中央：Y 11～17）
	for (int i = 0; i < 2; i++) {
		Treasure* treasure = new Treasure();
		treasure->Initialize();

		float x = static_cast<float>(rand() % 501 - 250) / 10.0f; // -25 ~ +25
		float y = -11.0f + static_cast<float>(rand() % 7);          // 11 ~ 17
		float z = 0.0f;

		treasure->SetPosition({ x, y, z });
		midlleTreasures_.push_back(treasure);
	}

	// 高い宝（下側：Y 22～24）
	for (int i = 0; i < 3; i++) {
		Treasure* treasure = new Treasure();
		treasure->Initialize();

		float x = static_cast<float>(rand() % 501 - 250) / 10.0f; // -25 ~ +25
		float y = -22.0f + static_cast<float>(rand() % 3);          // 22 ~ 24
		float z = 0.0f;

		treasure->SetPosition({ x, y, z });
		highTreasures_.push_back(treasure);
	}

}

void GameScene::Update() {
	if (input_->TriggerKey(DIK_RETURN)) {
		finished_ = true;
	}

	// プレイヤーの更新
	player_->Update();

	// ステージの更新
	stage_->Update();

	// グラフの更新
	graph_->Update();

	// スコアの更新
	static int currentScore = 0;
	score_->SetNumber(currentScore);
	score_->Update();

	// 低い宝の更新
	for (Treasure* treasure : lowTreasures_) {
		treasure->Update();
	}

	// 中くらいの宝の更新
	for (Treasure* treasure : midlleTreasures_) {
		treasure->Update();
	}

	// 高い宝の更新
	for (Treasure* treasure : highTreasures_) {
		treasure->Update();
	}
}

void GameScene::Draw() {
	// DirectXCommon インスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// ステージの描画
	//stage_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dモデル描画
	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	// プレイヤーの描画
	player_->Draw();

	// 低い宝の描画
	for (Treasure* treasure : lowTreasures_) {
		treasure->Draw(&camera_);
	}

	// 中くらいの宝の描画
	for (Treasure* treasure : midlleTreasures_) {
		treasure->Draw(&camera_);
	}

	// 高い宝の描画
	for (Treasure* treasure : highTreasures_) {
		treasure->Draw(&camera_);
	}

	// 3Dモデル描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// グラフの描画
	graph_->Draw();

	// スコアの描画
	score_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}