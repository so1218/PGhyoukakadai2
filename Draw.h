#pragma once
#include "Structures.h"
#include "GameBaseInfo.h"

class DrawShapes
{
public:
    // 矩形の描画関数
    static void QuadWithData(RectangleObject* ro, float srcW, float srcH, int GH, int spriteNumX, int spriteNumY, unsigned int color);
};
