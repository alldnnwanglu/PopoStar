//
//  GameMainScene.cpp
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015年 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "GameMainScene.h"
#include "GameEntity.h"
#include "GameMap.h"
#include "UIDestoryStar.h"
#include "UIManager.h"
#include "SimpleAudioEngine.h"
#include "StarContainer.h"
#include "MusicManager.h"
#include "pay/SWXPayUI.h"

USING_NS_CC;

bool GameMainScene::init()
{
	if( !CCLayer::init() )
		return false;
	this->setKeypadEnabled( true );
	this->setTouchEnabled(true);
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	GameMap* gameMap = GameMap::GetInstance();
	this->addChild( gameMap );
	return true;
}

bool GameMainScene::ccTouchBegan( ::cocos2d::CCTouch *pTouches, ::cocos2d::CCEvent *pEvent)
{
	StarContainer* scoreModule = GameMap::GetInstance()->GetScoreModule();
	scoreModule->ClickStar(pTouches->getLocation());
	return true;
}

void GameMainScene::registerWithTouchDispatcher(void)
{
	CCLayer::registerWithTouchDispatcher();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void GameMainScene::keyBackClicked()
{
	if(UIManager::GetInstance()->getStopMenuUI()!=NULL)
	{
		UIManager::GetInstance()->getStopMenuUI()->activate();
	}
}

void GameMainScene::keyMenuClicked()
{
	if(UIManager::GetInstance()->getStopMenuUI()!=NULL)
	{
		UIManager::GetInstance()->getStopMenuUI()->activate();
	}
}

CCScene* GameMainScene::scene( )
{
	CCScene* pScene = CCScene::create();
	
	CCLayer* pLayer =  GameMainScene::create();
	pScene->addChild( pLayer );
	// init ui
	UIDestoryStar* pDestoryStar = UIDestoryStar::create();
	UILaoHuJi* pLaoHuiJi = UILaoHuJi::create();
	UIUseItem* pUseItem = UIUseItem::create();
	UISingleIn* pSingIn = UISingleIn::create();
	UILevelFail* pLevelFail = UILevelFail::create();
	StopMenuUI* pStopMenUI = StopMenuUI::create();
	SWXPayUI*	pPayUI = SWXPayUI::create();

	UIManager::GetInstance()->setUIDestoryStar( pDestoryStar );
	UIManager::GetInstance()->setUILaoHuJi( pLaoHuiJi );
	UIManager::GetInstance()->setUIUseItem( pUseItem );
	UIManager::GetInstance()->setUISingleIn( pSingIn );
	UIManager::GetInstance()->setUILevelFail( pLevelFail );
	UIManager::GetInstance()->setStopMenuUI( pStopMenUI );
	UIManager::GetInstance()->setPayUI(pPayUI);

	pScene->addChild( pDestoryStar );
	pScene->addChild( pLaoHuiJi );
	pScene->addChild( pUseItem );
	pScene->addChild( pSingIn );
	pScene->addChild( pLevelFail );
	pScene->addChild(pStopMenUI);
	pScene->addChild(pPayUI);
	pPayUI->deactivate();

	GameMap::GetInstance()->init();
	return pScene;
}


