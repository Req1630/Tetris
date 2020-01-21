#include "Console/Console.h"
#include "FrameRate/FrameRate.h"
#include "Scene/SceneManager.h"
#include "Scene/Scenes.h"
#include "Field/Field.h"

int main()
{
	// �R���\�[���̏�����.
	if( FAILED( CConsole::Init() )) return 0;

	// �t���[�����[�g(FPS)�̏�����.
	CFrameRate::Init();

	CField::FieldDataRead();

	// �V�[���}�l�[�W���[�̍쐬.
	std::shared_ptr<CSceneManager> pSceneManager 
		= std::make_shared<CSceneManager>();

	pSceneManager->Push( std::make_shared<CTitleScene>( pSceneManager ) );

	while(1){
		CFrameRate::Start();	// FPS�̌v���X�^�[�g.

#ifdef _DEBUG
		if( GetAsyncKeyState(VK_ESCAPE) & 0x0001 ) break;
#endif	// #ifdef _DEBUG.
		if( pSceneManager->GetGameEnd() == true ) break;

		pSceneManager->Update();
		pSceneManager->Render();

		CFrameRate::Wait();		// FPS�v����̑ҋ@.
	}

	pSceneManager->Release();
	if( FAILED( CConsole::Destroy() ) ) return 0;

	return 0;
}