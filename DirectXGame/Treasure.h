#pragma once
#include <KamataEngine.h>

enum class TreasureType {
    Shallow,
    Middle,
    Deep
};

class Treasure
{
public:
    Treasure();
    ~Treasure();

    void Initialize(TreasureType type);
    void Update();
    void Draw(KamataEngine::Camera* camera);

    void Collect() { collected_ = true; }
    bool IsCollected() const { return collected_; }
    int GetScore() const { return score_; }

    const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }
    KamataEngine::Vector3 GetSize() const { return size_; }

private:
    TreasureType type_;
    int score_ = 0;
    bool collected_ = false;
    KamataEngine::WorldTransform worldTransform_;
    KamataEngine::Model* treasureModel_ = nullptr;
    KamataEngine::Vector3 size_ = { 1.0f, 1.0f, 1.0f };
};