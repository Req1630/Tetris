#include "Level.h"
#include "..\..\Console\Console.h"

CLevel::CLevel()
	: m_Level			( 1 )
	, m_AddDeleteLine	( 0 )
{
}

CLevel::~CLevel()
{
}

void CLevel::Render()
{
	CConsole::SetColor( (int)enColor::H_WHITE, (int)enColor::L_BLACK );
	CConsole::Draw( 39, 15, "Level : ", m_Level );
}

void CLevel::SetDeleteLine( const int& line )
{ 
	m_AddDeleteLine += line;
	m_Level = m_AddDeleteLine / 10 + 1;
}

int CLevel::GetDownTime() const
{
	int time = 30 - m_Level;
	if( time <= 5 ) time = 5;
	return time;
}