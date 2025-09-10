#pragma once
#include <KamataEngine.h>

class Pose {
public:
    enum class Action { None, Resume, Retry, Title };

    Pose();
    ~Pose();

    void Initialize();

    void Activate();              // ポーズ開始
    bool IsPosed() const;         // ポーズ中か
    void Update();                 // 入力＆矢印移動
    Action GetSelectedAction() const;  // 決定されたアクション
    void Reset();                  // 選択を初期化
    void Draw();

private:
    bool isPosed_ = false;
    int poseSelect_ = 0;
    int isPoseSelect_ = 0;
    int Time = 0;
    float arrowPosX = 0;
    float direction = 1;

    // スプライト
    uint32_t poseHandle_ = 0;
    KamataEngine::Sprite* poseBGSprite_ = nullptr;
    uint32_t retryHandle_ = 0;
    KamataEngine::Sprite* retrySprite_ = nullptr;
    uint32_t titlePoseHandle_ = 0;
    KamataEngine::Sprite* titlePoseSprite_ = nullptr;
    uint32_t gameHandle_ = 0;
    KamataEngine::Sprite* gameSprite_ = nullptr;
    uint32_t arrowHandle_ = 0;
    KamataEngine::Sprite* arrowSprite_ = nullptr;

    Action selectedAction_ = Action::None;

    KamataEngine::Input* input_ = nullptr;  // 入力取得用
};