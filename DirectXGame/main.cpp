#include "scene/SceneManager.h"
#include "scene/TitleScene.h"
#include "scene/GameScene.h"
#include "scene/ResultScene.h"

#include <KamataEngine.h>
#include <Windows.h>

using namespace KamataEngine;

// ==============================
// Windowsアプリケーション エントリーポイント
// ==============================
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

    // ----- エンジン初期化 -----
    Initialize(L"3042_swim");

    // DirectXCommon のインスタンス取得
    DirectXCommon* dxCommon = DirectXCommon::GetInstance();

    // ----- シーンマネージャー初期化 -----
    SceneManager sceneManager;

    // 各シーンを登録
    sceneManager.RegisterScene(SceneName::Title, []() { return std::make_unique<TitleScene>(); });
    sceneManager.RegisterScene(SceneName::Game, []() { return std::make_unique<GameScene>(); });
    sceneManager.RegisterScene(SceneName::Result, []() { return std::make_unique<ResultScene>(); });

    // 初期シーンをタイトルに設定
    sceneManager.ChangeScene(SceneName::Title);

    // ==============================
    // メインループ
    // ==============================
    while (true) {

        // ----- エンジン更新 -----
        if (Update()) {
            break;  // 終了リクエストがあればループを抜ける
        }

        // ----- シーン更新 -----
        sceneManager.Update();

        // ----- 描画処理 -----
        dxCommon->PreDraw();    // 描画開始
        sceneManager.Draw();    // シーン描画
        dxCommon->PostDraw();   // 描画終了
    }

    // ----- エンジン終了処理 -----
    Finalize();

    return 0;
}