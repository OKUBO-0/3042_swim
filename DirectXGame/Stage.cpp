#include "Stage.h"

using namespace KamataEngine;

Stage::Stage() {
}

Stage::~Stage() {
	
}

void Stage::Initialize() {
	
	// モデル読みこっみ
	BGModel = Model::CreateFromOBJ("seaBG");
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}

void Stage::Update(float playerY) {
	float scrollRatio = 0.5f; // 背景の動きはプレイヤーの半分
	worldTransform_.translation_.y = playerY * scrollRatio;
}

void Stage::Draw(const KamataEngine::Camera& camera) {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Model::PreDraw(dxCommon->GetCommandList());

	BGModel->Draw(worldTransform_, camera);
	
	Model::PostDraw();
}
