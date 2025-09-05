#pragma once
#include "../Player.h"
#include "../TreasureManager.h"
#include "../Stage.h"
#include "../Graph2D.h"
#include "../Score.h"
#include "../Timer.h"

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

	int GetScore() const { return currentScore_; }

	bool returnToTitle_ = false;

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
	int currentScore_ = 0;

	// タイマー
	Timer* timer_ = nullptr;

	// 終了フラグ
	bool finished_ = false;
};