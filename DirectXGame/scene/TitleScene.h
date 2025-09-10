#pragma once
#include "../Fade.h"
#include "IScene.h"
#include <KamataEngine.h>

/// ===============================================
/// @class TitleScene
/// @brief タイトル画面のシーンを管理するクラス
/// ===============================================
class TitleScene : public IScene
{
public:
    // コンストラクタ・デストラクタ
    TitleScene();
    ~TitleScene();

    // 初期化
    void Initialize();

    // 更新
    void Update();

    // 描画
    void Draw();

    // シーン終了判定
    bool IsFinished() const { return finished_; }

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
    // 背景スプライト
    // ==============================
    uint32_t backgroundSpriteHandle_ = 0;
    KamataEngine::Sprite* backgroundSprite_ = nullptr;

    // ==============================
    // タイトルスプライト
    // ==============================
    uint32_t titleSpriteHandle_ = 0;
    KamataEngine::Sprite* titleSprite_ = nullptr;
    float titleAlpha_ = 0.0f;

    // ==============================
    // タイトルUIスプライト
    // ==============================
    uint32_t titleUISpriteHandle_ = 0;
    KamataEngine::Sprite* titleUISprite_ = nullptr;

    // タイトルBGM
    uint32_t titleBGMHandle_ = 0;

    // フェード
    Fade fade_;
    bool fadeOutStarted_ = false;

    // ==============================
    // 終了フラグ
    // ==============================
    bool finished_ = false;
};