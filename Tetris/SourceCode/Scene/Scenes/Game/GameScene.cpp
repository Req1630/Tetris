#include "GameScene.h"
#include "..\..\..\Console\Console.h"
#include "..\..\..\Game\Stage\Stage.h"

CGameScene::CGameScene( sceneManager sceneManager )
	: CSceneBase	( sceneManager )
	, m_pStage		( std::make_unique<CStage>() )
{
	srand(time(NULL));

	m_pField->SetFadeIn();
	m_pStage->CreateStage();
	m_pStage->CreateBlock();
	m_pStage->InitNowPosition();
	m_pField->Render();	// フィールドの表示.
}

CGameScene::~CGameScene()
{
}

void CGameScene::Update()
{
	m_pStage->Update();
}

void CGameScene::Render()
{
	m_pStage->Render();
}