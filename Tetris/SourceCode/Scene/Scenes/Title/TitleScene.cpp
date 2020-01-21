#include "TitleScene.h"
#include "..\..\..\Console\Console.h"
#include "..\..\..\Game\Stage\Stage.h"
#include "..\Game\GameScene.h"
#include "..\..\SceneManager.h"
#include "..\..\..\Field\Field.h"

#include <memory>

CTitleScene::CTitleScene( sceneManager sceneManager )
	: CSceneBase( sceneManager )

	, m_Select	( Start )
{
	CField::SetFadeOut();
	CField::Render();
	CField::SetTitle();
	CField::Render();
}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::Update()
{
	if( GetAsyncKeyState(VK_UP) & 0x0001 ){
		m_Select = Start;
		m_NoSelect = End;
	}
	if( GetAsyncKeyState(VK_DOWN) & 0x0001 ){
		m_Select = End;
		m_NoSelect = Start;
	}
	if( GetAsyncKeyState( VK_RETURN ) & 0x0001 ){
		switch( m_Select ){
			case Start:
				m_pSceneManager->Change( std::make_shared<CGameScene>(m_pSceneManager) );
				
				break;
			case End:
				m_isGameEnd = true;

				break;
		}
	}
}

void CTitleScene::Render()
{
	CConsole::SetColor( (int)enColor::H_WHITE, (int)enColor::L_BLACK );
	CConsole::Draw( 32, 14, "START" );
	CConsole::SetColor( (int)enColor::H_WHITE, (int)enColor::L_BLACK );
	CConsole::Draw( 33, 16, "END" );
	CConsole::SetColor( (int)enColor::L_BLACK, (int)enColor::L_BLACK );
	CConsole::Draw( 29, m_NoSelect+14, ">" );
	CConsole::SetColor( (int)enColor::H_WHITE, (int)enColor::L_BLACK );
	CConsole::Draw( 29, m_Select+14, ">" );
}