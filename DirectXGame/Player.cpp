#include "Player.h"
using namespace KamataEngine;

Player::Player() {}

Player::~Player() {
    delete playerModel_;
}

void Player::Initialize() {
    // 入力インスタンス取得
    input_ = Input::GetInstance();

    // カメラ初期化
    camera_.Initialize();

    // プレイヤーモデル読み込み
    playerModel_ = Model::CreateFromOBJ("octopus");

    // ワールドトランスフォーム初期化
    worldTransform_.Initialize();
    worldTransform_.translation_ = { 0.0f, 10.0f, 0.0f }; // 初期位置（Y=10）

    // 衝突判定用サイズ
    size_ = { 1.0f, 2.0f, 1.0f };

    // 回転初期化
    worldTransform_.rotation_ = { 0.0f, 0.0f, 0.0f };
}

void Player::Update() {
    // 移動
    if (input_->PushKey(DIK_W)) {
        worldTransform_.translation_.y += speed_;
        if (worldTransform_.translation_.y > 10.0f) worldTransform_.translation_.y = 10.0f;
    }
    if (input_->PushKey(DIK_S)) {
        worldTransform_.translation_.y -= speed_;
        if (worldTransform_.translation_.y < -30.0f) worldTransform_.translation_.y = -30.0f;
    }
    if (input_->PushKey(DIK_A)) {
        worldTransform_.translation_.x -= speed_;
        if (worldTransform_.translation_.x < -30.0f) worldTransform_.translation_.x = -30.0f;
    }
    if (input_->PushKey(DIK_D)) {
        worldTransform_.translation_.x += speed_;
        if (worldTransform_.translation_.x > 30.0f) worldTransform_.translation_.x = 30.0f;
    }

    // --- 回転処理 ---
    // デフォルトは正面向き
    float targetRotX = 0.0f;
    float targetRotY = 0.0f;

    // Sキーで下向き（前回転で -π/2）
    if (input_->PushKey(DIK_S)) {
        targetRotX = -3.14159265f / 2.0f; // -90度（前回転で下向き）
    }
    else if (input_->PushKey(DIK_W)) {
        targetRotX = 0.0f; // 上は正面
    }

    // A・DでY軸回転
    if (input_->PushKey(DIK_A)) {
        targetRotY = 3.14159265f / 2.0f; // 左90度
    }
    if (input_->PushKey(DIK_D)) {
        targetRotY = -3.14159265f / 2.0f;  // 右90度
    }

    // --- スムーズ補間 ---
    worldTransform_.rotation_.x += (targetRotX - worldTransform_.rotation_.x) * rotationSpeed_;
    worldTransform_.rotation_.y += (targetRotY - worldTransform_.rotation_.y) * rotationSpeed_;

    // -----------------------------
    // ワールド行列更新
    // -----------------------------
    worldTransform_.UpdateMatrix();

    // -----------------------------
    // カメラ Y 追従
    // プレイヤーが水中（0 >= y >= -30）の場合のみ追従
    // -----------------------------
    if (worldTransform_.translation_.y <= 0.0f &&
        worldTransform_.translation_.y >= -30.0f)
    {
        camera_.translation_.y = worldTransform_.translation_.y;
        camera_.UpdateMatrix();
    }
}

void Player::Draw() {
    // プレイヤーモデル描画
    playerModel_->Draw(worldTransform_, camera_);
}