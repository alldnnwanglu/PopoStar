#ifndef Config_Manager_h
#define Config_Manager_h

#include "MacrosDefine.h"
#include "CHStringConfig.h"

class ConfigManager
{
private:
	ConfigManager();

protected:
	CHStringConfig*			m_pChStringConf;

public:
	static ConfigManager* GetInstance()
	{
		static ConfigManager instance;
		return &instance;
	}

	SWX_PROPERTY( CHStringConfig* , m_pChStringConf , CHStringConfig );

	~ConfigManager();

};

#endif