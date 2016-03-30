//
//  GameMainScene.cpp
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015年 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "UILaoHuJi.h"
#include "GameMap.h"
#include "RandomUtil.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

bool UILaoHuJi::init()
{
	m_fileName = "LaoHuJi.ExportJson";
	topLight = 0;
	bottomLight = 0;
	topDtime = 0;
	buttomDtime = 0;
	bLinkTime = 0;
	runDtime = 0;

	state = LaoHuJi_Hiddent;

	if( UIBase::init() )
	{
		// parse
		UIImageView* bgImage = static_cast<UIImageView*>(m_pWidget->getChildByName("bg"));
		m_pLeftListView = static_cast<ListView*>(bgImage->getChildByName("leftListView"));
		m_pRightListView = static_cast<ListView*>(bgImage->getChildByName("rightListView"));

		m_pCloseBtn = static_cast<UIButton*>(m_pWidget->getChildByName("closeBtn"));
		m_pDrawBtn =  static_cast<UIButton*>(m_pWidget->getChildByName("drawBtn"));
		m_pFreeImg =  static_cast<UIImageView*>(m_pDrawBtn->getChildByName("freeImg"));

		UIPanel* buttomPanel = static_cast<UIPanel*>(m_pWidget->getChildByName("buttomPanel"));
		
		CCString* str;
		for( int i = 0 ; i < 24 ; i++ )
		{
			str = CCString::createWithFormat("normalLight_%d",(i+1));
			m_pNormalLight[i] = static_cast<UIImageView*>(buttomPanel->getChildByName(str->getCString()));
			m_pOnLight[i] = static_cast<UIImageView*>(m_pNormalLight[i] ->getChildByName("onLight"));

			m_pOnLight[i]->setVisible( false );
		}

		UIPanel* topPanel = static_cast<UIPanel*>(m_pWidget->getChildByName("topPanel"));
		for( int i = 0 ; i < 5 ; i++ )
		{
			str = CCString::createWithFormat("noramStar_%d",(i+1));
			m_pNormalStar[i] = static_cast<UIImageView*>(topPanel->getChildByName(str->getCString()));
			m_pOnStar[i] = static_cast<UIImageView*>(m_pNormalStar[i] ->getChildByName("onStar"));
			m_pOnStarBg[i] = static_cast<UIImageView*>(m_pNormalStar[i] ->getChildByName("onStarBg"));
		
			m_pOnStarBg[i]->setVisible( false );
			m_pOnStar[i]->setVisible( false );
		}

		// register event
		m_pCloseBtn->addTouchEventListener( this , toucheventselector( UILaoHuJi::closeLaoHuJi));
		m_pDrawBtn->addTouchEventListener( this , toucheventselector( UILaoHuJi::starLaoHuJi));

		m_pUILayer->retain();
		m_pWidget->retain();
	}

	this->setHiddent( true );
	return true;
}

bool UILaoHuJi::setHiddent( bool hiddent )
{

	if(hiddent)
	{
		UIBase::deactivate();
		state = LaoHuJi_Hiddent;
	}
	else
	{
		UIBase::activate();
		state = LaoHuJi_Ready;
	}
	return hiddent;
}

void UILaoHuJi::update( float delta )
{
	//allLightBlink( delta );
	switch (state)
	{
	case LaoHuJi_Hiddent:
		break;
	case LaoHuJi_Ready:
		PlayLightReady( delta );
		break;
	case LaoHuJi_Run:
		PlayLightRun( delta );
		break;
	case LaoHuJi_Hold_Item:
		PlayLightHold( delta);
		break;
	}
}

void UILaoHuJi::PlayLightReady( float delta )
{
	if( (topDtime += delta) > 0.4 )
	{
		topLight = topLight % 5;
		m_pOnStarBg[topLight]->setVisible( !m_pOnStarBg[topLight]->isVisible() );
		m_pOnStar[topLight]->setVisible( !m_pOnStar[topLight]->isVisible() );
		topLight++;
		topDtime = 0;
	}

	if( (buttomDtime += delta) > 0.8 )
	{
		bottomLight = bottomLight % 6;
		m_pOnLight[bottomLight]->setVisible(!m_pOnLight[bottomLight]->isVisible() );
		m_pOnLight[bottomLight + 6]->setVisible(!m_pOnLight[bottomLight + 6]->isVisible() );
		m_pOnLight[bottomLight + 12]->setVisible( !m_pOnLight[bottomLight + 12]->isVisible() );
		m_pOnLight[bottomLight + 18]->setVisible( !m_pOnLight[bottomLight + 18]->isVisible() );

		bottomLight++;
		buttomDtime = 0;
	}
}

void UILaoHuJi::closeLaoHuJi( CCObject* pSender , TouchEventType type )
{
	if(type == cocos2d::ui::TOUCH_EVENT_ENDED)
	{
		this->setHiddent( true );
	}
}

void UILaoHuJi::starLaoHuJi( CCObject* pSender , TouchEventType type )
{
	if(type == cocos2d::ui::TOUCH_EVENT_ENDED)
	{
		if(GameMap::GetInstance()->Buy(8))
		{
			if(state == LaoHuJi_Run) return;

			m_pLeftListView->removeAllItems();
			m_pLeftListView->refreshView();

			m_pRightListView->removeAllItems();
			m_pRightListView->refreshView();

			CCString* ccstr;
			UIImageView* sprite;
			int index = 0;
			for (int i = 0; i < 30; ++i)
			{
				
				index =  RandomUtil::RangeInt(1,5);
				ccstr = CCString::createWithFormat("dj%d.png",index);
				sprite = UIImageView::create();
				sprite->loadTexture(ccstr->getCString() ,UI_TEX_TYPE_PLIST);
				m_pLeftListView->insertCustomItem( sprite , i );
			}

			for (int i = 0; i < 62; ++i)
			{
				ccstr = CCString::createWithFormat("LaoHuJi_%d.png", ( i % 10 ));
				sprite = UIImageView::create();
				sprite->loadTexture(ccstr->getCString() ,UI_TEX_TYPE_PLIST);
				m_pRightListView->insertCustomItem( sprite , i );
			}

			m_pLeftListView->refreshView();
			m_pLeftListView->scrollToBottom( 8 , true );
			m_pLeftListView->setInertiaScrollEnabled(true);

			m_pRightListView->refreshView();
			m_pRightListView->scrollToBottom( 8 , true );
			m_pRightListView->setInertiaScrollEnabled(true);

			ResetAllLight();
			state = LaoHuJi_Run;
		
			if( index == 1 )
				GameItemManager::GetInstance()->BuyItem(Item_Lolly);

			if( index == 2 )
				GameItemManager::GetInstance()->BuyItem(Item_Candy);

			if( index == 3 )
				GameItemManager::GetInstance()->BuyItem(Item_Return);

			if( index == 4 )
				GameItemManager::GetInstance()->BuyItem(Item_Refresh);

			if( index == 5 )
				GameMap::GetInstance()->AddMoney( 1 );

		}
		else
		{
			this->setHiddent( true );
			GameMap::GetInstance()->getPay()->pay("1000","1");
		}
	}
}

void UILaoHuJi::PlayLightRun( float delta )
{
	//m_pLeftListView->update(delta);
	if( (runDtime += delta) > 8 )
	{
		ResetAllLight();
		state = LaoHuJi_Hold_Item;
		runDtime = 0;

	} if( runDtime> 0.1)
	{
		topLight = topLight % 5;
		m_pOnStarBg[topLight]->setVisible( !m_pOnStarBg[topLight]->isVisible() );
		m_pOnStar[topLight]->setVisible( !m_pOnStar[topLight]->isVisible() );

		bottomLight = bottomLight % 24;
		m_pOnLight[bottomLight]->setVisible(!m_pOnLight[bottomLight]->isVisible() );
		
		topLight++;
		bottomLight++;
	}

}

void UILaoHuJi::PlayLightHold( float delta )
{
	if( (topDtime += delta) > 0.5 )
	{
		for( int i = 0 ; i< 5; i++)
		{
			m_pOnStarBg[i]->setVisible( !m_pOnStarBg[i]->isVisible() );
			m_pOnStar[i]->setVisible( !m_pOnStar[i]->isVisible() );
		}

		for( int i = 0 ; i< 24; i++)
			m_pOnLight[i]->setVisible( !m_pOnLight[i]->isVisible());

		topDtime = 0;

		bLinkTime++;
		
		if(bLinkTime > 4)
		{
			bLinkTime = 0;
			ResetAllLight();
			state = LaoHuJi_Ready;
		}
	}
}



void UILaoHuJi::ResetAllLight()
{
	for( int i = 0 ; i< 5; i++)
	{
		m_pOnStarBg[i]->setVisible( false );
		m_pOnStar[i]->setVisible( false );
	}

	for( int i = 0 ; i< 24; i++)
		m_pOnLight[i]->setVisible( false);

	topDtime = 0;
	topLight = 0;
	bottomLight = 0;
	buttomDtime = 0;
	bLinkTime = 0;
	
} 

UILaoHuJi::~UILaoHuJi()
{

}
