//
//  GameMainScene.h
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015Äê Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef HelloCpp_GameMainScene_h
#define HelloCpp_GameMainScene_h
#include "cocos2d.h"
class GameMainScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
	//static cocos2d::CCScene* 

    CREATE_FUNC( GameMainScene );

	// listen android press return key
	virtual void keyBackClicked();

	// listen android press Menu key
	virtual void keyMenuClicked();

	//void ccTouchesBegan( ::cocos2d::CCSet *pTouches, ::cocos2d::CCEvent *pEvent );
    //void ccTouchesMoved( ::cocos2d::CCSet *pTouches, ::cocos2d::CCEvent *pEvent );
	virtual bool ccTouchBegan( ::cocos2d::CCTouch *pTouches, ::cocos2d::CCEvent *pEvent);
	virtual void registerWithTouchDispatcher(void);

private:
	::cocos2d::CCPoint m_touchPoint;

public:
	int				   state;
};


#endif
