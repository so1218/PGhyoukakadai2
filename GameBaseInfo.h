#pragma once

#if defined(_DEBUG)
#include <imgui.h>
#endif

#include "Structures.h"
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <vector>
#include <deque>
#include <math.h>
#include <memory>
#include <stdlib.h>
#include < algorithm >

const int kWindowWidth = 1300;
const int kWindowHeight = 700;
const int blockSize = 50;

class KeyManager
{
public:
    // キー入力結果を受け取る箱
    static char keys[256];
    static char preKeys[256];
    static int numJoysticks;
public:
    // コンストラクタ
    KeyManager()
    {
    }

    // キーが押された瞬間
    static bool IsKeyJustPressed(unsigned char key)
    {
        return keys[key] && !preKeys[key];
    }
    // キーが常に押されてるかどうか
    static bool IsKeyBeingPressed(unsigned char key)
    {
        return  keys[key];
    }
    // キーを離した瞬間
    static bool IsKeyJustReleased(unsigned char key)
    {
        return !keys[key] && preKeys[key];
    }
    // キーが常に押されてないかどうか
    static bool IsKeyBeingReleased(unsigned char key)
    {
        return !keys[key];
    }

    // ゲッター
    const char* GetKeys() const { return keys; }
    const char* GetPreKeys() const { return preKeys; }
    int GetNumJoysticks() const { return numJoysticks; }
};

// オブジェクトの向き
enum Direction
{
    Right,
    Left,
    Up,
    Down,
};

class ObjectBaseInfo
{
public:
    ObjectBaseInfo();

    // ゲッター
    RectangleObject* GetRectangle() {
        return &rect_;
    }
    Vector2 GetVel() const {
        return vel_;
    }
    float GetRadius() const {
        return radius_;
    }
    float GetMass() const {
        return mass_;
    }
    int GetIsExist() const {
        return isExist_;
    }

    // セッター
    void SetIsExist(int value) { isExist_ = value; }
    // スコアを加算するセッター
    void addSetVelX(float value) {
        vel_.x += value;
    }
    void addSetVelY(float value) {
        vel_.y += value;
    }
    

protected:
    // 2次元的要素
    Vector2 pos_;                // 座標
    Vector2 prePos_;             // 座標(1フレーム前)
    Vector2 startPos_;           // 初期座標
    Vector2 endPos_;             // 終端座標
    Vector2 screenPos_;          // 座標(スクリーン描画用)
    Vector2 vel_;                // 速度
    Vector2 velMax_;             // 速度上限
    Vector2 firstVel_;           // 初期速度
    Vector2 acc_;                // 加速度
    Vector2 eDir_;                //位置の単位ベクトル
    Vector2 scale_;
    Vector2 airResistance_;
    Vector2 airResistanceAcc_;
    Vector2 fricForce_;
    Vector2 fricNormalForce_;
    Vector2 fricDir_;

    // フロートまとめ
    float speed_;                // 速度
    float width_;                // 幅
    float height_;               // 高さ
    float radius_;               // 半径
    float theta_;                // 角度
    float radian_;               // ラジアン
    float gravity_;
    float srcW_;
    float srcH_;
    float bounceFactor_;
    float airResist_;
    float fricMag_;
    float baseMass_;
    float mass_;   
    float miu_;
    float airDrag_;

    // フラグ
    int isExist_;                // 生存フラグ
    int invincibleTime_;         // 無敵時間
    int canMoveUp_;              // 上に進めるか
    int canMoveDown_;            // 下に進めるか
    int canMoveLeft_;            // 左に進めるか
    int canMoveRight_;           // 右に進めるか
    Direction direction_;        // 向き
    int GH_;                     // 画像
    int frameCount_;             // フレームカウント
    int animeCount_;             // アニメーションカウント
    int spriteNum_;
    unsigned int color_;          // カラー
    unsigned int startColor_;     // 初期カラー
    unsigned int endColor_;       // 終端カラー

    // 4つ角(更新処理用)
    Vector2 leftTop_;
    Vector2 rightTop_;
    Vector2 leftBottom_;
    Vector2 rightBottom_;
    // 4つ角(1フレーム前)
    Vector2 leftTopPrev_;
    Vector2 rightTopPrev_;
    Vector2 leftBottomPrev_;
    Vector2 rightBottomPrev_;
    // 4つ角(描画処理用)
    Vector2 drawLeftTop_;
    Vector2 drawRightTop_;
    Vector2 drawLeftBottom_;
    Vector2 drawRightBottom_;
    // 4つ角(スクリーン描画用)
    Vector2 screenLeftTop_;
    Vector2 screenRightTop_;
    Vector2 screenLeftBottom_;
    Vector2 screenRightBottom_;

    float amplitude = 10.0f;
    IntVector2 currentChipNo;       //現在いるチップのナンバー格納
    IntVector2 nextChipNo;          //次回いるチップのナンバー格納
    IntVector2 startChipNo;
    bool isNextScene = false;
    RectangleObject rect_;
};