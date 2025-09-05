#include "Score.h"

using namespace KamataEngine;

// ==============================================
// コンストラクタ / デストラクタ
// ==============================================
Score::Score() {}

Score::~Score() {
    // スプライトの解放
    for (int i = 0; i < kDigitCount; ++i) {
        delete sprite_[i];
    }
}

// ==============================================
// 初期化
// ==============================================
void Score::Initialize() {
    // テクスチャの読み込み
    textureHandle_ = TextureManager::Load("number.png");

    // スプライトの生成（横に並べる）
    for (int i = 0; i < kDigitCount; ++i) {
        sprite_[i] = Sprite::Create(textureHandle_, { 800.0f + size_.x * i, 5.0f });
        sprite_[i]->SetSize(size_);
        sprite_[i]->SetTextureRect({ 0.0f, 0.0f }, size_);
    }
}

// ==============================================
// 更新
// ==============================================
void Score::Update() {
    // 今は特に更新処理なし
}

// ==============================================
// 描画
// ==============================================
void Score::Draw() {
    DirectXCommon* dxCommon = DirectXCommon::GetInstance();

    // スプライト描画前処理
    Sprite::PreDraw(dxCommon->GetCommandList());

    // 各桁の描画
    for (int i = 0; i < kDigitCount; ++i) {
        sprite_[i]->Draw();
    }

    // 描画後処理
    Sprite::PostDraw();
}

// ==============================================
// 数値設定
// ==============================================
void Score::SetNumber(int number) {
    int32_t digit = 10000; // 5桁分の割る値

    for (int i = 0; i < kDigitCount; ++i) {
        int nowNumber = number / digit;
        sprite_[i]->SetTextureRect({ size_.x * nowNumber, 0.0f }, size_);
        number %= digit;
        digit /= 10;
    }
}