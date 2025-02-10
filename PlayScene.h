#pragma once

#include "Novice.h"
#include "Player.h"
#include "Map.h"
#include "Camera.h"
#include "SceneManager.h"
#include "Enemy.h"

class PlayScene {
public:
    // コンストラクタとデストラクタ
    PlayScene(Player* player, Map* map, Camera* camera, Bullet* bullet);
    ~PlayScene();

public:
    // メンバ関数
    // シーンの更新処理
    SceneManager::Scene Update();
    // シーンの描画処理
    void Draw();
    // シーンの初期化処理
    void Init();
    // シーンの演出に関する初期化
    void InitEffect();
private:
    // メンバ変数
    Player* player_;
    Map* map_;
    Camera* camera_;
    std::unique_ptr<EnemyManager> enemies;
    Bullet* bullet_;
    int frameCount_ = 0;
    int frameCountSecond_ = 0;
    int isEnd_ = false;
};