#include "WarListLayer.h"

#include "WarBriefLayer.h"

#include "cocos-ext.h"
#include "Settings.h"

#include "Win32Utf8Cpp.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

bool WarListLayer::PostInit()
{
	const Size& LAYER_SIZE = this->getContentSize();

	// header
	Label* offenceLabel = Label::createWithTTF("공격", MY_FONT, NORMAL_FONT_SIZE);
	Point offenceLabelCT(LAYER_SIZE.width*.25f, LAYER_SIZE.height - VERT_LONG_MARGIN);
	offenceLabel->setAnchorPoint(ANCHOR_CT);
	offenceLabel->setPosition(offenceLabelCT);
	this->addChild(offenceLabel, 1);

	Label* defenceLabel = Label::createWithTTF("방어", MY_FONT, NORMAL_FONT_SIZE);
	Point defenceLabelCT(LAYER_SIZE.width*.75f, LAYER_SIZE.height - VERT_LONG_MARGIN);
	defenceLabel->setAnchorPoint(ANCHOR_CT);
	defenceLabel->setPosition(defenceLabelCT);
	this->addChild(defenceLabel, 1);

	float headerHeight = offenceLabel->getContentSize().height + VERT_LONG_MARGIN * 2.f;
	LayerColor* headerLayer = LayerColor::create(GRAY4(80.f));
	Point headerLayerLB(0.f, LAYER_SIZE.height - headerHeight);
	headerLayer->setContentSize(Size(LAYER_SIZE.width, headerHeight));
	headerLayer->setPosition(headerLayerLB);
	this->addChild(headerLayer, 0);

	LayerColor* centerLineLayer = LayerColor::create(Color4B::GRAY);
	Point centerLineLayerLB(LAYER_SIZE.width*.5f, LAYER_SIZE.height - offenceLabel->getContentSize().height - VERT_LONG_MARGIN);
	centerLineLayer->setContentSize(Size(1.f, offenceLabel->getContentSize().height));
	centerLineLayer->setPosition(centerLineLayerLB);
	this->addChild(centerLineLayer, 1);

	// footer
	const float FOOTER_HEIGHT = 2.f;
	LayerColor* footerLayer = LayerColor::create(GRAY4(80.f));
	footerLayer->setContentSize(Size(LAYER_SIZE.width, FOOTER_HEIGHT));
	footerLayer->setPosition(ORIGIN);
	this->addChild(footerLayer);

	// body
	LayerColor* bodyLayer = LayerColor::create(GRAY4(30.f));
	//LayerGradient* bodyLayer = LayerGradient::create(Color4B::WHITE, Color4B::BLACK); // for test
	bodyLayer->setContentSize(Size(LAYER_SIZE.width, LAYER_SIZE.height - headerHeight - FOOTER_HEIGHT));
    
	ScrollView* scrollView = ScrollView::create(bodyLayer->getContentSize(), bodyLayer);
	scrollView->setDirection(ScrollView::Direction::VERTICAL);
	scrollView->setBounceable(false);
	scrollView->setPosition(Point(0.f, FOOTER_HEIGHT));
	this->addChild(scrollView);
	// change _touchListener->setSwallowTouches(true) of ScrollView::setTouchEnabled(...) to false!

	// list items
    size_t itemSize = 10;
    float ITEM_HEIGHT = Settings::Instance().GetWarBriefHeight();

	for (size_t i = 0; i < itemSize; i++)
	{
        float currItemBottom = i * ITEM_HEIGHT;

		WarBriefLayer* itemLayer = WarBriefLayer::create(GRAY4(50.f));
		itemLayer->SetId(i);
		//WarBriefLayer* itemLayer = WarBriefLayer::create(Color4B::YELLOW, Color4B::RED); // for test
		Point listItemLayerLB(0.f, currItemBottom);
		itemLayer->setContentSize(Size(LAYER_SIZE.width, ITEM_HEIGHT));
		itemLayer->setPosition(listItemLayerLB);
		itemLayer->PostInit();
		bodyLayer->addChild(itemLayer, 0);

		//if (i > 0)
		//{
			const float SEPARATOP_HEIGHT = 1.f;
			LayerColor* bottomLineLayer = LayerColor::create(Color4B::GRAY);
			bottomLineLayer->setContentSize(Size(LAYER_SIZE.width, SEPARATOP_HEIGHT));
			bottomLineLayer->setPosition(listItemLayerLB);
			bodyLayer->addChild(bottomLineLayer);
		//}
    }
    
    float itemTotalHeight = itemSize * ITEM_HEIGHT;
    float bodyContentHeight = bodyLayer->getContentSize().height;
    
    if (bodyContentHeight > itemTotalHeight)
    {
        float marginHeight = bodyContentHeight - itemTotalHeight;
        
        const Vector<Node*> itemLayers = bodyLayer->getChildren();
        for(Node* itemLayer : itemLayers)
        {
            Point itemLayerLB = itemLayer->getPosition();
            itemLayerLB.y += marginHeight;
            itemLayer->setPosition(itemLayerLB);
        }
    }
    else
    {
        bodyLayer->setContentSize(Size(LAYER_SIZE.width, itemTotalHeight));
    }

	return true;
}
