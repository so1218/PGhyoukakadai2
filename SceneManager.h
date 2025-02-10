#pragma once
#include "Structures.h"
#include "GameBaseInfo.h"

class SceneManager
{
public:
    // シーンの列挙クラス
    enum class Scene
    {
        Title = 0,
        Select = 1,
        Play = 2,
    };

    // コンストラクタ
    SceneManager();
    // デストラクタ
    ~SceneManager();

    // セッター
    void SetScene(Scene scene);

    // ゲッター
    Scene GetCurrentScene() const;

private:
    Scene currentScene;
};
