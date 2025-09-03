#include "Score.h"

using namespace KamataEngine;

Score::Score() {}

Score::~Score() {
	for (int i = 0; i < kDigitCount; ++i) {
		delete sprite_[i];
	}
}

void Score::Initialize() {
	// テクスチャの読み込み
	textureHandle_ = TextureManager::Load("number.png");

	// スプライトの生成（横に並べる）
	for (int i = 0; i < kDigitCount; ++i) {
		sprite_[i] = Sprite::Create(textureHandle_, {100.0f + size_.x * i, 5.0f});
		sprite_[i]->SetSize(size_);
		sprite_[i]->SetTextureRect({ 0.0f, 0.0f }, size_);
	}
}

void Score::Update() {
}

void Score::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Sprite::PreDraw(dxCommon->GetCommandList());

	for (int i = 0; i < kDigitCount; ++i) {
		sprite_[i]->Draw();
	}

	Sprite::PostDraw();
}

void Score::SetNumber(int number) {
	int32_t digit = 10000; // 5桁分の割る値

	for (int i = 0; i < kDigitCount; ++i) {
		int nowNumber = number / digit;
		sprite_[i]->SetTextureRect({ size_.x * nowNumber, 0.0f }, size_);
		number %= digit;
		digit /= 10;
	}
}