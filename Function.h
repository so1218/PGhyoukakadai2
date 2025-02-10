#pragma once

#include "GameBaseInfo.h"

enum BlendModeType
{
    None = 0,
    Normal = 1,
    Add = 2,
    Subtract = 3,
    Multiply = 4,
    Screen = 5,
    Exclusion = 6
};

class BlendModeFunc
{
public:

    // コンストラクタ
    BlendModeFunc()
    {}

    // ブレンドモードの更新処理
    static void UpdateBlendMode(int type);
   
    // ブレンドモードのリセット処理
    static void ResetBlendMode();
   
    // ゲッターとセッター
    static int GetMode() { return mode; }
    static void SetMode(int newMode) { mode = newMode; }

public:
    static int mode;
    
};