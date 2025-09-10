#pragma once
#include <KamataEngine.h>

/// <summary>
/// 宝物の種類
/// </summary>
enum class TreasureType {
    Shallow,  // 浅瀬
    Middle,   // 中層
    Deep      // 深層
};

/// <summary>
/// 宝物クラス
/// </summary>
class Treasure
{
public:
    // ==============================
    // コンストラクタ / デストラクタ
    // ==============================
    Treasure();
    ~Treasure();

    // ==============================
    // 初期化・更新・描画
    // ==============================
    void Initialize(TreasureType type);          // 初期化
    void Update();                               // 更新
    void Draw(KamataEngine::Camera* camera);     // 描画

    // ==============================
    // 状態管理
    // ==============================
    void Collect() { collected_ = true; }           // 取得
    bool IsCollected() const { return collected_; } // 取得済み判定
    int GetScore() const { return score_; }         // スコア取得
    TreasureType GetType() const { return type_; }

    // ==============================
    // 衝突判定用
    // ==============================
    const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }
    KamataEngine::Vector3 GetSize() const { return size_; }

private:
    // ==============================
    // メンバ変数
    // ==============================
    TreasureType type_;                    // 宝物タイプ
    int score_ = 0;                        // 獲得スコア
    bool collected_ = false;               // 取得済みか
    KamataEngine::WorldTransform worldTransform_; // ワールド変換
    KamataEngine::Model* treasureModel_ = nullptr; // モデル
    KamataEngine::Vector3 size_ = { 1.0f, 1.0f, 1.0f }; // 衝突判定用サイズ
};