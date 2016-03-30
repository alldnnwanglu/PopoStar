//
//  GameMainScene.cpp
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015年 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "UISingleIn.h"
#include "GameMap.h"
#include "TimeUtil.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace gui;

bool UISingleIn::init()
{
	m_fileName = "SingleIn.ExportJson";
	if( UIBase::init() )
	{
		// parse
		UIPanel* centerPanel = static_cast<UIPanel*>(m_pWidget->getChildByName("centerPanel"));

		for(int i = 0 ; i< 7 ; i++)
		{
			CCString* str = CCString::createWithFormat("%dImg",(i+1));
			UIImageView* uiImage = static_cast<UIImageView*>(centerPanel->getChildByName(str->getCString()));
			m_pImg[i] = static_cast<UIImageView*>(uiImage->getChildByName("bgImg"));
		}

		m_pHoldBtn = static_cast<UIButton*>(m_pWidget->getChildByName("holdBtn"));



		// register event
		m_pHoldBtn->addTouchEventListener( this , toucheventselector( UISingleIn::singleInCallBack));
		

		confYear = CCUserDefault::sharedUserDefault()->getIntegerForKey("Year");
		confMoth = CCUserDefault::sharedUserDefault()->getIntegerForKey("Moth");
		confDay = CCUserDefault::sharedUserDefault()->getIntegerForKey("Day");
		index = CCUserDefault::sharedUserDefault()->getIntegerForKey("singleIndex") % 7;

		nowYear = TimeUtil::GetSystemTime( Year );
		nowMoth = TimeUtil::GetSystemTime( Moth );
		nowDay= TimeUtil::GetSystemTime( Day );

		bool isShow = false;
		if(nowYear > confYear)
			isShow = true;
		else if(nowMoth > confMoth)
			isShow = true;
		else if(nowDay > confDay )
			isShow = true;
		
		// how time we can show

		for(int i = 0;i<index;i++)
		{
			m_pImg[i]->setVisible( false );
		}

		if (isShow)
			activate();
		else
			deactivate();

		return true;
	}

	
	return false;
}

void UISingleIn::singleInCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type )
{
	if(type == cocos2d::ui::TOUCH_EVENT_ENDED)
	{
		// delete money 
		if(GameMap::GetInstance()->Buy(5))
		{	
	
			// hold Item
			if( index == 0 )
				GameItemManager::GetInstance()->BuyItem(Item_Candy);
			
			if( index == 1 )
				GameItemManager::GetInstance()->BuyItem(Item_Return);

			if( index == 2 )
				GameItemManager::GetInstance()->BuyItem(Item_Refresh);

			if( index == 3 )
				GameItemManager::GetInstance()->BuyItem(Item_Lolly);

			if( index == 4 )
				GameItemManager::GetInstance()->BuyItem(Item_Return);

			if( index == 5 )
				GameItemManager::GetInstance()->BuyItem(Item_Lolly);
			
			if( index == 6 )
				GameItemManager::GetInstance()->BuyItem(Item_Candy);


			CCUserDefault::sharedUserDefault()->setIntegerForKey("singleIndex" , (++index) % 7);
			CCUserDefault::sharedUserDefault()->setIntegerForKey( "Year" , nowYear );
			CCUserDefault::sharedUserDefault()->setIntegerForKey( "Moth" , nowMoth );
			CCUserDefault::sharedUserDefault()->setIntegerForKey( "Day" , nowDay );
		}
		else
		{
			// TODO 支付页面 
		}
		
		deactivate();
	}
}



UISingleIn::~UISingleIn()
{
	m_pImg[7] = NULL;
	m_pHoldBtn = NULL;
}