#include "Timer.h"

using namespace KamataEngine;

// ==============================
// コンストラクタ / デストラクタ
// ==============================
Timer::Timer() {}

Timer::~Timer() {
    // スプライト解放
    for (int i = 0; i < kDigitCount; ++i) {
        delete sprite_[i];
    }
}

// ==============================
// 初期化
// ==============================
void Timer::Initialize() {
    // テクスチャ読み込み
    textureHandle_ = TextureManager::Load("number.png");

    // スプライト生成（横に並べる）
    for (int i = 0; i < kDigitCount; ++i) {
        sprite_[i] = Sprite::Create(textureHandle_, { 608.0f + size_.x * i, 5.0f });
        sprite_[i]->SetSize(size_);
        sprite_[i]->SetTextureRect({ 0.0f, 0.0f }, size_);
    }

    // 残り時間初期化
    remainingTime_ = maxTime_;
}

// ==============================
// 更新
// ==============================
void Timer::Update(float deltaTime) {
    // 残り時間を減少
    if (remainingTime_ > 0.0f) {
        remainingTime_ -= deltaTime;
        if (remainingTime_ < 0.0f) remainingTime_ = 0.0f;
    }

    // スプライトに反映
    SetNumber(static_cast<int>(remainingTime_));
}

// ==============================
// 描画
// ==============================
void Timer::Draw() {
    DirectXCommon* dxCommon = DirectXCommon::GetInstance();
    Sprite::PreDraw(dxCommon->GetCommandList());

    for (int i = 0; i < kDigitCount; ++i) {
        sprite_[i]->Draw();
    }

    Sprite::PostDraw();
}

// ==============================
// 数値をスプライトに反映
// ==============================
void Timer::SetNumber(int number) {
    int digit = 10; // 10の位から
    for (int i = 0; i < kDigitCount; ++i) {
        int nowNumber = number / digit;
        sprite_[i]->SetTextureRect({ size_.x * nowNumber, 0.0f }, size_);
        number %= digit;
        digit /= 10;
    }
}

// ==============================
// タイムアップ判定
// ==============================
bool Timer::IsTimeUp() const {
    return remainingTime_ <= 0.0f;
}