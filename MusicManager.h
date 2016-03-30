#ifndef Music_MusicManager_h
#define Music_MusicManager_h
#include "BgSound.h"
#include "MacrosDefine.h"
#include "EffectSound.h"

enum
{
	BG_SOUND,
	Click_Effect_Sound,
	Greate_Effect_Sound,
	Prefect_Effect_Sound,
	Excellent_Effect_Sound,
};

class MusicManager
{
private:
	MusicManager();

protected:
	BgSound*				m_pBgSound;
	EffectSound*			m_pGreateSound;
	EffectSound*			m_pPrefectSound;
	EffectSound*			m_pExcellentSound;
	EffectSound*			m_pClickSound;
	bool					isStopMusic;

public:
	static MusicManager* GetInstance()
	{
		static MusicManager instance;
		return &instance;
	}

	bool Stop();
	bool Open();
	bool Play(int type);

	SWX_PROPERTY( BgSound*, m_pBgSound, BgSound );
	void setGreateSound(EffectSound* sound) { m_pGreateSound = sound;};
	void setPrefectSound(EffectSound* sound) { m_pPrefectSound = sound;};
	void setExcellentSound(EffectSound* sound) { m_pExcellentSound = sound;};
	void setClickSound(EffectSound* sound) { m_pClickSound = sound;};

	~MusicManager();
};

#endif