#pragma once
#include "Treasure.h"
#include "Player.h"
#include <vector>
#include <KamataEngine.h>

class TreasureManager
{
public:
    TreasureManager();
    ~TreasureManager();

    void Initialize();
    void Update();
    void Draw(KamataEngine::Camera* cam);

    // Player との AABB 判定
    void CheckCollision(const Player* player);

    int GetPendingScore() const { return pendingScore_; }
    void ClearPendingScore() { pendingScore_ = 0; }

private:
    std::vector<Treasure*> treasures_;
    int pendingScore_ = 0;
};