#ifndef CONSOLE_H
#define CONSOLE_H

#include "..\SingletonBase\SingletonBase.h"

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

enum class enColor
{
	L_BLACK,	// 低輝度・黒色
	L_BLUE,		// 低輝度・青色
	L_GREEN,	// 低輝度・緑色
	L_CYAN,		// 低輝度・水色
	L_RED,		// 低輝度・赤色
	L_PURPLE,	// 低輝度・紫色
	L_YELLOW,	// 低輝度・黄色
	L_WHITE,	// 低輝度・白色

	H_BLACK,	// 高輝度・黒色
	H_BLUE,		// 高輝度・青色
	H_GREEN,	// 高輝度・緑色
	H_CYAN,		// 高輝度・水色
	H_RED,		// 高輝度・赤色
	H_PURPLE,	// 高輝度・紫色
	H_YELLOW,	// 高輝度・黄色
	H_WHITE,	// 高輝度・白色
};

class CConsole : public CSingletonBase<CConsole>
{
public:
	CConsole();
	~CConsole();

	static HRESULT Init();
	static HRESULT Destroy();

	template<class... T1>
	static void Draw( int x, int y, const T1&... t1 )
	{
		COORD coord = { (SHORT)x, (SHORT)y };
		SetConsoleCursorPosition( GetInstance()->m_hConStdOut, coord );

		std::string out = GetInstance()->initstring( t1... );
		cout << out << endl;
	}

	static void SetColor( int fore, int back );

	static void Clear( int x, int y, const char *c, enColor f = enColor::L_WHITE, enColor b = enColor::L_BLACK );

	HANDLE GetHandle();

private:
	template <class T>
	std::string to_std_string( const T& x )
	{
		std::stringstream ss;
		ss << x;
		return ss.str();
	}
	template<class T1, class... T2>
	std::string initstring( const T1& t1, const T2&... t2 )
	{
		std::string s = to_std_string( t1 );
		return s + initstring( t2... );
	}
	template<class T1>
	std::string initstring( const T1& t1 )
	{
		std::string s = to_std_string( t1 );
		return s;
	}

private:
	HANDLE m_hConStdOut;
};

#endif // #ifndef CONSOLE_H.