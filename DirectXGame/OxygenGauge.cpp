#include "OxygenGauge.h"

using namespace KamataEngine;

// ==============================
// コンストラクタ / デストラクタ
// ==============================
OxygenGauge::OxygenGauge() {}

OxygenGauge::~OxygenGauge() {
    delete background_;
    delete fill_;
}

// ==============================
// 初期化
// ==============================
void OxygenGauge::Initialize() {
    // 1x1ピクセルの白テクスチャを読み込む
    dummyTextureHandle_ = TextureManager::Load("white1x1.png");

    // ----- 背景バー（赤） -----
    background_ = Sprite::Create(dummyTextureHandle_, position_);
    background_->SetSize(size_);
    background_->SetColor({ 1.0f, 0.0f, 0.0f, 0.5f });

    // ----- 満タンバー（青） -----
    fill_ = Sprite::Create(dummyTextureHandle_, position_);
    fill_->SetSize(size_);
    fill_->SetColor({ 0.0f, 0.0f, 1.0f, 0.8f });
}

// ==============================
// 更新
// ==============================
void OxygenGauge::Update(float playerY, float deltaTime) {
    // ----- 水中か判定（Y座標が水面より下なら水中） -----
    bool inWater = playerY < 9.0f;

    if (inWater) {
        // ----- 酸素減少 -----
        currentOxygen_ -= decreaseSpeed_ * deltaTime;
        if (currentOxygen_ < 0.0f) currentOxygen_ = 0.0f;
    }
    else {
        // ----- 水上で徐々に回復 -----
        currentOxygen_ += recoverySpeed_ * deltaTime;
        if (currentOxygen_ > maxOxygen_) currentOxygen_ = maxOxygen_;
    }

    // ----- fill の幅を酸素残量に応じて更新 -----
    float fillWidth = size_.x * (currentOxygen_ / maxOxygen_);
    fill_->SetSize({ fillWidth, size_.y });

    // 左端を固定
    fill_->SetPosition(position_);
}

// ==============================
// 描画
// ==============================
void OxygenGauge::Draw() {
    DirectXCommon* dxCommon = DirectXCommon::GetInstance();

    // 前景スプライト描画前処理
    Sprite::PreDraw(dxCommon->GetCommandList());

    // 背景バー・満タンバー描画
    background_->Draw();
    fill_->Draw();

    // 描画後処理
    Sprite::PostDraw();
}