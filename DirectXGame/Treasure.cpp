#include "Treasure.h"
using namespace KamataEngine;

// ==============================
// コンストラクタ / デストラクタ
// ==============================
Treasure::Treasure() {}

Treasure::~Treasure() {
    delete treasureModel_;
}

// ==============================
// 初期化
// ==============================
void Treasure::Initialize(TreasureType type) {
    type_ = type;

    // ワールドトランスフォーム初期化
    worldTransform_.Initialize();

    // モデル読み込み（ここでは cube を使用）
    treasureModel_ = Model::CreateFromOBJ("cube");

    // 宝物の種類に応じて位置とスコアを設定
    switch (type_) {
    case TreasureType::Shallow:
        worldTransform_.translation_ = { static_cast<float>(rand() % 61 - 30), 5.0f, 0.0f };
        score_ = 10;
        break;

    case TreasureType::Middle:
        worldTransform_.translation_ = { static_cast<float>(rand() % 61 - 30), -10.0f, 0.0f };
        score_ = 30;
        break;

    case TreasureType::Deep:
        worldTransform_.translation_ = { static_cast<float>(rand() % 61 - 30), -25.0f, 0.0f };
        score_ = 50;
        break;
    }

    // 衝突判定用サイズ
    size_ = { 2.0f, 2.0f, 2.0f };
}

// ==============================
// 更新
// ==============================
void Treasure::Update() {
    // ワールド行列更新
    worldTransform_.UpdateMatrix();
}

// ==============================
// 描画
// ==============================
void Treasure::Draw(Camera* camera) {
    // 取得済みでない場合のみ描画
    if (!collected_ && camera) {
        treasureModel_->Draw(worldTransform_, *camera);
    }
}