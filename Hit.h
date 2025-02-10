#pragma once

#include "Structures.h"
#include "GameBaseInfo.h"

//矩形と矩形の当たり判定の関数
//bool CheckRectangleRectangleCollision(RectangleObject* rect1, RectangleObject* rect2);

bool CheckGround(float TLx1, float TLy1, float BRx1, float BRy1, float TLx2, float TLy2, float BRx2, float BRy2);

//void ApplyKnockback(Knockback* knockback, RectangleObject* rect1, RectangleObject* rect2, Vector2* beDonePos, Vector2* doPos);

