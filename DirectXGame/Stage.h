#pragma once
#include <KamataEngine.h>

class Stage {
public:
	// コンストラクタ
	Stage();

	// デストラクタ
	~Stage();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	uint32_t backgroundHandle_;
	uint32_t inversionHandle_;
	KamataEngine::Sprite* background1_ = nullptr;
	KamataEngine::Sprite* background2_ = nullptr;

	KamataEngine::Vector2 position1_;
	KamataEngine::Vector2 position2_;

	const float scrollSpeed_ = 2.0f;
};