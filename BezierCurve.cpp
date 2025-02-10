#include "Structures.h"
#include "Calculate.h"
#include "Easing.h"

//2次曲線のベジエ曲線


//3次曲線のベジエ曲線


// Catmull-Romスプライン関数
Vector2 CatmullRom(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, float t)
{
    // tの2乗と3乗を計算
    float t2 = t * t;
    float t3 = t2 * t;

    // x座標の計算
    float x = 0.5f * ((2.0f * p1.x) +
        (-p0.x + p2.x) * t +
        (2.0f * p0.x - 5.0f * p1.x + 4.0f * p2.x - p3.x) * t2 +
        (-p0.x + 3.0f * p1.x - 3.0f * p2.x + p3.x) * t3);

    // y座標の計算
    float y = 0.5f * ((2.0f * p1.y) +
        (-p0.y + p2.y) * t +
        (2.0f * p0.y - 5.0f * p1.y + 4.0f * p2.y - p3.y) * t2 +
        (-p0.y + 3.0f * p1.y - 3.0f * p2.y + p3.y) * t3);

    return Vector2{ x, y };
}