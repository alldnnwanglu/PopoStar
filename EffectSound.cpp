#include "EffectSound.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

EffectSound::EffectSound( const char* fileName , int type )
{
	char* str = (char*)malloc(100);
	std::strcpy(str,fileName);
	m_fileName = str;
	m_type = type;
	init();
}

bool EffectSound::init()
{
	SimpleAudioEngine::sharedEngine()->preloadEffect( m_fileName );
	return true;
}

bool EffectSound::play()
{
	m_nSoundId = SimpleAudioEngine::sharedEngine()->playEffect( m_fileName );
	return true;
}

bool EffectSound::stop()
{
	SimpleAudioEngine::sharedEngine()->stopEffect( m_nSoundId );
	return true;
}

EffectSound::~EffectSound()
{
	SimpleAudioEngine::sharedEngine()->unloadEffect( m_fileName );
}