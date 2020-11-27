#include "RoundButton.h"

#include "RoundButtonLayer.h"
#include "Grid9Sprite.h"
#include "CocosHelper.h"
#include "Settings.h"

USING_NS_CC;
using namespace std;

RoundButton::RoundButton(uint32_t id)
	: _id(id)
{

}

bool RoundButton::Init(Layer* parent, const string& text, const Color3B& textColor, float fontSize,
	const Color3B& backColor, float horiPadding, float vertPadding)
{
	_layer = RoundButtonLayer::create();
	_layer->SetId(_id);

	_label = Label::createWithTTF(text, MY_FONT, fontSize);
	_label->setColor(textColor);
	_label->setAnchorPoint(ANCHOR_LB);
	_label->setPosition(Point(horiPadding, vertPadding));
	_layer->addChild(_label, 1);

	const Size& labelSize = _label->getContentSize();
	Size buttonSize(labelSize.width + horiPadding*2.f,
		labelSize.height + vertPadding*2.f);

	_sprite = Grid9Sprite::create(ROUND_BUTTON, buttonSize);
	_sprite->setColor(backColor);
	_sprite->setAnchorPoint(ANCHOR_LB);
	_sprite->setPosition(ORIGIN);
	_layer->addChild(_sprite, 0);
	
	_layer->setContentSize(buttonSize);

	parent->addChild(_layer);

	return true;
}

void RoundButton::SetPosition(const Vec2& anchorPoint, const Vec2& position)
{
	if (_layer == nullptr || _sprite == nullptr || _label == nullptr)
		return;

	const Size& layerSize = _layer->getContentSize();

	Point layerLB(position.x - layerSize.width*anchorPoint.x,
		position.y - layerSize.height*anchorPoint.y);
	_layer->setPosition(layerLB);
}

const Size& RoundButton::GetSize()
{
	return _layer->getContentSize();
}
