#pragma once

#include "Structures.h"
#include "Camera.h"
#include "Map.h"
#include "Character.h"
#include "Bullet.h"
#include "Easing.h"
#include "Draw.h"
#include "Rectangle.h"
#include "Particle.h"
#include "Hit.h"
#include "GrovalTextureHandles.h"
#include "Function.h"
#include "Particle.h"

// プレイヤーの移動処理
class Player : public Character
{
public:
    // コンストラクタ
    Player(Bullet* pin);
    // デストラクタ
    ~Player();

    // ゲッター
    RectangleObject* GetRectangle() {
        return &rect_;
    }
    unsigned int GetColor() const {
        return color_;
    }

    // セッター
    void SetColor(unsigned int value) { color_ = value; }

private:

    // メンバ変数
    Vector2 pos_;
    Vector2 vel_;
    Vector2 acc_;
    float speed_;
    int width_;
    int height_;
    unsigned int color_ = WHITE;
    float gravity_;

    bool isJumping_;
    float jumpSpeed_;
    int isGrounded_;
    int collisionCount_;
    float maxJumpSpeed_ = 20.0f;
    float minJumpSpeed_;

    float jumpDuration_ = 0.0f;  // ジャンプを行うための時間（長押し時間）
    const float maxJumpTime_ = 60.0f;
    int numJumpStage_ = 16;
    float jumpStrength_ = 0;
    Vector2 velLimit_;

    DrawShapes* draw_;
    Direction direction_;
    RectangleObject rect_;

    Bullet* bullet_;
    std::unique_ptr<ParticleEmitter> particle;
    std::unique_ptr<Camera> camera_;
	
public:
    // ゲッター

    // セッター

public:
    // メンバ関数
    // プレイヤーの状態を管理するメンバ関数
    void Move();
    // プレイヤーの描画処理
    void Draw();
    // プレイヤーの初期化処理
    void Init();
    
private:
    
};





