#include "Hit.h"
#include "Calculate.h"

//========================================================
// 当たり判定の関数
//========================================================

//矩形と矩形の当たり判定の関数
//bool CheckRectangleRectangleCollision(RectangleObject* rect1, RectangleObject* rect2)
//{
//    if (rect1->wVertex.RT.x < rect2->wVertex.LT.x)
//        return false;
//   
//    if (rect1->wVertex.LT.x > rect2->wVertex.RT.x)
//        return false;
//    
//    if (rect1->wVertex.LT.y < rect2->wVertex.RB.y)
//        return false;
//    
//    if (rect1->wVertex.RB.y > rect2->wVertex.LT.y)
//        return false;
//
//    // 矩形が重なっている
//    return true;
//}
//
////着地の当たり判定（ワールド座標）
bool CheckGround(float TLx1, float TLy1, float BRx1, float BRy1, float TLx2, float TLy2, float BRx2, float BRy2)
{
	bool ret = false;

	if ((TLx1 < BRx2) && (BRx1 > TLx2))
	{
		if ((TLy1 > BRy2) && (BRy1 < TLy2))
		{
			ret = true;
		}
	}

	return ret;
}

//void ApplyKnockback(Knockback* knockback, RectangleObject* rect1, RectangleObject* rect2, Vector2* beDonePos, Vector2* doPos)
//{
//	if (CheckRectangleRectangleCollision(rect1, rect2))
//	{
//
//		knockback->dir = { beDonePos->x - doPos->x, beDonePos->y - doPos->y };
//
//		knockback->normalizedDir = MathUtils::CalculateNormalize(knockback->dir);
//
//		knockback->vel_.x = knockback->normalizedDir.x * knockback->strength;
//		knockback->vel_.y = knockback->normalizedDir.y * knockback->strength;
//
//		knockback->isKnockback = true;
//	}
//
//	if (knockback->isKnockback)
//	{
//		knockback->vel_.x *= 0.95f;
//		knockback->vel_.y *= 0.95f;
//		beDonePos->x += knockback->vel_.x;
//		beDonePos->y += knockback->vel_.y;
//	}
//	if (fabs(knockback->vel_.x) < 0.1f || fabs(knockback->vel_.y) < 0.1f)
//	{
//		knockback->isKnockback = false;
//		knockback->vel_.x = 0.0f;
//		knockback->vel_.y = 0.0f;
//	}
//}

