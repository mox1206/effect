#include "HelloWorldScene.h"
#include "Effect.h"
#include "EffectBlur.h"
#include "EffectGray.h"
#include "EffectCelShading.h"
#include "EffectEdgeDetection.h"
#include "EffectBloom.h"
#include "CardSprite.h"
#include "ShapeLayer.h"
#include "CustomPageView.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	
	//auto shapeLayer = ShapeLayer::create("HelloWorld.png");
	//this->addChild(shapeLayer);

	Size size = Director::getInstance()->getWinSize();

	Sprite *sprite = Sprite::create("HelloWorld.png");
	CustomPageView *pageView = CustomPageView::create(size / 4);
	pageView->setPosition(size / 2);
	pageView->addPage(sprite);
	this->addChild(pageView);

    return true;
}
