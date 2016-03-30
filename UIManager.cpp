#include "UIManager.h"

UIManager::UIManager()
{
	state = NewGame;
}

void UIManager::update( float dt )
{
	if( m_pDestoryStar != NULL )
		m_pDestoryStar->update( dt );

	if( m_pLaoHuJi != NULL )
		m_pLaoHuJi->update( dt );
}