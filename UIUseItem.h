//
//  GameMainScene.h
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015Äê Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef UI_UseItem_h
#define UI_UseItem_h
#include "cocos2d.h"
#include "cocos-ext.h"
#include "UIBase.h"

class UIUseItem : public UIBase
{
public:
	virtual bool init();
	~UIUseItem();
	CREATE_FUNC( UIUseItem );
	void use( int type );

protected:
	::cocos2d::ui::UIImageView*		m_pDj1Img;
	::cocos2d::ui::UIImageView*		m_pDj2Img;
	::cocos2d::ui::UIImageView*		m_pDj3Img;
	::cocos2d::ui::UIImageView*		m_pDj4Img;
	::cocos2d::ui::UILabelAtlas*	m_pItemPriceLab;
	::cocos2d::ui::UIButton*		m_pCloseBtn;

protected:
	virtual void closeCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );
};


#endif
