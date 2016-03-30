#include "GameItem.h"

GameItem::GameItem(  int itemType, int nAmount ) : m_nItemType( itemType ),m_nAmount( nAmount )
{

}

bool GameItem::use()
{
	if( m_nAmount > 1)
	{
		--m_nAmount;
		return true;
	} 

	return false;
}

void GameItem::buy()
{
	++m_nAmount;
} 