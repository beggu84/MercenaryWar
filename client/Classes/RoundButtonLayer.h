#ifndef __ROUND_BUTTON_LAYER_H__
#define __ROUND_BUTTON_LAYER_H__

#include "cocos2d.h"

#include "GetterSetter.h"

class RoundButtonLayer : public cocos2d::Layer
{
private:
	uint32_t _id{ 0 };

public:
	CREATE_FUNC(RoundButtonLayer);

	virtual bool init();

	virtual bool onTouchBegin(cocos2d::Touch* touch, cocos2d::Event* unusedEvent);

	GETTER_SETTER(uint32_t, Id, _id);
};

#endif // __ROUND_BUTTON_LAYER_H__
