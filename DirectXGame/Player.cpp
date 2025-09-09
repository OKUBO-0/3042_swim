#include "Player.h"
using namespace KamataEngine;

// ==============================
// コンストラクタ / デストラクタ
// ==============================
Player::Player() {}

Player::~Player() {
    delete playerModel_;
}

// ==============================
// 初期化
// ==============================
void Player::Initialize() {
    // 入力インスタンス取得
    input_ = Input::GetInstance();

    // カメラ初期化
    camera_.Initialize();

    // プレイヤーモデル読み込み
    playerModel_ = Model::CreateFromOBJ("whale");

    // ワールドトランスフォーム初期化
    worldTransform_.Initialize();
    worldTransform_.translation_ = { 0.0f, 10.0f, 0.0f }; // 初期位置（Y=10）

    // 回転初期化
    worldTransform_.rotation_ = { 0.0f, 0.0f, 0.0f };

    // 衝突判定用サイズ
    size_ = { 1.0f, 2.0f, 1.0f };
}

// ==============================
// 更新
// ==============================
void Player::Update() {
    // -----------------------------
    // 移動処理
    // -----------------------------
    if (input_->PushKey(DIK_W)) {
        worldTransform_.translation_.y += speed_;
        if (worldTransform_.translation_.y > 10.0f) worldTransform_.translation_.y = 10.0f;
    }
    if (input_->PushKey(DIK_S)) {
        worldTransform_.translation_.y -= speed_;
        if (worldTransform_.translation_.y < -50.0f) worldTransform_.translation_.y = -50.0f;
    }
    if (input_->PushKey(DIK_A)) {
        worldTransform_.translation_.x -= speed_;
        if (worldTransform_.translation_.x < -30.0f) worldTransform_.translation_.x = -30.0f;
    }
    if (input_->PushKey(DIK_D)) {
        worldTransform_.translation_.x += speed_;
        if (worldTransform_.translation_.x > 30.0f) worldTransform_.translation_.x = 30.0f;
    }

    // -----------------------------
    // 回転処理（スムーズ補間）
    // -----------------------------
    float targetRotX = 0.0f; // X軸回転（前後）
    float targetRotY = 0.0f; // Y軸回転（左右）

    // 前後方向
    if (input_->PushKey(DIK_S)) {
        targetRotX = -3.14159265f / 2.0f; // 下向き（前回転で-90度）
    }
    else if (input_->PushKey(DIK_W)) {
        targetRotX = 0.0f; // 正面
    }

    // 左右方向
    if (input_->PushKey(DIK_A)) {
        targetRotY = 3.14159265f / 2.0f; // 左90度
    }
    if (input_->PushKey(DIK_D)) {
        targetRotY = -3.14159265f / 2.0f;  // 右90度
    }

    // スムーズに補間
    worldTransform_.rotation_.x += (targetRotX - worldTransform_.rotation_.x) * rotationSpeed_;
    worldTransform_.rotation_.y += (targetRotY - worldTransform_.rotation_.y) * rotationSpeed_;

    // -----------------------------
    // ワールド行列更新
    // -----------------------------
    worldTransform_.UpdateMatrix();

    // -----------------------------
    // カメラ Y 追従
    // -----------------------------
    if (worldTransform_.translation_.y <= 0.0f &&
        worldTransform_.translation_.y >= -35.0f)
    {
        camera_.translation_.y = worldTransform_.translation_.y;
        camera_.UpdateMatrix();
    }
}

// ==============================
// 描画
// ==============================
void Player::Draw() {
    if (playerModel_) {
        playerModel_->Draw(worldTransform_, camera_);
    }
}