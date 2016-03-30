//
//  Effect.cpp
//  StarPlane
//
//  Created by shaoleibo on 15-3-1.
//
//

#include "BgSound.h"
#include "SimpleAudioEngine.h"
#include "MusicManager.h"
#include "ConfigManager.h"
USING_NS_CC;
using namespace CocosDenshion;

bool BgSound::init()
{
	CCString* strMusic =  ConfigManager::GetInstance()->getCHStringConfig()->objectForKey("bg_music");
	char* str = (char*)malloc(100);
	std::strcpy(str,strMusic->getCString());
	m_fileName = str;

	m_type = BG_SOUND;
	return true;
}

bool BgSound::play()
{
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	if (!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(m_fileName, true);
	return true;
}

bool BgSound::stop()
{
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	return true;
}

BgSound::~BgSound()
{
	SimpleAudioEngine::sharedEngine()->unloadEffect( m_fileName );
}