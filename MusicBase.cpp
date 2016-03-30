#include "MusicBase.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

MusicBase::MusicBase(): m_fileName((char*)malloc(100))
{
}

MusicBase::~MusicBase()
{
}

bool MusicBase::play()
{
	return true;
}

bool MusicBase::stop()
{
	return true;
}
