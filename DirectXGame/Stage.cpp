#include "Stage.h"

using namespace KamataEngine;

Stage::Stage() {
}

Stage::~Stage() { delete stageModel_; }

void Stage::Initialize() {
	// ステージモデル読み込み
	stageModel_ = Model::CreateFromOBJ("stage");
	// ワールドトランスフォーム初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f}; // 初期位置
}

void Stage::Update() { worldTransform_.UpdateMatrix(); }

void Stage::Draw(Camera* camera) {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
#pragma region 3Dモデル描画
	Model::PreDraw(dxCommon->GetCommandList());

	stageModel_->Draw(worldTransform_, *camera);

	Model::PostDraw();
#pragma endregion
}
