#pragma once
#include <KamataEngine.h>

class AirMeter {
public:
	AirMeter();
	~AirMeter();

	// 初期化
	void Initialize();

	// 更新
	void Update(KamataEngine::Vector3 playerPos);

	// 描画
	void Draw();



private:
	//座標
	KamataEngine::Vector3 targetPos;

	KamataEngine::Vector2 greenPos_;

	float airMeter = 0.0f;

	//画像
	KamataEngine::Sprite* redGraph_ = nullptr;
	KamataEngine::Sprite* greenGraph_ = nullptr;

	uint32_t meterTextureHandle_ = 0;


};


