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

// 次に数値の各桁に対応した画像を描画する。
// 以下の方法で各桁の値に応じた数値を描画するようにする
// 
// 1.最初に割る数値は5桁なので1000で初期化設定する
// 2.5桁分ループして処理を行う
// 3.数値を桁に対応した値で割り、今の桁の値を出す
// 4.今の桁の数値の部分を切り出すようにする
// 5.次の桁の処理の為に、数値を残りの桁の数値にする
// 6.次の桁の処理の為に、割る数値を10で割って桁に応じた値にする
// 変数numberで指定された数値の各桁に対応した画像を描画する
// int32_t digit = 10000;
// for (int i = 0; i < kDigitCount; ++i) {
// int nowNumber = number / digit;  // 現在の桁の数値を取得
// sprite_[i]->SetTextureRect({size.x * nowNumber, 0} 自分で考える);
// number % = digit;
// digit /= 10;
// }