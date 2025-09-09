#pragma once
#include "../Player.h"
#include "../TreasureManager.h"
#include "../Stage.h"
#include "../Graph2D.h"
#include "../Score.h"

#include "IScene.h"

#include <KamataEngine.h>

class GameScene : public IScene
{
public:
	// コンストラクタ
	GameScene();

	// デストラクタ
	~GameScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	// 終了フラグ
	bool IsFinished() const { return finished_; }

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// カメラ
	KamataEngine::Camera camera_;

	// プレイヤー
	Player* player_ = nullptr;

	// 宝
	TreasureManager* treasureManager_ = nullptr;

	// ステージ
	Stage* stage_ = nullptr;

	// グラフ
	Graph2D* graph_ = nullptr;

	// スコア
	Score* score_ = nullptr;

	// 終了フラグ
	bool finished_ = false;

	// ポーズ画面
	bool isPosed_ = false;
	int poseSelect_ = 0;

	//背景
	uint32_t poseHandle_ = 0;
	KamataEngine::Sprite* poseBGSprite_ = nullptr;
	//リトライ
	uint32_t retryHandle_ = 0;
	KamataEngine::Sprite* retrySprite_ = nullptr;
	// タイトル
	uint32_t titlePoseHandle_ = 0;
	KamataEngine::Sprite* titlePoseSprite_ = nullptr;
	// ゲーム画面
	uint32_t gameHandle_ = 0;
	KamataEngine::Sprite* gameSprite_ = nullptr;

};