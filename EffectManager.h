//
//  EffectManager.h
//  StarPlane
//
//  Created by shaoleibo on 15-3-1.
//
//

#ifndef __StarPlane__EffectManager__
#define __StarPlane__EffectManager__

#include "cocos2d.h"
#include "Effect.h"
#include <map>
#include <vector>
class EffectManager : public ::cocos2d::CCObject
{
public:
    static EffectManager& getInstance()
	{
		static EffectManager instance;
		return instance;
	}
    void addEffect( EffectInfo& effectInfo );
    void removeEffect(EffectNode* effectNode);
	void removeEffect(EffectNode* effectNode, const char* effectName);
	void removeAllEffect();
    void tick(float dt);
    void pauseTick();
    void resumeTick();
private:
	EffectManager();
	EffectManager(const EffectManager&);
	EffectManager& operator=(const EffectManager&);
	~EffectManager();
private:
	std::map<EffectNode*, std::vector<Effect*> > effectDic;
};



#endif /* defined(__StarPlane__EffectManager__) */
