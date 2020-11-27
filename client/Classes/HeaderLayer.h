#ifndef __HEADER_LAYER_H__
#define __HEADER_LAYER_H__

#include "cocos2d.h"

#include "GetterSetter.h"

class HeaderLayer : public cocos2d::Layer
{
private:
	float _height{ 0.f };

public:
	CREATE_FUNC(HeaderLayer);

    virtual bool init();

	GETTER(float, Height, _height);
};

#endif // __HEADER_LAYER_H__
