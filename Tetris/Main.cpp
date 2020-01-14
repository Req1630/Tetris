#include "Console/Console.h"
#include "FrameRate/FrameRate.h"

void StageDraw()
{
}

int main()
{
	// ƒRƒ“ƒ\[ƒ‹‚Ì‰Šú‰».
	if( FAILED( CConsole::Init() )) return 0;
	CFrameRate::Init();

	while(1){
		CFrameRate::Start();
		if( GetAsyncKeyState(VK_ESCAPE) & 0x0001 ) break;

		StageDraw();

		CFrameRate::Wait();
	}

	if( FAILED( CConsole::Destroy() ) ) return 0;

	return 0;
}