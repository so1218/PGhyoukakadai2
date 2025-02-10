#pragma once

#include "Structures.h"
#include "Draw.h"
#include "Rectangle.h"
#include "Camera.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Easing.h"


enum ChipType
{
    none,
    block,
};

class MapChip: ObjectBaseInfo
{
public:
    // コンストラクタで初期化
    MapChip()
    {
        ro_.width = width_;
        ro_.height = height_;

        //colorEase_ = std::make_unique<Easing>();
    }

    // メンバ関数

    // ゲッターとセッター
    // チップの位置を設定
    Vector2 GetPosition() const { return pos_; }
    void SetPosition(float newPosX, float newPosY)
    {
        pos_.x = newPosX;
        pos_.y = newPosY;
        ro_.wPos.x = newPosX + width_ / 2;
        ro_.wPos.y = newPosY + height_ / 2;
    }

    // メンバ変数
    float GetHeight() const { return height_; }
    void SetHeight(float newHeight) { height_ = newHeight; }

    float GetWidth() const { return width_; }
    void SetWidth(float newWidth) { width_ = newWidth; }

    unsigned int GetColor() const { return color_; }
    void SetColor(unsigned int newColor) { color_ = newColor; }

    int GetChipType() const { return chipType_; }
    void SetChipType(int newChipType) { chipType_ = newChipType; }

    RectangleObject& GetRectangleObject() { return ro_; }
    void SetRectangleObject(const RectangleObject& newRectangle) { ro_ = newRectangle; }   

   
private:
    // メンバ変数
    int chipType_ = 0;
    Vector2 pos_;
    float height_ = 50.0f;
    float width_ = 50.0f;
    unsigned int color_ = WHITE;
        
    // Rectangleオブジェクト
    RectangleObject ro_;


};

class Map
{
public:
    //コンストラクタで初期化
    Map()
    {
        // チップの座標と角を設定
        for (int i = 0; i < kFloorHeight; ++i)
        {
            for (int j = 0; j < kFloorWidth; ++j)
            {
                chip[i][j].SetPosition(float((j * chip[i][j].GetWidth())),
                float(kWindowHeight - chip[i][j].GetHeight() - (i * chip[i][j].GetHeight())));
            }
        }

        rgColorEase_ = std::make_unique<Easing>();
        gbColorEase_ = std::make_unique<Easing>();
        brColorEase_ = std::make_unique<Easing>();

        rgColorEase_->isEase = true;

    }

    //メンバ関数
    void SetMap();
    void DrawMap(/*Camera* camera*/);

    bool collisionCheck(float wx, float wy);
    bool collisionCharaLeft(float wx, float wy);
    bool collisionCharaRight(float wx, float wy);
    bool collisionCharaTop(float wx, float wy);
    bool collisionCharaBottom(float wx, float wy);

    //メンバ変数
    //ゲッターとセッター
    static int GetFloorWidth() { return kFloorWidth; }
    static int GetFloorHeight() { return kFloorHeight; }

    int GetStageNo() const { return stageNo_; }
    void SetStageNo(int newStage) { stageNo_ = newStage; }

    MapChip& GetChip(int x, int y)
    {
        if (x >= 0 && x < kFloorWidth && y >= 0 && y < kFloorHeight)
        {
            return chip[y][x];
        }
        //エラーチェック
        static MapChip defaultChip;
        return defaultChip;
    }

    void SetChip(int x, int y, const MapChip& mapChip)
    {
        if (x >= 0 && x < kFloorWidth && y >= 0 && y < kFloorHeight)
        {
            chip[y][x] = mapChip;
        }
    }

    unsigned int color_=0xffffffff;
    int timer_=0;
    unsigned int preColor_ = 0xffffffff;
    unsigned int endColor_ = 0xffffffff;
    std::unique_ptr<Easing> rgColorEase_;
    std::unique_ptr<Easing> gbColorEase_;
    std::unique_ptr<Easing> brColorEase_;


    // マップをCSVファイルから読み込む関数
    //void SetMapFromCSV()
    //{
    //    std::string filename = "MapData/map.csv";
    //    std::ifstream file(filename);
    //    std::string line;
    //    int row = 0;
    //    // ファイルを1行ずつ読み込む
    //    while (std::getline(file, line))
    //    {
    //        std::stringstream ss(line);
    //        std::string value;
    //        int col = 0;

    //        // CSVの各値を読み込んでchipDataに設定
    //        while (std::getline(ss, value, ','))
    //        {
    //            chipData[0][row][col] = std::stoi(value);  // 数字として格納
    //            col++;
    //        }
    //        row++;
    //    }
    //    file.close();
    //}

private:
    static const int kFloorWidth = 19;
    static const int kFloorHeight = 32;
    static const int stageSum = 1;
  
    //メンバ変数
    int stageNo_ = 0;

    Vector2 lineStartPos;
    Vector2 lineEndPos;

    Vector2 pos;
    float easingTimer = 0.0f;

    //チップの配列
    MapChip chip[kFloorHeight][kFloorWidth];
};