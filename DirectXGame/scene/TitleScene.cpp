#include "TitleScene.h"

using namespace KamataEngine;

// ==============================
// コンストラクタ / デストラクタ
// ==============================
TitleScene::TitleScene() {}

TitleScene::~TitleScene() {
    delete backgroundSprite_;
    delete titleSprite_;
    delete titleUISprite_;
}

// ==============================
// 初期化
// ==============================
void TitleScene::Initialize() {
    // ----- エンジン関連の取得 -----
    dxCommon_ = DirectXCommon::GetInstance();
    input_ = Input::GetInstance();
    audio_ = Audio::GetInstance();

    // ----- カメラ初期化 -----
    camera_.Initialize();

    // ----- 背景スプライト初期化 -----
    backgroundSpriteHandle_ = TextureManager::Load("black1x1.png");
    backgroundSprite_ = Sprite::Create(backgroundSpriteHandle_, { 0.0f, 0.0f });
    backgroundSprite_->SetSize(Vector2(1280, 720));

    // ----- タイトルスプライト初期化 -----
    titleSpriteHandle_ = TextureManager::Load("title.png");
    titleSprite_ = Sprite::Create(titleSpriteHandle_, { 0.0f, -300.0f });
    titleSprite_->SetSize(Vector2(1280, 720));

    // ----- タイトルUIスプライト初期化 -----
    titleUISpriteHandle_ = TextureManager::Load("EnterUI.png");
    titleUISprite_ = Sprite::Create(titleUISpriteHandle_, { 0.0f, 0.0f });
    titleUISprite_->SetSize(Vector2(1280, 720));
    titleUISprite_->SetColor({ 1, 1, 1, 0 }); // 初期透明
}

// ==============================
// 更新
// ==============================
void TitleScene::Update() {
    // ----- Enterキーでシーン終了 -----
    if (input_->TriggerKey(DIK_RETURN)) {
        finished_ = true;
    }

    // ----- タイトルスプライトの演出 -----
    Vector2 pos = titleSprite_->GetPosition();

    if (pos.y < 0.0f) {
        // 上から降りてくるアニメーション
        pos.y += 3.0f;
        if (pos.y > 0.0f) pos.y = 0.0f;
        titleSprite_->SetPosition(pos);
    }
    else {
        // Enter点滅演出
        static float timer = 0.0f;
        timer += 0.02f;  // 点滅速度

        float alpha = 0.5f + 0.5f * sinf(timer * 3.1415f * 2.0f);
        titleUISprite_->SetColor({ 1.0f, 1.0f, 1.0f, alpha });
    }
}

// ==============================
// 描画
// ==============================
void TitleScene::Draw() {
    DirectXCommon* dxCommon = DirectXCommon::GetInstance();

#pragma region 背景スプライト描画
    Sprite::PreDraw(dxCommon->GetCommandList());
    backgroundSprite_->Draw();
    Sprite::PostDraw();

    dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dモデル描画
    Model::PreDraw(dxCommon->GetCommandList());
    Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
    Sprite::PreDraw(dxCommon->GetCommandList());
    titleSprite_->Draw();
    titleUISprite_->Draw();
    Sprite::PostDraw();
#pragma endregion
}