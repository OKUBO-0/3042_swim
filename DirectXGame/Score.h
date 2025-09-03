#pragma once

#include <array>
#include <KamataEngine.h>

class Score
{
public:
	// コンストラクタ
    Score();

    // デストラクタ
    ~Score();

    // 初期化
    void Initialize();

    // 更新
    void Update();

    // 描画
    void Draw();

    // 数値をセット
    void SetNumber(int number);

private:
    // 桁数
    static const int kDigitCount = 5;

    // スプライト
    std::array<KamataEngine::Sprite*, kDigitCount> sprite_{};
    uint32_t textureHandle_ = 0;

    // サイズ
    KamataEngine::Vector2 size_ = { 32.0f, 64.0f };
};