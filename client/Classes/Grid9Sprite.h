#ifndef __GRID9_SPRITE_H__
#define __GRID9_SPRITE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

class Grid9Sprite : public cocos2d::extension::Scale9Sprite
{
public:
	static cocos2d::Sprite* create(const char* fileName,
		const cocos2d::Size& spriteSize, int minTextureSize=16, int maxTextureSize=64,
		float wishCornerSize =5.f, int minCornerSize=5, int unitCornerSize=5);

	//static cocos2d::extension::Scale9Sprite* createWithSize(const std::string& file,
	//	float textSize, float cornerSize);
	static cocos2d::extension::Scale9Sprite* createWithScaledSize(const std::string& file,
		float scaledTextSize, float scaledCornerSize);
};

#endif // __GRID9_SPRITE_H__
