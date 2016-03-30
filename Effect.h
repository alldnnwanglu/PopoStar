//
//  Effect.h
//  StarPlane
//
//  Created by shaoleibo on 15-3-1.
//
//

#ifndef StarPlane_Effect_h
#define StarPlane_Effect_h

#include "cocos2d.h"
#include "EffectNode.h"

enum
{
	ELEMENT_TYPE_ANIM,
	ELEMENT_TYPE_PARTICLE,
};

class EffectInfo
{
public:
	int m_elementType;
    ::cocos2d::CCPoint m_startPixelPos;
    float m_startTime;
	float m_duration;
    int   m_zorder;
    std::string m_effectName;
    std::string m_elementFilePath;
    EffectNode* m_effectParent;
public:
    EffectInfo()
    {
        m_startTime = 0;
        m_zorder = 65535;
    }
};

class Effect
{
public:
    Effect(void);
	~Effect(void);
    void tick( float dt );
    void init();
    void setEffectInfo(EffectInfo& ei);
    void stop();
    void reset();
    bool isDead();
	CC_SYNTHESIZE(bool, m_isPlaying, IsPlaying);
	CC_SYNTHESIZE_READONLY(::cocos2d::CCNode*, m_displayNode, DisplayNode);
private:
	EffectInfo m_effectInfo;
	float m_sElapsed;
    float m_dElapsed;
    void addElement();
    void removeElement();
};



#endif
