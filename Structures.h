#pragma once

#include <deque>
class GameBaseInfo;

struct Vector2
{
	float x = 0.0f;
	float y = 0.0f;
};

struct IntVector2
{
	int x = 0;
	int y = 0;
};

struct Vector3
{
	float x = 0;
	float y = 0;
	float z = 0;
};

//3x3行列の構造体
struct Matrix3x3
{
	float m[3][3];
};

// (T = Top, B = Bottom, L = Left, R = Right)
struct Vertex
{
	Vector2 LT = { -10,10 };
	Vector2 LB = { -10,-10 };
	Vector2 RT = { 10,10 };
	Vector2 RB = { 10,-10 };
};

// (T = Top, B = Bottom, L = Left, R = Right)
struct VertexOnMap
{
	IntVector2 LT;
	IntVector2 LB;
	IntVector2 RT;
	IntVector2 RB;
};

// 四角形の構造体
struct RectangleObject
{
	Vector2 pos;

	// 移動前の座標
	Vector2 prePos;

	// 移動後の座標
	Vector2 nextPos;

	Vector2 radius = { 0.0f, 0.0f };

	unsigned int color = 0x000000ff;

	//ワールド座標の中心の座標
	Vector2 wPos = { 0,0 };
	Vector2 preWPos = { 0,0 };
	IntVector2 wPosCurrentChipNo = {};

	Vector2 sPos = { 0,0 };
	Vector2 DrawPos = { 0,0 };

	// ワールド用の４つ角 
	Vertex wVertex;
	// スクリーン用の４つ角 
	Vertex sVertex;
	Vertex sDrawVertex;

	// 座標が移動する直前の4つ角の保管。当たり判定で使う。
	Vertex preVertex;

	VertexOnMap currentChipNo;
	VertexOnMap preChipNo;

	Vector2 scale = { 1.0f,1.0f };
	float theta = { 0.0f };
	float width = 40;
	float height = 40;

	IntVector2 shakingPos = {};
	bool isShake = false;
	int shakeDuration = 20;
	int shakeCounter = 0;
	int magnitude = 15;

};


//ノックバックの構造体
struct Knockback
{
	Vector2 dir;
	Vector2 normalizedDir;
	float strength = 10;
	
	bool isKnockback = false;
	bool isKnockbacked = false;
	int frameCount = 0;

	
};

//残像の構造体
//struct AfterImage
//{
//	std::deque<Vector2> posHistory;
//	static const int maxHistory = 10;
//	int frameCounter = 0;
//	Vector2 pastPos = {};
//
//	unsigned int colorRGB = 0x000000;
//	float colorAlpha = 0.0f;
//	float scale = 1.0f;
//	bool isFading = false;
//	float fadeTimer = 0;
//	
//};

//struct Particle
//{
//	bool isEmit = false;
//
//	unsigned int colorRGB = 0x000000;
//	unsigned int colorAlpha = 0xff;
//
//	float lifetime;
//	int elapsedTime = 0;
//	int direction;
//	float radius = 10.0f;
//	IntVector2 emitterRange = { 80,80 };
//	IntVector2 activeDistance = { 60,60 };
//	Vector2 speed = {};
//	float gravity = 0.7f;
//	int appearInterval = 20;
//	int randNum = 0;
//	Vector2 speedRange = { 2.0f,2.0f };
//	Vector2 speedAdd = { 1.0f,1.0f };
//
//	/*BlendModeFunc blendMode;*/
//	Knockback knockback;
//
//	//ベジエ曲線のデータ
//	Vector2 p0;
//	Vector2 p1;
//	Vector2 p2;
//	Vector2 p3;
//	Vector2 p4;
//	Vector2 p5;
//	Vector2 center;
//
//	bool hasExisted = false;
//
//	int amount;
//
//	AfterImage afterImage;
//	
//};
