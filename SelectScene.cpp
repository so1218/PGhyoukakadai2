#include "SelectScene.h"

// コントラクタ
SelectScene::SelectScene()
{

}

// デストラクタ
SelectScene::~SelectScene()
{
    
}

// セレクトシーンの更新処理
SceneManager::Scene SelectScene::Update()
{
    SceneManager::Scene nextScene = SceneManager::Scene::Select;
   
   
    return nextScene;
}

// セレクトシーンの描画処理
void SelectScene::Draw()
{
#if defined(_DEBUG)
    // デバッグ時に画面に表示
    Novice::ScreenPrintf(0, 0, "SelectScene");
#endif
}

// セレクトシーンの初期化
void SelectScene::Init()
{
   
}

// セレクトシーンの演出に関する初期化
void SelectScene::InitEffect()
{
    
}