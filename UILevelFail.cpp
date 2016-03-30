//
//  GameMainScene.cpp
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015年 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "UILevelFail.h"
#include "GameMap.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

bool UILevelFail::init()
{
	m_fileName = "LevelFail.ExportJson";
	if( UIBase::init() )
	{
		// parse
		m_pOkBtn = static_cast<UIButton*>(m_pWidget->getChildByName("okBtn"));
		m_pCanelBtn = static_cast<UIButton*>(m_pWidget->getChildByName("chanelBtn"));

		// register Event
		m_pOkBtn->addTouchEventListener( this,toucheventselector(UILevelFail::okBtnCallBack));
		m_pCanelBtn->addTouchEventListener( this,toucheventselector(UILevelFail::chanlBtnCallBack));

		deactivate();
		return true;
	}

	
	return false;
}

void UILevelFail::okBtnCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type )
{
	if(type == cocos2d::ui::TOUCH_EVENT_ENDED)
	{
		if(GameMap::GetInstance()->Buy( 20 ))
		{
			GameMap::GetInstance()->GoNoNetLevel();
		}
		else
		{
			GameMap::GetInstance()->LevelReset();
		}
		deactivate();
	}
}

void UILevelFail::chanlBtnCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type )
{
	if(type == cocos2d::ui::TOUCH_EVENT_ENDED)
	{
		GameMap::GetInstance()->LevelReset();
		deactivate();
	}
}



UILevelFail::~UILevelFail()
{
	m_pOkBtn = NULL;
	m_pCanelBtn = NULL;
}