#include "ResultScene.h"

using namespace KamataEngine;

// コンストラクタ
ResultScene::ResultScene() {
}

// デストラクタ
ResultScene::~ResultScene() {
}

void ResultScene::Initialize() {
	// DirectXCommonインスタンスの取得
	dxCommon_ = DirectXCommon::GetInstance();
	// Inputインスタンスの取得
	input_ = Input::GetInstance();
	// Audioインスタンスの取得
	audio_ = Audio::GetInstance();

	// カメラ
	camera_.Initialize();
}

void ResultScene::Update() {
	if (input_->TriggerKey(DIK_RETURN)) {
		finished_ = true;
	}
}

void ResultScene::Draw() {
	// DirectXCommon インスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// スプライト描画後処理
	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dモデル描画
	// 3Dモデル描画前処理
	Model::PreDraw(dxCommon->GetCommandList());

	// 3Dモデル描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}