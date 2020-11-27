#include "MainScene.h"

//#include "SimpleAudioEngine.h"

#include "HeaderLayer.h"
#include "WarListLayer.h"

#include "CocosHelper.h"
#include "Settings.h"

#include "Win32Utf8Cpp.h"

USING_NS_CC;
using namespace std;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	const Size SCREEN_SIZE = Director::getInstance()->getVisibleSize();
	Settings::Instance().SetScreenWidth(SCREEN_SIZE.width);

	HeaderLayer* headerLayer = HeaderLayer::create();
	this->addChild(headerLayer);

	float headerHeight = headerLayer->GetHeight();

	Size warListLayerSize(SCREEN_SIZE.width, SCREEN_SIZE.height - headerHeight);
	WarListLayer* warListLayer = WarListLayer::create();
	warListLayer->setContentSize(warListLayerSize);
	warListLayer->PostInit();
	this->addChild(warListLayer);

	//----- footer -----
	//float scaleFactor = Director::getInstance()->getContentScaleFactor();
	//float imageSize = 128.f;
	//float cornerSize = 20.f;
	//float width = imageSize / scaleFactor;
	//float padding = cornerSize / scaleFactor;
	//Sprite* buttonSprite = Scale9Sprite::create("Button.png",
	//	Rect(0, 0, width, width),
	//	Rect(padding, padding, width-padding*2.f, width-padding*2.f));
	//Point buttonSpriteCM(SCREEN_SIZE.width * .5f, SCREEN_SIZE.height * .5f);
	//buttonSprite->setAnchorPoint(ANCHOR_CM);
	//buttonSprite->setPosition(buttonSpriteCM);
	//buttonSprite->setContentSize(Size(300.f, 200.f));
	//this->addChild(buttonSprite);



	//HttpRequest* request = new HttpRequest();

	//request->setUrl("http://localhost:4832/redirect");
	//request->setRequestType(HttpRequest::Type::GET);
	//request->setResponseCallback(this, httpresponse_selector(MainScene::onHttpRequestCompleted));

	//request->setTag("Get test");

	//HttpClient::getInstance()->send(request);

	//request->release();

	//scheduleUpdate();
    
    return true;
}

void MainScene::update(float delta)
{
	CCLOG("%f", delta);
}

void MainScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void MainScene::onHttpRequestCompleted(HttpClient* sender, HttpResponse* response)
{
	if (!response) return;

	if (strlen(response->getHttpRequest()->getTag()) != 0)
	{
		CCLOG("%s completed", response->getHttpRequest()->getTag());
	}

	long statusCode = response->getResponseCode();

	CCLOG("response code: %ld", statusCode);

	if (!response->isSucceed())
	{
		CCLOG("response failed");
		CCLOG("error buffer: %s", response->getErrorBuffer());
		return;
	}

	vector<char>* buffer = response->getResponseData();
	char str[256] = {};
	for (uint32_t i = 0; i < buffer->size(); i++)
	{
		sprintf(str, "%s%c", str, (*buffer)[i]);
	}
	CCLOG("%s", str);
}
