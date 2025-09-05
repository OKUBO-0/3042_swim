#pragma once
#include <KamataEngine.h>

class Player
{
public:
    // コンストラクタ・デストラクタ
    Player();
    ~Player();

    // 初期化
    void Initialize();

    // 更新
    void Update();

    // 描画
    void Draw();

    // カメラ参照を取得
    KamataEngine::Camera& GetCamera() { return camera_; }

    // ワールドトランスフォーム参照を取得
    const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }

    // 衝突判定用のサイズを取得
    KamataEngine::Vector3 GetSize() const { return size_; }

private:
    // -----------------------------
    // メンバ変数
    // -----------------------------

    // 入力インスタンス
    KamataEngine::Input* input_ = nullptr;

    // プレイヤーワールド変換
    KamataEngine::WorldTransform worldTransform_;

    // カメラ
    KamataEngine::Camera camera_;

    // プレイヤーモデル
    KamataEngine::Model* playerModel_ = nullptr;

    // 移動速度
    float speed_ = 0.3f;

    // 回転速度
	float rotationSpeed_ = 0.1f;

    // 衝突判定用のサイズ
    KamataEngine::Vector3 size_ = { 1.0f, 2.0f, 1.0f };
};