#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "network/HttpClient.h"

using namespace cocos2d::network;

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);

    virtual bool init();

	virtual void update(float delta);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void onHttpRequestCompleted(HttpClient* sender, HttpResponse* response);
};

#endif // __MAIN_SCENE_H__
