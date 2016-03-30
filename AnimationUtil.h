#ifndef HelloCpp_AnimationUtil_h
#define HelloCpp_AnimationUtil_h
#include "cocos2d.h"

class AnimationUtil
{
public:
	static ::cocos2d::CCAnimation* createAnimWithSingleFrameN( const char* name,
		float delay, unsigned int iLoops );
};
#endif