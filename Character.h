#pragma once

#include "Structures.h"
#include "Function.h"

class Character
{
public:

public:
    struct Data 
    {
        //メンバ変数
        Vector2 pos_;
        Vector2 velocity_;
        Vector2 acceleration_;
        float speed_;
        int width_;
        int height_;
        unsigned int color_ = WHITE;
        float gravity_;
        RectangleObject ro_;
        int GH_ = 0;
    };
    Data data;

public:
  
protected:

};