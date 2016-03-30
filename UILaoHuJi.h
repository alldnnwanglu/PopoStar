//
//  GameMainScene.h
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015Äê Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef UI_LaoHuJi_h
#define UI_LaoHuJi_h
#include "cocos2d.h"
#include "cocos-ext.h"
#include "UIBase.h"

enum
{
	LaoHuJi_Hiddent,
	LaoHuJi_Ready,
	LaoHuJi_Run,
	LaoHuJi_Hold_Item,
};

class UILaoHuJi : public UIBase
{
public:
	virtual bool init();
	bool	setHiddent( bool hiddent );
	~UILaoHuJi();
	CREATE_FUNC( UILaoHuJi );
	void update( float delta );

protected:
	void PlayLightReady( float delta );
	void PlayLightRun( float delta );
	void PlayLightHold( float delta );
	void ResetAllLight();

	virtual void starLaoHuJi( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );
	virtual void closeLaoHuJi( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );

private:
	::cocos2d::ui::UIImageView*		m_pNormalStar[5];
	::cocos2d::ui::UIImageView*		m_pOnStar[5];
	::cocos2d::ui::UIImageView*		m_pOnStarBg[5];
	::cocos2d::ui::UIImageView*		m_pNormalLight[24];
	::cocos2d::ui::UIImageView*		m_pOnLight[24];

	::cocos2d::ui::UIButton*		m_pCloseBtn;
	::cocos2d::ui::UIButton*		m_pDrawBtn;
	::cocos2d::ui::UIImageView*		m_pFreeImg;

	::cocos2d::ui::ListView*		m_pLeftListView;
	::cocos2d::ui::ListView*		m_pRightListView;
	
	int			topLight;
	int			bottomLight;
	float		topDtime;
	float		buttomDtime;
	float		runDtime;
	int			bLinkTime;
	int			state;
};


#endif
