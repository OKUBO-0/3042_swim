#include "SceneManager.h"

// ==============================
// コンストラクタ / デストラクタ
// ==============================
SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

// ==============================
// シーン登録
// ==============================
void SceneManager::RegisterScene(SceneName name, std::function<std::unique_ptr<IScene>()> createFunc) {
    sceneFactory_[name] = createFunc;
}

// ==============================
// シーン切り替え
// ==============================
void SceneManager::ChangeScene(SceneName name) {
    if (sceneFactory_.find(name) != sceneFactory_.end()) {
        currentScene_ = sceneFactory_[name]();
        currentScene_->Initialize();
        currentSceneName_ = name;
    }
}

// ==============================
// 更新
// ==============================
void SceneManager::Update() {
    if (!currentScene_) return;

    // 現在のシーンを更新
    currentScene_->Update();

    // ----- GameScene で ESC キー押下時にタイトルに戻す -----
    if (currentSceneName_ == SceneName::Game) {
        auto gameScene = dynamic_cast<GameScene*>(currentScene_.get());
        if (gameScene && gameScene->returnToTitle_) {
            ChangeScene(SceneName::Title);
            return;
        }
    }

    // ----- シーン終了判定 -----
    if (currentScene_->IsFinished()) {
        if (currentSceneName_ == SceneName::Title) {
            ChangeScene(SceneName::Game);
        }
        else if (currentSceneName_ == SceneName::Game) {
            TransferScoreToResult();
        }
        else if (currentSceneName_ == SceneName::Result) {
            ChangeScene(SceneName::Title);
        }
    }
}

// ==============================
// 描画
// ==============================
void SceneManager::Draw() {
    if (currentScene_) {
        currentScene_->Draw();
    }
}

// ==============================
// GameScene のスコアを ResultScene に渡して切り替える
// ==============================
void SceneManager::TransferScoreToResult() {
    // GameScene のスコアを取得
    auto gameScene = dynamic_cast<GameScene*>(currentScene_.get());
    if (!gameScene) return;

    int score = gameScene->GetScore();

    // ResultScene を生成してスコアをセット
    auto resultSceneFunc = sceneFactory_[SceneName::Result];
    currentScene_ = resultSceneFunc();
    auto resultScene = dynamic_cast<ResultScene*>(currentScene_.get());
    if (resultScene) resultScene->SetScore(score);

    currentScene_->Initialize();
    currentSceneName_ = SceneName::Result;
}