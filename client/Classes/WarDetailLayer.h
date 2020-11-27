#ifndef __WAR_DETAIL_LAYER_H__
#define __WAR_DETAIL_LAYER_H__

#include "cocos2d.h"

#include "CocosHelper.h"

class WarDetailLayer : public cocos2d::LayerColor
{
public:
	FUNC_CREATE_WITH_COLOR(WarDetailLayer);

	FUNC_POST_INIT_WITH_COLOR();
};

#endif // __WAR_DETAIL_LAYER_H__
