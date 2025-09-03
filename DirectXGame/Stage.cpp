#include "Stage.h"

using namespace KamataEngine;

Stage::Stage() {
}

Stage::~Stage() {
	delete background1_;
	delete background2_;
}

void Stage::Initialize() {
	// テクスチャ読み込み
	backgroundHandle_ = TextureManager::Load("stage.png");
	inversionHandle_ = TextureManager::Load("inversion.png");

	// スプライト生成（2枚）
	background1_ = Sprite::Create(backgroundHandle_, { 0.0f, 0.0f });
	background2_ = Sprite::Create(inversionHandle_, { 1280.0f, 0.0f });

	// サイズ指定
	background1_->SetSize({ 1280, 720 });
	background2_->SetSize({ 1280, 720 });

	// 初期位置
	position1_ = { 0.0f, 0.0f };
	position2_ = { 1280.0f, 0.0f };
}

void Stage::Update() {
	// 左にスクロール
	position1_.x -= scrollSpeed_;
	position2_.x -= scrollSpeed_;

	// 1枚目が左端を超えたら右に移動
	if (position1_.x <= -1280.0f) {
		position1_.x = position2_.x + 1280.0f;
	}
	if (position2_.x <= -1280.0f) {
		position2_.x = position1_.x + 1280.0f;
	}

	// 位置反映
	background1_->SetPosition(position1_);
	background2_->SetPosition(position2_);
}

void Stage::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Sprite::PreDraw(dxCommon->GetCommandList());

	background1_->Draw();
	background2_->Draw();

	Sprite::PostDraw();
}
