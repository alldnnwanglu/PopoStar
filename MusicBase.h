#ifndef Music_MusicBase_h
#define Music_MusicBase_h

#include "cocos2d.h"
#include "cocos-ext.h"

class MusicBase : public ::cocos2d::CCObject
{
public:
	MusicBase();
	~MusicBase();
	virtual int GetType() const { return m_type; }
	virtual bool play();
	virtual bool stop();

protected:
    char*		m_fileName;
	int				m_type;

};


#endif