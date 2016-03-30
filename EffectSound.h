//
//  EffectSound.h
//
//  Created by rodking on 15-3-10.
//
//

#ifndef Effect_Sound_h
#define Effect_Sound_h

#include "cocos2d.h"
#include "MusicBase.h"

class EffectSound : public MusicBase
{
public:
	int			m_nSoundId;

public:
	virtual bool init();
	EffectSound( const char* fileName , int type );
	~EffectSound();

	bool play();
	bool stop();

};



#endif
