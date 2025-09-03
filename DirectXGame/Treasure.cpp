#include "Treasure.h"

using namespace KamataEngine;


Treasure::Treasure()
{
}

Treasure::~Treasure()
{
	delete treasureModel_;
}

void Treasure::Initialize()
{
	// カメラの初期化
	camera_.Initialize();

	// プレイヤーモデルの読み込み
	treasureModel_ = Model::CreateFromOBJ("octopus");

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0.0f, 0.0f, 0.0f };
}

void Treasure::Update()
{
	worldTransform_.UpdateMatrix();
}

void Treasure::Draw(const Camera* camera)
{
	treasureModel_->Draw(worldTransform_,*camera);
}