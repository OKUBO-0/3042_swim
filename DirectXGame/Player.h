#pragma once
#include <KamataEngine.h>

class Player
{
public:
    Player();
    ~Player();

    void Initialize();
    void Update();
    void Draw();

    KamataEngine::Camera& GetCamera() { return camera_; }
    const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }
    KamataEngine::Vector3 GetSize() const { return size_; } // 衝突判定用

	KamataEngine::Vector3 GetPosition() { return worldTransform_.translation_; }


private:
    KamataEngine::Input* input_ = nullptr;
    KamataEngine::WorldTransform worldTransform_;
    KamataEngine::Camera camera_;
    KamataEngine::Model* playerModel_ = nullptr;

    float speed_ = 0.15f;
    KamataEngine::Vector3 size_ = { 1.0f, 2.0f, 1.0f };
};