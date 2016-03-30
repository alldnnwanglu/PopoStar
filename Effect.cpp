//
//  Effect.cpp
//  StarPlane
//
//  Created by shaoleibo on 15-3-1.
//
//

#include "Effect.h"
#include "AnimationUtil.h"
USING_NS_CC;

Effect::Effect(void)
{
	m_sElapsed = 0.0f;
	m_dElapsed = 0.0f;
	m_displayNode = NULL;
	m_isPlaying = false;
}

Effect::~Effect()
{
    removeElement();
    CC_SAFE_RELEASE_NULL(m_displayNode);    
}

void Effect::setEffectInfo( EffectInfo& ei )
{
	m_effectInfo = ei;
}

void Effect::stop()
{
	if (m_displayNode)
	{
		m_displayNode->stopAllActions();
	}
}

void Effect::reset()
{
	m_sElapsed = 0;
	m_dElapsed = 0;
}

void Effect::tick(float dt)
{
	if (m_effectInfo.m_effectParent == NULL)
	{
		return;
	}
	m_sElapsed += dt;
	if (m_sElapsed >= m_effectInfo.m_startTime)
	{
		if (m_isPlaying)
		{
			if (m_effectInfo.m_duration <= 0)
			{
                
			}
			else
			{
				m_dElapsed += dt;
				if (m_dElapsed >= m_effectInfo.m_duration)
				{
					removeElement();
				}
			}
		}
		else
		{
			m_isPlaying = true;
			addElement();
		}
	}
}

void Effect::init()
{
    if (m_displayNode)
	{
		return;
	}
	switch ( m_effectInfo.m_elementType )
	{
	case ELEMENT_TYPE_ANIM:
		m_displayNode = CCSprite::create();
		m_displayNode->retain();
		break;
	case ELEMENT_TYPE_PARTICLE:
		m_displayNode = CCParticleSystemQuad::create( m_effectInfo.m_elementFilePath.c_str() );
		m_displayNode->retain();
		break;
	}

}

void Effect::addElement()
{
    if (!m_displayNode || !m_effectInfo.m_effectParent)
	{
		return;
	}

	switch ( m_effectInfo.m_elementType )
	{
	case ELEMENT_TYPE_ANIM:
		{
			CCAnimation* animation = AnimationUtil::createAnimWithSingleFrameN( m_effectInfo.m_elementFilePath.c_str(), 0.2, 1 );
			CCAnimate* animate = CCAnimate::create( animation );
			if( animate )
			{
				m_displayNode->setPosition( m_effectInfo.m_startPixelPos );
				m_displayNode->runAction( animate );
				m_effectInfo.m_effectParent->addChild( m_displayNode, m_effectInfo.m_zorder );
			}
			break;
		}
	case ELEMENT_TYPE_PARTICLE:
		{
			m_displayNode->setPosition( m_effectInfo.m_startPixelPos );
			m_effectInfo.m_effectParent->addChild( m_displayNode, m_effectInfo.m_zorder );
		    break;
		}
	}

    
}

void Effect::removeElement()
{
    if ( m_displayNode && m_effectInfo.m_effectParent )
	{
		stop();
		m_effectInfo.m_effectParent->removeChild(m_displayNode, true);
	}
}

bool Effect::isDead()
{
    if ( m_effectInfo.m_duration>0 )
	{
		return (this->m_dElapsed >= m_effectInfo.m_duration);
	}
	else
	{
		return false;
	}
}


