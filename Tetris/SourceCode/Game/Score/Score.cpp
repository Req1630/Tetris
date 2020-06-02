#include "Score.h"
#include "..\..\Console\Console.h"

CScore::CScore()
	: m_Score	( 0 )
{
}

CScore::~CScore()
{
}

//-------------------------.
// 描画.
//-------------------------.
void CScore::Render()
{
	CConsole::SetColor( (int)enColor::H_WHITE, (int)enColor::L_BLACK );
	CConsole::Draw( 39, 18, "Score : ", m_Score );
}

//-------------------------.
// 消したラインの取得.
//-------------------------.
void CScore::SetDeleteLine( const int& line )
{
	enDELETE_LINE deleteLine = static_cast<enDELETE_LINE>(line);
	int addScore = 0;
	switch( deleteLine )
	{
	case enDELETE_LINE::None:
		addScore = enADD_SCORE::None;
		break;
	case enDELETE_LINE::SINGLE:
		addScore = enADD_SCORE::SINGLE;
		break;
	case enDELETE_LINE::DOUBLE:
		addScore = enADD_SCORE::DOUBLE;
		break;
	case enDELETE_LINE::TRIPLE:
		addScore = enADD_SCORE::TRIPLE;
		break;
	case enDELETE_LINE::TETRIS:
		addScore = enADD_SCORE::TETRIS;
		// テトリスの場合beep音を再生.
		Beep( 440, 50 );
		Beep( 587, 50 );
		Beep( 440, 50 );
		Beep( 587, 50 );
		break;
	case enDELETE_LINE::MAX:
		addScore = enADD_SCORE::None;
		break;
	default:
		break;
	}
	m_Score += addScore;
}