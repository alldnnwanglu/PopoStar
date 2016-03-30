
#ifndef GameItemMgr_h
#define GameItemMgr_h
#include "GameItem.h"
#include <vector>
#include "cocos2d.h"
#include "MacrosDefine.h"

class GameItemManager
{
private:
	GameItem*	m_pLolly;
	GameItem*	m_pCandy;
	GameItem*	m_pRefresh;
	GameItem*	m_pReturn;

private:
	GameItemManager();
	GameItemManager( const GameItemManager& );
	GameItemManager& operator=( const GameItemManager& );
	~GameItemManager();

public:
	static GameItemManager* GetInstance()
	{
		static GameItemManager instance;
		return &instance;
	}
	int getItemCount( int type );
	bool UseItem( int type );
	void BuyItem( int type );
};

#endif