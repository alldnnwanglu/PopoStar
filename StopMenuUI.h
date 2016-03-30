//
//  GameMainScene.h
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015�� Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef Stop_Menu_h
#define Stop_Menu_h
#include "cocos2d.h"
#include "cocos-ext.h"
#include "UIBase.h"

class StopMenuUI : public UIBase
{
public:
	virtual bool init();
	virtual ~StopMenuUI();
	CREATE_FUNC( StopMenuUI );

protected:
	virtual void okBtnCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );
	virtual void chanlBtnCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );


protected:
	::cocos2d::ui::UIButton*			m_pOkBtn;
	::cocos2d::ui::UIButton*			m_pCanelBtn;
};

#endif
