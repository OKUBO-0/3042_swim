#include "Timer.h"

using namespace KamataEngine;

Timer::Timer() {}

Timer::~Timer() {
    for (int i = 0; i < kDigitCount; ++i) {
        delete sprite_[i];
    }
}

void Timer::Initialize() {
    // テクスチャ読み込み
    textureHandle_ = TextureManager::Load("number.png");

    // スプライト生成
    for (int i = 0; i < kDigitCount; ++i) {
        sprite_[i] = Sprite::Create(textureHandle_, { 640.0f + size_.x * i, 5.0f });
        sprite_[i]->SetSize(size_);
        sprite_[i]->SetTextureRect({ 0.0f, 0.0f }, size_);
    }

    remainingTime_ = maxTime_;
}

void Timer::Update(float deltaTime) {
    if (remainingTime_ > 0.0f) {
        remainingTime_ -= deltaTime;
        if (remainingTime_ < 0.0f) remainingTime_ = 0.0f;
    }
    SetNumber(static_cast<int>(remainingTime_));
}

void Timer::Draw() {
    DirectXCommon* dxCommon = DirectXCommon::GetInstance();
    Sprite::PreDraw(dxCommon->GetCommandList());

    for (int i = 0; i < kDigitCount; ++i) {
        sprite_[i]->Draw();
    }

    Sprite::PostDraw();
}

void Timer::SetNumber(int number) {
    int digit = 10;
    for (int i = 0; i < kDigitCount; ++i) {
        int nowNumber = number / digit;
        sprite_[i]->SetTextureRect({ size_.x * nowNumber, 0.0f }, size_);
        number %= digit;
        digit /= 10;
    }
}

bool Timer::IsTimeUp() const {
    return remainingTime_ <= 0.0f;
}