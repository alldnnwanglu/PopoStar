#ifndef UI_UIBase_h
#define UI_UIBase_h

#include "cocos2d.h"
#include "cocos-ext.h"

class UIBase : public ::cocos2d::CCLayer
{
public:
	UIBase();
	virtual ~UIBase();
	virtual bool init();
	virtual void activate();
	virtual void deactivate();
	CC_SYNTHESIZE( ::cocos2d::CCObject*, m_pCustomData, CustomData );
protected:
	::cocos2d::ui::UILayer*  m_pUILayer;
	::cocos2d::ui::Layout*   m_pWidget;
	const char* m_fileName;
};


#endif