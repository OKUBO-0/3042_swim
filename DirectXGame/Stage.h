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
	void Draw(KamataEngine::Camera* camera);

private:
	KamataEngine::WorldTransform worldTransform_; // ワールド変換
	KamataEngine::Model* stageModel_ = nullptr; // ステージモデル
};