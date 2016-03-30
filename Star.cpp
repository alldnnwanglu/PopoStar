#include "Star.h"
#include "GameMap.h"
#include "EffectManager.h"
USING_NS_CC;

Star::Star( int type )
{
	m_type = type;
	
	// lod res
	CCString* str= CCString::createWithFormat("candy%d.png",type);
	m_pSprite = CCSprite::createWithSpriteFrameName(str->getCString());
	m_pSprite->retain();
	m_pSprite->setAnchorPoint( ccp( 0.5f , 0.5f));
	m_pSprite->setScaleX( 40.0f/50.0f );
	m_pSprite->setScaleY( 40.0f/50.0f );

	// save in config
	//str = CCString::createWithFormat("%d_index",arrayIndex );
	//CCUserDefault::sharedUserDefault()->setIntegerForKey( str->getCString(), m_type );
}


void Star::Die( void )
{
	// load particle res ,use effect manager to pay particle
	EffectInfo info;
	info.m_effectParent = GameMap::GetInstance();
	info.m_elementType = ELEMENT_TYPE_PARTICLE;
	info.m_startPixelPos = GetPosition();
	info.m_effectName = "huoquxingxing";
	info.m_elementFilePath = "particle/huoquxingxing.plist";
	info.m_duration = 2;
	EffectManager::getInstance().addEffect( info );

	//CCString* str = CCString::createWithFormat("%d_index",arrayIndex );
	//CCUserDefault::sharedUserDefault()->setIntegerForKey( str->getCString(), 0 );
}

CCPoint Star::getPosition(int x , int y)
{
	x = (x + 0.5) * GameMap::GetInstance()->cellWidth + 5;
	y = (y + 0.5) * GameMap::GetInstance()->cellHeight + 5;
	return CCPoint( x  + 20  , y + 140);
}