#ifndef UI_UIManager_h
#define UI_UIManager_h
#include "MacrosDefine.h"
#include "UIDestoryStar.h"
#include "UILaoHuJi.h"
#include "UIUseItem.h"
#include "UISingleIn.h"
#include "UILevelFail.h"
#include "UIWelcome.h"
#include "StopMenuUI.h"
#include "pay/SWXPayUI.h"
enum
{
	NewGame,
	LoadGame,
};
class UIManager
{
private:
	UIManager();

protected:
	UIDestoryStar*			m_pDestoryStar;
	UILaoHuJi*				m_pLaoHuJi;
	UIUseItem*				m_pUseItem;
	UISingleIn*				m_pUISingleIn;
	UILevelFail*			m_pUILevelFail;
	UIWelcome*				m_pUIWelcome;
	StopMenuUI*				m_pStopMenuUI;
	//KLWPayUI*				m_pKLWPayUI;

public:
	static UIManager* GetInstance()
	{
		static UIManager instance;
		return &instance;
	}

	SWX_PROPERTY( UIDestoryStar* , m_pDestoryStar , UIDestoryStar );
	SWX_PROPERTY( UILaoHuJi* , m_pLaoHuJi , UILaoHuJi );
	SWX_PROPERTY( UIUseItem* , m_pUseItem , UIUseItem );
	SWX_PROPERTY( UISingleIn* , m_pUISingleIn , UISingleIn );
	SWX_PROPERTY( UILevelFail* , m_pUILevelFail , UILevelFail );
	SWX_PROPERTY( UIWelcome* , m_pUIWelcome , UIWelcome );
	SWX_PROPERTY( StopMenuUI* , m_pStopMenuUI , StopMenuUI );
	CC_SYNTHESIZE(SWXPayUI*, m_pKLWPayUI, PayUI);
	void update( float dt );

	virtual ~UIManager()
	{
		m_pDestoryStar = NULL;
		m_pLaoHuJi = NULL;
		m_pUseItem = NULL;
		m_pUISingleIn = NULL;
		m_pUILevelFail = NULL;
		m_pUIWelcome = NULL;
		m_pStopMenuUI = NULL;
	}

public:
	int						state;
};

#endif
