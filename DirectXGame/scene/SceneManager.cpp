#include "SceneManager.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

void SceneManager::RegisterScene(SceneName name, std::function<std::unique_ptr<IScene>()> createFunc) {
	sceneFactory_[name] = createFunc;
}

void SceneManager::ChangeScene(SceneName name) {
	if (sceneFactory_.find(name) != sceneFactory_.end()) {
		currentScene_ = sceneFactory_[name]();
		currentScene_->Initialize();
		currentSceneName_ = name;
	}
}

void SceneManager::Update() {
	if (!currentScene_) return;

	currentScene_->Update();

	// GameSceneでEscape押下時にタイトルに戻す
	if (currentSceneName_ == SceneName::Game) {
		auto gameScene = dynamic_cast<GameScene*>(currentScene_.get());
		if (gameScene && gameScene->returnToTitle_) {
			ChangeScene(SceneName::Title);
			return;
		}
	}

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

void SceneManager::Draw() {
	if (currentScene_) {
		currentScene_->Draw();
	}
}

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