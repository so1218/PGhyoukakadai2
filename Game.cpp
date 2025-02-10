#include "Game.h"
int GHs[128];

Game::Game()
    : p_sceneManager(std::make_unique<SceneManager>())
{
    // 初期シーンを設定
    p_sceneManager->SetScene(SceneManager::Scene::Title);

    // ゲームリソースの初期化
    int currentTime = static_cast<int>(time(nullptr));
    srand(currentTime);
    p_bullet = std::make_unique<Bullet>();
    p_player = std::make_unique<Player>(p_bullet.get());
    p_camera = std::make_unique<Camera>();
    p_map = std::make_unique<Map>();
    p_ts = std::make_unique<TitleScene>();
    p_ss = std::make_unique<SelectScene>();
    p_ps = std::make_unique<PlayScene>(p_player.get(), p_map.get(), p_camera.get(), p_bullet.get());
}

Game::~Game()
{
    //解放処理は不要
}

void Game::Init() 
{
    // ゲームの初期化
    p_ts->Init();
    p_ss->Init();
    p_ps->Init();
    p_map->SetMap();
    AudioInitialize();

}

void Game::UpdateScene() {
    // SceneManagerによるシーンの更新
   // 現在のシーンに基づいて描画処理
    switch (p_sceneManager->GetCurrentScene()) {
    case SceneManager::Scene::Title:
        p_sceneManager->SetScene(p_ts->Update());
        break;

    case SceneManager::Scene::Select:
        p_sceneManager->SetScene(p_ss->Update());
        break;

    case SceneManager::Scene::Play:
        p_sceneManager->SetScene(p_ps->Update());
        break;

    default:
        break;
    }
}

void Game::DrawScene() 
{
    // 現在のシーンに基づいて描画処理
    switch (p_sceneManager->GetCurrentScene()) {
    case SceneManager::Scene::Title:
        p_ts->Draw();
        break;

    case SceneManager::Scene::Select:
        p_ss->Draw();
        break;

    case SceneManager::Scene::Play:
        p_ps->Draw();
        break;

    default:
        break;
    }
}

void Game::Run()
{
    //ゲームループ
    while (Novice::ProcessMessage() == 0)
    {
        // フレームの開始
        Novice::BeginFrame();

        // GHs配列を初期化
        for (int i{ 0 }; i < _countof(GHs); ++i)
        {
            GHs[i] = -1;
        }

        // テクスチャ読み込み
        TextureManager::LoadTextures();

        // キー入力を受け取る
        memcpy(KeyManager::preKeys, KeyManager::keys, 256);
        Novice::GetHitKeyStateAll(KeyManager::keys);

        

        // ゲームの更新処理
        UpdateScene();
        // ゲームの描画処理
        DrawScene();

        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (KeyManager::preKeys[DIK_ESCAPE] == 0 && KeyManager::keys[DIK_ESCAPE] != 0)
        {
            break;
        }
    }
}