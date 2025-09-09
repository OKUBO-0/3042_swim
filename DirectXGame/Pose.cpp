#include "Pose.h"

using namespace KamataEngine;

Pose::Pose() {}

Pose::~Pose() {
	delete poseBGSprite_;
	delete gameSprite_;
	delete retrySprite_;
	delete titlePoseSprite_;
	delete arrowSprite_;
}

void Pose::Initialize() {

	// ポーズUI
	poseHandle_ = TextureManager::Load("Pose/PoseBG.png");
	poseBGSprite_ = Sprite::Create(poseHandle_, {320, 180});
	gameHandle_ = TextureManager::Load("Pose/PoseGameStart.png");
	gameSprite_ = Sprite::Create(gameHandle_, {530, 200});
	retryHandle_ = TextureManager::Load("Pose/PoseRetry.png");
	retrySprite_ = Sprite::Create(retryHandle_, {530, 300});
	titlePoseHandle_ = TextureManager::Load("Pose/PoseTitle.png");
	titlePoseSprite_ = Sprite::Create(titlePoseHandle_, {530, 400});
	arrowHandle_ = TextureManager::Load("Pose/PoseArrow.png");
	arrowSprite_ = Sprite::Create(arrowHandle_, {0, 0});
}

void Pose::Update(int poseSelect) {
	poseSelect_ = poseSelect;
	if (poseSelect_ != isPoseSelect_) {
		Time = 0;
		direction = 1;
		arrowPosX = 0;
	}

	Time++;

	if (Time % 5 == 0) {
		arrowPosX += 1 * direction;
	}
	if (arrowPosX >= 5 || arrowPosX <= -5) {
		direction *= -1;
	}

	if (poseSelect_ == 0) {
		arrowSprite_->SetPosition({450 + arrowPosX, 225});
	} 
	else if (poseSelect_ == 1) {
		arrowSprite_->SetPosition({450 + arrowPosX, 325});
	} 
	else if (poseSelect_ == 2) {
		arrowSprite_->SetPosition({450 + arrowPosX, 425});
	}
	isPoseSelect_ = poseSelect_;
}

void Pose::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Sprite::PreDraw(dxCommon->GetCommandList());

	poseBGSprite_->Draw();
	retrySprite_->Draw();
	titlePoseSprite_->Draw();
	gameSprite_->Draw();
	arrowSprite_->Draw();

	Sprite::PostDraw();
}

