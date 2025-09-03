#include "Player.h"
using namespace KamataEngine;

Player::Player() {}
Player::~Player() { delete playerModel_; }

void Player::Initialize() {
    input_ = Input::GetInstance();
    camera_.Initialize();
    playerModel_ = Model::CreateFromOBJ("octopus");

    worldTransform_.Initialize();
    worldTransform_.translation_ = { 0.0f, 10.0f, 0.0f };

    size_ = { 1.0f, 2.0f, 1.0f };
}

void Player::Update() {
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

    worldTransform_.UpdateMatrix();

    // カメラ y 追従
    if (worldTransform_.translation_.y <= 0.0f && worldTransform_.translation_.y >= -30.0f) {
        camera_.translation_.y = worldTransform_.translation_.y;
        camera_.UpdateMatrix();
    }
}

void Player::Draw() {
    playerModel_->Draw(worldTransform_, camera_);
}