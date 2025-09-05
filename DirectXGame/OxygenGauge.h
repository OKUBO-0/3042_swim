#pragma once
#include <KamataEngine.h>

class OxygenGauge {
public:
    OxygenGauge();
    ~OxygenGauge();

    // 初期化
    void Initialize();

    // 更新
    // playerY : プレイヤーのy座標（水面を0とした例）
    // deltaTime : フレーム時間（秒）
    void Update(float playerY, float deltaTime);

    // 描画
    void Draw();

    // 酸素が切れたか
    bool IsEmpty() const { return currentOxygen_ <= 0.0f; }

    // 酸素を満タンに戻す
    void Refill() { currentOxygen_ = maxOxygen_; }

private:
    uint32_t dummyTextureHandle_ = 0;

    KamataEngine::Sprite* background_ = nullptr;  // 赤バー（背景）
    KamataEngine::Sprite* fill_ = nullptr;        // 青バー（酸素）

    KamataEngine::Vector2 position_ = { 300.0f, 50.0f };
    KamataEngine::Vector2 size_ = { 200.0f, 20.0f };

    float maxOxygen_ = 100.0f;
    float currentOxygen_ = 100.0f;

    float decreaseSpeed_ = 20.0f; // 1秒あたり減少量
    float recoverySpeed_ = 10.0f; // 1秒あたり回復量
};