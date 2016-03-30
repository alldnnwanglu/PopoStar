#include "StarContainer.h"
#include <math.h>
#include "GameMap.h"
#include <vector>
#include "RandomUtil.h"
#include "UIManager.h"
#include "ConfigManager.h"

USING_NS_CC;

StarContainer::StarContainer()
{
	canReturn = false;
	srand(time(NULL));
	openList = new std::vector<int>();
	closeList = new std::vector<int>();

}

void StarContainer::init()
{
	openList->clear();
	closeList->clear();

	for ( int i = 0 ; i < ROLE_NUM ; i++ )
	{
		for ( int j = 0 ;j < ROLE_NUM ; j++ )
		{
			int index = RandomUtil::RangeInt(1,5);
			

			m_pStars[i][j] = new Star( index );
			CCSprite* sprite = m_pStars[i][j]->GetAvata();
			CCMoveTo* moveTo = CCMoveTo::create( 0.7f , m_pStars[i][j]->getPosition( i , j ));
			CCEaseBounceOut* easeOut = CCEaseBounceOut::create(moveTo);
			CCCallFunc* callFunc = CCCallFunc::create(this,callfunc_selector(StarContainer::PlayStartAnimOver));
			CCActionInterval* intervalAction = CCSequence::create( easeOut , callFunc , NULL );
			sprite->runAction(intervalAction);
			
			GameMap::GetInstance()->getSpriteBatchBode()->addChild(sprite);
		}
	}

	SavePreStep();
}

void StarContainer::loadGame()
{
	openList->clear();
	closeList->clear();

	for ( int i = 0 ; i < ROLE_NUM ; i++ )
	{
		for ( int j = 0 ;j < ROLE_NUM ; j++ )
		{
			CCString* str = CCString::createWithFormat("%d_index",getArrayIndex( i , j ) );
			int index = CCUserDefault::sharedUserDefault()->getIntegerForKey( str->getCString());
			if(index <= 0 || index >5)
			{
				m_pStars[i][j] = NULL;
				continue;
			}
			m_pStars[i][j] = new Star( index );
			CCSprite* sprite = m_pStars[i][j]->GetAvata();
			CCMoveTo* moveTo = CCMoveTo::create( 0.7f , m_pStars[i][j]->getPosition( i , j ));
			CCEaseBounceOut* easeOut = CCEaseBounceOut::create(moveTo);
			CCCallFunc* callFunc = CCCallFunc::create(this,callfunc_selector(StarContainer::PlayStartAnimOver));
			CCActionInterval* intervalAction = CCSequence::create( easeOut , callFunc , NULL );
			sprite->runAction(intervalAction);

			GameMap::GetInstance()->getSpriteBatchBode()->addChild(sprite);

			
		}
	}

	SavePreStep();
}


void StarContainer::ClickStar(::cocos2d::CCPoint point)
{
	int x = (point.x - 20) / GameMap::GetInstance()->cellWidth;
	int y = ( point.y - 140 ) / GameMap::GetInstance()->cellHeight;

	// begin search star by type
	openList->clear();
	closeList->clear();

	if( !IsInMap(x,y) || GameMap::GetInstance()->GetGameState() == WAIT_START) return;

	switch (GameMap::GetInstance()->GetGameState())
	{
	case  NORMAL:
		{
			SearchDelStar( getArrayIndex( x , y ) , m_pStars[x][y]->GetType());
			if(closeList->size() <= 1) return;
			canReturn = true;
			break;
		}

	case Use_Item_Lolly:
		{
			closeList->push_back( getArrayIndex( x , y ) );
			if(GameItemManager::GetInstance()->UseItem(Item_Lolly))
			{
				if(closeList->size() < 1) return;
				canReturn = true;
			}
			else
				closeList->clear();

			GameMap::GetInstance()->SetGameStage(NORMAL);
			UIManager::GetInstance()->getUIUseItem()->deactivate();
			break;
		}
		
	case Use_Item_Candy:
		{
			if(m_pStars[x][y] == NULL) return;

			if(GameItemManager::GetInstance()->UseItem(Item_Candy))
			{
				
				GameMap::GetInstance()->getSpriteBatchBode()->removeChild( m_pStars[x][y]->GetAvata(),true );
				m_pStars[x][y] = new Star( 7 );
				m_pStars[x][y]->SetPosition( m_pStars[x][y]->getPosition( x , y));
				GameMap::GetInstance()->getSpriteBatchBode()->addChild(m_pStars[x][y]->GetAvata());
			}
			GameMap::GetInstance()->SetGameStage(NORMAL);
			UIManager::GetInstance()->getUIUseItem()->deactivate();
			return;
		}

	case Use_Item_Return:
		{
			if(canReturn && GameItemManager::GetInstance()->UseItem(Item_Return))
			{
				canReturn = false;
				GameMap::GetInstance()->UseReturn();
			}
			GameMap::GetInstance()->SetGameStage(NORMAL);
			UIManager::GetInstance()->getUIUseItem()->deactivate();
			return;
		}

	case Use_Item_Refresh:
		{
			if(GameItemManager::GetInstance()->UseItem(Item_Refresh))
			{
				canReturn = true;
				GameMap::GetInstance()->UseRefresh();
			}
			GameMap::GetInstance()->SetGameStage(NORMAL);
			UIManager::GetInstance()->getUIUseItem()->deactivate();
			return;
		}
	
	}

	SavePreStep();
	
	// play click effect sound
	std::vector<int>::iterator it = closeList->begin();
	for( ; it!= closeList->end(); it++ )
	{
		x = getArrayX( *it );
		y = getArrayY( *it );

		GameMap::GetInstance()->getSpriteBatchBode()->removeChild( m_pStars[x][y]->GetAvata() , true );
		m_pStars[x][y]->Die();

		delete m_pStars[x][y];
		m_pStars[x][y] = NULL;
	}

	GameMap::GetInstance()->PopStarSettle( closeList->size() );

	// reset  x 
	it = closeList->begin();
	for( ; it!= closeList->end(); it++ )
	{
		x = getArrayX( *it );
		y = getArrayY( *it );

		int startIndex = -1;

		for( int j = 0 ; j < ROLE_NUM ; j++ )
		{
			if(m_pStars[x][j] == NULL) 
			{
				startIndex = j;
				break;
			}
		}

		if(startIndex == -1) continue;

		for( int j = startIndex + 1; j < ROLE_NUM ; j++ )
		{
			Star* mTemp = m_pStars[x][j-1];
			m_pStars[x][j-1] = m_pStars[x][j];
			m_pStars[x][j] = mTemp; 
		}
	}

	// rest  y
	it = closeList->begin();
	for( ; it!= closeList->end(); it++ )
	{
		x = getArrayX( *it );
		y = getArrayY( *it );

		int startIndex = -1;

		for( int j = 0 ; j < ROLE_NUM ; j++ )
		{
			if(m_pStars[x][j] == NULL) 
			{
				startIndex = j;
				break;
			}
		}

		if(startIndex == -1) continue;

		for( int j = startIndex + 1; j < ROLE_NUM ; j++ )
		{
			Star* mTemp = m_pStars[x][j-1];
			m_pStars[x][j-1] = m_pStars[x][j];
			m_pStars[x][j] = mTemp; 
		}
	}

	// rest x
	it = closeList->begin();
	for( ; it!= closeList->end(); it++ )
	{
		x = getArrayX( *it );
		y = getArrayY( *it );

		int nullCount = 0;
		int startIndex = -1;

		for( int i = 0 ; i < ROLE_NUM ; i++ )
		{
			nullCount = 0;
			for( int j = 0 ; j < ROLE_NUM ; j++ )
			{
				if( m_pStars[i][j] == NULL ) 
				{
					startIndex = i;
					nullCount++;
				}
			}
			if(nullCount == ROLE_NUM) break;
		}

		if(nullCount == ROLE_NUM)
		{
			for( int i= startIndex + 1 ; i < ROLE_NUM ; i++ )
			{
				for( int j = 0; j < ROLE_NUM ; j++ )
				{
					Star* mTemp = m_pStars[i-1][j];
					m_pStars[i-1][j] = m_pStars[i][j];
					m_pStars[i][j] = mTemp; 
				}
			}
		}
	}

	

	// rest graph
	for (int i=0;i<10;i++)
	{
		for (int j=0;j<10;j++)
		{
			if(m_pStars[i][j] != NULL)
			{
				CCSprite* sprite = m_pStars[i][j]->GetAvata();
				CCMoveTo* moveTo = CCMoveTo::create( MOVE_TIME , m_pStars[i][j]->getPosition( i , j));
				CCEaseBounceOut* easeOut = CCEaseBounceOut::create(moveTo);
				sprite->runAction(easeOut);
			}
		}
	}

	bool gameOver = true;

	// check the is no star to destory
	for( int i = 0 ; i< ROLE_NUM ; i++ )
	{
		for( int j = 0 ; j < ROLE_NUM ; j++ )
		{
			if( m_pStars[i][j] == NULL ) continue;
			closeList->clear();
			SearchDelStar( getArrayIndex( i , j) , m_pStars[i][j]->GetType() );
			if (closeList->size() > 1)
			{
				gameOver = false;
				break;
			}
		}
	}

	// gameOver next stage
	if(gameOver)
		GameMap::GetInstance()->CompleteLevel();
}

void StarContainer::SaveLevel()
{
	//save config
	for ( int i = 0 ; i < ROLE_NUM ; i++ )
	{
		for ( int j = 0 ;j < ROLE_NUM ; j++ )
		{
			CCString* str = CCString::createWithFormat("%d_index",getArrayIndex( i , j ) );
			if(m_pStars[i][j] == NULL)
				CCUserDefault::sharedUserDefault()->setIntegerForKey( str->getCString(), 0 );
			else
				CCUserDefault::sharedUserDefault()->setIntegerForKey( str->getCString(), m_pStars[i][j]->GetType() );
		}
	}
}

void StarContainer::SearchDelStar(int index,int type)
{
	int x , y , dx , dy , tIndex;
	x = getArrayX( index );
	y = getArrayY( index );

	// left
	dx = x - 1;
	tIndex = getArrayIndex( dx , y);
	if( IsInMap( dx , y ) && IsMatchType( m_pStars[dx][y]->GetType() , type ) && IsNotInList(tIndex) )
		openList->push_back( tIndex );

	// right
	dx = x + 1;
	tIndex = getArrayIndex( dx , y);
	if( IsInMap( dx , y ) && IsMatchType(m_pStars[dx][y]->GetType() , type )  && IsNotInList(tIndex) )
		openList->push_back( tIndex );

	// top
	dy = y - 1;
	tIndex = getArrayIndex( x , dy); 
	if( IsInMap( x , dy ) && IsMatchType(m_pStars[x][dy]->GetType() , type )  && IsNotInList(tIndex) )
		openList->push_back( tIndex );

	// buttom
	dy = y + 1;
	tIndex = getArrayIndex( x , dy); 
	if( IsInMap( x , dy )  && IsMatchType(m_pStars[x][dy]->GetType() , type)  && IsNotInList(tIndex) )
		openList->push_back( tIndex );

	closeList->push_back( index );

	if( openList->size() == 0 )  return;

	index = openList->back();
	openList->pop_back();

	SearchDelStar(index,type);
}

bool StarContainer::IsInVect(int index,std::vector<int>* vect)
{
	std::vector<int>::iterator it = vect->begin();
	for( ; it!= vect->end(); it++ )
		if( index == *it) return true;

	return false;
}

bool StarContainer::IsMatchType( int type , int matchType )
{
	return (type == matchType || type == 7);
}

bool StarContainer::IsInMap( int x , int y )
{
	if ( x < 0 || x >= ROLE_NUM ) return false;
	if ( y < 0 || y >= ROLE_NUM ) return false;

	if( m_pStars[x][y] == NULL ) return false; 
	return true;
}

void StarContainer::Refresh()
{
	openList->clear();
	closeList->clear();
	for ( int i = 0 ; i < ROLE_NUM ; i++ )
	{
		for ( int j = 0 ;j < ROLE_NUM ; j++ )
		{
			if(m_pStars[i][j] == NULL) continue;
			GameMap::GetInstance()->getSpriteBatchBode()->removeChild(m_pStars[i][j]->GetAvata(),true);
			m_pStars[i][j] = new Star( RandomUtil::RangeInt(1,5));
			CCSprite* sprite = m_pStars[i][j]->GetAvata();
			CCMoveTo* moveTo = CCMoveTo::create( 0.7f , m_pStars[i][j]->getPosition( i , j ));
			CCEaseBounceOut* easeOut = CCEaseBounceOut::create(moveTo);
			CCCallFunc* callFunc = CCCallFunc::create(this,callfunc_selector(StarContainer::PlayStartAnimOver));
			CCActionInterval* intervalAction = CCSequence::create( easeOut , callFunc , NULL );
			sprite->runAction(intervalAction);

			GameMap::GetInstance()->getSpriteBatchBode()->addChild(sprite);
		}
	}
}

void StarContainer::PlayStartAnimOver()
{
	GameMap::GetInstance()->SetGameStage(NORMAL);
}

void StarContainer::SavePreStep()
{
	for( int i = 0 ; i < ROLE_NUM ; i++ )
	{
		for( int j = 0 ; j < ROLE_NUM ; j++ )
		{
			if(  m_pStars[i][j] == NULL)
				m_pTempStars[i][j] = -1;
			else 
				m_pTempStars[i][j] = m_pStars[i][j]->GetType();
		}
	}
}

void StarContainer::Return()
{
	removeAllChild();

	for( int i = 0 ; i < ROLE_NUM ; i++ )
	{
		for( int j = 0 ; j < ROLE_NUM ; j++ )
		{
			m_pStars[i][j] = NULL;

			if( m_pTempStars[i][j] != -1 )
			{
				m_pStars[i][j] = new Star( m_pTempStars[i][j] );

				CCSprite* sprite = m_pStars[i][j]->GetAvata();
				CCMoveTo* moveTo = CCMoveTo::create( 0.7f , m_pStars[i][j]->getPosition( i , j ));
				CCEaseBounceOut* easeOut = CCEaseBounceOut::create(moveTo);
				CCCallFunc* callFunc = CCCallFunc::create(this,callfunc_selector(StarContainer::PlayStartAnimOver));
				CCActionInterval* intervalAction = CCSequence::create( easeOut , callFunc , NULL );
				sprite->runAction(intervalAction);

				GameMap::GetInstance()->getSpriteBatchBode()->addChild(sprite);
			}	
		}
	}
}

int StarContainer::BalanceSettle()
{
	int count = 0;
	for( int i = 0 ; i < ROLE_NUM ; i++ )
	{
		for( int j = 0 ; j < ROLE_NUM ; j++ )
		{
			if( m_pStars[i][j] != NULL )
			{	
				count ++;
				m_pStars[i][j]->Die();
				GameMap::GetInstance()->getSpriteBatchBode()->removeChild( m_pStars[i][j]->GetAvata(),true);

				delete m_pStars[i][j];
				m_pStars[i][j] = NULL;
			}
		}
	}

	return count;
}

bool StarContainer::IsNotInList(int tIndex)
{
	return (!IsInVect( tIndex , openList ) && !IsInVect( tIndex , closeList ));
}

void StarContainer::removeAllChild()
{
	for( int i = 0 ; i < ROLE_NUM ; i++ )
	{
		for( int j = 0 ; j < ROLE_NUM ; j++ )
		{
			if( m_pStars[i][j] != NULL )
			{
				GameMap::GetInstance()->getSpriteBatchBode()->removeChild(m_pStars[i][j]->GetAvata(),true);
				m_pStars[i][j] = NULL;
			}
		}
	}
}

StarContainer::~StarContainer(){}