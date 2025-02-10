#pragma once

#include "GameBaseInfo.h"
extern int GHs[128];

//テキスチャの名前を作成
enum TextureName
{
	// テクスチャの数
	COUNT,
};

class TextureManager 
{
public:
	// テクスチャを読み込む関数
	static void LoadTextures();
};