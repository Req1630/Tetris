#include "Console.h"

CConsole::CConsole()
	: m_hConStdOut	( nullptr )
{
}

CConsole::~CConsole()
{
}

HRESULT CConsole::Init()
{
	GetInstance()->m_hConStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if( GetInstance()->m_hConStdOut == nullptr ) return E_FAIL;

	CONSOLE_CURSOR_INFO cci;
	// CONSOLE_CURSOR_INFO構造体の現在の状態を取得する.
	bool isGetCursorInfo = GetConsoleCursorInfo( GetInstance()->m_hConStdOut, &cci );
	if( isGetCursorInfo == false ) return E_FAIL;

	// メンバ変数であるbVisibleがカーソルの表示・非表示を制御する変数なので、
	// これをFALSEにする事でカーソルを非表示にできる.
	cci.bVisible = FALSE;

	// 変更した構造体情報をコンソールWindowにセットする.
	bool isSetCursorInfo = SetConsoleCursorInfo( GetInstance()->m_hConStdOut, &cci );
	if( isSetCursorInfo == false ) return E_FAIL;

	return S_OK;
}

HRESULT CConsole::Destroy()
{
	bool isClosedHandle = false;
	if( GetInstance()->m_hConStdOut != INVALID_HANDLE_VALUE ){
		isClosedHandle = CloseHandle( GetInstance()->m_hConStdOut );
	}
	if( isClosedHandle == false ) return E_FAIL;

	return S_OK;
}

void CConsole::SetColor( int fore, int back )
{
	WORD wFore = fore;
	WORD wBack = back;
	SetConsoleTextAttribute( GetInstance()->m_hConStdOut, wFore + (wBack << 4) );
}

void CConsole::Clear( int x, int y, const char *c, enColor f , enColor b )
{
	SetColor( static_cast<int>(f), static_cast<int>(b) );
	GetInstance()->Draw ( x, y, c );
}

HANDLE CConsole::GetHandle()
{
	return m_hConStdOut;
}