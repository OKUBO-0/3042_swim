#include "Treasure.h"
using namespace KamataEngine;

Treasure::Treasure() {}
Treasure::~Treasure() { delete treasureModel_; }

void Treasure::Initialize(TreasureType type) {
    type_ = type;
    worldTransform_.Initialize();
    treasureModel_ = Model::CreateFromOBJ("cube");

    switch (type_) {
    case TreasureType::Shallow:
        worldTransform_.translation_ = { static_cast<float>(rand() % 61 - 30), 5.0f, 0.0f };
        score_ = 10; break;
    case TreasureType::Middle:
        worldTransform_.translation_ = { static_cast<float>(rand() % 61 - 30), -10.0f, 0.0f };
        score_ = 30; break;
    case TreasureType::Deep:
        worldTransform_.translation_ = { static_cast<float>(rand() % 61 - 30), -25.0f, 0.0f };
        score_ = 50; break;
    }

    size_ = { 1.0f, 1.0f, 1.0f };
}

void Treasure::Update() {
    worldTransform_.UpdateMatrix();
}

void Treasure::Draw(Camera* camera) {
    if (!collected_ && camera) treasureModel_->Draw(worldTransform_, *camera);
}