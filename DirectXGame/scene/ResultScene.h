#pragma once
#include "../Score.h"

#include "IScene.h"

#include <KamataEngine.h>

class ResultScene : public IScene
{
public:
	// コンストラクタ
	ResultScene();

	// デストラクタ
	~ResultScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	// 終了フラグ
	bool IsFinished() const { return finished_; }

	void SetScore(int score);

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// カメラ
	KamataEngine::Camera camera_;

	// スコア
	Score* scoreDisplay_ = nullptr;
	int finalScore_ = 0;

	// 終了フラグ
	bool finished_ = false;
};