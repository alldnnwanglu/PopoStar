#include "AnimationUtil.h"
USING_NS_CC;

CCAnimation* AnimationUtil::createAnimWithSingleFrameN( const char* name, float delay, unsigned int iLoops )
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCArray* framesArray = CCArray::create();
	CCSpriteFrame* frame = NULL;
	int index = 0;
	do 
	{
		frame = cache->spriteFrameByName( CCString::createWithFormat( "%s%d.png", name, index++ )->getCString() );
		if( frame == NULL )
			break;
		framesArray->addObject( frame );
	} while( true );
	CCAnimation* animation = CCAnimation::createWithSpriteFrames( framesArray );
	animation->setLoops( iLoops );
	animation->setRestoreOriginalFrame( true );
	animation->setDelayPerUnit( delay );
	return animation;
}

