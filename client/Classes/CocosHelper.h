#ifndef __COCOS_HELPER_H__
#define __COCOS_HELPER_H__

#include "cocos2d.h"

const cocos2d::Point ORIGIN(0.f, 0.f);

const cocos2d::Point ANCHOR_CM(.5f, .5f);
const cocos2d::Point ANCHOR_LM(0.f, .5f);
const cocos2d::Point ANCHOR_RM(1.f, .5f);
const cocos2d::Point ANCHOR_CB(.5f, 0.f);
const cocos2d::Point ANCHOR_CT(.5f, 1.f);

const cocos2d::Point ANCHOR_LB(0.f, 0.f);
const cocos2d::Point ANCHOR_RB(1.f, 0.f);
const cocos2d::Point ANCHOR_LT(0.f, 1.f);
const cocos2d::Point ANCHOR_RT(1.f, 1.f);

#define GRAY3(value) cocos2d::Color3B(value, value, value)
#define GRAY4(value) cocos2d::Color4B(value, value, value, 255.f)

using TouchListener = cocos2d::EventListenerTouchOneByOne;

#define FUNC_CREATE_WITH_COLOR(__TYPE__) \
static __TYPE__* create(const cocos2d::Color4B& color) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->initWithColor(color)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

#define FUNC_CREATE_WITH_GRADIENT(__TYPE__) \
static __TYPE__* create(const cocos2d::Color4B& start, const cocos2d::Color4B& end) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->initWithColor(start, end)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

#define FUNC_POST_INIT() \
virtual bool init() \
{ \
    if ( !Layer::init() ) \
		return false; \
    return true; \
} \
\
bool PostInit()

#define FUNC_POST_INIT_WITH_COLOR() \
bool initWithColor(const cocos2d::Color4B& color) \
{ \
    if ( !LayerColor::initWithColor(color) ) \
		return false; \
    return true; \
} \
\
bool PostInit()

#define FUNC_POST_INIT_WITH_GRADIENT() \
bool initWithColor(const cocos2d::Color4B& start, const cocos2d::Color4B& end) \
{ \
    if ( !LayerGradient::initWithColor(start, end) ) \
		return false; \
    return true; \
} \
\
bool PostInit()

class CocosHelper
{
public:
	static float ScaleSpriteByWidth(cocos2d::Sprite* sprite, float scaledWidth);
	static float ScaleSpriteByHeight(cocos2d::Sprite* sprite, float scaledHeight);
};

#endif // __COCOS_HELPER_H__
