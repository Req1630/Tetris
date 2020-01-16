#include "Console/Console.h"
#include "FrameRate/FrameRate.h"
#include "Scene/SceneManager.h"
#include "Scene/Scenes.h"

int main()
{
	// �R���\�[���̏�����.
	if( FAILED( CConsole::Init() )) return 0;

	// �t���[�����[�g(FPS)�̏�����.
	CFrameRate::Init();

	// �V�[���}�l�[�W���[�̍쐬.
	std::shared_ptr<CSceneManager> pSceneManager 
		= std::make_shared<CSceneManager>( std::make_shared<CGameScene>( pSceneManager ) );

	while(1){
		CFrameRate::Start();	// FPS�̌v���X�^�[�g.

#ifdef _DEBUG
		if( GetAsyncKeyState(VK_ESCAPE) & 0x0001 ){
			break;
		}
#endif	// #ifdef _DEBUG.

		pSceneManager->Update();
		pSceneManager->Render();

		CFrameRate::Wait();		// FPS�v����̑ҋ@.
	}

	pSceneManager->Release();
	if( FAILED( CConsole::Destroy() ) ) return 0;

	return 0;
}