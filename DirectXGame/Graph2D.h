#pragma once
#include <KamataEngine.h>

class Graph2D {
public:
	// コンストラクタ
	Graph2D();

	// デストラクタ
	~Graph2D();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	uint32_t dummyTextureHandle_ = 0;

	KamataEngine::Sprite* redGraph_ = nullptr;
	KamataEngine::Sprite* greenGraph_ = nullptr;

	KamataEngine::Vector2 greenPos_;
	const float scrollSpeed_ = 2.0f;
};
