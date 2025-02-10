#include "Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

    // ゲームの初期化と実行
    Game game;
    game.Init();
    game.Run();

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}