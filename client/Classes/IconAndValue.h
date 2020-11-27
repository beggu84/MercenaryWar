#ifndef __ICON_AND_VALUE_H__
#define __ICON_AND_VALUE_H__

#include <string>

namespace cocos2d
{
	class Layer;
	class Sprite;
	class Label;
}

class IconAndValue
{
private:
	cocos2d::Sprite* _iconSprite{ nullptr };
	cocos2d::Label* _valueLabel{ nullptr };

public:
	bool Init(cocos2d::Layer* layer, float width, float top,
		const std::string& iconFile, int value, float fontSize);

	void AlignLeft();
	void AlignCenter();

	float GetBottom();
};

#endif // __ICON_AND_VALUE_H__
