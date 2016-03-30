//
//  GameMap.cpp
//  HelloCpp
//
//  Created by shaoleibo on 15-2-2.
//  Copyright (c) 2015ï¿?Bullets in a Burning Box, Inc. All rights reserved.
//

#include "GameMap.h"
#include <vector>
#include <algorithm>
#include "UIManager.h"
#include "RandomUtil.h"
#include "MusicManager.h"
#include "cocos-ext.h"
#include "ConfigManager.h"
#include "pay/PayFactory.h"

USING_NS_CC;
using namespace cocos2d::extension;

GameMap::GameMap()
{
	m_fTotalTime = 0;
	level = 0;
	score = 0;
	gameState = WAIT_START;

	maxTop = 430;
	maxWidth = 430;
	cellHeight = maxTop / ROLE_NUM;
	cellWidth = maxWidth / ROLE_NUM;

	// Load Music
	BgSound* m_pBgSound = BgSound::create();

	CCString* strMusic   = ConfigManager::GetInstance()->getCHStringConfig()->objectForKey("greate_music");
	EffectSound* m_pGreateSound = new EffectSound( strMusic->getCString() , Greate_Effect_Sound );

	strMusic   =   ConfigManager::GetInstance()->getCHStringConfig()->objectForKey("prefect_music");
	EffectSound* m_pPrefectSound = new EffectSound( strMusic->getCString(), Prefect_Effect_Sound );

	
	strMusic   =  ConfigManager::GetInstance()->getCHStringConfig()->objectForKey("excellent_music");
	EffectSound* m_pExcellentSound = new EffectSound(strMusic->getCString() , Excellent_Effect_Sound );

	strMusic   =  ConfigManager::GetInstance()->getCHStringConfig()->objectForKey("click_music");
	EffectSound* m_pClickSound = new EffectSound( strMusic->getCString() , Click_Effect_Sound );

	MusicManager::GetInstance()->setBgSound(m_pBgSound);
	MusicManager::GetInstance()->setGreateSound(m_pGreateSound);
	MusicManager::GetInstance()->setPrefectSound(m_pPrefectSound);
	MusicManager::GetInstance()->setExcellentSound(m_pExcellentSound);
	MusicManager::GetInstance()->setClickSound(m_pClickSound);
	
	m_pBgSound->retain();
	m_pGreateSound->retain();
	m_pPrefectSound->retain();
	m_pExcellentSound->retain();
	m_pClickSound->retain();
	
	m_pPay = PayFactory::CreatePay();// PayFactory::CHANNEL_ZYF );

	m_pBgSprite = CCSprite::create("gamebg.png");
	this->addChild(m_pBgSprite);

	m_pSpriteBatchNode = CCSpriteBatchNode::create( "PopStar.png" );
	this->addChild( m_pSpriteBatchNode , 1);

	historyMaxScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("MaxHistoryScore");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( "PopStar.plist" ,"PopStar.png");

	// single data
	int notFist = CCUserDefault::sharedUserDefault()->getBoolForKey("NotFirst");

	if(!notFist)
	{
		money = 20;
		CCUserDefault::sharedUserDefault()->setBoolForKey("NotFirst",true);
	}
	else
		money = CCUserDefault::sharedUserDefault()->getIntegerForKey("money");

	//money =1000;
	// load bg01
	CCScale9Sprite* sprite = CCScale9Sprite::createWithSpriteFrameName( "tbk.png" );
	sprite->setAnchorPoint( ccp(0,0));
	sprite->setPosition(ccp( 20 ,140 ));
	sprite->setCapInsets( CCRectMake(39, 3, 1, 6) );
	sprite->setContentSize(CCSizeMake(440,440));
	this->addChild(sprite,0);
	//m_pSpriteBatchNode->addChild( sprite,0 );

	sprite = CCScale9Sprite::createWithSpriteFrameName( "tbk.png" );
	sprite->setAnchorPoint( ccp(0,0));
	sprite->setPosition(ccp( 23 ,143 ));
	sprite->setCapInsets( CCRectMake(39, 3, 1, 6) );
	sprite->setContentSize(CCSizeMake(434,434));
	this->addChild(sprite,0);
	//m_pSpriteBatchNode->addChild( sprite,0 );

	// load bg02
	for ( int i = 0 ; i < ROLE_NUM ; i++ )
	{
		for ( int j = 0 ;j < ROLE_NUM ; j++ )
		{
			CCScale9Sprite* sprite = CCScale9Sprite::createWithSpriteFrameName( "tbk.png" );
			sprite->setAnchorPoint( ccp(0,0));
			sprite->setPosition(ccp( i * 43.2 + 24,j * 43.2 + 144 ));
			sprite->setCapInsets( CCRectMake(14, 35, 30, 1) );
			sprite->setContentSize(CCSizeMake(43.2,43.2));
			sprite->setPreferredSize( ccp(43.2,43.2));
			this->addChild(sprite);

			//m_pSpriteBatchNode->addChild( sprite );
		}
	}
	m_pGreateSprite =  CCSprite::createWithSpriteFrameName( "lj1.png" );
	m_pPrefectSprite =  CCSprite::createWithSpriteFrameName( "lj2.png" );
	m_pExcellentSprite = CCSprite::createWithSpriteFrameName( "lj3.png" );

	m_pSpriteBatchNode->addChild( m_pGreateSprite ,1);
	m_pSpriteBatchNode->addChild( m_pPrefectSprite ,1);
	m_pSpriteBatchNode->addChild( m_pExcellentSprite ,1);

	m_pGreateSprite->setVisible( false );
	m_pPrefectSprite->setVisible( false );
	m_pExcellentSprite->setVisible( false );
	//m_p
	//init();
}

bool GameMap::init()
{
	if( !CCNode::init() )
		return false;
	MusicManager::GetInstance()->Play(BG_SOUND);

	// int data
	this->scheduleUpdate();
	this->schedule( schedule_selector( GameMap::UpdateMap ), 0.1f );
	InitGoalScore();
	
	LoadRes();

	// base set
	m_pBgSprite->setAnchorPoint(ccp(0,0));
	m_pBgSprite->setPosition(ccp(0,0));
	UIManager::GetInstance()->getUIDestoryStar()->SetPromptText( "" );
	
	return true;
}

void GameMap::LoadRes()
{
	
	
	
	
	m_pScoreModule = new StarContainer();
	
	if( UIManager::GetInstance()->state == NewGame)
		NextLevel();
	else
		LoadLevel();
}

void GameMap::update(float dt)
{
	m_fTotalTime += dt;

}

void GameMap::UpdateMap( float dt )
{
	UIManager::GetInstance()->update( dt );
}

void GameMap::SetScene( CCScene* scene )
{
	m_pScene = scene;
}

void GameMap::LevelReset()
{
	level = 0;
	score = 0;

	level++;
	InitGoalScore();
	PlayStarAnim();
}


void GameMap::GoNoNetLevel()
{
	++level;
	score = goalScore;
	InitGoalScore();
	PlayStarAnim();
}

void GameMap::NextLevel()
{
	gameState = WAIT_START;

	UIManager::GetInstance()->getUIDestoryStar()->SetPromptText( "" );
	if(score >= goalScore )
	{
		level++;
		InitGoalScore();
		PlayStarAnim();
		
		// modify history Max Score
		if(historyMaxScore < score)
		{
			historyMaxScore = score;
			CCUserDefault::sharedUserDefault()->setIntegerForKey("MaxHistoryScore", historyMaxScore);
		}
	}
	else
	{
		UIManager::GetInstance()->getUILevelFail()->activate();
	}
}

void GameMap::LoadLevel()
{

	score = CCUserDefault::sharedUserDefault()->getIntegerForKey( "score_index");
	level = CCUserDefault::sharedUserDefault()->getIntegerForKey( "level_index");
	if( level >0 )
	{
		InitGoalScore();
		PlayStarAnim();
		
	}
	else 
	{
		UIManager::GetInstance()->state = NewGame;
		NextLevel();
	}
}

const char* GameMap::getCHStringConf(const char* key )
{
	CCString* ccStr = ConfigManager::GetInstance()->getCHStringConfig()->objectForKey( key );
	return ccStr->getCString();
}

void GameMap::PlayFinishAnim(int count , int holdScore)
{
	CCString* goalStr1 =  CCString::createWithFormat( "%s %d %s" , getCHStringConf("residue") ,count , getCHStringConf("ge"));
	// label 1
	m_pLabel1 = CCLabelTTF::create( goalStr1->getCString(), "fonts/arial.ttf", 24 );
	m_pLabel1->setPosition( ccp( CCDirector::sharedDirector()->getVisibleSize().width + m_pLabel1->getContentSize().width/2,
		CCDirector::sharedDirector()->getVisibleSize().height/2 + 50 ));
	m_pLabel1->setColor( ccc3(0,255,0 ));
	// move to center
	CCMoveTo* moveCenter1 = CCMoveTo::create( 0.8f , ccp( CCDirector::sharedDirector()->getVisibleSize().width/2 ,
		CCDirector::sharedDirector()->getVisibleSize().height/2 + 50));
	CCDelayTime* delayT1 = CCDelayTime::create(0.4f);
	CCMoveTo* moveout1 = CCMoveTo::create( 0.8f , ccp( -m_pLabel1->getContentSize().width/2,
		CCDirector::sharedDirector()->getVisibleSize().height/2 + 50));
	CCActionInterval* intervalAction1= CCSequence::create( moveCenter1 , delayT1 , moveout1 , NULL );
	m_pLabel1->runAction( intervalAction1 );


	// label 2
	CCString* strScore =  ConfigManager::GetInstance()->getCHStringConfig()->objectForKey("score");
	CCString* strAward   = ConfigManager::GetInstance()->getCHStringConfig()->objectForKey("award");
	CCString* goalStr2 = CCString::createWithFormat("%s %d %s", getCHStringConf("award") , holdScore , getCHStringConf("score"));
	m_pLabel2 = CCLabelTTF::create( goalStr2->getCString(), "fonts/arial.ttf", 24 );
	m_pLabel2->setPosition( ccp( CCDirector::sharedDirector()->getVisibleSize().width + m_pLabel2->getContentSize().width/2,
		CCDirector::sharedDirector()->getVisibleSize().height/2));
	m_pLabel2->setColor( ccc3(0,255,0 ));
	// move to center
	CCMoveTo* moveCenter2 = CCMoveTo::create( 1 , ccp( CCDirector::sharedDirector()->getVisibleSize().width/2 ,
		CCDirector::sharedDirector()->getVisibleSize().height/2));
	// destory callback
	CCCallFunc* callFunc2 = CCCallFunc::create(this,callfunc_selector(GameMap::PlayFinishAnimCallback));
	CCDelayTime* delayT2 = CCDelayTime::create(0.4f);
	CCMoveTo* moveout2 = CCMoveTo::create( 0.8f , ccp( -m_pLabel2->getContentSize().width/2,
		CCDirector::sharedDirector()->getVisibleSize().height/2));
	CCActionInterval* intervalAction2 = CCSequence::create( moveCenter2 , delayT2 , moveout2 , callFunc2 , NULL );
	m_pLabel2->runAction( intervalAction2 );

	this->addChild(m_pLabel1,2);
	this->addChild(m_pLabel2,2);
}

void GameMap::PlayFinishAnimCallback()
{
	this->removeChild(m_pLabel1);
	this->removeChild(m_pLabel2);
	m_pLabel1 = NULL;
	m_pLabel2 = NULL;
	NextLevel();
}

//-------------------------------------------------------------------------
//  [3/13/2015 modify by: rodking]
// des: play star game anim 
//-------------------------------------------------------------------------
void GameMap::PlayStarAnim()
{
	// play pass level condition
	CCString* goalStr1 =  CCString::createWithFormat( "%s %d" , getCHStringConf("level") ,level );
	// label 1
	m_pLabel1 = CCLabelTTF::create( goalStr1->getCString(), "fonts/arial.ttf", 24 );
	m_pLabel1->setPosition( ccp( CCDirector::sharedDirector()->getVisibleSize().width + m_pLabel1->getContentSize().width/2,
		CCDirector::sharedDirector()->getVisibleSize().height/2 + 50 ));
	m_pLabel1->setColor( ccc3(0,255,0 ));
	// move to center
	CCMoveTo* moveCenter1 = CCMoveTo::create( 0.8f , ccp( CCDirector::sharedDirector()->getVisibleSize().width/2 ,
		CCDirector::sharedDirector()->getVisibleSize().height/2 + 50));
	CCDelayTime* delayT1 = CCDelayTime::create(0.4f);
	CCMoveTo* moveout1 = CCMoveTo::create( 0.8f , ccp( -m_pLabel1->getContentSize().width/2,
		CCDirector::sharedDirector()->getVisibleSize().height/2 + 50));
	CCActionInterval* intervalAction1= CCSequence::create( moveCenter1 , delayT1 , moveout1 , NULL );
	m_pLabel1->runAction( intervalAction1 );

	
	// label 2
	CCString* goalStr2 = CCString::createWithFormat("%s %d %s",getCHStringConf("goal") , goalScore , getCHStringConf("score"));
	m_pLabel2 = CCLabelTTF::create( goalStr2->getCString(), "fonts/arial.ttf", 24 );
	m_pLabel2->setPosition( ccp( CCDirector::sharedDirector()->getVisibleSize().width + m_pLabel2->getContentSize().width/2,
		CCDirector::sharedDirector()->getVisibleSize().height/2));
	m_pLabel2->setColor( ccc3(0,255,0 ));
	// move to center
	CCMoveTo* moveCenter2 = CCMoveTo::create( 1 , ccp( CCDirector::sharedDirector()->getVisibleSize().width/2 ,
		CCDirector::sharedDirector()->getVisibleSize().height/2));
	// destory callback
	CCCallFunc* callFunc2 = CCCallFunc::create(this,callfunc_selector(GameMap::PlayStarAnimCallback));
	CCDelayTime* delayT2 = CCDelayTime::create(0.4f);
	CCMoveTo* moveout2 = CCMoveTo::create( 0.8f , ccp( -m_pLabel2->getContentSize().width/2,
		CCDirector::sharedDirector()->getVisibleSize().height/2));
	CCActionInterval* intervalAction2 = CCSequence::create( moveCenter2 , delayT2 , moveout2 , callFunc2 , NULL );
	m_pLabel2->runAction( intervalAction2 );

	this->addChild(m_pLabel1,2);
	this->addChild(m_pLabel2,2);
}

void GameMap::PlayStarAnimCallback()
{
	this->removeChild(m_pLabel1);
	this->removeChild(m_pLabel2);
	m_pLabel1 = NULL;
	m_pLabel2 = NULL;

	
	if( UIManager::GetInstance()->state == NewGame)
		m_pScoreModule->init();
	else
		m_pScoreModule->loadGame();

	 UIManager::GetInstance()->state = NewGame;
}

bool GameMap::UseRefresh()
{
	gameState = Use_Item_Refresh;
	m_pScoreModule->Refresh();
	return true;
}

bool GameMap::UseReturn()
{
	gameState = Use_Item_Return;
	m_pScoreModule->Return();
	return true;
}
//-------------------------------------------------------------------------
//  [3/12/2015 modify by: rodking]
// des: when level over go here 
//-------------------------------------------------------------------------
void GameMap::CompleteLevel()
{
	int count = m_pScoreModule->BalanceSettle();

	int holdScore = ( count < 10 ? (2000 - count * 5) : 0);
	if( holdScore > 0 ) score += holdScore;
	
	PlayFinishAnim( count , holdScore );
}

//-------------------------------------------------------------------------
//  [3/12/2015 modify by: rodking]
// des: popStar use this
//-------------------------------------------------------------------------
void GameMap::PopStarSettle( int count )
{
	
	// modify hold score
	int addScore =  pow( count , 2 ) * 5;
	score += addScore;
	
	
	CCSprite* m_pPromptSprite = NULL;
	
	// play music
	if( count >=5 && count <7 )
	{
		m_pPromptSprite = m_pGreateSprite;
		MusicManager::GetInstance()->Play( Greate_Effect_Sound );
	}
	else if( count >= 7 && count <9 )
	{
		m_pPromptSprite = m_pPrefectSprite;
		MusicManager::GetInstance()->Play( Prefect_Effect_Sound );
	}
	else if( count >= 9 )
	{
		m_pPromptSprite = m_pExcellentSprite;
		MusicManager::GetInstance()->Play( Excellent_Effect_Sound );
	}
	else
		MusicManager::GetInstance()->Play( Click_Effect_Sound );

	// play prompt sprite
	if( m_pPromptSprite != NULL )
	{
		m_pPromptSprite->setVisible( true );
		m_pPromptSprite->setAnchorPoint( ccp( 0.5f , 0.5f ));
		// start postion center
		m_pPromptSprite->setPosition( ccp( CCDirector::sharedDirector()->getVisibleSize().width/2 ,
			CCDirector::sharedDirector()->getVisibleSize().height/2));

		CCMoveTo* moveTo = CCMoveTo::create( 0.4f , ccp( CCDirector::sharedDirector()->getVisibleSize().width/2 ,
			CCDirector::sharedDirector()->getVisibleSize().height/2 + 50));
		// destory callback
		CCCallFunc* callFunc = CCCallFunc::create(this,callfunc_selector(GameMap::PlayPromptOver));
		
		CCActionInterval* intervalAction = CCSequence::create( moveTo  , callFunc , NULL );
		m_pPromptSprite->runAction(intervalAction);
		//m_pSpriteBatchNode->addChild(m_pPromptSprite);
	}

	// set prompt
	CCString* countStr =  CCString::createWithFormat( "%d%s%d%s" ,  count , getCHStringConf("attack_add") , addScore , getCHStringConf("score"));
	UIManager::GetInstance()->getUIDestoryStar()->SetPromptText(countStr->getCString());

	// save score
	CCUserDefault::sharedUserDefault()->setIntegerForKey( "score_index", score );

}

void GameMap::PlayPromptOver()
{
	m_pGreateSprite->setVisible( false );
	m_pPrefectSprite->setVisible( false );
	m_pExcellentSprite->setVisible( false );
}

int GameMap::InitGoalScore()
{
	if( level == 1 ) goalScore = 1000;
	else if( level > 1 ) goalScore = ( level - 1 ) * 3000;
	else  goalScore = 0;
	return goalScore;
}


bool GameMap::Buy( int m )
{
	if( money >= m)
	{
		money -=m;
		CCUserDefault::sharedUserDefault()->setIntegerForKey("money",money);
		CCUserDefault::sharedUserDefault()->flush();
		return true;
	}

	getPay()->pay("1000","1");
	return false;
}

int GameMap::AddMoney( int m )
{
	money+=m;
	CCUserDefault::sharedUserDefault()->setIntegerForKey("money",money);
	CCUserDefault::sharedUserDefault()->flush();
	return money;
}

void GameMap::SaveLevel()
{
	if(gameState == WAIT_START) return ;
	m_pScoreModule->SaveLevel();
	CCUserDefault::sharedUserDefault()->setIntegerForKey( "level_index",level);
}

void GameMap::Pause(){}

GameMap::~GameMap()
{
	this->unschedule( schedule_selector( GameMap::UpdateMap ) );
	this->removeAllChildren();
	m_pLabel1 = NULL;
	m_pLabel2 = NULL;
	m_pBgSprite = NULL;
	m_pScoreModule = NULL;
	m_pSpriteBatchNode = NULL;
	m_pScene = NULL;
}
