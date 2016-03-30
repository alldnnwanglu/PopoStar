#include "UIBase.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

UIBase::UIBase():m_pUILayer( NULL ), m_pWidget(NULL), m_fileName("")
{
	m_pCustomData = NULL;
}

UIBase::~UIBase()
{
	m_pWidget = NULL;
	m_pUILayer = NULL;
	m_pCustomData = NULL;
}

bool UIBase::init()
{
	if( CCLayer::init() && strlen( m_fileName ) > 0 )
	{
		m_pUILayer = UILayer::create();
		addChild(m_pUILayer);

		m_pWidget = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile( m_fileName ));
		m_pUILayer->addWidget( m_pWidget );
		return true;
	}
	return false;
}

void UIBase::activate( )
{
	setVisible( true );
	m_pWidget->setEnabled( true );
}

void UIBase::deactivate()
{
	setVisible( false );
	m_pWidget->setEnabled( false );
}


