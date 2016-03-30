//
//  GameMainScene.h
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015Äê Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef UI_SingleIn_h
#define UI_SingleIn_h
#include "cocos2d.h"
#include "cocos-ext.h"
#include "UIBase.h"

class UISingleIn : public UIBase
{
public:
	virtual bool init();
	~UISingleIn();
	CREATE_FUNC( UISingleIn );

protected:
	virtual void singleInCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );

protected:
	::cocos2d::ui::UIImageView*			m_pImg[7];
	::cocos2d::ui::UIButton*			m_pHoldBtn;

	int									confYear;
	int									confMoth;
	int									confDay;
	int									nowYear;
	int									nowMoth;
	int									nowDay;
	int									index;
};


#endif
