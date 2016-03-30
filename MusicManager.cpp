#include "MusicManager.h"
#include "BgSound.h"
#include "SimpleAudioEngine.h"
#include "ConfigManager.h"

USING_NS_CC;
using namespace CocosDenshion;

MusicManager::MusicManager()
{
}

bool MusicManager::Stop()
{
	isStopMusic = true;
	m_pBgSound->stop();
	return true;
}

bool MusicManager::Open()
{
	isStopMusic = false;
	m_pBgSound->play();
	return true;
}

bool MusicManager::Play( int type )
{
	if(isStopMusic) return false;

	switch ( type )
	{
	case BG_SOUND:
		{
			m_pBgSound->play();
			break;
		}
	case Click_Effect_Sound:
		{
			m_pClickSound->play();
			break;
		}
	case Greate_Effect_Sound:
		{
			m_pGreateSound->play();
			break;
		}
	case Prefect_Effect_Sound:
		{
			m_pPrefectSound->play();
			break;
		}
	case Excellent_Effect_Sound:
		{
			m_pExcellentSound->play();
			break;
		}
	}

	return true;
}

MusicManager::~MusicManager()
{
	m_pBgSound = NULL;
	m_pGreateSound = NULL;
	m_pPrefectSound = NULL;
	m_pExcellentSound = NULL;
	m_pClickSound = NULL;

	SimpleAudioEngine::sharedEngine()->end();
}