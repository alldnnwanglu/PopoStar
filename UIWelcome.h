//
//  GameMainScene.h
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015Äê Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef UI_Welcome_h
#define UI_Welcome_h
#include "cocos2d.h"
#include "cocos-ext.h"
#include "UIBase.h"

class UIWelcome : public UIBase
{
public:
	virtual bool init();
	CREATE_FUNC( UIWelcome );
	~UIWelcome();

protected:
	virtual void starGameCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );
	virtual void loadGameCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );

protected:
	::cocos2d::ui::UIButton*		m_pStartGame;
	::cocos2d::ui::UIButton*		m_pLoadGame;

};


#endif
