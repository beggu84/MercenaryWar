#include "CocosHelper.h"

USING_NS_CC;
using namespace std;

float CocosHelper::ScaleSpriteByWidth(Sprite* sprite, float scaledWidth)
{
	const Size& spriteSize = sprite->getContentSize();

	float scale = scaledWidth / spriteSize.width;
	float scaledHeight = spriteSize.height * scale;
	sprite->setContentSize(Size(scaledWidth, scaledHeight));

	return scaledHeight;
}

float CocosHelper::ScaleSpriteByHeight(Sprite* sprite, float scaledHeight)
{
	const Size& spriteSize = sprite->getContentSize();

	float scale = scaledHeight / spriteSize.height;
	float scaledWidth = spriteSize.width * scale;
	sprite->setContentSize(Size(scaledWidth, scaledHeight));

	return scaledWidth;
}
