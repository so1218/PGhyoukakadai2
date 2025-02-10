#pragma once
#include <deque>
#include <algorithm>
#include "GameBaseInfo.h"
#include "Structures.h"
#include "Camera.h"

class AfterImage {
public:
    // 定数
    static const int maxHistory = 5;

    // コンストラクタ


    AfterImage() : frameCounter(0), colorAlpha(0.0f), scale(1.0f), isFading(false), fadeTimer(0) {}

    // 残像位置履歴
    std::deque<Vector2> posHistory;

    // 状態管理
    int frameCounter;
    Vector2 pastPos;

    // 見た目設定
    unsigned int colorRGB = 0xffffff;
    float colorAlpha;
    float scale;
    bool isFading;
    float fadeTimer;

    // メンバ関数
    void UpdatePositionHistory(Vector2 newPos) {

        frameCounter++;

        if (frameCounter >= 3)
        {
            posHistory.push_front(newPos);

            if (posHistory.size() > maxHistory)
            {
                posHistory.pop_back();
            }

            // フレームカウンタをリセット
           frameCounter = 0;
        }
    }

    void UpdateFade() {
        if (isFading) {
            for (int i = 0; i < posHistory.size(); ++i)
            {
                colorAlpha = 1.0f - (i / static_cast<float>(maxHistory));
            }
            if (colorAlpha <= 0.0f) {
                isFading = false;
            }
        }
    }

    void StartFading() {
        isFading = true;
        fadeTimer = 0.0f; // フェードタイマーをリセット
    }

    void DrawAfterImageRect(int width, int height, float srcW, float srcH, int GH, int spriteNumX, int spriteNumY, Camera* camera) const 
    {
      
        for (int i = 0; i < posHistory.size(); ++i)
        {

           
            // RGB を結合して colorRGB を計算
         
            Vector2 pos = posHistory[i];

            pos.x -= camera->pos.x;
            pos.y -= camera->pos.y;
            float alpha = colorAlpha - (i * 0.1f); // 後ろの方の履歴は透明度が高くなる
            //float scaleFactor = scale * (1.0f - (i * 0.1f)); // 後ろの方の履歴は小さくなる

            Novice::DrawQuad(
                static_cast<int>(pos.x),
                static_cast<int>(pos.y),
                static_cast<int>(pos.x) + width,
                static_cast<int>(pos.y),
                static_cast<int>(pos.x),
                static_cast<int>(pos.y) + height,
                static_cast<int>(pos.x) + width,
                static_cast<int>(pos.y) + height,
                int(srcW * spriteNumX), int(srcH * spriteNumY), int(srcW), int(srcH), GH, (0xffffff << 8) |
                static_cast<unsigned int>(alpha * 255));
        }
    }

    void DrawAfterImageCircle(int radius/*, Camera* camera*/) const
    {

        for (int i = 0; i < posHistory.size(); ++i)
        {


            // RGB を結合して colorRGB を計算

            Vector2 pos = posHistory[i];

         /*   pos.x -= camera->pos.x;
            pos.y -= camera->pos.y;*/
            float alpha = colorAlpha - (i * 0.1f); // 後ろの方の履歴は透明度が高くなる
            //float scaleFactor = scale * (1.0f - (i * 0.1f)); // 後ろの方の履歴は小さくなる

            Novice::DrawEllipse(
                (int)pos.x,
                kWindowHeight - (int)pos.y,
                radius,
                radius,
                0.0f,
                (0xffffff << 8) |
                static_cast<unsigned int>(alpha * 255),
                kFillModeSolid
            );
        }
    }
};
