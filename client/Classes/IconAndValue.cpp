#include "IconAndValue.h"

#include "cocos2d.h"

#include "CocosHelper.h"
#include "Settings.h"

USING_NS_CC;
using namespace std;

bool IconAndValue::Init(Layer* layer, float width, float top,
	const string& iconFile, int value, float fontSize)
{
	char buf[64];

	sprintf(buf, "%d", value);
	_valueLabel = Label::createWithTTF(buf, MY_FONT, fontSize);
	Point valueLabelRT(width, top);
	_valueLabel->setAnchorPoint(ANCHOR_RT);
	_valueLabel->setPosition(valueLabelRT);
	layer->addChild(_valueLabel);

	_iconSprite = Sprite::create(iconFile);
	Point iconSpriteRM(valueLabelRT.x - _valueLabel->getContentSize().width,
		valueLabelRT.y - _valueLabel->getContentSize().height*.5f);
	_iconSprite->setAnchorPoint(ANCHOR_RM);
	_iconSprite->setPosition(iconSpriteRM);
	CocosHelper::ScaleSpriteByHeight(_iconSprite, _valueLabel->getContentSize().height);
	layer->addChild(_iconSprite);

	return false;
}

void IconAndValue::AlignLeft()
{
}

void IconAndValue::AlignCenter()
{
	Point iconSpriteRM = _iconSprite->getPosition();
	Point valueLabelRT = _valueLabel->getPosition();

	float iconHoriMargin = (iconSpriteRM.x - _iconSprite->getContentSize().width) * .5f;
	iconSpriteRM.x -= iconHoriMargin;
	valueLabelRT.x -= iconHoriMargin;
	_iconSprite->setPosition(iconSpriteRM);
	_valueLabel->setPosition(valueLabelRT);
}

float IconAndValue::GetBottom()
{
	return _valueLabel->getPosition().y - _valueLabel->getContentSize().height;
}
