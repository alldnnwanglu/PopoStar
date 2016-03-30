//
//  Entity.h
//  HelloCpp
//
//  Created by shaoleibo on 15-1-31.
//  Copyright (c) 2015Äê Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef Score_Module_h
#define Score_Module_h
#include "cocos2d.h"
#include "Star.h"

int		const	ROLE_NUM = 10;
int		const	MAX_ROLE_NUM = 16;
float	const	MOVE_TIME = 0.2f;
class StarContainer : public ::cocos2d::CCObject
{
private:
	Star*							m_pStars[MAX_ROLE_NUM][MAX_ROLE_NUM];
	int								m_pTempStars[ROLE_NUM][ROLE_NUM];
	bool							canReturn;
	std::vector<int>*				openList;
	std::vector<int>*				closeList;

private:
	::cocos2d::CCPoint GetVisableSize() const { return ::cocos2d::CCDirector::sharedDirector()->getVisibleSize();};
	::cocos2d::CCPoint GetVisiableOrigin() const {return ::cocos2d::CCDirector::sharedDirector()->getVisibleOrigin();};
	void SavePreStep();
	bool IsInVect(int index,std::vector<int>* vect);
	bool IsInMap( int x , int y );
	void SearchDelStar(int index,int type);
	bool IsNotInList( int tIndex);
	bool IsMatchType( int type , int matchType );
	void removeAllChild();

	int getArrayX( int index ) const { return index >> 4; };
	int getArrayY( int index ) const { return index - ((index >> 4) << 4); };
	int getArrayIndex( int x , int y ) const { return (x << 4) + y; };




public:
	virtual void init();
	void loadGame();
	void ClickStar(::cocos2d::CCPoint point);
	void PlayStartAnimOver();
	void Refresh();
	void Return();
	void SaveLevel();

	int BalanceSettle();


public:
   StarContainer();
   ~StarContainer();
};


#endif