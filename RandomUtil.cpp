#include "RandomUtil.h"
#include "cocos2d.h"
USING_NS_CC;

float RandomUtil::RangeFloat( float min, float max )
{
	return CCRANDOM_0_1()*( max - min ) + min;
}

int RandomUtil::RangeInt( int min, int max )
{
	return (int)( CCRANDOM_0_1()*( max - min ) + min + 0.5 );
}