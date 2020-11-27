#ifndef __WAR_BRIEF_LAYER_H__
#define __WAR_BRIEF_LAYER_H__

#include "cocos2d.h"

#include "CocosHelper.h"
#include "GetterSetter.h"

class WarBriefLayer : public cocos2d::LayerColor
{
private:
	uint32_t _id{ 0 };

public:
	FUNC_CREATE_WITH_COLOR(WarBriefLayer);

	FUNC_POST_INIT_WITH_COLOR();

	GETTER_SETTER(uint32_t, Id, _id);
};

#endif // __WAR_BRIEF_LAYER_H__
