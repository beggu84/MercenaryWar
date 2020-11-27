#include "WarBriefLayer.h"

#include "WarBriefCountryLayer.h"
#include "WarBriefCompanyLayer.h"

#include "Settings.h"
#include "RoundButton.h"

#include "Win32Utf8Cpp.h"

USING_NS_CC;
using namespace std;

bool WarBriefLayer::PostInit()
{
    const float BOTTOM = 1.f;
    Size layerSize = this->getContentSize();
    layerSize.height -= BOTTOM;

	char buf[32];
    
	//----- remain time -----
	const float timeTop = layerSize.height - VERT_NORMAL_MARGIN;
	const float TIME_HORI_MARGIN = TO_REAL(1.f);

    int minute = 30;
    sprintf(buf, "%d", minute);
    Label* minuteValueLabel = Label::createWithTTF(buf, MY_FONT, SMALL_FONT_SIZE);
    Point minuteValueLabelRT(layerSize.width * .5f, timeTop);
    minuteValueLabel->setAnchorPoint(ANCHOR_RT);
    minuteValueLabel->setPosition(minuteValueLabelRT);
    this->addChild(minuteValueLabel);
    
    Label* minuteUnitLabel = Label::createWithTTF("m", MY_FONT, SMALL_FONT_SIZE);
    minuteUnitLabel->setColor(Color3B::YELLOW);
    Point minuteUnitLabelLT(layerSize.width * .5f, timeTop);
    minuteUnitLabel->setAnchorPoint(ANCHOR_LT);
    minuteUnitLabel->setPosition(minuteUnitLabelLT);
    this->addChild(minuteUnitLabel);
    
    Label* hourUnitLabel = Label::createWithTTF("h", MY_FONT, SMALL_FONT_SIZE);
    hourUnitLabel->setColor(Color3B::YELLOW);
    Point hourUnitLabelRT(minuteValueLabelRT.x
		- minuteValueLabel->getContentSize().width - TIME_HORI_MARGIN, timeTop);
    hourUnitLabel->setAnchorPoint(ANCHOR_RT);
    hourUnitLabel->setPosition(hourUnitLabelRT);
    this->addChild(hourUnitLabel);
    
    int hour = 1;
    sprintf(buf, "%d", hour);
    Label* hourValueLabel = Label::createWithTTF(buf, MY_FONT, SMALL_FONT_SIZE);
    Point hourValueLabelRT(hourUnitLabelRT.x
		- hourUnitLabel->getContentSize().width, timeTop);
    hourValueLabel->setAnchorPoint(ANCHOR_RT);
    hourValueLabel->setPosition(hourValueLabelRT);
    this->addChild(hourValueLabel);
    
    int second = 14;
    sprintf(buf, "%d", second);
    Label* secondValueLabel = Label::createWithTTF(buf, MY_FONT, SMALL_FONT_SIZE);
    Point secondValueLabelLT(minuteUnitLabelLT.x
		+ minuteUnitLabel->getContentSize().width + TIME_HORI_MARGIN, timeTop);
    secondValueLabel->setAnchorPoint(ANCHOR_LT);
    secondValueLabel->setPosition(secondValueLabelLT);
    this->addChild(secondValueLabel);
    
    Label* secondUnitLabel = Label::createWithTTF("s", MY_FONT, SMALL_FONT_SIZE);
    secondUnitLabel->setColor(Color3B::YELLOW);
    Point secondUnitLabelLT(secondValueLabelLT.x
		+ secondValueLabel->getContentSize().width, timeTop);
    secondUnitLabel->setAnchorPoint(ANCHOR_LT);
    secondUnitLabel->setPosition(secondUnitLabelLT);
    this->addChild(secondUnitLabel);

	//----- etc -----
	int state = rand() % 2;
	Sprite* stateSprite = Sprite::create(state == 0 ? "Ready.png" : "Battle.png");
	Point stateSpriteCM(layerSize.width*.5f, layerSize.height*.5f);
	stateSprite->setAnchorPoint(ANCHOR_CM);
	stateSprite->setPosition(stateSpriteCM);
	const float stateSpriteWidth = TO_REAL(20.f);
	CocosHelper::ScaleSpriteByWidth(stateSprite, stateSpriteWidth);
	this->addChild(stateSprite, 1);

	LayerColor* centerLineLayer = LayerColor::create(GRAY4(30.f));
	float centerLineHeight = layerSize.height
		- minuteValueLabel->getContentSize().height
		- (VERT_NORMAL_MARGIN * 3.f);
	centerLineLayer->setContentSize(Size(1.f, centerLineHeight));
	Point centerLineLayerLB(layerSize.width*.5f, VERT_NORMAL_MARGIN);
	centerLineLayer->setPosition(centerLineLayerLB);
	this->addChild(centerLineLayer, 0);

	RoundButton leftDetailButton(_id);
	leftDetailButton.Init(this, "자세히", Color3B::BLACK, SMALL_FONT_SIZE,
		Color3B::GRAY, HORI_SHORT_MARGIN, VERT_NORMAL_MARGIN);
	Point leftDetailButtonCT(layerSize.width*.25f, timeTop);
	leftDetailButton.SetPosition(ANCHOR_CT, leftDetailButtonCT);

	RoundButton RightDetailButton(_id);
	RightDetailButton.Init(this, "자세히", Color3B::BLACK, SMALL_FONT_SIZE,
		Color3B::GRAY, HORI_SHORT_MARGIN, VERT_NORMAL_MARGIN);
	Point RightDetailButtonCT(layerSize.width*.75f, timeTop);
	RightDetailButton.SetPosition(ANCHOR_CT, RightDetailButtonCT);

	//----- countries & companies -----
	const float emptyHalfWidth =
		layerSize.width*.5f - stateSpriteWidth*.5f - HORI_LONG_MARGIN*2.f;
	const float countryWidth = emptyHalfWidth * .45f;
	const float companyWidth = emptyHalfWidth * .55f;
	const float countryHeight = layerSize.height
		- leftDetailButton.GetSize().height - TO_REAL(5.f);
	const float companyHeight = countryHeight;

	// left - offence
	WarBriefCountryLayer* leftCountryLayer = WarBriefCountryLayer::create();
	Point leftCountryLayerLB(HORI_LONG_MARGIN, BOTTOM);
	leftCountryLayer->setPosition(leftCountryLayerLB);
	leftCountryLayer->setContentSize(Size(countryWidth, countryHeight));
	leftCountryLayer->PostInit();
	this->addChild(leftCountryLayer);

	WarBriefCompanyLayer* leftCompanyLayer = WarBriefCompanyLayer::create();
	Point leftCompanyLayerLB(layerSize.width*.5f - stateSpriteWidth*.5f
		- HORI_LONG_MARGIN - companyWidth, BOTTOM);
	leftCompanyLayer->setPosition(leftCompanyLayerLB);
	leftCompanyLayer->setContentSize(Size(companyWidth, companyHeight));
	leftCompanyLayer->PostInit();
	this->addChild(leftCompanyLayer);

	//Sprite* leftPlusSprite = Sprite::create("Plus.png");
	//leftPlusSprite->setColor(Color3B::YELLOW);
	//Point leftPlusSpriteCM(leftCompanyLayerLB.x, layerSize.height*.5f);
	//leftPlusSprite->setAnchorPoint(ANCHOR_CM);
	//leftPlusSprite->setPosition(leftPlusSpriteCM);
	//CocosHelper::ScaleSpriteByHeight(leftPlusSprite, layerSize.height * .1f);
	//this->addChild(leftPlusSprite);

	// right - defence
	WarBriefCountryLayer* rightCountryLayer = WarBriefCountryLayer::create();
	Point rightCountryLayerLB(layerSize.width - countryWidth
		- HORI_LONG_MARGIN, BOTTOM);
	rightCountryLayer->setPosition(rightCountryLayerLB);
	rightCountryLayer->setContentSize(Size(countryWidth, countryHeight));
	rightCountryLayer->PostInit();
	this->addChild(rightCountryLayer);

	WarBriefCompanyLayer* rightCompanyLayer = WarBriefCompanyLayer::create();
	Point rightCompanyLayerLB(layerSize.width*.5f
		+ stateSpriteWidth*.5f + HORI_LONG_MARGIN, BOTTOM);
	rightCompanyLayer->setPosition(rightCompanyLayerLB);
	rightCompanyLayer->setContentSize(Size(companyWidth, companyHeight));
	rightCompanyLayer->PostInit();
	this->addChild(rightCompanyLayer);

	//Sprite* rightPlusSprite = Sprite::create("Plus.png");
	//rightPlusSprite->setColor(Color3B::YELLOW);
	//Point rightPlusSpriteCM(rightCountryLayerLB.x, layerSize.height*.5f);
	//rightPlusSprite->setAnchorPoint(ANCHOR_CM);
	//rightPlusSprite->setPosition(rightPlusSpriteCM);
	//CocosHelper::ScaleSpriteByHeight(rightPlusSprite, layerSize.height * .1f);
	//this->addChild(rightPlusSprite);

	return true;
}
