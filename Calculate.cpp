#include "Calculate.h"  

// 階乗関数
int MathUtils::Factorial(int n)
{
    if (n < 2)
    {
        return 1;
    }
    return n * Factorial(n - 1);
}
// 指数関数
float MathUtils::Power(float t, int n)
{
    if (n < 1)
    {
        return 1.0f;
    }
    return t * Power(t, n - 1);
}
// 二項係数関数
int MathUtils::Binomial(int n, int k)
{
    return Factorial(n) / (Factorial(k) * Factorial(n - k));
}
// バーンスタイン基底関数
float MathUtils::Bernstein(int n, int i, float t)
{
    return static_cast<float>(Binomial(n, i)) * Power(t, i) * Power(1 - t, n - i);
}
// 2点の距離の関数
float MathUtils::CalculateDistance(const Vector2& a, const Vector2& b)
{
    return sqrtf((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}
// ベクトルの長さの関数
float MathUtils::Length(const Vector2& vec)
{
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}
// ベクトルの正規化の関数
Vector2 MathUtils::CalculateNormalize(Vector2& vec)
{
    float length = sqrtf(vec.x * vec.x + vec.y * vec.y);
    if (length == 0)
    {
        return Vector2(0, 0);
    }
    return Vector2(vec.x / length, vec.y / length);
}
// 2Dベクトルの内積
float MathUtils::DotProduct2D(const Vector2& a, const Vector2& b)
{
    return a.x * b.x + a.y * b.y;
}
// 2Dベクトルの外積
float MathUtils::CrossProduct2D(const Vector2& a, const Vector2& b)
{
    return a.x * b.y - a.y * b.x;
}
// 回転の関数
Vector2 MathUtils::Rotate(Vector2 v, float angle)
{
    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);
    return Vector2
    (
        cosAngle * v.x - sinAngle * v.y,
        sinAngle * v.x + cosAngle * v.y
    );
}
