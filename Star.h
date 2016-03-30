#ifndef HelloCpp_Star_h
#define HelloCpp_Star_h

#include "GameEntity.h"
#include<map>
#include "cocos2d.h"

enum
{
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
};

class Star : public GameEntity
{
public:
	Star(int type);
	int GetType() const { return m_type;}
	virtual void Die( );
	::cocos2d::CCPoint getPosition( int x , int y);

protected:
	int					m_type;
};

#endif