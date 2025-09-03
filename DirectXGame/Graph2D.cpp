#include "Graph2D.h"

using namespace KamataEngine;

Graph2D::Graph2D() {
}

Graph2D::~Graph2D() {
	delete redGraph_;
	delete greenGraph_;
}

void Graph2D::Initialize() {
	// 1x1ピクセルのダミーテクスチャを使用（単色塗り）
	dummyTextureHandle_ = TextureManager::Load("white1x1.png");

	// 赤グラフ（背景）
	redGraph_ = Sprite::Create(dummyTextureHandle_, { 100, 100 });
	redGraph_->SetSize({ 600, 50 });  // サイズ（ピクセル）
	redGraph_->SetColor({ 1, 0, 0, 0.5 });  // 赤, 不透明

	// 緑グラフ（上に乗せる、スクロールする）
	greenGraph_ = Sprite::Create(dummyTextureHandle_, { 100, 100 });
	greenGraph_->SetSize({ 600, 50 });
	greenGraph_->SetColor({ 0, 1, 0, 0.8f });  // 緑, 半透明

	// 緑グラフの初期位置
	greenPos_ = { 100, 100 };
}

void Graph2D::Update() {
	// 緑の表示幅を縮める
	static float greenWidth = 600.0f;
	//greenWidth -= scrollSpeed_;

	// 完全に消えたらリセット
	if (greenWidth <= 0.0f) {
		greenWidth = 600.0f;
	}

	// サイズ更新（高さは固定）
	greenGraph_->SetSize({ greenWidth, 50 });

	// 位置は固定（左端を動かさない）
	greenGraph_->SetPosition({ 100.0f, 100.0f });
}

void Graph2D::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Sprite::PreDraw(dxCommon->GetCommandList());

	redGraph_->Draw();
	greenGraph_->Draw();

	Sprite::PostDraw();
}
