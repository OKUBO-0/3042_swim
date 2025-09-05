#pragma once

/// ===============================================
/// @class IScene
/// @brief シーン共通インターフェース
/// ===============================================
class IScene {
public:
    // デストラクタ（仮想）
    virtual ~IScene() = default;

    // 初期化
    virtual void Initialize() = 0;

    // 更新
    virtual void Update() = 0;

    // 描画
    virtual void Draw() = 0;

    // シーン終了判定
    virtual bool IsFinished() const = 0;
};