#include "AirMeter.h"

using namespace KamataEngine;

AirMeter::AirMeter() {}

AirMeter::~AirMeter() {
	delete redGraph_;
	delete greenGraph_;
}

void AirMeter::Initialize() { 
	meterTextureHandle_ = TextureManager::Load("white1x1.png");

	// 赤グラフ（上に乗せる、スクロールする）
	redGraph_ = Sprite::Create(meterTextureHandle_, {100, 100});
	redGraph_->SetSize({25, 0});// サイズ（ピクセル）
	redGraph_->SetPosition({50, 150});   // 位置（ピクセル）
	redGraph_->SetColor({1, 0, 0, 1.0f}); // 赤, 不透明

	// 緑グラフ（背景）
	greenGraph_ = Sprite::Create(meterTextureHandle_, {100, 100});
	greenGraph_->SetSize({25, 150});
	greenGraph_->SetPosition({50, 150});    // 位置（ピクセル）
	greenGraph_->SetColor({0, 1, 0, 0.8f}); // 緑, 半透明

}


void AirMeter::Update(Vector3 playerPos) {
	targetPos = playerPos;

	if (targetPos.y < 10.0f) {
		redHeight += 0.5f; // 伸びるスピード
	} 
	else {
		redHeight -= 0.5f; // 縮むスピード
	}

	if (redHeight >= 150) {
		redHeight = 150;  //最大値
	} 
	else if(redHeight <= 0){
		redHeight = 0.0f; // 最小値
	}

	// サイズ更新（幅は固定）
	redGraph_->SetSize({25, redHeight});


}

void AirMeter::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Sprite::PreDraw(dxCommon->GetCommandList());

	greenGraph_->Draw();
	redGraph_->Draw();

	Sprite::PostDraw();

}
