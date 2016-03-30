#ifndef HelloCpp_GameItem_h
#define HelloCpp_GameItem_h

#include "cocos2d.h"
#include "GameEntity.h"
#include "MacrosDefine.h"
enum
{
	Item_Lolly,
	Item_Candy,
	Item_Refresh,
	Item_Return,
};

class GameItem : public GameEntity
{
protected:
	int   m_nItemType;
	int   m_nAmount;
public:
	GameItem( int itemType, int nAmount = 1 );
	int getItemType() const { return m_nItemType; }
	int getAmount() const { return m_nAmount; }
	void setAmount(int count) { m_nAmount=count; }
	bool use();
	void buy();
};
#endif // !

