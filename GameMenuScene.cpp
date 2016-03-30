//
//  GameMainScene.cpp
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015Äê Bullets in a Burning Box, Inc. All rights reserved.
//

#include "GameMenuScene.h"
#include "GameEntity.h"
#include "GameMap.h"
#include "GameMainScene.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "UIManager.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

bool GameMenuScene::init()
{
	if ( !CCLayer::init() )
		return false;
	this->setKeypadEnabled(true);
	this->setTouchEnabled(true);
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCSprite* bgSprite = CCSprite::create("bg01.png");
	bgSprite->setAnchorPoint( ccp( 0 , 0 ));
	bgSprite->setPosition( ccp( 0 , 0 ));
	this->addChild(bgSprite);
	
	UIWelcome* uiWelcome = UIWelcome::create();
	UIManager::GetInstance()->setUIWelcome( uiWelcome );

	this->addChild( uiWelcome );

	return true;
}

void GameMenuScene::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}

void GameMenuScene::keyMenuClicked()
{
	CCDirector::sharedDirector()->end();
}

CCScene* GameMenuScene::scene()
{
	CCScene* scene = CCScene::create();
	GameMenuScene* layer = GameMenuScene::create();
	scene->addChild( layer );
	return scene;
}
