#include "TimeUtil.h"
#include "cocos2d.h"
USING_NS_CC;

int TimeUtil::GetSystemTime( int type)
{
	struct tm *tm;  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	//win32平台  
	time_t timep;  
	time(&timep);  
	tm = localtime(&timep);  
#else  
	//android、ios平台  

	struct cc_timeval now;  
	CCTime::gettimeofdayCocos2d(&now, NULL);  
	tm = localtime(&now.tv_sec);  
#endif  
	int year = tm->tm_year + 1900;  
	int month = tm->tm_mon + 1;  
	int day = tm->tm_mday;  
	int hour=tm->tm_hour;  
	int min=tm->tm_min;  

	switch ( type )
	{
	case Year:
		{
			return year;
		}
	case Moth:
		{
			return month;
		}
	case Day:
		{
			return day;
		}
	}
	return 0;
}

