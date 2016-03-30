//
//  GameMainScene.cpp
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015年 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "StopMenuUI.h"
#include "GameMap.h"
#if defined( PAY_WITH_UMENG )
#include "MobClickCpp.h"
#endif
USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

bool StopMenuUI::init()
{
	m_fileName = "StopMenu.ExportJson";
	if( UIBase::init() )
	{
		// parse
		m_pOkBtn = static_cast<UIButton*>(m_pWidget->getChildByName("okBtn"));
		m_pCanelBtn = static_cast<UIButton*>(m_pWidget->getChildByName("canelBtn"));

		// register Event
		m_pOkBtn->addTouchEventListener( this,toucheventselector(StopMenuUI::okBtnCallBack));
		m_pCanelBtn->addTouchEventListener( this,toucheventselector(StopMenuUI::chanlBtnCallBack));

		deactivate();
		return true;
	}

	
	return false;
}

void StopMenuUI::okBtnCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type )
{
	if(type == cocos2d::ui::TOUCH_EVENT_ENDED)
	{

		GameMap::GetInstance()->SaveLevel();
		deactivate();
	}
}

void StopMenuUI::chanlBtnCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type )
{
	if(type == cocos2d::ui::TOUCH_EVENT_ENDED)
	{
		GameMap::GetInstance()->SaveLevel();
		deactivate();
#if defined( PAY_WITH_UMENG )
		umeng::MobClickCpp::end();
#endif
		CCDirector::sharedDirector()->end();
	}
}



StopMenuUI::~StopMenuUI()
{
	m_pOkBtn = NULL;
	m_pCanelBtn = NULL;
}