//
//  GameMainScene.h
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015Äê Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef UI_Destory_Star_h
#define UI_Destory_Star_h
#include "cocos2d.h"
#include "cocos-ext.h"
#include "UIBase.h"
const float UPDATE_TIME = 0.8f;

class UIDestoryStar : public UIBase
{
public:
	virtual bool init();

	~UIDestoryStar();
	CREATE_FUNC( UIDestoryStar );
	void update( float delta );
	void SetPromptText( const char* text ); 


protected:
	virtual void UseItem101CallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );
	virtual void UseItem102CallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );
	virtual void UseItem103CallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );
	virtual void UseItem104CallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );

	virtual void openLaoHuJiCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );
	virtual void stopMusicCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );
	virtual void openMusicCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );

	virtual void addPointCallBack( ::cocos2d::CCObject* pSender, ::cocos2d::ui::TouchEventType type );

private:
	int								score;
	int								level;
	int								historyScroe;
	int								gloalScore;
	int								money;
	float							dtime;
	bool							musicStoped;

	::cocos2d::ui::UILabelAtlas*	m_pHistoryScoreLab;
	::cocos2d::ui::UILabelAtlas*	m_pLevelLab;
	::cocos2d::ui::UILabelAtlas*	m_pGoalScoreLab;
	::cocos2d::ui::UILabelAtlas*	m_pScoreLab;
	::cocos2d::ui::UIButton*		m_pDj101Btn;
	::cocos2d::ui::UIButton*		m_pDj102Btn;
	::cocos2d::ui::UIButton*		m_pDj103Btn;
	::cocos2d::ui::UIButton*		m_pDj104Btn;

	::cocos2d::ui::UILabelAtlas*	m_pDj101NumLab;
	::cocos2d::ui::UILabelAtlas*	m_pDj102NumLab;
	::cocos2d::ui::UILabelAtlas*	m_pDj103NumLab;
	::cocos2d::ui::UILabelAtlas*	m_pDj104NumLab;
	::cocos2d::ui::UILabel*			m_pPromptLab;
	
	::cocos2d::ui::UILabelAtlas*	m_pPointLab;
	::cocos2d::ui::UIButton*		m_pStopMusicBtn;
	::cocos2d::ui::UIButton*		m_pOpenMusicBtn;
	::cocos2d::ui::UIButton*		m_pAddPointBtn;
	::cocos2d::ui::UIButton*		m_pOpenLHJBtn;
};


#endif
