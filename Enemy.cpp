#include "Enemy.h"

Enemy::Enemy()
{
	isExist_ = false;
	camera_ = std::make_unique<Camera>();
	afterImage_ = std::make_unique<AfterImage>();
	bullet_ = std::make_unique<Bullet>();
	theta_ = 1.0f;
	scale_ = { 1.0f,1.0f };
	bounceFactor_ = 1.0f;
	acc_ = { 0.0f,0.0f };
	mass_ = 1.0f;
	baseMass_ = 1.5f;
	miu_ = 0.0006f;
	gravity_ = -0.6f;
	kGravity_ = { 0, -9.8f };
	airDrag_ = 0.1f;
	airResistance_ = { airDrag_ * -vel_.x,airDrag_ * -vel_.y };
	airResistanceAcc_ = { airResistance_.x / mass_,airResistance_.y / mass_ };
	isAirResistance_ = false;
	isAfterImage_ = false;
	isAttacked_ = true;
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	if (!isExist_) 
	{
		rect_.wPos.x = static_cast<float>(1300);
		rect_.wPos.y = static_cast<float>(rand() % 400 + 200);
		radius_ = static_cast<float>(rand()) / RAND_MAX * 50.0f + 10.0f;
		vel_.x = -(static_cast<float>(rand()) / RAND_MAX * 5.0f + 1.0f);
		vel_.y = 0.0f;
		mass_ = baseMass_ * (radius_ / 30);
		isExist_ = true;
		airResistance_ = { airDrag_ * -vel_.x,airDrag_ * -vel_.y };
		airResistanceAcc_ = { airResistance_.x / mass_,airResistance_.y / mass_ };
	}
	if (isExist_)
	{
		if (rect_.wPos.y == 100.0f + radius_)
		{

			// 摩擦力を計算
			fricNormalForce_ = { -mass_ * kGravity_.x, -mass_ * kGravity_.y };
			fricMag_ = miu_ * MathUtils::Length(fricNormalForce_);
			Vector2 normalizedVelocity = MathUtils::CalculateNormalize(vel_);
			fricDir_ = { -normalizedVelocity.x, -normalizedVelocity.y };

			// 摩擦力ベクトルを計算
			fricForce_.x = fricMag_ * fricDir_.x;

			// 摩擦力を加速度として反映
			acc_.x = fricForce_.x / mass_;
		}
		else
		{
			acc_.x = 0.0f;
		}

		if (!isAirResistance_)
		{
			if (KeyManager::IsKeyJustPressed(DIK_F))
			{
				isAirResistance_ = true;
			}
		}
		else
		{
			if (KeyManager::IsKeyJustPressed(DIK_F))
			{
				isAirResistance_ = false;
			}

		}
		if (isAirResistance_)
		{
			airResistance_ = { airDrag_ * -vel_.x, airDrag_ * -vel_.y };
			airResistanceAcc_ = { airResistance_.x / mass_, airResistance_.y / mass_ };
		}
		else
		{
			airResistanceAcc_ = { 0,0 };
		}

		if (fabs(acc_.x / 60.0f) > fabs(vel_.x))
		{
			acc_.x = vel_.x * 60.0f + airResistanceAcc_.x;
		}

		// 速度に加速度を適用して更新
		vel_.x += acc_.x;

		// 速度の減衰（摩擦による影響）によって位置を更新
		rect_.wPos.x += vel_.x;

		// 重力の影響を計算
		acc_.y = gravity_ + airResistanceAcc_.y;
		vel_.y += acc_.y * mass_;
		rect_.wPos.y += vel_.y;
		if (rect_.wPos.y < 100.0f + radius_)
		{
			rect_.wPos.y = 100.0f + radius_;
			bounceFactor_ = 1.0f / (mass_ / 1.0f);
			if (bounceFactor_ > 1.0f) {
				bounceFactor_ = 0.95f;
			}

			vel_.y *= -(bounceFactor_);

		}
		if (rect_.wPos.x <= 100.0f + radius_)
		{
			isExist_ = false;
			isAttacked_ = true;
		}
		if (rect_.wPos.x >= 1400.0f + radius_)
		{
			isExist_ = false;
		}

		if (!isAfterImage_)
		{
			if (KeyManager::IsKeyJustPressed(DIK_G))
			{
				isAfterImage_ = true;
			}
		}
		else
		{
			if (KeyManager::IsKeyJustPressed(DIK_G))
			{
				isAfterImage_ = false;
			}
		}

		if (isAfterImage_)
		{
			afterImage_->UpdatePositionHistory(rect_.wPos);
		}
	}
	camera_->MakeCameraMatrix(&rect_);
}

void Enemy::Draw()
{
	Novice::DrawEllipse((int)rect_.sPos.x, (int)rect_.sPos.y , (int)radius_, (int)radius_, 0.0f, WHITE, kFillModeSolid);
	if (isAfterImage_)
	{
		afterImage_->DrawAfterImageCircle((int)radius_);
	}
	
}

bool CheckCollision(Enemy& enemy1, Enemy& enemy2)
{
	// 2つの敵の中心の距離
	float dx = enemy1.GetRectangle()->wPos.x - enemy2.GetRectangle()->wPos.x;
	float dy = enemy1.GetRectangle()->wPos.y - enemy2.GetRectangle()->wPos.y;
	float distance = sqrtf(dx * dx + dy * dy);

	// 衝突判定
	return distance < (enemy1.GetRadius() + enemy2.GetRadius());
}

void HandleCollision(Enemy& enemy1, Enemy& enemy2)
{
	// 衝突時の速度差
	Vector2 relativeVelocity = { enemy1.GetVel().x - enemy2.GetVel().x, enemy1.GetVel().y - enemy2.GetVel().y};

	// 衝突法線ベクトル（接線方向）
	Vector2 collisionNormal = { enemy1.GetRectangle()->wPos.x - enemy2.GetRectangle()->wPos.x, enemy1.GetRectangle()->wPos.y - enemy2.GetRectangle()->wPos.y };
	float distance = MathUtils::Length(collisionNormal);
	collisionNormal = { collisionNormal.x / distance, collisionNormal.y / distance };  // 単位ベクトル

	// 法線方向の速度差
	float velocityAlongNormal = relativeVelocity.x * collisionNormal.x + relativeVelocity.y * collisionNormal.y;

	// 反発係数（弾性衝突の割合）
	float e = 0.8f; // 弾性係数（0.8などの値に設定）

	// 衝突しない場合は何もしない
	if (velocityAlongNormal > 0)
		return;

	// 衝突後の速度の調整
	float impulse = -(1 + e) * velocityAlongNormal;
	impulse /= (1 / enemy1.GetMass() + 1 / enemy2.GetMass());

	// 速度を調整
	Vector2 impulseVector = { impulse * collisionNormal.x, impulse * collisionNormal.y };

	enemy1.addSetVelX(impulseVector.x / enemy1.GetMass());
	enemy1.addSetVelY(impulseVector.y / enemy1.GetMass());

	enemy2.addSetVelX(-impulseVector.x / enemy2.GetMass());
	enemy2.addSetVelY(-impulseVector.y / enemy2.GetMass());
}

EnemyManager::EnemyManager()
{
	for (int i = 0; i < enemyAmount; ++i)
	{
		enemies.push_back(std::make_unique<Enemy>());
		isCollisionEnemy_ = true;
	}
	score_ = 200;
}

void EnemyManager::Init()
{
	appearInterval_ = 100;
	frameCount_ = 0;
	score_ = 100;
}

void EnemyManager::Update() 
{
	if (frameCount_ <= 0)
	{
		frameCount_ = appearInterval_;
	}

	// 敵の存在判定
	for (int i = 0; i < enemyAmount; ++i)
	{
		if (frameCount_ == appearInterval_)
		{
			enemies[i]->SetIsExist(true);
		}
	}

	frameCount_--;

	// 衝突判定と反発処理
	if (!isCollisionEnemy_)
	{
		if (KeyManager::IsKeyJustPressed(DIK_H))
		{
			isCollisionEnemy_ = true;
		}
	}
	else
	{
		if (KeyManager::IsKeyJustPressed(DIK_H))
		{
			isCollisionEnemy_ = false;
		}
	}

	if (isCollisionEnemy_)
	{
		for (int i = 0; i < enemyAmount; ++i)
		{
			for (int j = i + 1; j < enemyAmount; ++j)
			{
				if (CheckCollision(*enemies[i], *enemies[j]))
				{
					HandleCollision(*enemies[i], *enemies[j]);
				}
			}
		}
	}

	for (int i = 0; i < enemyAmount; ++i)
	{
		enemies[i]->Update();

		// 画面外に出た敵の処理
		if (enemies[i]->GetIsAttacked())
		{
			// スコアを減らす例
			score_ -= 10; 
			enemies[i]->SetIsAttacked(false);
		}
	}
}

void EnemyManager::Draw()
{
	for (int i = 0; i < enemyAmount; ++i)
	{
		enemies[i]->Draw();
	}
}

void Enemy::Init()
{
	isExist_ = false;
	camera_ = std::make_unique<Camera>();
	afterImage_ = std::make_unique<AfterImage>();
	bullet_ = std::make_unique<Bullet>();
	theta_ = 1.0f;
	scale_ = { 1.0f,1.0f };
	bounceFactor_ = 1.0f;
	acc_ = { 0.0f,0.0f };
	mass_ = 1.0f;
	baseMass_ = 1.5f;
	miu_ = 0.0006f;
	gravity_ = -0.6f;
	kGravity_ = { 0, -9.8f };
	airDrag_ = 0.1f;
	airResistance_ = { airDrag_ * -vel_.x,airDrag_ * -vel_.y };
	airResistanceAcc_ = { airResistance_.x / mass_,airResistance_.y / mass_ };
	isAirResistance_ = false;
	isAfterImage_ = false;
	isAttacked_ = true;
}