#include "Player.h"

Player::Player(Bullet* bullet)
{
    rect_.wPos.x = 150.0f;
    rect_.wPos.y = 300.0f;
    rect_.width = 100;
    rect_.height = 100;
    color_ = RED;
    gravity_ = 0.7f;
    vel_ = { 3.0f,3.0f };
    acc_ = { 0.1f };
    jumpSpeed_ = 20.0f;
    minJumpSpeed_ = -10.0f;
    isJumping_ = false;
    collisionCount_ = 1;
    isGrounded_ = true;
    velLimit_ = { 3.0f,7.0f };
   
    bullet_ = bullet;
    particle = std::make_unique<ParticleEmitter>();
    camera_ = std::make_unique<Camera>();
}

Player::~Player()
{

}

//========================================================
// プレイヤーの挙動
//========================================================
void Player::Move()
{
    if (KeyManager::IsKeyBeingPressed(DIK_W))
    {
        rect_.wPos.y += vel_.y;
    }
    if (KeyManager::IsKeyBeingPressed(DIK_S))
    {
        rect_.wPos.y -= vel_.y;
    }
    if (KeyManager::IsKeyBeingPressed(DIK_D))
    {
        rect_.wPos.x += vel_.x;
    }
    if (KeyManager::IsKeyBeingPressed(DIK_A))
    {
        rect_.wPos.x -= vel_.x;
    }
    
    bullet_->Move(this);
    camera_->MakeCameraMatrix(&rect_);
}

//========================================================
// プレイヤーの描画処理
//========================================================

//	プレイヤーの描画
void Player::Draw()
{
    // ピンの描画
    particle->Draw(0);
    bullet_->Draw();
    // プレイヤーの描画
    DrawShapes::QuadWithData(&rect_, 0, 0, 0, 0, 0, color_);

    
    // デバックの描画

#if defined(_DEBUG)
	
    /*ImGui::Begin("player");
    ImGui::DragInt("  playerisGrounded_", &isGrounded_);
    ImGui::DragFloat2("ro_.wCenterPos", &rect_.wPos.x, 0.01f);
    ImGui::DragFloat2("ro_.pos", &rect_.pos.x, 0.01f);

    ImGui::DragInt2(" ro_.currentChipNo.LT", &rect_.currentChipNo.LT.x);
    ImGui::DragInt2(" ro_.currentChipNo.RT", &rect_.currentChipNo.RT.x);
    ImGui::DragInt2(" ro_.currentChipNo.LB", &rect_.currentChipNo.LB.x);
    ImGui::DragInt2(" ro_.currentChipNo.RB", &rect_.currentChipNo.RB.x);
    ImGui::DragInt2(" ro_.wCenterCurrentChipNo", &rect_.wPosCurrentChipNo.x);
    ImGui::DragFloat2(" ro_.prePos ", &rect_.prePos.x);
    ImGui::DragFloat2(" ro_.wVertex.RT ", &rect_.wVertex.RT.x);
    ImGui::DragFloat2(" ro_.wVertex.LB ", &rect_.wVertex.LB.x);
    ImGui::DragFloat2("velocity_.x ", &vel_.x);
   
    ImGui::DragFloat(" velocity_.x ", &vel_.x);
    ImGui::End();*/
#endif
}

//========================================================
// プレイヤーの初期化
//========================================================

void Player::Init()
{
    rect_.wPos.x = 150.0f;
    rect_.wPos.y = 300.0f;
    rect_.width = 100;
    rect_.height = 100;
    color_ = RED;
    gravity_ = 0.7f;
    vel_ = { 3.0f,3.0f };
    acc_ = { 0.1f };
    jumpSpeed_ = 20.0f;
    minJumpSpeed_ = -10.0f;
    isJumping_ = false;
    collisionCount_ = 1;
    isGrounded_ = true;
    velLimit_ = { 3.0f,7.0f };

   /* particle->Init();*/
}

//プレイヤーの演出に関する初期化
void InitPlayerEffect()
{

}