#include "GameScene.h"
#include "..\..\..\Console\Console.h"

CGameScene::CGameScene( sceneManager sceneManager )
	: CSceneBase ( sceneManager )
{
	m_pField->SetFadeIn();
}

CGameScene::~CGameScene()
{
}

void CGameScene::Update()
{
	// フェード中なので終了.
	if( m_pField->IsNotFade() == false ) return;
}

void CGameScene::Render()
{
	m_pField->Render();	// フィールドの表示.
}