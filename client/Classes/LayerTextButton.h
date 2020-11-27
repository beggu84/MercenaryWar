#ifndef __LAYER_TEXT_BUTTON_H__
#define __LAYER_TEXT_BUTTON_H__

#include "cocos2d.h"

#include "GetterSetter.h"

class LayerTextButton
{
private:
	cocos2d::Layer* _layer{ nullptr };
	cocos2d::Label* _label{ nullptr };

public:
	LayerTextButton() {}
	~LayerTextButton() {}

	bool Init(const cocos2d::Color4B& color, const std::string& text,
		const std::string& fontFilePath, float fontSize, float horiPadding=0.f, float vertPadding = 0.f);
	void SetPosition(const cocos2d::Vec2& anchorPoint, const cocos2d::Vec2& position);

	const cocos2d::Size& GetSize() { return _layer->getContentSize(); }

	GETTER(cocos2d::Layer*, Layer, _layer);
};

#endif // __LAYER_TEXT_BUTTON_H__
