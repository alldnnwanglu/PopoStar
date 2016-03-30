//
//  GameMainScene.cpp
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015年 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "CHStringConfig.h"
USING_NS_CC;

bool CHStringConfig::init()
{
	m_pfileName = "CHString.xml";
	return true;	
}

CCString* CHStringConfig::objectForKey( const char* key )
{
	CCDictionary* m_pDic = CCDictionary::createWithContentsOfFile(m_pfileName);
	return ((CCString*)m_pDic->objectForKey( key ));
}

CHStringConfig::~CHStringConfig()
{
	m_pfileName = NULL;
}