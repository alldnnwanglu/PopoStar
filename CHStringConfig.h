//
//  GameMainScene.h
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015Äê Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef CH_String_Config_h
#define CH_String_Config_h
#include "cocos2d.h"

class CHStringConfig : public ::cocos2d::CCObject
{
public:
	virtual bool init();
	~CHStringConfig();
	CREATE_FUNC( CHStringConfig );
	::cocos2d::CCString* objectForKey( const char* key );
private:
	const char*			m_pfileName;
};


#endif
