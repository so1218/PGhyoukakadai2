#include "Structures.h"
#include "Camera.h"
#include "Draw.h"
#include "Rectangle.h"
#include "Map.h"


//========================================================
// マップの設定、初期化
//========================================================

// マップの設定
void Map::SetMap()
{
    int static chipData[stageSum][kFloorHeight][kFloorWidth] =
    {
        {
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},



           
        }
    };

    // チップデータの設定
    for (int k = stageNo_; k < stageNo_ + 1; ++k)
    {
        for (int i = 0; i < kFloorHeight; ++i)
        {
            for (int j = 0; j < kFloorWidth; ++j)
            {

                chip[i][j].SetChipType(chipData[k][i][j]);



                CalcVertexRectangle(&chip[i][j].GetRectangleObject());


                switch (chip[i][j].GetChipType())
                {
                case none:
                    chip[i][j].SetColor(0x00000000);
                    break;
                case block:
                    
                    break;
                default:
                    break;
                }
            }
        }
    }

  
}

bool Map::collisionCheck(float wx, float wy) {
    // ワールド座標からマップDataの列colと行rowを求める
    int col = (int)wx / (int)blockSize;
    int row = (int)wy / (int)blockSize;
    // Dataの範囲外は判定できないので除外
    if ((col < 0) || (col >= kFloorWidth) || (row < 0) || (row >= kFloorHeight)) {
        return false;
    }
    // 次の記述で座標がマップチップの中に入っているか判定できる
    if (chip[row][col].GetChipType() == block)
    {
        return true;
    }
    return false;
}

// マップチップとキャラの左辺が重なっているか
bool Map::collisionCharaLeft(float wx, float wy) 
{
    bool leftTop = collisionCheck(wx, kWindowHeight - wy);
    bool leftBottom = collisionCheck(wx, kWindowHeight-(wy - 25));
    return leftTop || leftBottom;
}
// マップチップとキャラの右辺が重なっているか
bool Map::collisionCharaRight(float wx, float wy) 
{
    bool rightTop = collisionCheck(wx + 25, kWindowHeight - wy);
    bool rightBottom = collisionCheck(wx + 25, kWindowHeight - (wy - 25));
    return rightTop || rightBottom;
}
// マップチップとキャラの上辺が重なっているか
bool Map::collisionCharaTop(float wx, float wy)
{
    bool topLeft = collisionCheck(wx, kWindowHeight - wy);
    bool topRight = collisionCheck(wx + 25, kWindowHeight - wy);
    return topLeft || topRight;
}
// マップチップとキャラの下辺が重なっている、または、接しているか。ここだけ他と違う！
bool Map::collisionCharaBottom(float wx, float wy)
{
    // wy + Map.chipSizeをCheck関数に渡すことにより
    // キャラがマップチップと接しているかチェックできる。
    bool bottomLeft = collisionCheck(wx, kWindowHeight - (wy - 25));
    bool bottomRight = collisionCheck(wx + 25, kWindowHeight - (wy - 25));

    return bottomLeft || bottomRight;
}

unsigned int GenerateRandomColor() {
    // 各色コンポーネント (赤、緑、青、透明度) をランダムに生成
    unsigned char red = rand() % 128 + 128;    // 0〜255 のランダム値
    unsigned char green = rand() % 128 + 128;
    unsigned char blue = rand() % 128 + 128;
    unsigned char alpha = 255;  // 透明度（0〜255）

    // それぞれの色コンポーネントを8ビットシフトして unsigned int に結合
    return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

// マップの描画
void Map::DrawMap(/*Camera* camera*/)
{
    if (rgColorEase_->isEase)
    {
        rgColorEase_->SetEasing(EasingType::EaseOutCubic);
        rgColorEase_->Easing::CountEaseLinear(RED, GREEN, color_);
        if (!rgColorEase_->isEase)
        {
            gbColorEase_->isEase = true;
            preColor_ = color_;
            endColor_ = GenerateRandomColor();
        }
        
    }
    if (gbColorEase_->isEase)
    {
        gbColorEase_->SetEasing(EasingType::EaseOutCubic);
        gbColorEase_->Easing::CountEaseLinear(preColor_, endColor_, color_);
        if (!gbColorEase_->isEase)
        {
            brColorEase_->isEase = true;
            preColor_ = color_;
            endColor_ = GenerateRandomColor();
        }
    }
    if (brColorEase_->isEase)
    {
        brColorEase_->SetEasing(EasingType::EaseOutCubic);
        brColorEase_->Easing::CountEaseLinear(preColor_, endColor_, color_);
        if (!brColorEase_->isEase)
        {
            gbColorEase_->isEase = true;
            preColor_ = color_;
            endColor_ = GenerateRandomColor();
        }
    }
    for (int i = 0; i < kFloorHeight; ++i)
    {
        for (int j = 0; j < kFloorWidth; ++j)
        {
            if (chip[i][j].GetChipType() == none)
            {
                DrawShapes::QuadWithData(&chip[i][j].GetRectangleObject(), 0, 0, 0, 0, 0, chip[i][j].GetColor());
            }
            if (chip[i][j].GetChipType() == block)
            {
                DrawShapes::QuadWithData(&chip[i][j].GetRectangleObject(), 0, 0, 0, 0, 0, color_);
            }
        }
    }

    // グリッド線を描画する処理
    //for (int i = 0; i <= kFloorHeight; ++i) {
    //    // カメラ行列を使って、グリッド線の始点と終点の座標を変換
    //    Vector2 start = { -1275, (float)i * 50 - 25 };
    //    Vector2 end = { (float)kWindowWidth-1275, (float)i * 50 - 25 };

    //    // 座標変換を適用
    //    start = camera->Transform(start, camera->cameraMatrix);  // カメラ行列で変換
    //    end = camera->Transform(end, camera->cameraMatrix);      // 同上

    //    // 変換後の座標で線を描画
    //    Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, BLACK);
    //}

    //for (int i = 0; i <= kFloorWidth; ++i) {
    //    // カメラ行列を使って、グリッド線の始点と終点の座標を変換
    //    Vector2 start = { (float)i * 50 - 1275, -25 };
    //    Vector2 end = { (float)i * 50 - 1275, (float)kWindowHeight - 25 };

    //    // 座標変換を適用
    //    start = camera->Transform(start, camera->cameraMatrix);  // カメラ行列で変換
    //    end = camera->Transform(end, camera->cameraMatrix);      // 同上

    //    // 変換後の座標で線を描画
    //    Novice::DrawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, BLACK);
    //}

#if defined(_DEBUG)

#endif
}

