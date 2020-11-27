#include "LayerTextButton.h"

#include "CocosHelper.h"

USING_NS_CC;
using namespace std;

bool LayerTextButton::Init(const Color4B& color, const string& text,
	const string& fontFile, float fontSize, float horiPadding, float vertPadding)
{
	_layer = LayerColor::create(color);
	if (_layer == nullptr)
		return false;

	_label = Label::createWithTTF(text, fontFile, fontSize);
	if (_label == nullptr)
		return false;

	_label->setAnchorPoint(ANCHOR_LB);
	_label->setPosition(Point(horiPadding, vertPadding));

	const Size& labelSize = _label->getContentSize();
	Size layerSize(labelSize.width + horiPadding*2.f,
		labelSize.height + vertPadding*2.f);
	_layer->setContentSize(layerSize);

	_layer->addChild(_label);

	return true;
}

void LayerTextButton::SetPosition(const Vec2& anchorPoint, const Vec2& position)
{
	if (_layer == nullptr || _label == nullptr)
		return;

	const Point& labelAnchor = _label->getAnchorPoint();
	const Size& labelSize = _label->getContentSize();

	Point layerLB(position.x - labelSize.width*anchorPoint.x,
		position.y - labelSize.height*anchorPoint.y);
	_layer->setPosition(layerLB);
}
