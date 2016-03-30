#include "IAPCallback.h"
#include "GameMap.h"

#if defined( PAY_WITH_UMENG )
#include "MobClickCpp.h"
#endif

void IAPCallback::PaySucess( int pointNum )
{
	GameMap* gMap = GameMap::GetInstance();
	if (gMap == NULL) return;

	GameMap::GetInstance()->AddMoney(160);
#if defined( PAY_WITH_UMENG )
	umeng::MobClickCpp::pay(10, 25, 160);
#endif
}


void IAPCallback::PayFailed( int errorCode, int pointNum )
{
}