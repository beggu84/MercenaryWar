#ifndef __ROUND_BUTTON_H__
#define __ROUND_BUTTON_H__

#include "cocos2d.h"

#include "GetterSetter.h"

class RoundButtonLayer;
class RoundButton
{
private:
	uint32_t _id{ 0 };
	RoundButtonLayer* _layer{ nullptr };
	cocos2d::Sprite* _sprite{ nullptr };
	cocos2d::Label* _label{ nullptr };

public:
	RoundButton(uint32_t id);

	bool Init(cocos2d::Layer* parent, const std::string& text, const cocos2d::Color3B& textColor, float fontSize,
		const cocos2d::Color3B& backColor, float horiPadding=0.f, float vertPadding = 0.f);
	void SetPosition(const cocos2d::Vec2& anchorPoint, const cocos2d::Vec2& position);
	const cocos2d::Size& GetSize();
};

#endif // __ROUND_BUTTON_H__
