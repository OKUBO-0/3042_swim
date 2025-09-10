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
    input_ = Input::GetInstance();

    // スプライト読み込み
    poseHandle_ = TextureManager::Load("Pose/PoseBG.png");
    poseBGSprite_ = Sprite::Create(poseHandle_, { 320, 180 });
    gameHandle_ = TextureManager::Load("Pose/PoseGameStart.png");
    gameSprite_ = Sprite::Create(gameHandle_, { 530, 200 });
    retryHandle_ = TextureManager::Load("Pose/PoseRetry.png");
    retrySprite_ = Sprite::Create(retryHandle_, { 530, 300 });
    titlePoseHandle_ = TextureManager::Load("Pose/PoseTitle.png");
    titlePoseSprite_ = Sprite::Create(titlePoseHandle_, { 530, 400 });
    arrowHandle_ = TextureManager::Load("Pose/PoseArrow.png");
    arrowSprite_ = Sprite::Create(arrowHandle_, { 0, 0 });
}

void Pose::Activate() {
    isPosed_ = true;
    poseSelect_ = 0;
    selectedAction_ = Action::None;
    Time = 0;
    arrowPosX = 0;
    direction = 1;
}

bool Pose::IsPosed() const {
    return isPosed_;
}

void Pose::Reset() {
    isPosed_ = false;
    selectedAction_ = Action::None;
}

Pose::Action Pose::GetSelectedAction() const {
    return selectedAction_;
}

void Pose::Update() {
    if (!isPosed_) return;

    // 選択変更
    if (input_->TriggerKey(DIK_W)) poseSelect_--;
    if (input_->TriggerKey(DIK_S)) poseSelect_++;
    if (poseSelect_ < 0) poseSelect_ = 0;
    if (poseSelect_ > 2) poseSelect_ = 2;

    // 決定
    if (input_->TriggerKey(DIK_SPACE)) {
        switch (poseSelect_) {
        case 0: selectedAction_ = Action::Resume; break;
        case 1: selectedAction_ = Action::Retry; break;
        case 2: selectedAction_ = Action::Title; break;
        }
    }

    // 矢印アニメーション
    if (poseSelect_ != isPoseSelect_) {
        Time = 0;
        direction = 1;
        arrowPosX = 0;
    }
    Time++;
    if (Time % 5 == 0) arrowPosX += 1 * direction;
    if (arrowPosX >= 5 || arrowPosX <= -5) direction *= -1;

    // 矢印位置
    int baseY = 225 + poseSelect_ * 100;
    arrowSprite_->SetPosition({ 450 + arrowPosX, (float)baseY });
    isPoseSelect_ = poseSelect_;
}

void Pose::Draw() {
    if (!isPosed_) return;

    DirectXCommon* dxCommon = DirectXCommon::GetInstance();
    Sprite::PreDraw(dxCommon->GetCommandList());

    poseBGSprite_->Draw();
    gameSprite_->Draw();
    retrySprite_->Draw();
    titlePoseSprite_->Draw();
    arrowSprite_->Draw();

    Sprite::PostDraw();
}