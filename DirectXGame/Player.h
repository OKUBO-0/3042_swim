#pragma once
#include <KamataEngine.h>

/// ===============================================
/// @class Player
/// @brief プレイヤーの操作、描画、カメラ管理を行うクラス
/// ===============================================
class Player
{
public:
    // コンストラクタ / デストラクタ
    Player();
    ~Player();

    // 初期化
    void Initialize();

    // 更新
    void Update();

    // 描画
    void Draw();

    // 取得系
    KamataEngine::Camera& GetCamera() { return camera_; }                      // カメラ参照取得
    const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; } // ワールド変換取得
    KamataEngine::Vector3 GetSize() const { return size_; }                    // 衝突判定用サイズ取得

private:
    // ==============================
    // エンジン関連
    // ==============================
    KamataEngine::Input* input_ = nullptr;         // 入力管理
    KamataEngine::Model* playerModel_ = nullptr;   // プレイヤーモデル

    // ==============================
    // プレイヤー情報
    // ==============================
    KamataEngine::WorldTransform worldTransform_;  // プレイヤーのワールド変換
    KamataEngine::Camera camera_;                  // プレイヤーカメラ
    float speed_ = 0.2f;                           // 移動速度
    float rotationSpeed_ = 0.1f;                   // 回転速度
    KamataEngine::Vector3 size_ = { 1.0f, 2.0f, 1.0f }; // 衝突判定用サイズ
};