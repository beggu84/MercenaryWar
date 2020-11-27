#include "HeaderLayer.h"

#include "CocosHelper.h"
#include "Settings.h"

#include "Win32Utf8Cpp.h"

USING_NS_CC;
using namespace std;

// on "init" you need to initialize your instance
bool HeaderLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	const Size SCREEN_SIZE = Director::getInstance()->getVisibleSize();

	Point leftTop(VERT_NORMAL_MARGIN, SCREEN_SIZE.height - VERT_NORMAL_MARGIN);
	Point rightTop(SCREEN_SIZE.width - VERT_NORMAL_MARGIN, SCREEN_SIZE.height - VERT_NORMAL_MARGIN);
	Point leftBottom(0.f, 0.f);
	Point rightBottom(SCREEN_SIZE.width, 0.f);

	char buf[32];
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Atlas.plist", "Atlas.png");
	//Sprite* goldSprite = Sprite::createWithSpriteFrameName("Gold.png");

	// Name
	string name("참한 용병단");
	//Label* nameLabel = Label::createWithTTF(name, MY_FONT, 16.f);
	Label* nameLabel = Label::createWithTTF(name, MY_FONT, GREAT_FONT_SIZE);
	Point nameLabelLT(leftTop);
	nameLabel->setAnchorPoint(ANCHOR_LT);
	nameLabel->setPosition(nameLabelLT);
	this->addChild(nameLabel);

	_height = nameLabel->getContentSize().height + VERT_NORMAL_MARGIN * 2.f;

	// Gold - from right top corner
	int gold = 10000;
	sprintf(buf, "%d", gold);
	Label* goldLabel = Label::createWithTTF(buf, MY_FONT, NORMAL_FONT_SIZE);
	Point goldLabelRT(rightTop);
	goldLabel->setAnchorPoint(ANCHOR_RT);
	goldLabel->setPosition(goldLabelRT);
	this->addChild(goldLabel);

	const float SMALL_LABELS_HEIGHT = goldLabel->getContentSize().height;

	Sprite* goldSprite = Sprite::create("Gold.png");
	Point goldSpriteRT(goldLabelRT.x - goldLabel->getContentSize().width, rightTop.y);
	goldSprite->setAnchorPoint(ANCHOR_RT);
	goldSprite->setPosition(goldSpriteRT);
	float goldSpriteScale = SMALL_LABELS_HEIGHT / goldSprite->getContentSize().height;
	goldSprite->setScale(goldSpriteScale, goldSpriteScale);
	this->addChild(goldSprite);

	// Force - dependant to Gold
	int force = 100;
	sprintf(buf, "%d", force);
	Label* forceLabel = Label::createWithTTF(buf, MY_FONT, NORMAL_FONT_SIZE);
	Point forceLabelRT(goldSpriteRT.x - SMALL_LABELS_HEIGHT - SMALL_FONT_SIZE, rightTop.y);
	forceLabel->setAnchorPoint(ANCHOR_RT);
	forceLabel->setPosition(forceLabelRT);
	this->addChild(forceLabel);

	Sprite* forceSprite = Sprite::create("Force.png");
	Point forceSpriteRT(forceLabelRT.x - forceLabel->getContentSize().width, rightTop.y);
	forceSprite->setAnchorPoint(ANCHOR_RT);
	forceSprite->setPosition(forceSpriteRT);
	float forceSpriteScale = SMALL_LABELS_HEIGHT / forceSprite->getContentSize().height;
	forceSprite->setScale(forceSpriteScale, forceSpriteScale);
	this->addChild(forceSprite);

	// Honor - dependant to Honor
	int honor = 100;
	sprintf(buf, "%d", honor);
	Label* honorLabel = Label::createWithTTF(buf, MY_FONT, NORMAL_FONT_SIZE);
	Point honorLabelRT(forceSpriteRT.x - SMALL_LABELS_HEIGHT - SMALL_FONT_SIZE, rightTop.y);
	honorLabel->setAnchorPoint(ANCHOR_RT);
	honorLabel->setPosition(honorLabelRT);
	this->addChild(honorLabel);

	Sprite* honorSprite = Sprite::create("Honor.png");
	Point honorSpriteRT(honorLabelRT.x - honorLabel->getContentSize().width, rightTop.y);
	honorSprite->setAnchorPoint(ANCHOR_RT);
	honorSprite->setPosition(honorSpriteRT);
	float honorSpriteScale = SMALL_LABELS_HEIGHT / honorSprite->getContentSize().height;
	honorSprite->setScale(honorSpriteScale, honorSpriteScale);
	this->addChild(honorSprite);
    
    return true;
}
