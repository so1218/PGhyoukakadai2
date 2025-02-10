#include "Draw.h"

// 矩形の描画関数
void DrawShapes::QuadWithData(RectangleObject* ro, float srcW, float srcH, int GH, int spriteNumX, int spriteNumY, unsigned int color)
{
    Novice::DrawQuad(
        static_cast<int>(ro->sVertex.LT.x) + ro->shakingPos.x,
        static_cast<int>(ro->sVertex.LT.y) + ro->shakingPos.y,
        static_cast<int>(ro->sVertex.RT.x) + ro->shakingPos.x,
        static_cast<int>(ro->sVertex.RT.y) + ro->shakingPos.y,
        static_cast<int>(ro->sVertex.LB.x) + ro->shakingPos.x,
        static_cast<int>(ro->sVertex.LB.y) + ro->shakingPos.y,
        static_cast<int>(ro->sVertex.RB.x) + ro->shakingPos.x,
        static_cast<int>(ro->sVertex.RB.y) + ro->shakingPos.y,
        int(srcW * spriteNumX), int(srcH * spriteNumY), int(srcW), int(srcH), GH, color);
}

