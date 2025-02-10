#pragma once

#include "Structures.h"
#include "Character.h"
#include "Camera.h"
#include "Draw.h"
#include "Function.h"
#include "GrovalTextureHandles.h"
#include "Map.h"
#include "Easing.h"
//#include <imgui.h>
#include "GameBaseInfo.h"


const int pinsCount = 5;

class Player;

class Bullet : public Character
{
public:
	//コンストラクタ
	Bullet();
	//デストラクタ
	~Bullet();

public:
	void ConvertScreenToWorld(const IntVector2& screenPos, IntVector2& worldPos);
	void Move(Player* player);
	void Draw();
	void Init();

	// ゲッター
	Vector2 GetRectWPos(int index) { return data[index].ro_.wPos; }
	Vector2 GetRadius(int index) { return data[index].ro_.radius; }
	int GetIsActive(int index) { return bullets[index].isActive_; }

	// セッター
	void SetRectWPosX(int index, float valueX, float valueY)
	{
		data[index].ro_.wPos.x = valueX;
		data[index].ro_.wPos.y = valueY;
	}
	void SetIsRadiusX(int index, float value) { data[index].ro_.radius.x = value; }
	void SetIsActive(int index, int value) { bullets[index].isActive_ = value; }


private:
	struct Data
	{
		// マウス座標取得
		IntVector2 screenMousePos_;
		IntVector2 worldMousePos_;
		IntVector2 playerLocalWorldMousePos_;
		
		// 方向ベクトル
		Vector2 dir_;
		float angle_;
		float length_;
		// イージング用変数
		Vector2 startPos_;
		Vector2 goalPos_;
		float globalEasedT_;
		int isGlobalEasingActive_;
		// アクティブかどうか
		int isActive_;
		// 壁にくっついてるか
		int isStickWall_;
		// なにかしらのオブジェクトに当たったか
		int isObjectHit_;
		// 残り本数
		int isRemainingNumber_;
		float distance_;

		int coolTimeInterval_;
		int coolTime_;

		// パッド操作
		IntVector2 padPos_;

		// 予測線
		RectangleObject preLineRect_;
		Vector2 preDir_;
		float predictionLength_;

		std::unique_ptr<Easing> attractEase_;
	};
	std::vector<Data> bullets;
	std::vector<Character::Data> data;
	std::unique_ptr<Camera> camera_;
};
