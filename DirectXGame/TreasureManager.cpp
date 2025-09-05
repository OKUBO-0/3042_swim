#include "TreasureManager.h"
#include <cmath>
using namespace KamataEngine;

TreasureManager::TreasureManager() {}
TreasureManager::~TreasureManager() {
    for (auto t : treasures_) delete t;
}

void TreasureManager::Initialize() {
    for (int i = 0; i < 5; ++i) { Treasure* t = new Treasure(); t->Initialize(TreasureType::Shallow); treasures_.push_back(t); }
    for (int i = 0; i < 4; ++i) { Treasure* t = new Treasure(); t->Initialize(TreasureType::Middle); treasures_.push_back(t); }
    for (int i = 0; i < 2; ++i) { Treasure* t = new Treasure(); t->Initialize(TreasureType::Deep); treasures_.push_back(t); }
}

void TreasureManager::Update() {
    for (auto t : treasures_) t->Update();
}

void TreasureManager::Draw(Camera* cam) {
    for (auto t : treasures_) t->Draw(cam);
}

void TreasureManager::CheckCollision(const Player* player) {
    Vector3 playerPos = player->GetWorldTransform().translation_;
    Vector3 playerSize = player->GetSize();

    for (auto t : treasures_) {
        if (!t->IsCollected()) {
            Vector3 treasurePos = t->GetWorldTransform().translation_;
            Vector3 treasureSize = t->GetSize();

            bool collisionX = std::abs(playerPos.x - treasurePos.x) < (playerSize.x / 2 + treasureSize.x / 2);
            bool collisionY = std::abs(playerPos.y - treasurePos.y) < (playerSize.y / 2 + treasureSize.y / 2);
            bool collisionZ = std::abs(playerPos.z - treasurePos.z) < (playerSize.z / 2 + treasureSize.z / 2);

            if (collisionX && collisionY && collisionZ) {
                t->Collect();
                pendingScore_ += t->GetScore();
            }
        }
    }
}