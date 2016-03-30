#ifndef HELLOCPP_IAPCALLBACK_H
#define HELLOCPP_IAPCALLBACK_H

class IAPCallback
{
public:
	static void PaySucess( int pointNum );
	static void PayFailed( int errorCode, int pointNum );
};

#endif