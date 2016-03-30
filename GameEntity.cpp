//
//  Entity.cpp
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015Äê Bullets in a Burning Box, Inc. All rights reserved.
//

#include "GameEntity.h"
USING_NS_CC;
GameEntity::GameEntity():m_speed(0),m_position( CCPoint(0,0) ),m_size( CCSize() )
{
    m_pSprite = NULL;
	m_nType = ENTITY_NONE;
    m_fColliderRate = 1;
    m_position = CCPoint();
}

GameEntity::~GameEntity()
{
    m_pSprite = NULL;
}

void GameEntity::SetPosition( const CCPoint point )
{
    m_position = point;
    if( m_pSprite != NULL )
    {
        m_pSprite->setPosition( point );
    }
}

CCPoint GameEntity::GetPosition() const
{
    if( m_pSprite != NULL )
    {
        return m_pSprite->getPosition();
    }
    return CCPoint();
}

void GameEntity::Update( float dt )
{

}

void GameEntity::SetAvata( CCSprite* pSprite )
{
    if( pSprite == NULL )
    {
        m_pSprite = NULL;
        return;
    }
	if( m_pSprite != NULL )
	{
		if( pSprite != NULL )
			pSprite->retain();
		m_pSprite->release();
	}
	m_pSprite = pSprite;
}

CCSize GameEntity::GetSize() const
{
	if( m_pSprite != NULL )
	{
		return m_pSprite->getTextureRect().size;
	}
	return CCSize();
}

void GameEntity::SetVisible( bool bVisible )
{
	if( m_pSprite != NULL )
	{
		m_pSprite->setVisible( bVisible );
	}
}

void GameEntity::SetScale(const float scale)
{
    if( m_pSprite != NULL )
	{
        m_pSprite->setScale( scale );
	}
}

float GameEntity::GetScale() const
{
    if( m_pSprite != NULL )
	{
        return m_pSprite->getScale();
	}
    return 1;
}

bool GameEntity::GetVisible() const
{
	if( m_pSprite != NULL )
	{
		return m_pSprite->isVisible();
	}
	return false;
}

int GameEntity::GetZOrder() const
{
	if( m_pSprite != NULL )
	{
		return m_pSprite->getZOrder();
	}
	return 0;
}

void GameEntity::ColliderFrom(GameEntity *collider)
{
    
}

CCRect GameEntity::GetBoundingBox() const
{
    if( m_pSprite != NULL )
	{
		CCRect bound = m_pSprite->boundingBox();
		CCPoint anchor = m_pSprite->getAnchorPoint();
		CCPoint anchorPoint = CCPoint( bound.size.width / m_fColliderRate * anchor.x, bound.size.height / m_fColliderRate * anchor.y );
		int x = GetPosition().x - anchorPoint.x;
		int y = GetPosition().y - anchorPoint.y;
		return CCRect( x,y,bound.size.width / m_fColliderRate, bound.size.height / m_fColliderRate );
	}
	return CCRect();
}

void GameEntity::IntoCollider(GameEntity *entity)
{
	m_bInCollider = true;
}

void GameEntity::ExitCollider(GameEntity *entity)
{
	m_bInCollider = false;
}