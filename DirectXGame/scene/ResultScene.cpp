#include "ResultScene.h"

using namespace KamataEngine;

// ==============================
// コンストラクタ / デストラクタ
// ==============================
ResultScene::ResultScene() {}

ResultScene::~ResultScene() {
    delete scoreDisplay_;
	delete backgroundSprite_;
	delete resultUISprite_;
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
    scoreDisplay_->SetPosition({ 500.0f, 250.0f });
    scoreDisplay_->SetScale(2.0f);
    scoreDisplay_->SetNumber(finalScore_);

    // ----- 背景スプライト初期化 -----
    backgroundSpriteHandle_ = TextureManager::Load("black1x1.png");
    backgroundSprite_ = Sprite::Create(backgroundSpriteHandle_, { 0.0f, 0.0f });
    backgroundSprite_->SetSize(Vector2(1280, 720));

    // ----- リザルトUIスプライト初期化 -----
	resultUISpriteHandle_ = TextureManager::Load("EnterUI.png");
	resultUISprite_ = Sprite::Create(resultUISpriteHandle_, {0.0f, 0.0f});
	resultUISprite_->SetSize(Vector2(1280, 720));
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

    // 背景描画
    backgroundSprite_->Draw();

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

    // リザルトUI描画
    resultUISprite_->Draw();

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