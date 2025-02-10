#include "GameBaseInfo.h"

ObjectBaseInfo::ObjectBaseInfo()
{
	pos_ = {};
	prePos_ = {};
	startPos_ = {};
	endPos_;
	screenPos_ = {};
	vel_ = {};
	velMax_ = {};
	firstVel_ = {};
	acc_ = {};
	eDir_ = {};
	airResistance_ = {};
	airResistanceAcc_ = {};
	fricForce_ = {};
	fricNormalForce_ = {};
	fricDir_ = {};

	speed_ = 0;
	width_ = 0;
	height_ = 0;
	radius_ = 0;
	theta_ = 0;
	radian_ = 0;
	srcW_ = 0;
	srcH_ = 0;
	bounceFactor_ = 0;
	airResist_ = 0;
	fricMag_ = 0;
	miu_ = 0;
	airResist_ = 0;
	invincibleTime_ = 0;
	mass_ = 0;
	baseMass_ = 0;
	airDrag_ = 0;

	isExist_ = 0;
	canMoveUp_ = 0;
	canMoveDown_ = 0;
	canMoveLeft_ = 0;
	canMoveRight_ = 0;
	direction_ = Right;
	GH_ = 0;
	frameCount_ = 0;
	animeCount_ = 0;
	spriteNum_ = 0;
	color_ = 0xffffffff;
	startColor_ = 0xffffffff;
	endColor_ = 0xffffff00; 

	// 4つ角(更新処理用)
	leftTop_ = {};
	rightTop_ = {};
	leftBottom_ = {};
	rightBottom_ = {};
	// 4つ角(1フレーム前)
	leftTopPrev_ = {};
	rightTopPrev_ = {};
	leftBottomPrev_ = {};
	rightBottomPrev_ = {};
	// 4つ角(描画処理用)
	drawLeftTop_ = {};
	drawRightTop_ = {};
	drawLeftBottom_ = {};
	drawRightBottom_ = {};
	// 4つ角(スクリーン描画用)
	screenLeftTop_ = {};
	screenRightTop_ = {};
	screenLeftBottom_ = {};
	screenRightBottom_ = {};

	amplitude = 10.0f;
	currentChipNo = {};    
	nextChipNo = {};       
	startChipNo = {};
	isNextScene = 0;
}

char KeyManager::keys[256] = { 0 };
char KeyManager::preKeys[256] = { 0 };
//int KeyManager::numJoysticks = Novice::GetNumberOfJoysticks();
