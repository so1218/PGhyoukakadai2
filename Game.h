#pragma once

#include "TitleScene.h"
#include "SelectScene.h"
#include "PlayScene.h"
#include "GrovalAudio.h"
#include "Player.h"
#include "Camera.h"
#include "Map.h"
#include "GrovalTextureHandles.h"
#include "Easing.h"
#include "Bullet.h"
#include "Draw.h"
#include "Function.h"
#include "SceneManager.h"
#include "GameBaseInfo.h"

const char kWindowTitle[] = "MT2_評価課題_LC1A_21_ホリ_ソウヘイ";

class Game {
public:
    Game();  // コンストラクタ
    ~Game(); // デストラクタ

public:
    void Init();  // ゲームの初期化処理
    void Run();   // ゲームループ
    void UpdateScene();  // シーンごとの更新処理
    void DrawScene();    // シーンごとの描画処理

public:
    // ゲーム内のリソースのポインタ
    std::unique_ptr<Bullet> p_bullet;
    std::unique_ptr<Player> p_player;
    std::unique_ptr<Camera> p_camera;
    std::unique_ptr<Map> p_map;
    std::unique_ptr<Particle> p_particle;
    std::unique_ptr<ParticleEmitter> p_particleEmi;
    std::unique_ptr<TitleScene> p_ts;
    std::unique_ptr<SelectScene> p_ss;
    std::unique_ptr<PlayScene> p_ps;
    std::unique_ptr<SceneManager> p_sceneManager;
};