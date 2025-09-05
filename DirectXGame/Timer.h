#pragma once
#include <array>
#include <KamataEngine.h>

class Timer
{
public:
    Timer();
    ~Timer();

    // 初期化
    void Initialize();

    // 更新（deltaTime: 経過時間[秒]）
    void Update(float deltaTime);

    // 描画
    void Draw();

    // 数値をスプライトに反映
    void SetNumber(int number);

    // タイムアップ判定
    bool IsTimeUp() const;

private:
    static const int kDigitCount = 2;

    std::array<KamataEngine::Sprite*, kDigitCount> sprite_{};
    uint32_t textureHandle_ = 0;

    KamataEngine::Vector2 size_ = { 32.0f, 64.0f };

    const float maxTime_ = 30.0f;   // 制限時間 30 秒
    float remainingTime_ = 0.0f;
};