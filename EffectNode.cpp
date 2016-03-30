#include "EffectNode.h"
#include "EffectManager.h"

EffectNode::~EffectNode()
{
	EffectManager::getInstance().removeEffect(this);
}

