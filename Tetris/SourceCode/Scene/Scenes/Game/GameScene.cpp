#include "GameScene.h"
#include "..\..\..\Console\Console.h"
#include "..\..\..\Game\Stage\Stage.h"
#include "..\Title\TitleScene.h"
#include "..\..\SceneManager.h"
#include "..\..\..\Field\Field.h"
#include "..\..\..\Game\Score\Score.h"
#include "..\..\..\Game\Level\Level.h"

CGameScene::CGameScene( sceneManager sceneManager )
	: CSceneBase	( sceneManager )
	, m_pStage		( std::make_unique<CStage>() )
	, m_pScore		( std::make_unique<CScore>() )
	, m_pLevel		( std::make_unique<CLevel>() )
{	
	CField::SetFadeIn();
	m_pStage->CreateStage();
	m_pStage->CreateBlock();
	m_pStage->InitNowPosition();
	CField::Render();	// フィールドの表示.
}

CGameScene::~CGameScene()
{
}

void CGameScene::Update()
{
	m_pStage->Update();
	m_pScore->SetDeleteLine( m_pStage->GetDeleteLine() );
	m_pLevel->SetDeleteLine( m_pStage->GetDeleteLine() );
	m_pStage->SetDownTime( m_pLevel->GetDownTime() );
	if( m_pStage->GetGameEnd() == true ){
		m_pSceneManager->Change( std::make_shared<CTitleScene>( m_pSceneManager ) );
	}
}

void CGameScene::Render()
{
	m_pStage->Render();
	m_pScore->Render();
	m_pLevel->Render();
}