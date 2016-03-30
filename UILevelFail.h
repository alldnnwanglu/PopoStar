//
//  GameMainScene.h
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015Äê Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef UI_LevelFail_h
#define UI_LevelFail_h
#include "cocos2d.h"
#include "cocos-ext.h"
#include "UIBase.h"

class UILevelFail : public UIBase
{
public:
	virtual bool init();
	~UILevelFail();
	CREATE_FUNC( UILevelFail );

protected:
	virtual void okBtnCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );
	virtual void chanlBtnCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );


protected:
	::cocos2d::ui::UIButton*			m_pOkBtn;
	::cocos2d::ui::UIButton*			m_pCanelBtn;
};

#endif
