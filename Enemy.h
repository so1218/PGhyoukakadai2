#pragma once
#include "GameBaseInfo.h"
#include "AfterImage.h"
#include "Calculate.h"  
#include "Bullet.h"

const int enemyAmount = 10;

class Enemy:public ObjectBaseInfo
{
public:
	
	Enemy();
	~Enemy();

	
	void Update();
	void Draw();
	void Init();
	std::unique_ptr<Camera> camera_;
	std::unique_ptr<AfterImage> afterImage_;
	std::unique_ptr<Bullet> bullet_;

	// ゲッター
	bool GetIsAttacked() const {return isAttacked_;}

	// セッター
	void SetIsAttacked(bool attacked) {isAttacked_ = attacked;}

private:
	Vector2 kGravity_;
	bool isAirResistance_;
	bool isAfterImage_;
	bool isAttacked_;
	
};

class EnemyManager
{
public:
	std::vector<std::unique_ptr<Enemy>> enemies;
	
	EnemyManager();

	void Init();
	void Update();
	void Draw();

	// セッター
	void setScore(int score) {
		score_ = score;
	}

	// スコアを加算するセッター
	void addScore(int value) {
		score_ += value;
	}

	// ゲッター
	int getScore() const {
		return score_;
	}
private:
	int frameCount_;
	int appearInterval_;
	bool isCollisionEnemy_;
	int score_;

};