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
	void Update(float playerY);

	// 描画
	void Draw(const KamataEngine::Camera& camera);

private:

	const float scrollSpeed_ = 2.0f;

	KamataEngine::Model* BGModel = nullptr;
	KamataEngine::WorldTransform worldTransform_;
};