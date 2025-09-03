#include "Player.h"

using namespace KamataEngine;

// コンストラクタ
Player::Player() {
}

// デストラクタ
Player::~Player() {
	delete playerModel_;
}

// 初期化
void Player::Initialize() {
	// Inputインスタンスの取得
	input_ = Input::GetInstance();

	// カメラの初期化
	camera_.Initialize();

	// プレイヤーモデルの読み込み
	playerModel_ = Model::CreateFromOBJ("octopus");

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0.0f, 0.0f, 0.0f };
}

// 更新
void Player::Update() {
	// 入力の取得
	if (input_->PushKey(DIK_W)) {
		worldTransform_.translation_.y += speed_; // 前進
	}
	if (input_->PushKey(DIK_S)) {
		worldTransform_.translation_.y -= speed_; // 後退
	}
	if (input_->PushKey(DIK_A)) {
		worldTransform_.translation_.x -= speed_; // 左移動
	}
	if (input_->PushKey(DIK_D)) {
		worldTransform_.translation_.x += speed_; // 右移動
	}

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

// 描画
void Player::Draw() {
	// モデルの描画
	playerModel_->Draw(worldTransform_, camera_);
}