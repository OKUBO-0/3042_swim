#include "GameScene.h"

using namespace KamataEngine;

// ==============================
// コンストラクタ / デストラクタ
// ==============================
GameScene::GameScene() {}

GameScene::~GameScene() {
    delete player_;
    delete treasureManager_;
    delete stage_;
    delete score_;
    delete timer_;
    delete oxygenGauge_;
}

// ==============================
// 初期化
// ==============================
void GameScene::Initialize() {
    // ----- エンジン関連の初期化 -----
    dxCommon_ = DirectXCommon::GetInstance();
    input_ = Input::GetInstance();
    audio_ = Audio::GetInstance();

    // ----- オーディオ -----
    scoreSEHandle_ = audio_->LoadWave("Sounds/score_se.wav"); // SEファイル名

    // ----- カメラ初期化 -----
    camera_.Initialize();

    // ----- プレイヤー初期化 -----
    player_ = new Player();
    player_->Initialize();

    // ----- 宝管理初期化 -----
    treasureManager_ = new TreasureManager();
    treasureManager_->Initialize();

    // ----- ステージ初期化 -----
    stage_ = new Stage();
    stage_->Initialize();

    // ----- スコア初期化 -----
    score_ = new Score();
    score_->Initialize();
    currentScore_ = 0;
    score_->SetNumber(currentScore_);

    // ----- タイマー初期化 -----
    timer_ = new Timer();
    timer_->Initialize();

    // ----- 酸素ゲージ初期化 -----
    oxygenGauge_ = new OxygenGauge();
    oxygenGauge_->Initialize();
}

// ==============================
// 更新処理
// ==============================
void GameScene::Update() {
    // ----- プレイヤー更新 -----
    player_->Update();

    // ----- ステージ更新 -----
    stage_->Update(player_->GetPosition().y);

    // ----- 宝物の更新 & 当たり判定 -----
    treasureManager_->Update();
    treasureManager_->CheckCollision(player_);

    // ----- 宝物を取得したらスコア加算 -----
    if (player_->GetWorldTransform().translation_.y >= 10.0f) {
        int pending = treasureManager_->GetPendingScore();
        if (pending > 0) {
            currentScore_ += pending;
            treasureManager_->ClearPendingScore();

            // 前回スコアと比較して増えたらSE再生
            if (currentScore_ > previousScore_) {
                audio_->PlayWave(scoreSEHandle_);
            }

            previousScore_ = currentScore_; // スコア更新
        }
    }

    // ----- スコア更新 -----
    score_->SetNumber(currentScore_);
    score_->Update();

    // ----- タイマー更新 -----
    float deltaTime = 1.0f / 60.0f; // 仮に60FPS固定
    timer_->Update(deltaTime);

    // ----- 酸素ゲージ更新 -----
    oxygenGauge_->Update(player_->GetWorldTransform().translation_.y, deltaTime);

    // ----- ゲーム終了判定 -----
    if (timer_->IsTimeUp()) {
        finished_ = true;  // 制限時間切れ
    }

    if (oxygenGauge_->IsEmpty()) {
        finished_ = true;  // 酸素切れ
    }

    // ----- ESCキーでタイトルに戻る -----
    if (input_->TriggerKey(DIK_ESCAPE)) {
        returnToTitle_ = true;
        finished_ = true;
    }
}

// ==============================
// 描画処理
// ==============================
void GameScene::Draw() {
    // DirectXCommonインスタンス取得
    DirectXCommon* dxCommon = DirectXCommon::GetInstance();

    // ----- 背景スプライト描画 -----
#pragma region 背景スプライト描画
    Sprite::PreDraw(dxCommon->GetCommandList());
   

    Sprite::PostDraw();

    // 深度バッファクリア
    dxCommon_->ClearDepthBuffer();
#pragma endregion

    // ----- 3Dモデル描画 -----
#pragma region 3Dモデル描画
    Model::PreDraw(dxCommon->GetCommandList());
    player_->Draw();
    treasureManager_->Draw(&player_->GetCamera());

    stage_->Draw(player_->GetCamera());
    Model::PostDraw();
#pragma endregion

    // ----- 前景スプライト描画 -----
#pragma region 前景スプライト描画
    Sprite::PreDraw(dxCommon->GetCommandList());

    // 酸素ゲージ描画
    oxygenGauge_->Draw();

    // スコア描画
    score_->Draw();

    // タイマー描画
    timer_->Draw();

    Sprite::PostDraw();
#pragma endregion
}