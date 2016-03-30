//
//  Entity.h
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015年 Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef HelloCpp_GameEntity_h
#define HelloCpp_GameEntity_h
#include "cocos2d.h"
#include "MacrosDefine.h"
#include "Box2d/Box2D.h"

enum
{
	ENTITY_NONE = 0,
	ENTITY_PLAYER  = 1,
	ENTITY_ENEMY  = 2,
	ENTITY_BULLET = 3,
};
class GameEntity
{
protected:
	float m_speed;
	::cocos2d::CCPoint m_position;
	::cocos2d::CCSize m_size;
	::cocos2d::CCSprite* m_pSprite;

	int m_nType;
    float m_fColliderRate;//BoxCollider Adjust Rate
	bool m_bInCollider;

public:
    GameEntity();
    virtual ~GameEntity();
	void SetVisible( bool bVisible );
	bool GetVisible( ) const;
    ::cocos2d::CCSprite* GetAvata(){ return m_pSprite; }
    void SetAvata( ::cocos2d::CCSprite* pSprite );
	int GetZOrder() const;
	virtual ::cocos2d::CCPoint GetPosition() const;
	virtual void SetPosition( const ::cocos2d::CCPoint point );
    void SetScale( const float scale );
    float GetScale( ) const;
	::cocos2d::CCSize GetSize() const;
    virtual void Update( float dt );
    virtual void ColliderFrom( GameEntity* collider );
	/************************************************************************/
	/* 获取对象类型，判断是否是玩家飞机还是敌机                             */
	/************************************************************************/
	virtual int  GetObjType() { return m_nType;}
	virtual ::cocos2d::CCRect GetBoundingBox() const;
    SWX_PROPERTY( float, m_speed, Speed );
	CC_SYNTHESIZE( b2Body*, m_b2Body, b2Body );
	bool IsInCollider() const { return m_bInCollider; }
	virtual void IntoCollider( GameEntity *entity );
	virtual void ExitCollider( GameEntity *entity );
	virtual void MoveTo( ::cocos2d::CCPoint point ){};
};


#endif