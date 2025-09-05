#include "ResultScene.h"

using namespace KamataEngine;

// ==============================
// コンストラクタ / デストラクタ
// ==============================
ResultScene::ResultScene() {}

ResultScene::~ResultScene() {
    delete scoreDisplay_;
}

// ==============================
// 初期化
// ==============================
void ResultScene::Initialize() {
    // ----- エンジン関連の取得 -----
    dxCommon_ = DirectXCommon::GetInstance();
    input_ = Input::GetInstance();
    audio_ = Audio::GetInstance();

    // ----- カメラ初期化 -----
    camera_.Initialize();

    // ----- スコア表示初期化 -----
    scoreDisplay_ = new Score();
    scoreDisplay_->Initialize();
    scoreDisplay_->SetNumber(finalScore_);
}

// ==============================
// 更新
// ==============================
void ResultScene::Update() {
    // ----- Enterキーでシーン終了 -----
    if (input_->TriggerKey(DIK_RETURN)) {
        finished_ = true;
    }

    // ----- スコア表示更新 -----
    if (scoreDisplay_) {
        scoreDisplay_->SetNumber(finalScore_);
    }
}

// ==============================
// 描画
// ==============================
void ResultScene::Draw() {
    DirectXCommon* dxCommon = DirectXCommon::GetInstance();

#pragma region 背景スプライト描画
    Sprite::PreDraw(dxCommon->GetCommandList());
    // 背景スプライトは必要ならここに追加
    Sprite::PostDraw();

    dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dモデル描画
    Model::PreDraw(dxCommon->GetCommandList());
    // 3Dモデル描画は必要ならここに追加
    Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
    Sprite::PreDraw(dxCommon->GetCommandList());

    // スコア描画
    if (scoreDisplay_) scoreDisplay_->Draw();

    Sprite::PostDraw();
#pragma endregion
}

// ==============================
// スコア設定
// ==============================
void ResultScene::SetScore(int score) {
    finalScore_ = score;
    if (scoreDisplay_) scoreDisplay_->SetNumber(finalScore_);
}