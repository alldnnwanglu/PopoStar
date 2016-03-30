//
//  GameMainScene.cpp
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015年 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "UIUseItem.h"
#include "GameItem.h"
#include "GameMap.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

bool UIUseItem::init()
{

	// read json
	m_fileName = "UseItem.ExportJson";
	if( UIBase::init() )
	{
		// parse
		UIPanel* buttomItem = static_cast<UIPanel*>(m_pWidget->getChildByName("buttomItem"));
		UIImageView* leftImg =  static_cast<UIImageView*>(buttomItem->getChildByName("letImg"));

		m_pDj1Img = static_cast<UIImageView*>(leftImg->getChildByName("dj1Img"));
		m_pDj2Img = static_cast<UIImageView*>(leftImg->getChildByName("dj2Img"));
		m_pDj3Img = static_cast<UIImageView*>(leftImg->getChildByName("dj3Img"));
		m_pDj4Img = static_cast<UIImageView*>(leftImg->getChildByName("dj4Img"));

		m_pItemPriceLab =  static_cast<UILabelAtlas*>(leftImg->getChildByName("itemPriceLab"));
		m_pCloseBtn =  static_cast<UIButton*>(buttomItem->getChildByName("closeButton"));

		// register event
		m_pCloseBtn->addTouchEventListener( this,toucheventselector(UIUseItem::closeCallBack));
		
		this->deactivate();
		return true;
	}
	return false;
}

void UIUseItem::closeCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type )
{

	if(type == cocos2d::ui::TOUCH_EVENT_ENDED)
	{
		deactivate();
		GameMap::GetInstance()->SetGameStage( NORMAL );
	}
}

void UIUseItem::use( int type )
{

	if( GameMap::GetInstance()->GetGameState() != NORMAL ) return;

	this->activate();
	m_pDj1Img->setVisible( false );
	m_pDj2Img->setVisible( false );
	m_pDj3Img->setVisible( false );
	m_pDj4Img->setVisible( false );
	switch ( type )
	{
	case Item_Lolly:
		{
			m_pDj1Img->setVisible( true );
			m_pItemPriceLab->setStringValue("10");
			GameMap::GetInstance()->SetGameStage(Use_Item_Lolly);
			break;
		}
	case Item_Candy:
		{
			m_pDj2Img->setVisible( true );
			m_pItemPriceLab->setStringValue("10");
			GameMap::GetInstance()->SetGameStage(Use_Item_Candy);
			break;
		}
	case Item_Refresh:
		{
			m_pDj4Img->setVisible( true );
			m_pItemPriceLab->setStringValue("8");
			GameMap::GetInstance()->SetGameStage(Use_Item_Refresh);
			break;
		}
	case Item_Return:
		{
			m_pDj3Img->setVisible( true );
			m_pItemPriceLab->setStringValue("6");
			 GameMap::GetInstance()->SetGameStage(Use_Item_Return);
			break;
		}
	}
}

UIUseItem::~UIUseItem()
{
	m_pDj1Img = NULL;
	m_pDj2Img = NULL;
	m_pDj3Img = NULL;
	m_pDj4Img = NULL;
	m_pItemPriceLab = NULL;
	m_pCloseBtn = NULL;
}