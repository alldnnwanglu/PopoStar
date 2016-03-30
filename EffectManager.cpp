//
//  EffectManager.cpp
//  StarPlane
//
//  Created by shaoleibo on 15-3-1.
//
//

#include "EffectManager.h"
USING_NS_CC;

EffectManager::EffectManager(void)
{
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(EffectManager::tick), this, 0, false);
	CCDirector::sharedDirector()->getScheduler()->pauseTarget(this);
}

EffectManager::~EffectManager(void)
{
	removeAllEffect();
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(EffectManager::tick), this);
}

void EffectManager::pauseTick()
{
	CCDirector::sharedDirector()->getScheduler()->pauseTarget(this);
}

void EffectManager::resumeTick()
{
	if (effectDic.size()>0)
	{
		CCDirector::sharedDirector()->getScheduler()->resumeTarget(this);
	}
}

void EffectManager::addEffect( EffectInfo &effectInfo )
{
    if ( effectInfo.m_elementFilePath=="" || !effectInfo.m_effectParent )
	{
		return;
	}
    Effect* effect = new Effect();
	effect->setEffectInfo(effectInfo);
	effect->init();
	std::map<EffectNode*, std::vector<Effect*> >::iterator itr = effectDic.find(effectInfo.m_effectParent);
	if (itr!=effectDic.end())
	{
		itr->second.push_back( effect );
	}
	else
	{
		std::vector<Effect*> effVec;
		effVec.push_back( effect );
		effectDic.insert(std::map<EffectNode*, std::vector<Effect*> >::value_type(effectInfo.m_effectParent, effVec));
	}
	if (effectDic.size()==1)
	{
		CCDirector::sharedDirector()->getScheduler()->resumeTarget(this);
	}
}

void EffectManager::removeEffect(EffectNode* effectNode)
{
	if( effectDic.empty() )
	{
		return;
	}
	std::map<EffectNode*, std::vector<Effect*> >::iterator dicItr = effectDic.find(effectNode);
	if (dicItr!=effectDic.end())
	{
		std::vector<Effect*>::iterator itr = dicItr->second.begin();
		while (itr!=dicItr->second.end())
		{
			if (*itr)
			{
				delete *itr;
			}
			itr = dicItr->second.erase( itr );
		}
		effectDic.erase(dicItr);
	}
}


void EffectManager::removeAllEffect()
{
	if( effectDic.empty() )
		return;
	std::map<EffectNode*, std::vector<Effect*> >::iterator dicItr = effectDic.begin();
	std::vector<Effect*>::iterator itr = dicItr->second.begin();
	for (;dicItr!=effectDic.end();dicItr++)
	{
		for (;itr!=dicItr->second.end();itr++)
		{
			if (*itr)
			{
				delete *itr;
			}
		}
	}
	std::map<EffectNode*, std::vector<Effect*> > blank;
	effectDic.swap(blank);
}

void EffectManager::tick(float dt)
{
	std::map<EffectNode*, std::vector<Effect*> >::iterator dicItr = effectDic.begin();
	std::vector<Effect*>::iterator itr;
	while (dicItr!=effectDic.end())
	{
		itr = dicItr->second.begin();
		while (itr!=dicItr->second.end())
		{
			(*itr)->tick(dt);
			if ((*itr)->isDead())
			{
				if (*itr)
				{
					delete *itr;
				}
				itr = dicItr->second.erase(itr);
			}
			else
			{
				++itr;
			}
		}
		if (dicItr->second.size()==0)
		{
			effectDic.erase(dicItr++);
		}
		else
		{
			++dicItr;
		}
	}
	if (effectDic.size()==0)
	{
		CCDirector::sharedDirector()->getScheduler()->pauseTarget(this);
	}
}




