#include "Structures.h"
#include "Map.h"
#include "Player.h"
#include "Easing.h"
#include "SelectScene.h"
#include "Particle.h"
#include "Rectangle.h"
#include "Matrix.h"
#include "GrovalTextureHandles.h"
#include "PlayScene.h"
#include "Function.h"
#include "Camera.h"

//========================================================
// プレイシーンの更新処理
//========================================================

// コンストラクタ
PlayScene::PlayScene(Player* player, Map* map, Camera* camera, Bullet* bullet)
{
    player_ = player;
    map_ = map;
    camera_ = camera;
    enemies = std::make_unique<EnemyManager>();
    bullet_ = bullet;
    frameCount_ = 1800;
    isEnd_ = false;
}

// デストラクタ
PlayScene::~PlayScene() {
}

// プレイシーンの更新処理
SceneManager::Scene PlayScene::Update()
{
    SceneManager::Scene nextScene = SceneManager::Scene::Play;

    if (!isEnd_)
    {
        enemies->Update();
        player_->Move();

        --frameCount_;
        frameCountSecond_ = frameCount_ / 60;
        if (frameCountSecond_ < 0)
        {
            isEnd_ = true;
        }
        if (KeyManager::IsKeyJustPressed(DIK_R))
        {
            Init();
            for (int j = 0; j < enemyAmount; ++j)
            {
                enemies->enemies[j]->Init();
            }
            player_->Init();
            bullet_->Init();
            enemies->Init();
            nextScene = SceneManager::Scene::Title;
        }

        for (int i = 0; i < pinsCount; ++i)
        {
            for (int j = 0; j < enemyAmount; ++j)
            {
                float distance = MathUtils::CalculateDistance(enemies->enemies[j]->GetRectangle()->wPos, bullet_->GetRectWPos(i));
                if (distance < (enemies->enemies[j]->GetRadius() + bullet_->GetRadius(i).x))
                {
                    enemies->enemies[j]->SetIsExist(false);
                    bullet_->SetIsActive(i, false);
                    bullet_->SetRectWPosX(i, 0, 0);
                    enemies->addScore(10);
                }
            }
        }

        player_->SetColor(RED);
        for (int j = 0; j < enemyAmount; ++j)
        {
            float distance = MathUtils::CalculateDistance(enemies->enemies[j]->GetRectangle()->wPos, player_->GetRectangle()->wPos);
            if (distance < (enemies->enemies[j]->GetRadius() + 25))
            {
                enemies->enemies[j]->SetIsExist(false);
                enemies->addScore(-50);
                player_->SetColor(BLUE);
            }
        }

        for (int i = 0; i < map_->GetFloorHeight(); ++i) {
            for (int j = 0; j < map_->GetFloorWidth(); ++j) {
                camera_->MakeCameraMatrix(&map_->GetChip(j, i).GetRectangleObject());
            }
        }

        if (player_->GetRectangle()->isShake) {
            camera_->ShakeObject(player_->GetRectangle());
        }

        // カメラのシェイク処理
        if (KeyManager::IsKeyJustPressed(DIK_SPACE)) {
            camera_->isShake = true;
        }

        if (camera_->isShake) {
            camera_->ShakeCamera();
        }



        camera_->DebugCameraMovement();
        camera_->DebugRectMovement(player_->GetRectangle());
    }
    else
    {
        if (KeyManager::IsKeyJustPressed(DIK_SPACE)) {
            Init();
            for (int j = 0; j < enemyAmount; ++j)
            {
                enemies->enemies[j]->Init();
            }
            player_->Init();
            bullet_->Init();
            enemies->Init();
            nextScene = SceneManager::Scene::Title;
        }
    }

    return nextScene;
}

// プレイシーンの描画処理
void PlayScene::Draw() 
{ 
    Novice::DrawBox(0, 0, kWindowWidth, kWindowHeight, 0.0f, BLACK, kFillModeSolid);
   /* map_->DrawMap();*/
    Novice::DrawLine(0, kWindowHeight - 100, kWindowWidth, kWindowHeight - 100, WHITE);
    Novice::DrawLine(100, 0, 100, kWindowHeight, WHITE);
    player_->Draw(/*map_*/);
    enemies->Draw();
    
    Novice::ScreenPrintf(630, 160, "TIMER %d", frameCountSecond_);
    Novice::ScreenPrintf(0, 20, "Press SPACE : Fire Bullet");
    if (isEnd_)
    {
        Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0xA8C88Bff, kFillModeSolid);
        Novice::ScreenPrintf(600, 400, "Press SPACE");
    }
    Novice::ScreenPrintf(630, 200, "SCORE::%d", enemies->getScore());
    
    
   
   

#if defined(_DEBUG)
    /*Novice::ScreenPrintf(0, 0, "PlayScene");*/
#endif
}

// プレイシーンの初期化処理
void PlayScene::Init()
{
    player_->Init();
    enemies->Init();
    frameCount_ = 1800;
    frameCountSecond_ = 0;
    isEnd_ = false;
}

// プレイシーンの演出に関する初期化
void PlayScene::InitEffect() 
{
    // 必要な初期化処理を追加
}