#include "Grid9Sprite.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

Sprite* Grid9Sprite::create(const char* fileName,
	const Size& spriteSize, int minTextureSize, int maxTextureSize,
	float wishCornerSize, int minCornerSize, int unitCornerSize)
{
	float screenScaleFactor = Director::getInstance()->getContentScaleFactor();
	//CCLOG("screenScaleFactor: %f", screenScaleFactor);

	float minSpriteLength = min(spriteSize.width, spriteSize.height);

	int textureSize = minTextureSize;
	float scaledTextureSize;
	while (true)
	{
		scaledTextureSize = (float)textureSize / screenScaleFactor;
		if (scaledTextureSize >= minSpriteLength / 2.f || textureSize >= maxTextureSize)
			break;
		textureSize *= 2;
	}
	//CCLOG("textureSize: %d, scaledTextureSize: %f", textureSize, scaledTextureSize);

	int cornerSize = minCornerSize;
	float scaledCornerSize;
	while (true)
	{
		scaledCornerSize = (float)cornerSize / screenScaleFactor;
		if (scaledCornerSize >= wishCornerSize || cornerSize >= textureSize / 2 - unitCornerSize)
			break;
		cornerSize += unitCornerSize;
	}
	//CCLOG("cornerSize: %d, scaledCornerSize: %f", cornerSize, scaledCornerSize);

	char buf[64];
	sprintf(buf, "%s%d%d.png", fileName, textureSize, cornerSize);
	Sprite* sprite = Grid9Sprite::createWithScaledSize(buf, scaledTextureSize, scaledCornerSize);
	sprite->setContentSize(spriteSize);

	return sprite;
}

//Scale9Sprite* Grid9Sprite::createWithSize(const string& filename,
//	float textSize, float cornerSize)
//{
//	const float screenScaleFactor = Director::getInstance()->getContentScaleFactor();
//	return createWithScaledSize(filename, textSize*screenScaleFactor, cornerSize*screenScaleFactor);
//}

Scale9Sprite* Grid9Sprite::createWithScaledSize(const string& filename,
	float scaledTextSize, float scaledCornerSize)
{
	Rect rect(0.0f, 0.0f, scaledTextSize, scaledTextSize);
	Rect capInsets(scaledCornerSize, scaledCornerSize,
		scaledTextSize - scaledCornerSize*2.f, scaledTextSize - scaledCornerSize*2.f);

	Scale9Sprite* ret = new (nothrow) Scale9Sprite();
	if (ret && ret->initWithFile(filename, rect, capInsets))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}
