//
//  Effect.h
//  StarPlane
//
//  Created by shaoleibo on 15-3-1.
//
//

#ifndef Bg_Sound_h
#define Bg_Sound_h

#include "cocos2d.h"
#include "MusicBase.h"

class BgSound : public MusicBase
{
public:
	virtual bool init();
	CREATE_FUNC(BgSound);
	~BgSound();

	bool play();
	bool stop();

};



#endif
