#include "Treasure.h"

using namespace KamataEngine;

// コンストラクタ
Treasure::Treasure() {
}

// デストラクタ
Treasure::~Treasure() {
	delete treasureModel_;
}

// 初期化
void Treasure::Initialize() {
	// プレイヤーモデルの読み込み
	treasureModel_ = Model::CreateFromOBJ("cube");

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 10.0f, 00.0f, 0.0f };
}

// 更新
void Treasure::Update() {
	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Treasure::Draw(KamataEngine::Camera* camera) {
	if (camera) {
		treasureModel_->Draw(worldTransform_, *camera);
	}
}