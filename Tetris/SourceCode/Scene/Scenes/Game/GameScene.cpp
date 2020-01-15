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
	// �t�F�[�h���Ȃ̂ŏI��.
	if( m_pField->IsNotFade() == false ) return;
}

void CGameScene::Render()
{
	m_pField->Render();	// �t�B�[���h�̕\��.
}