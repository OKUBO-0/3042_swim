#include "OxygenGauge.h"

using namespace KamataEngine;

OxygenGauge::OxygenGauge() {}

OxygenGauge::~OxygenGauge() {
    delete background_;
    delete fill_;
}

void OxygenGauge::Initialize() {
    dummyTextureHandle_ = TextureManager::Load("white1x1.png");

    // 背景バー（赤）
    background_ = Sprite::Create(dummyTextureHandle_, position_);
    background_->SetSize(size_);
    background_->SetColor({ 1.0f, 0.0f, 0.0f, 0.5f });

    // 満タンバー（青）
    fill_ = Sprite::Create(dummyTextureHandle_, position_);
    fill_->SetSize(size_);
    fill_->SetColor({ 0.0f, 0.0f, 1.0f, 0.8f });
}

void OxygenGauge::Update(float playerY, float deltaTime) {
    bool inWater = playerY < 9.0f; // 水中判定

    if (inWater) {
        // 酸素減少
        currentOxygen_ -= decreaseSpeed_ * deltaTime;
        if (currentOxygen_ < 0.0f) currentOxygen_ = 0.0f;
    }
    else {
        // 水上で徐々に回復
        currentOxygen_ += recoverySpeed_ * deltaTime;
        if (currentOxygen_ > maxOxygen_) currentOxygen_ = maxOxygen_;
    }

    // fill の幅を酸素残量に応じて更新
    float fillWidth = size_.x * (currentOxygen_ / maxOxygen_);
    fill_->SetSize({ fillWidth, size_.y });
    fill_->SetPosition(position_); // 左端固定
}

void OxygenGauge::Draw() {
    DirectXCommon* dxCommon = DirectXCommon::GetInstance();
    Sprite::PreDraw(dxCommon->GetCommandList());

    background_->Draw();
    fill_->Draw();

    Sprite::PostDraw();
}