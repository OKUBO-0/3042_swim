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
	void Draw(const KamataEngine::Camera* camera);

	void SetPosition(const KamataEngine::Vector3& pos) {
		worldTransform_.translation_ = pos;
	}

private:
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera camera_;

	// プレイヤーモデル
	KamataEngine::Model* treasureModel_ = nullptr;
};

