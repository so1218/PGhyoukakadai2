#pragma once

#include "Structures.h"
#include "Easing.h"
#include "SelectScene.h"
#include "Rectangle.h"
#include "Player.h"
#include "Particle.h"
#include "SceneManager.h"

class TitleScene
{
public:
    // コンストラクタとデストラクタ
    TitleScene();
    ~TitleScene(); 

public:
    // メンバ関数
    // タイトルシーンの更新処理
    SceneManager::Scene Update();
    // タイトルシーンの描画処理
    void Draw();       
    // タイトルシーンの初期化
    void Init();       
    // タイトルシーンの演出に関する初期化
    void InitEffect(); 

public:
    // メンバ変数
};

