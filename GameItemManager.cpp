#include "GameItemManager.h"
#include "GameMap.h"
#include "UIManager.h"

USING_NS_CC;

GameItemManager::GameItemManager()
{
	int itemCount = CCUserDefault::sharedUserDefault()->getIntegerForKey("itemLolly");
	m_pLolly = new GameItem( Item_Lolly , itemCount );

	itemCount = CCUserDefault::sharedUserDefault()->getIntegerForKey("itemCandy");
	m_pCandy = new GameItem( Item_Candy , itemCount);

	itemCount = CCUserDefault::sharedUserDefault()->getIntegerForKey("itemRefresh");
	m_pRefresh = new GameItem( Item_Refresh , itemCount);

	itemCount = CCUserDefault::sharedUserDefault()->getIntegerForKey("itemReturn");
	m_pReturn = new GameItem( Item_Return , itemCount);
}

bool GameItemManager::UseItem( int type )
{
	bool isUse = false;
	switch (type)
	{
	case Item_Lolly:
		{
			if(!(isUse = m_pLolly->use()))
				 isUse = GameMap::GetInstance()->Buy( 10 );
			break;
		}

	case Item_Candy:
		{
			if(!(isUse = m_pCandy->use()))
				isUse = GameMap::GetInstance()->Buy( 10 );
			break;
		}

	case Item_Refresh:
		{
			if(!(isUse = m_pRefresh->use()))
				isUse = GameMap::GetInstance()->Buy( 8 );
			break;
		}

	case Item_Return:
		{
			if(!(isUse = m_pReturn->use()))
				isUse = GameMap::GetInstance()->Buy( 6 );
			break;
		}
	}

	if(!isUse)
	{
		// TODO µ¯³öÖ§¸¶Ò³Ãæ
	}
	else
	{
		CCUserDefault::sharedUserDefault()->setIntegerForKey("itemLolly" , m_pLolly->getAmount());
		CCUserDefault::sharedUserDefault()->setIntegerForKey("itemCandy" , m_pCandy->getAmount());
		CCUserDefault::sharedUserDefault()->setIntegerForKey("itemRefresh" , m_pRefresh->getAmount());
		CCUserDefault::sharedUserDefault()->setIntegerForKey("itemReturn" , m_pReturn->getAmount());
	}

	return isUse;
}

int GameItemManager::getItemCount( int type )
{
	switch (type)
	{
	case Item_Lolly:
		return m_pLolly->getAmount();

	case Item_Candy:
		return m_pCandy->getAmount();

	case Item_Refresh:
		return m_pRefresh->getAmount();

	case Item_Return:
		return m_pReturn->getAmount();
	}
	return 0;
}

void GameItemManager::BuyItem( int type )
{
	int count = 0;
	switch (type)
	{
	case Item_Lolly:
		{
			m_pLolly->buy();
			CCUserDefault::sharedUserDefault()->setIntegerForKey("itemLolly" , m_pLolly->getAmount());
			break;
		}
	case Item_Candy:
		{
			m_pCandy->buy();
			CCUserDefault::sharedUserDefault()->setIntegerForKey("itemCandy" , m_pCandy->getAmount());
			break;
		}
	case Item_Refresh:
		{
			m_pRefresh->buy();
			CCUserDefault::sharedUserDefault()->setIntegerForKey("itemRefresh" , m_pRefresh->getAmount());
			break;
		}
	case Item_Return:
		{
			m_pReturn->buy();
			CCUserDefault::sharedUserDefault()->setIntegerForKey("itemReturn" , m_pReturn->getAmount());
			break;
		}
	}
}

GameItemManager::~GameItemManager()
{

}