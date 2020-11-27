#include "WarBriefCountryLayer.h"

#include "Settings.h"
#include "IconAndValue.h"

#include "Win32Utf8Cpp.h"

USING_NS_CC;
using namespace std;

bool WarBriefCountryLayer::PostInit()
{
    const Size& LAYER_SIZE = this->getContentSize();
    
	const float CENTER = LAYER_SIZE.width*.5f;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Flags.plist", "Flags.png");
	Sprite* flagSprite = Sprite::createWithSpriteFrameName("Italy.png");
	Point flagSpriteCT(CENTER, LAYER_SIZE.height);
    flagSprite->setAnchorPoint(ANCHOR_CT);
    flagSprite->setPosition(flagSpriteCT);
	const float flagSpriteHeight = LAYER_SIZE.height * .35f;
    const float flagSpriteScale = flagSpriteHeight / flagSprite->getContentSize().height;
	const float flagSpriteWidth = flagSprite->getContentSize().width * flagSpriteScale;
	flagSprite->setContentSize(Size(flagSpriteWidth, flagSpriteHeight));
    this->addChild(flagSprite);
    
	string name("Italy");
	Label* nameLabel = Label::createWithTTF(name, MY_FONT, NORMAL_FONT_SIZE);
	Point nameLabelCT(CENTER,
		flagSpriteCT.y - flagSpriteHeight - VERT_NORMAL_MARGIN);
	nameLabel->setAnchorPoint(ANCHOR_CT);
	nameLabel->setPosition(nameLabelCT);
	this->addChild(nameLabel);

	int force = 100000;
	IconAndValue forceLine;
	forceLine.Init(this, LAYER_SIZE.width,
		nameLabelCT.y - nameLabel->getContentSize().height - VERT_SHORT_MARGIN,
		"Force.png", force, SMALL_FONT_SIZE);
	forceLine.AlignCenter();

	int reward = 1000;
	IconAndValue rewardLine;
	rewardLine.Init(this, LAYER_SIZE.width, forceLine.GetBottom() - VERT_SHORT_MARGIN,
		"Reward.png", reward, SMALL_FONT_SIZE);
	rewardLine.AlignCenter();

	return true;
}
