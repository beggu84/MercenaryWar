#include "WarBriefCompanyLayer.h"

#include "Settings.h"
#include "IconAndValue.h"
#include "RoundButton.h"

#include "Win32Utf8Cpp.h"

USING_NS_CC;
using namespace std;

bool WarBriefCompanyLayer::PostInit()
{
	const Size& LAYER_SIZE = this->getContentSize();

	const float CENTER = LAYER_SIZE.width*.5f;

	char buf[32];

	int companies[3] = { 0, 10, 100 };
	int total = companies[rand() % 3];
	sprintf(buf, "용병단: %d", total);
	Label* totalSizeLabel = Label::createWithTTF(buf, MY_FONT, NORMAL_FONT_SIZE);
	Point totalSizeLabelCT(CENTER, LAYER_SIZE.height);
	totalSizeLabel->setAnchorPoint(ANCHOR_CT);
	totalSizeLabel->setPosition(totalSizeLabelCT);
	this->addChild(totalSizeLabel);

	if (total > 0)
	{
		int totalForce = 10000;
		IconAndValue totalForceLine;
		totalForceLine.Init(this, LAYER_SIZE.width,
			totalSizeLabelCT.y - totalSizeLabel->getContentSize().height - VERT_SHORT_MARGIN,
			"Force.png", totalForce, SMALL_FONT_SIZE);
		totalForceLine.AlignCenter();
	}

	bool myJoin = (rand() % 2 == 0);
	const float MY_TOP = LAYER_SIZE.height * .6f;
	const Color3B DARK_RED(180.f, 0.f, 0.f);

	if (total > 0 && myJoin)
	{
		Label* myJoinLabel = Label::createWithTTF("참여", MY_FONT, NORMAL_FONT_SIZE);
		Point myJoinLabelCT(CENTER, MY_TOP);
		myJoinLabel->setAnchorPoint(ANCHOR_CT);
		myJoinLabel->setPosition(myJoinLabelCT);
		this->addChild(myJoinLabel, 1);

		const Size& myJoinLabelSize = myJoinLabel->getContentSize();
		Sprite* cancelButtonSprite = Sprite::create("Cancel.png");
		cancelButtonSprite->setColor(DARK_RED);
		Point cancelButtonSpriteLM(CENTER + myJoinLabelSize.width*.5f + TO_REAL(3.f),
			myJoinLabelCT.y - myJoinLabelSize.height*.55f);
		cancelButtonSprite->setAnchorPoint(ANCHOR_LM);
		cancelButtonSprite->setPosition(cancelButtonSpriteLM);
		CocosHelper::ScaleSpriteByHeight(cancelButtonSprite, myJoinLabelSize.height*.9f);
		this->addChild(cancelButtonSprite);

		int myForce = 1000;
		IconAndValue myForceLine;
		myForceLine.Init(this, LAYER_SIZE.width,
			myJoinLabelCT.y - myJoinLabel->getContentSize().height - VERT_SHORT_MARGIN,
			"Force.png", myForce, SMALL_FONT_SIZE);
		myForceLine.AlignCenter();

		int myReward = 100;
		IconAndValue myRewardLine;
		myRewardLine.Init(this, LAYER_SIZE.width, myForceLine.GetBottom() - VERT_SHORT_MARGIN,
			"Reward.png", myReward, SMALL_FONT_SIZE);
		myRewardLine.AlignCenter();
	}
	else
	{
		RoundButton joinButton(rand() % 300);
		joinButton.Init(this, "참여", Color3B::BLACK, BIG_FONT_SIZE,
			DARK_RED, HORI_SHORT_MARGIN, VERT_NORMAL_MARGIN);
		Point joinButtonCM(CENTER, MY_TOP * .5f);
		joinButton.SetPosition(ANCHOR_CM, joinButtonCM);
	}

	return true;
}
