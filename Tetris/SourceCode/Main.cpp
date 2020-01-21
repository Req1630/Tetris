#include "Console/Console.h"
#include "FrameRate/FrameRate.h"
#include "Scene/SceneManager.h"
#include "Scene/Scenes.h"
#include "Field/Field.h"

int main()
{
	// コンソールの初期化.
	if( FAILED( CConsole::Init() )) return 0;

	// フレームレート(FPS)の初期化.
	CFrameRate::Init();

	CField::FieldDataRead();

	// シーンマネージャーの作成.
	std::shared_ptr<CSceneManager> pSceneManager 
		= std::make_shared<CSceneManager>();

	pSceneManager->Push( std::make_shared<CTitleScene>( pSceneManager ) );

	while(1){
		CFrameRate::Start();	// FPSの計測スタート.

#ifdef _DEBUG
		if( GetAsyncKeyState(VK_ESCAPE) & 0x0001 ) break;
#endif	// #ifdef _DEBUG.
		if( pSceneManager->GetGameEnd() == true ) break;

		pSceneManager->Update();
		pSceneManager->Render();

		CFrameRate::Wait();		// FPS計測後の待機.
	}

	pSceneManager->Release();
	if( FAILED( CConsole::Destroy() ) ) return 0;

	return 0;
}