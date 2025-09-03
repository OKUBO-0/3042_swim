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