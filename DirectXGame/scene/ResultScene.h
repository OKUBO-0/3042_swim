#pragma once

#include "../Score.h"
#include "IScene.h"
#include <KamataEngine.h>

/// ===============================================
/// @class ResultScene
/// @brief ゲーム終了後のリザルト画面を管理するシーン
/// ===============================================
class ResultScene : public IScene
{
public:
    // コンストラクタ・デストラクタ
    ResultScene();
    ~ResultScene();

    // 初期化
    void Initialize();

    // 更新
    void Update();

    // 描画
    void Draw();

    // シーン終了判定
    bool IsFinished() const { return finished_; }

    // スコアを設定
    void SetScore(int score);

private:
    // ==============================
    // エンジン関連
    // ==============================
    KamataEngine::DirectXCommon* dxCommon_ = nullptr;
    KamataEngine::Input* input_ = nullptr;
    KamataEngine::Audio* audio_ = nullptr;

    // ==============================
    // カメラ
    // ==============================
    KamataEngine::Camera camera_;

    // ==============================
    // スコア表示
    // ==============================
    Score* scoreDisplay_ = nullptr;  // 表示用スコア
    int finalScore_ = 0;             // 最終スコア

    // ==============================
   // 背景スプライト
   // ==============================
    uint32_t backgroundSpriteHandle_ = 0;
    KamataEngine::Sprite* backgroundSprite_ = nullptr;

    // ==============================
    // UIスプライト
    // ==============================
    uint32_t resultUISpriteHandle_ = 0;
    KamataEngine::Sprite* resultUISprite_ = nullptr;

    // ==============================
    // シーン状態
    // ==============================
    bool finished_ = false;          // 終了フラグ
};