#include "ConfigManager.h"

ConfigManager::ConfigManager()
{
	m_pChStringConf = CHStringConfig::create();
	m_pChStringConf->retain();
}

ConfigManager::~ConfigManager()
{
	m_pChStringConf = NULL;
}
