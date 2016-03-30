#ifndef Time_Util_h
#define Time_Util_h
enum
{
	Year,
	Moth,
	Day,
};
class TimeUtil
{
public:
	static int GetSystemTime( int type);
};

#endif