#pragma once
#include "Treasure.h"
#include "Player.h"
#include <vector>
#include <KamataEngine.h>

/// ===============================================
/// @class TreasureManager
/// @brief 宝物を管理するクラス（生成・更新・描画・衝突判定）
/// ===============================================
class TreasureManager
{
public:
    // ==============================
    // コンストラクタ / デストラクタ
    // ==============================
    TreasureManager();
    ~TreasureManager();

    // ==============================
    // 初期化・更新・描画
    // ==============================
    void Initialize();                   // 宝物の生成と初期化
    void Update();                       // 各宝物の更新
    void Draw(KamataEngine::Camera* cam);// 描画（カメラ参照が必要）

    // ==============================
    // 衝突判定
    // ==============================
    void CheckCollision(const Player* player); // Player との AABB 判定

    // ==============================
    // スコア管理
    // ==============================
    int GetPendingScore() const { return pendingScore_; } // 未取得スコア取得
    void ClearPendingScore() { pendingScore_ = 0; }       // 未取得スコアクリア

private:
    std::vector<Treasure*> treasures_;   // 宝物リスト
    int pendingScore_ = 0;               // プレイヤーが取得した未反映スコア
};