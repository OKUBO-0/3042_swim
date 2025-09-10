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

    // 宝物の種類に応じて位置とスコアを設定
    switch (type_) {
    case TreasureType::Shallow:
        treasureModel_ = Model::CreateFromOBJ("bottle");
        worldTransform_.translation_ = {
            static_cast<float>(rand() % 61 - 30),      // X: -30 ~ 30
            static_cast<float>(-(rand() % 16)),        // Y: 0 ~ -20
            0.0f
        };
        score_ = 10;
        break;

    case TreasureType::Middle:
        treasureModel_ = Model::CreateFromOBJ("coin");
        worldTransform_.translation_ = {
           static_cast<float>(rand() % 61 - 30),          // X: -30 ~ 30
           static_cast<float>(-(rand() % 16 + 25)),       // Y: -25 ~ -40
           0.0f
        };
        score_ = 30;
        break;

    case TreasureType::Deep:
        treasureModel_ = Model::CreateFromOBJ("chest");
        worldTransform_.translation_ = { static_cast<float>(rand() % 61 - 30), -50.0f, 0.0f };
        score_ = 100;
        break;
    }

    // 衝突判定用サイズ
    size_ = { 2.0f, 2.0f, 2.0f };
}

// ==============================
// 更新
// ==============================
void Treasure::Update() {
    // Middle（中層）の宝物だけ回転
    if (type_ == TreasureType::Middle) {
        worldTransform_.rotation_.y += 0.05f;
    }

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