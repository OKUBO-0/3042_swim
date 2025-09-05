#include "TreasureManager.h"
#include <cmath>
using namespace KamataEngine;

// ==============================
// コンストラクタ / デストラクタ
// ==============================
TreasureManager::TreasureManager() {}

TreasureManager::~TreasureManager() {
    // 動的に確保した宝物を解放
    for (auto t : treasures_) delete t;
}

// ==============================
// 初期化
// ==============================
void TreasureManager::Initialize() {
    // 浅瀬の宝物 5 個
    for (int i = 0; i < 5; ++i) {
        Treasure* t = new Treasure();
        t->Initialize(TreasureType::Shallow);
        treasures_.push_back(t);
    }

    // 中層の宝物 4 個
    for (int i = 0; i < 4; ++i) {
        Treasure* t = new Treasure();
        t->Initialize(TreasureType::Middle);
        treasures_.push_back(t);
    }

    // 深層の宝物 2 個
    for (int i = 0; i < 2; ++i) {
        Treasure* t = new Treasure();
        t->Initialize(TreasureType::Deep);
        treasures_.push_back(t);
    }
}

// ==============================
// 更新
// ==============================
void TreasureManager::Update() {
    for (auto t : treasures_) {
        t->Update();
    }
}

// ==============================
// 描画
// ==============================
void TreasureManager::Draw(Camera* cam) {
    for (auto t : treasures_) {
        t->Draw(cam);
    }
}

// ==============================
// 衝突判定
// ==============================
void TreasureManager::CheckCollision(const Player* player) {
    Vector3 playerPos = player->GetWorldTransform().translation_;
    Vector3 playerSize = player->GetSize();

    for (auto t : treasures_) {
        if (!t->IsCollected()) {
            Vector3 treasurePos = t->GetWorldTransform().translation_;
            Vector3 treasureSize = t->GetSize();

            // AABB 判定
            bool collisionX = std::abs(playerPos.x - treasurePos.x) < (playerSize.x / 2 + treasureSize.x / 2);
            bool collisionY = std::abs(playerPos.y - treasurePos.y) < (playerSize.y / 2 + treasureSize.y / 2);
            bool collisionZ = std::abs(playerPos.z - treasurePos.z) < (playerSize.z / 2 + treasureSize.z / 2);

            if (collisionX && collisionY && collisionZ) {
                t->Collect();                     // 宝物取得
                pendingScore_ += t->GetScore();   // スコア加算
            }
        }
    }
}