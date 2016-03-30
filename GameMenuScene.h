//
//  GameMainScene.h
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015Äê Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef HelloCpp_GameMenuScene_h
#define HelloCpp_GameMenuScene_h
#include "cocos2d.h"
class GameMenuScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

	// listen android press return key
	virtual void keyBackClicked();

	// listen android press Menu key
	virtual void keyMenuClicked();
    
    CREATE_FUNC( GameMenuScene );
};


#endif
