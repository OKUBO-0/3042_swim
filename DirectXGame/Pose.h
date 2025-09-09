#pragma once
#include <KamataEngine.h>

class Pose {
public:
	// コンストラクタ
	Pose();

	// デストラクタ
	~Pose();

	// 初期化
	void Initialize();

	// 更新
	void Update(int poseSelect);

	// 描画
	void Draw();


private:

	// 背景
	uint32_t poseHandle_ = 0;
	KamataEngine::Sprite* poseBGSprite_ = nullptr;
	// リトライ
	uint32_t retryHandle_ = 0;
	KamataEngine::Sprite* retrySprite_ = nullptr;
	// タイトル
	uint32_t titlePoseHandle_ = 0;
	KamataEngine::Sprite* titlePoseSprite_ = nullptr;
	// ゲーム画面
	uint32_t gameHandle_ = 0;
	KamataEngine::Sprite* gameSprite_ = nullptr;

	// 矢印
	uint32_t arrowHandle_ = 0;
	KamataEngine::Sprite* arrowSprite_ = nullptr;

	int poseSelect_ = 0;
	int isPoseSelect_ = 0;
	int Time;
	float arrowPosX = 0;
	float direction = 1;
};
