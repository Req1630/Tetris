#include "Score.h"
#include "..\..\Console\Console.h"

CScore::CScore()
	: m_Score	( 0 )
{
}

CScore::~CScore()
{
}

void CScore::Render()
{
	CConsole::SetColor( (int)enColor::H_WHITE, (int)enColor::L_BLACK );
	CConsole::Draw( 39, 18, "Score : ", m_Score );
}

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
		break;
	case enDELETE_LINE::MAX:
		addScore = enADD_SCORE::None;
		break;
	default:
		break;
	}
	m_Score += addScore;
}