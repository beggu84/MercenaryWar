#include "RoundButtonLayer.h"

#include "Grid9Sprite.h"
#include "CocosHelper.h"
#include "Settings.h"

USING_NS_CC;
using namespace std;

bool RoundButtonLayer::init()
{
	if (!Layer::init())
		return false;

	TouchListener* listener = TouchListener::create();
	listener->onTouchBegan = CC_CALLBACK_2(RoundButtonLayer::onTouchBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

	return true;
}

bool RoundButtonLayer::onTouchBegin(Touch* touch, Event* unusedEvent)
{
	Point location = touch->getLocation();
	//CCLOG("touchLocation: %f, %f", location.x, location.y);

	//CCLOG("_position: %f, %f", _position.x, _position.y);
	Point worldLocation = this->convertToWorldSpace(_position);
	//CCLOG("worldLocation: %f, %f", worldLocation.x, worldLocation.y);

	Point realWorldLocation = worldLocation - _position;
	//CCLOG("realWorldLocation: %f, %f", worldLocation.x, worldLocation.y);
	Rect rect(realWorldLocation.x, realWorldLocation.y, _contentSize.width, _contentSize.height);

	if (rect.containsPoint(location))
	{
		CCLOG("id: %d", _id);
		return true;
	}

	return false;
}
