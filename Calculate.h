#pragma once

#include "Structures.h"
#include "GameBaseInfo.h"

class MathUtils
{
public:
    // 階乗関数
    static int Factorial(int n);
    // 指数関数
    static float Power(float t, int n);
    // 二項係数関数
    static int Binomial(int n, int k);
    // バーンスタイン基底関数
    static float Bernstein(int n, int i, float t);
    // 2点の距離の関数
    static float CalculateDistance(const Vector2& a, const Vector2& b);
    // ベクトルの長さの関数
    static float Length(const Vector2& vec);
    // ベクトルの正規化の関数
    static Vector2 CalculateNormalize(Vector2& vec);
    // 2Dベクトルの内積
    static float DotProduct2D(const Vector2& a, const Vector2& b);
    // 2Dベクトルの外積
    static float CrossProduct2D(const Vector2& a, const Vector2& b);
    // 回転の関数
    static Vector2 Rotate(Vector2 v, float angle);
};

