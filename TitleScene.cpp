#include "TitleScene.h"

// コンストラクタ
TitleScene::TitleScene()
{
   
}

// デストラクタ
TitleScene::~TitleScene()
{
   
}

// タイトルシーンの更新処理
SceneManager::Scene TitleScene::Update()
{
    SceneManager::Scene nextScene = SceneManager::Scene::Title;

    if (KeyManager::IsKeyJustPressed(DIK_SPACE))
    {
        nextScene = SceneManager::Scene::Play;
    }
  
    return nextScene;
}

// タイトルシーンの描画処理
void TitleScene::Draw()
{
    Novice::DrawBox(0, 0, kWindowWidth, kWindowHeight, 0.0f, BLACK, kFillModeSolid);
    // デバッグ時に画面に表示
    Novice::ScreenPrintf(600, 200, "TitleScene");
    Novice::ScreenPrintf(600, 400, "Press SPACE");
#if defined(_DEBUG)
   
#endif
}

// タイトルシーンの初期化
void TitleScene::Init()
{
    
}

// タイトルシーンの演出に関する初期化
void TitleScene::InitEffect()
{
   
}
