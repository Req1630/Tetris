#include "Console/Console.h"
#include "FrameRate/FrameRate.h"
#include "Scene/SceneManager.h"
#include "Scene/Scenes.h"

int main()
{
	// コンソールの初期化.
	if( FAILED( CConsole::Init() )) return 0;

	// フレームレート(FPS)の初期化.
	CFrameRate::Init();

	// シーンマネージャーの作成.
	std::shared_ptr<CSceneManager> pSceneManager 
		= std::make_shared<CSceneManager>( std::make_shared<CGameScene>( pSceneManager ) );

	while(1){
		CFrameRate::Start();	// FPSの計測スタート.

#ifdef _DEBUG
		if( GetAsyncKeyState(VK_ESCAPE) & 0x0001 ){
			break;
		}
#endif	// #ifdef _DEBUG.

		pSceneManager->Update();
		pSceneManager->Render();

		CFrameRate::Wait();		// FPS計測後の待機.
	}

	pSceneManager->Release();
	if( FAILED( CConsole::Destroy() ) ) return 0;

	return 0;
}