//
//  GameMainScene.cpp
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015年 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "UIDestoryStar.h"
#include "GameMap.h"
#include "GameItemManager.h"
#include "UIManager.h"
#include "MusicManager.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

bool UIDestoryStar::init()
{

	// read json
	m_fileName = "DestoryStar.ExportJson";
	score = 0;
	level = 0;
	historyScroe = 0;
	money = 0;
	dtime = 0;
	if( UIBase::init() )
	{
		// parse top
		UIPanel* topMenuPanel = static_cast<UIPanel*>(m_pWidget->getChildByName("topMenuPanel"));
		m_pLevelLab = static_cast<UILabelAtlas*>(topMenuPanel->getChildByName("levelLab"));
		UIImageView* lsImg = static_cast<UIImageView*>(topMenuPanel->getChildByName("lsTitleImg"));
		m_pHistoryScoreLab =  static_cast<UILabelAtlas*>(lsImg->getChildByName("lsLab"));
		m_pStopMusicBtn = static_cast<UIButton*>(topMenuPanel->getChildByName("stopMusicBtn"));
		m_pOpenMusicBtn = static_cast<UIButton*>(topMenuPanel->getChildByName("openMusicBtn"));

		UIPanel* pointPanel = static_cast<UIPanel*>(topMenuPanel->getChildByName("pointPanel")); 
		m_pAddPointBtn = static_cast<UIButton*>(pointPanel->getChildByName("addPointBtn")); 
		m_pPointLab = static_cast<UILabelAtlas*>(pointPanel->getChildByName("pointLab"));
		UIPanel* goalPanel = static_cast<UIPanel*>(topMenuPanel->getChildByName("golaPanel"));
		m_pGoalScoreLab = static_cast<UILabelAtlas*>(goalPanel->getChildByName("goalLab"));

		// parse center
		UIPanel* centerPanel = static_cast<UIPanel*>(m_pWidget->getChildByName("centPanel"));
		UIImageView* bgTitleImg = static_cast<UIImageView*>(centerPanel->getChildByName("bgImg"));
		m_pScoreLab = static_cast<UILabelAtlas*>(bgTitleImg->getChildByName("holdScoreLab")); 
		m_pOpenLHJBtn = static_cast<UIButton*>(centerPanel->getChildByName("openLHJBtn"));

		// item btn parse
		UIImageView* buttomMenuImg = static_cast<UIImageView*>(m_pWidget->getChildByName("buttomMenuImg"));

		m_pDj101Btn = static_cast<UIButton*>( buttomMenuImg->getChildByName("dj_101Btn"));
		m_pDj102Btn = static_cast<UIButton*>( buttomMenuImg->getChildByName("dj_102Btn"));
		m_pDj103Btn = static_cast<UIButton*>( buttomMenuImg->getChildByName("dj_103Btn"));
		m_pDj104Btn = static_cast<UIButton*>( buttomMenuImg->getChildByName("dj_104Btn"));
		
		UIImageView* djTitleImg = static_cast<UIImageView*>(m_pDj101Btn->getChildByName("djTitleImg"));
		m_pDj101NumLab = static_cast<UILabelAtlas*>(djTitleImg->getChildByName("numLab"));

		djTitleImg = static_cast<UIImageView*>(m_pDj102Btn->getChildByName("djTitleImg"));
		m_pDj102NumLab = static_cast<UILabelAtlas*>(djTitleImg->getChildByName("numLab"));

		djTitleImg = static_cast<UIImageView*>(m_pDj103Btn->getChildByName("djTitleImg"));
		m_pDj103NumLab = static_cast<UILabelAtlas*>(djTitleImg->getChildByName("numLab"));

		djTitleImg = static_cast<UIImageView*>(m_pDj104Btn->getChildByName("djTitleImg"));
		m_pDj104NumLab = static_cast<UILabelAtlas*>(djTitleImg->getChildByName("numLab"));

		m_pPromptLab = static_cast<UILabel*>(m_pWidget->getChildByName("promptLab"));

		musicStoped = CCUserDefault::sharedUserDefault()->getBoolForKey("musicStop");

		m_pStopMusicBtn->setEnabled( false );
		m_pOpenMusicBtn->setEnabled( false );

		if( musicStoped )
		{
			m_pOpenMusicBtn->setEnabled( true );
			MusicManager::GetInstance()->Stop();
		}
		else
		{
			m_pStopMusicBtn->setEnabled( true );
			MusicManager::GetInstance()->Open();
		}

		// register event
		m_pOpenLHJBtn->addTouchEventListener( this , toucheventselector( UIDestoryStar::openLaoHuJiCallBack));
		m_pDj101Btn->addTouchEventListener( this,toucheventselector(UIDestoryStar::UseItem101CallBack));
		m_pDj102Btn->addTouchEventListener( this,toucheventselector(UIDestoryStar::UseItem102CallBack));
		m_pDj103Btn->addTouchEventListener( this,toucheventselector(UIDestoryStar::UseItem103CallBack));
		m_pDj104Btn->addTouchEventListener( this,toucheventselector(UIDestoryStar::UseItem104CallBack));

		m_pStopMusicBtn->addTouchEventListener( this,toucheventselector(UIDestoryStar::stopMusicCallBack));
		m_pOpenMusicBtn->addTouchEventListener( this,toucheventselector(UIDestoryStar::openMusicCallBack));

		m_pAddPointBtn->addTouchEventListener( this,toucheventselector(UIDestoryStar::addPointCallBack));
		// red score
		
		m_pDj101NumLab->setStringValue("10");
		m_pDj102NumLab->setStringValue("10");
		m_pDj103NumLab->setStringValue("6");
		m_pDj104NumLab->setStringValue("8");
		
		return true;
	}
	return false;
}

void UIDestoryStar::UseItem101CallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type )
{
	if(type == cocos2d::ui::TOUCH_EVENT_ENDED)
	{
		UIManager::GetInstance()->getUIUseItem()->use( Item_Lolly );
	}
	
}

void UIDestoryStar::openLaoHuJiCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type )
{
	if(type == cocos2d::ui::TOUCH_EVENT_ENDED && GameMap::GetInstance()->GetGameState() == NORMAL)
	{
		UIManager::GetInstance()->getUILaoHuJi()->setHiddent( false );
	}
}

void UIDestoryStar::UseItem102CallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type )
{
	if(type == cocos2d::ui::TOUCH_EVENT_ENDED)
	{
		UIManager::GetInstance()->getUIUseItem()->use( Item_Candy );
	}

}

void UIDestoryStar::UseItem103CallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type )
{
	if(type == cocos2d::ui::TOUCH_EVENT_ENDED)
	{
		UIManager::GetInstance()->getUIUseItem()->use( Item_Return );
	}

}

void UIDestoryStar::UseItem104CallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type )
{
	if(type == cocos2d::ui::TOUCH_EVENT_ENDED)
	{
		UIManager::GetInstance()->getUIUseItem()->use( Item_Refresh );
	}

}

void UIDestoryStar::SetPromptText(const char* text )
{
	m_pPromptLab->setText( text );
}

void UIDestoryStar::stopMusicCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type )
{
	if(type == cocos2d::ui::TOUCH_EVENT_ENDED)
	{
		m_pStopMusicBtn->setEnabled( false );
		m_pOpenMusicBtn->setEnabled( true );

		MusicManager::GetInstance()->Stop();
		CCUserDefault::sharedUserDefault()->setBoolForKey("musicStop",true);
	}
}

void UIDestoryStar::openMusicCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type )
{
	if(type == cocos2d::ui::TOUCH_EVENT_ENDED)
	{
		m_pStopMusicBtn->setEnabled( true );
		m_pOpenMusicBtn->setEnabled( false );

		MusicManager::GetInstance()->Open();
		CCUserDefault::sharedUserDefault()->setBoolForKey("musicStop",false);
	}
}

void UIDestoryStar::addPointCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type )
{
	if(type == cocos2d::ui::TOUCH_EVENT_ENDED)
	{
		GameMap::GetInstance()->getPay()->pay( "1000" , "1" );
	}
}


void UIDestoryStar::update( float delta )
{
	if( (dtime += delta) > UPDATE_TIME )
	{
		int tGlobalScore = GameMap::GetInstance()->getGlobalScore();
		int tLevel = GameMap::GetInstance()->getLevel();
		int tHstoryScore = GameMap::GetInstance()->getHistoryScore();
		int tScore = GameMap::GetInstance()->getScore();
		int tMoney = GameMap::GetInstance()->money;

		CCString* countStr;
		if( tGlobalScore != gloalScore )
		{
			gloalScore = tGlobalScore;
			countStr = CCString::createWithFormat("%d",gloalScore);
			m_pGoalScoreLab->setStringValue(countStr->getCString());
		}

		if( tScore != score )
		{
			score = tScore;
			countStr = CCString::createWithFormat("%d",score);
			m_pScoreLab->setStringValue(countStr->getCString());
		}

		if( tLevel != level )
		{
			level = tLevel;
			countStr = CCString::createWithFormat( "%d",level );
			m_pLevelLab->setStringValue(countStr->getCString());
		}

		if( tHstoryScore != historyScroe )
		{
			historyScroe = tHstoryScore;
			countStr = CCString::createWithFormat( "%d",historyScroe );
			m_pHistoryScoreLab->setStringValue(countStr->getCString());
		}

		if(tMoney != money)
		{
			money = tMoney;
			countStr = CCString::createWithFormat( "%d",money );
			m_pPointLab->setStringValue(countStr->getCString());
		}
		dtime =0;
	}
}



UIDestoryStar::~UIDestoryStar()
{
	m_pScoreLab = NULL;
	m_pLevelLab = NULL;
	m_pGoalScoreLab = NULL;
	m_pHistoryScoreLab = NULL;
	m_pDj101Btn = NULL;
	m_pDj102Btn = NULL;
	m_pDj103Btn = NULL;
	m_pDj104Btn = NULL;
}
