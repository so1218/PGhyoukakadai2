#include "Bullet.h"
#include "Player.h"

Bullet::Bullet()
{
    // 弾の数を設定
    data.resize(pinsCount);
    bullets.resize(pinsCount);

    for (int i = 0; i < pinsCount; ++i) {
        data[i].velocity_.x = 0.0f;
        data[i].velocity_.y = 0.0f;
        data[i].speed_ = 18.0f;
        data[i].ro_.width = 32;
        data[i].ro_.height = 32;
        data[i].ro_.sDrawVertex.LT = { -data[i].ro_.width / 2, data[i].ro_.height / 2 };
        data[i].ro_.sDrawVertex.LB = { -data[i].ro_.width / 2, -data[i].ro_.height / 2 };
        data[i].ro_.sDrawVertex.RT = { data[i].ro_.width / 2, data[i].ro_.height / 2 };
        data[i].ro_.sDrawVertex.RB = { data[i].ro_.width / 2, -data[i].ro_.height / 2 };
        data[i].ro_.radius = { 10,10 };
        data[i].ro_.color = 0x0000ffff;
        bullets[i].startPos_ = {0.0f};
        bullets[i].goalPos_ = { 0.0f };
        bullets[i].dir_ = { 1.0f,0.0f };
        bullets[i].preDir_ = {};
        bullets[i].angle_ = 0.0f;
        bullets[i].length_ = 0.0f;
        bullets[i].isActive_ = false;
        bullets[i].isStickWall_ = false;
        bullets[i].isGlobalEasingActive_ = false;
        bullets[i].coolTimeInterval_ = 60;
        bullets[i].coolTime_ = 0;
        bullets[i].preLineRect_.width = 150;
        bullets[i].preLineRect_.height = 10;
        bullets[i].padPos_ = {};
        bullets[i].preLineRect_.sDrawVertex.LT = { -bullets[i].preLineRect_.width / 2, bullets[i].preLineRect_.height / 2 };
        bullets[i].preLineRect_.sDrawVertex.LB = { -bullets[i].preLineRect_.width / 2, -bullets[i].preLineRect_.height / 2 };
        bullets[i].preLineRect_.sDrawVertex.RT = { bullets[i].preLineRect_.width / 2, bullets[i].preLineRect_.height / 2 };
        bullets[i].preLineRect_.sDrawVertex.RB = { bullets[i].preLineRect_.width / 2, -bullets[i].preLineRect_.height / 2 };
        bullets[i].preLineRect_.color = 0xFFFF0055;
        bullets[i].predictionLength_ = 150.0f;
        bullets[i].attractEase_ = std::make_unique<Easing>();
        camera_ = std::make_unique<Camera>();;
        
    }
    
}

Bullet::~Bullet()
{

}

void Bullet::ConvertScreenToWorld(const IntVector2& screenPos, IntVector2& worldPos)
{
    worldPos.x = screenPos.x;
    worldPos.y = screenPos.y - kWindowHeight;
    worldPos.y *= -1;

    // カメラの回転を適用
    float cosTheta = cosf(camera_->theta);
    float sinTheta = sinf(camera_->theta);

    // 回転後のワールド座標を計算
    float rotatedX = worldPos.x * cosTheta - worldPos.y * sinTheta;
    float rotatedY = worldPos.x * sinTheta + worldPos.y * cosTheta;

    worldPos.x = static_cast<int>(rotatedX);
    worldPos.y = static_cast<int>(rotatedY);

}

// ピンの動きの処理
void Bullet::Move(Player* player)
{
    // マウス座標の取得と座標変換
    for (int i = 0; i < pinsCount; ++i) 
    {
        if (bullets[i].coolTime_ > 0) 
        {
            bullets[i].coolTime_ -= 1; 
            if (bullets[i].coolTime_ < 0) 
            {
                bullets[i].coolTime_ = 0;  
            }
        }

        Novice::GetMousePosition(&bullets[i].screenMousePos_.x, &bullets[i].screenMousePos_.y);
        ConvertScreenToWorld(bullets[i].screenMousePos_, bullets[i].worldMousePos_);

        bullets[i].playerLocalWorldMousePos_.x = bullets[i].worldMousePos_.x - (int)player->GetRectangle()->wPos.x + (int)camera_->pos.x - kWindowWidth / 2;
        bullets[i].playerLocalWorldMousePos_.y = bullets[i].worldMousePos_.y - (int)player->GetRectangle()->wPos.y + (int)camera_->pos.y - kWindowHeight / 2;

         //ピン発射処理
         //右クリックが押されたとき
        if (KeyManager::IsKeyJustPressed(DIK_SPACE))
        {   
            if (!bullets[i].isActive_ && bullets[i].coolTime_ == 0)
            {  
                // 自機から発射
                
                bullets[i].length_ = sqrtf(powf(bullets[i].dir_.x, 2) + powf(bullets[i].dir_.y, 2));

              

                // 自機位置に弾をセット
                data[i].ro_.wPos.x = player->GetRectangle()->wPos.x;
                data[i].ro_.wPos.y = player->GetRectangle()->wPos.y;

                // 正規化した方向ベクトルに速度を掛けて発射
                data[i].velocity_.x = bullets[i].dir_.x * data[i].speed_;
                data[i].velocity_.y = bullets[i].dir_.y * data[i].speed_;

                // 弾をアクティブに
                bullets[i].isActive_ = true;

                break; // 発射されたらループを抜ける
            }
        }

        //// 発射されたピンの移動処理
        if (bullets[i].isActive_)
        {
            data[i].ro_.wPos.x += data[i].velocity_.x;
            data[i].ro_.wPos.y += data[i].velocity_.y;

            // 壁に当たった場合
            if (data[i].ro_.wPos.x>1300) {
                bullets[i].isActive_ = false;
            }
            
        }



        // カメラの回転行列を計算
        data[i].ro_.theta = atan2f(bullets[i].dir_.y, bullets[i].dir_.x);
        camera_->MakeCameraMatrix(&data[i].ro_);
        camera_->MakeCameraMatrix(&bullets[i].preLineRect_);
    }
}

//Pinの描画処理
void Bullet::Draw()
{
    for (int i = 0; i < pinsCount; ++i)
    {
        BlendModeFunc::UpdateBlendMode(BlendModeType::Normal);

        if (bullets[i].isActive_)  
        {
            Novice::DrawEllipse(
                (int)data[i].ro_.sPos.x,
                (int)data[i].ro_.sPos.y,
                (int)data[i].ro_.radius.x, 
                (int)data[i].ro_.radius.y, 
                0.0f, 
                data[i].ro_.color,
                kFillModeSolid);
        }
       
        BlendModeFunc::ResetBlendMode();
     
      
    }
}

void Bullet::Init()
{
    for (int i = 0; i < pinsCount; ++i) {
        data[i].velocity_.x = 0.0f;
        data[i].velocity_.y = 0.0f;
        data[i].speed_ = 18.0f;
        data[i].ro_.width = 32;
        data[i].ro_.height = 32;
        data[i].ro_.sDrawVertex.LT = { -data[i].ro_.width / 2, data[i].ro_.height / 2 };
        data[i].ro_.sDrawVertex.LB = { -data[i].ro_.width / 2, -data[i].ro_.height / 2 };
        data[i].ro_.sDrawVertex.RT = { data[i].ro_.width / 2, data[i].ro_.height / 2 };
        data[i].ro_.sDrawVertex.RB = { data[i].ro_.width / 2, -data[i].ro_.height / 2 };
        data[i].ro_.radius = { 10,10 };
        data[i].ro_.color = 0x0000ffff;
        bullets[i].startPos_ = { 0.0f };
        bullets[i].goalPos_ = { 0.0f };
        bullets[i].dir_ = { 1.0f,0.0f };
        bullets[i].preDir_ = {};
        bullets[i].angle_ = 0.0f;
        bullets[i].length_ = 0.0f;
        bullets[i].isActive_ = false;
        bullets[i].isStickWall_ = false;
        bullets[i].isGlobalEasingActive_ = false;
        bullets[i].coolTimeInterval_ = 60;
        bullets[i].coolTime_ = 0;
        bullets[i].preLineRect_.width = 150;
        bullets[i].preLineRect_.height = 10;
        bullets[i].padPos_ = {};
        bullets[i].preLineRect_.sDrawVertex.LT = { -bullets[i].preLineRect_.width / 2, bullets[i].preLineRect_.height / 2 };
        bullets[i].preLineRect_.sDrawVertex.LB = { -bullets[i].preLineRect_.width / 2, -bullets[i].preLineRect_.height / 2 };
        bullets[i].preLineRect_.sDrawVertex.RT = { bullets[i].preLineRect_.width / 2, bullets[i].preLineRect_.height / 2 };
        bullets[i].preLineRect_.sDrawVertex.RB = { bullets[i].preLineRect_.width / 2, -bullets[i].preLineRect_.height / 2 };
        bullets[i].preLineRect_.color = 0xFFFF0055;
        bullets[i].predictionLength_ = 150.0f;
        

    }
}