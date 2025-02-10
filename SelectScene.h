#pragma once

#include "Structures.h"
#include "Map.h"
#include "Rectangle.h"
#include "Player.h"
#include "Particle.h"
#include "Easing.h"
#include "PlayScene.h"
#include "SceneManager.h"

class SelectScene
{
public:
    // コンストラクタとデストラクタ
    SelectScene();
    ~SelectScene(); 

public:
    // メンバ関数
    // セレクトシーンの更新処理
    SceneManager::Scene Update();
    // セレクトシーンの描画処理
    void Draw();    
    // セレクトシーンの初期化
    void Init();     
    // セレクトシーンの演出に関する初期化
    void InitEffect();

public:
    // メンバ変数
};