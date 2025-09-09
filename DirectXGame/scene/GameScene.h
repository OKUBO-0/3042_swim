#pragma once

#include "../Player.h"
#include "../TreasureManager.h"
#include "../Stage.h"
#include "../Score.h"
#include "../Timer.h"
#include "../OxygenGauge.h"

#include "IScene.h"
#include <KamataEngine.h>

/// ===============================================
/// @class GameScene
/// @brief ゲームプレイ中のシーンを管理するクラス
/// ===============================================
class GameScene : public IScene {
public:
    // コンストラクタ / デストラクタ
    GameScene();
    ~GameScene();

    // 初期化
    void Initialize();

    // 更新
    void Update();

    // 描画
    void Draw();

    // シーン終了判定
    bool IsFinished() const { return finished_; }

    // スコア取得
    int GetScore() const { return currentScore_; }

    // タイトルへ戻るフラグ
    bool returnToTitle_ = false;

private:
    // ==============================
    // エンジン関連
    // ==============================
    KamataEngine::DirectXCommon* dxCommon_ = nullptr; // DirectX共通管理
    KamataEngine::Input* input_ = nullptr;            // 入力管理
    KamataEngine::Audio* audio_ = nullptr;            // サウンド管理

    // ==============================
    // カメラ
    // ==============================
    KamataEngine::Camera camera_;                     // プレイヤー追従カメラ

    // ==============================
    // ゲーム要素
    // ==============================
    Player* player_ = nullptr;                        // プレイヤー
    TreasureManager* treasureManager_ = nullptr;      // 宝物管理
    Stage* stage_ = nullptr;                          // ステージ
    Score* score_ = nullptr;                          // スコア表示
    Timer* timer_ = nullptr;                          // 制限時間タイマー
    OxygenGauge* oxygenGauge_ = nullptr;              // 酸素ゲージ

    int previousScore_ = 0;

    // ==============================
    // オーディオ
    // ==============================
    uint32_t scoreSEHandle_ = 0; // 宝物取得時のSE

    // ==============================
    // スコア・状態管理
    // ==============================
    int currentScore_ = 0;                            // 現在のスコア
    bool finished_ = false;                           // シーン終了フラグ
};