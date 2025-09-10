#pragma once
#include <KamataEngine.h>

/// ===============================================
/// @class OxygenGauge
/// @brief プレイヤーの酸素量を管理するゲージクラス
/// ===============================================
class OxygenGauge {
public:
    // コンストラクタ・デストラクタ
    OxygenGauge();
    ~OxygenGauge();

    // 初期化
    void Initialize();

    // 更新
    void Update(float playerY, float deltaTime);

    // 描画
    void Draw();

    // 酸素チェック
    bool IsEmpty() const { return currentOxygen_ <= 0.0f; }

    // 酸素を満タンに戻す
    void Refill() { currentOxygen_ = maxOxygen_; }

private:
    // ==============================
    // スプライト
    // ==============================
    uint32_t dummyTextureHandle_ = 0;             // 1x1白テクスチャ
    KamataEngine::Sprite* background_ = nullptr;  // 赤バー（背景）
    KamataEngine::Sprite* fill_ = nullptr;        // 青バー（酸素残量）

    // ==============================
    // 表示位置とサイズ
    // ==============================
    KamataEngine::Vector2 position_ = { 300.0f, 25.0f };
    KamataEngine::Vector2 size_ = { 200.0f, 30.0f };

    // ==============================
    // 酸素量
    // ==============================
    float maxOxygen_ = 100.0f;       // 最大酸素量
    float currentOxygen_ = 100.0f;   // 現在の酸素量

    // ==============================
    // 酸素変化速度
    // ==============================
    float decreaseSpeed_ = 10.0f;    // 水中での1秒あたり減少量
    float recoverySpeed_ = 20.0f;    // 水上での1秒あたり回復量
};