//
//  GameMap.h
//  HelloCpp
//
//  Created by shaoleibo on 15-2-2.
//  Copyright (c) 2015年 Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef HelloCpp_GameMap_h
#define HelloCpp_GameMap_h
#include "cocos2d.h"
#include "ObjectPool.h"
#include<vector>
#include <map>
#include "Effect.h"
#include "StarContainer.h"
#include "GameItemManager.h"
#include "pay/IAndroidPay.h"
enum
{
	WAIT_START,
	NORMAL,
	Use_Item_Lolly,
	Use_Item_Candy,
	Use_Item_Refresh,
	Use_Item_Return,
};
class StarContainer;
class GameMap : public EffectNode
{
private:
    GameMap();
	~GameMap();
	int InitGoalScore();
public:
	float								cellHeight;
	float								cellWidth;
	int									money;

private:
	float								maxTop;
	float								maxWidth;
	int									level;
	int									goalScore;
	int									historyMaxScore;
	int									gameState;
	int									score;
	StarContainer*						m_pScoreModule;
	::cocos2d::CCSprite*				m_pBgSprite;

	::cocos2d::CCSprite*				m_pGreateSprite;
	::cocos2d::CCSprite*				m_pPrefectSprite;
	::cocos2d::CCSprite*				m_pExcellentSprite;
	
	::cocos2d::CCLabelTTF*				m_pLabel1;
	::cocos2d::CCLabelTTF*				m_pLabel2;

protected:
	::cocos2d::CCScene*					m_pScene;
	::cocos2d::CCSpriteBatchNode*		m_pSpriteBatchNode;
    float								m_fTotalTime;

protected:
	virtual void LoadRes();
	void PlayPromptOver();
	void PlayStarAnim();
	void PlayStarAnimCallback();
	void PlayFinishAnim( int count , int holdScore);
	void PlayFinishAnimCallback();

public:
    static GameMap* GetInstance()
    {
        static GameMap instance;
        return &instance;
    }

	CC_SYNTHESIZE( IAndroidPay*, m_pPay, Pay );
	
	int getScore() const { return score; };
	int getLevel() const { return level; };
	int setLevel( int lv ) { level = lv;  return lv; };
	int getHistoryScore() const { return historyMaxScore; };
	int getGlobalScore() const { return goalScore; };
	bool Buy( int m );
	int AddMoney( int m );
	void SaveLevel();
	
	const char* getCHStringConf( const char* key);

	void SetScene( ::cocos2d::CCScene* scene );
	::cocos2d::CCScene* GetScene() const{ return m_pScene; };
	StarContainer* GetScoreModule() const { return m_pScoreModule; };
	GameItemManager* ItemMgr() const { return GameItemManager::GetInstance(); };
	::cocos2d::CCSpriteBatchNode* getSpriteBatchBode() const { return m_pSpriteBatchNode; };

	int GetGameState() const { return gameState;};
	void SetGameStage( int state) { gameState = state; };
	virtual bool init();
    virtual void update( float dt );
    virtual void UpdateMap( float dt );
	virtual void CompleteLevel();
	virtual void PopStarSettle( int count );

	bool UseRefresh();
	bool UseReturn();

	void LoadLevel();
	void NextLevel();
	void LevelReset();
	void GoNoNetLevel();
	void Pause();
};
#endif
