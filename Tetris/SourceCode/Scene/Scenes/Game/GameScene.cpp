#include "GameScene.h"
#include "..\..\..\Console\Console.h"
#include "..\..\..\Game\Stage\Stage.h"
#include "..\Title\TitleScene.h"
#include "..\..\SceneManager.h"
#include "..\..\..\Field\Field.h"

CGameScene::CGameScene( sceneManager sceneManager )
	: CSceneBase	( sceneManager )
	, m_pStage		( std::make_unique<CStage>() )
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
	if( m_pStage->GetGameEnd() == true ){
		m_pSceneManager->Change( std::make_shared<CTitleScene>( m_pSceneManager ) );
	}
}

void CGameScene::Render()
{
	m_pStage->Render();
}