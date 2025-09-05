#pragma once

#include <memory>
#include <unordered_map>
#include <functional>
#include "IScene.h"
#include "GameScene.h"
#include "ResultScene.h"

// ==============================
// シーン名列挙
// ==============================
enum class SceneName {
    Title,
    Game,
    Result,
};

// ==============================
// シーンマネージャークラス
// ==============================
class SceneManager {
public:
    // コンストラクタ / デストラクタ
    SceneManager();
    ~SceneManager();

    // 更新
    void Update();

    // 描画
    void Draw();

    // シーン登録
    void RegisterScene(
        SceneName name,
        std::function<std::unique_ptr<IScene>()> createFunc
    );

    // シーン切り替え
    void ChangeScene(SceneName name);

private:
    // ==============================
    // メンバ変数
    // ==============================
    std::unordered_map<SceneName, std::function<std::unique_ptr<IScene>()>> sceneFactory_;
    std::unique_ptr<IScene> currentScene_;
    SceneName currentSceneName_;

    // ==============================
    // GameScene のスコアを ResultScene に渡して切り替える
    // ==============================
    void TransferScoreToResult();
};