#pragma once
#include <KamataEngine.h>

class Treasure
{
public:
	// コンストラクタ
	Treasure();

	// デストラクタ
	~Treasure();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera* camera);

private:
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	// プレイヤーモデル
	KamataEngine::Model* treasureModel_ = nullptr;
};