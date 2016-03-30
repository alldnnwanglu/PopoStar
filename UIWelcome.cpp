//
//  GameMainScene.cpp
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015年 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "UIWelcome.h"
#include "GameMainScene.h"
#include "UIManager.h"
#include "GameMap.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;


bool UIWelcome::init()
{
	m_fileName = "WelcomeUI.ExportJson";
	if( UIBase::init())
	{
		// parse
		m_pLoadGame = static_cast<UIButton*>(m_pWidget->getChildByName("loadGameBtn"));
		m_pStartGame = static_cast<UIButton*>(m_pWidget->getChildByName("starGameBtn"));
		
		// register Event
		m_pLoadGame->addTouchEventListener( this,toucheventselector(UIWelcome::loadGameCallBack));
		m_pStartGame->addTouchEventListener( this,toucheventselector(UIWelcome::starGameCallBack));

		return true;
	}
	return false;
}


void UIWelcome::starGameCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type )
{
	if(type == cocos2d::ui::TOUCH_EVENT_ENDED)
	{
		UIManager::GetInstance()->state = NewGame;
		CCDirector::sharedDirector()->purgeCachedData();
		CCScene* pScene = GameMainScene::scene();
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

void UIWelcome::loadGameCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type )
{
	if(type == cocos2d::ui::TOUCH_EVENT_ENDED)
	{
		UIManager::GetInstance()->state = LoadGame;
		CCDirector::sharedDirector()->purgeCachedData();
		CCScene* pScene = GameMainScene::scene();
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

UIWelcome::~UIWelcome()
{
	m_pStartGame = NULL;
	m_pLoadGame = NULL;
}
