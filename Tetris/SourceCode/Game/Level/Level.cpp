#include "Level.h"
#include "..\..\Console\Console.h"

CLevel::CLevel()
	: m_Level			( 1 )
	, m_OldLevel		( 1 )
	, m_AddDeleteLine	( 0 )
{
}

CLevel::~CLevel()
{
}

//----------------------------------.
// �`��.
//----------------------------------.
void CLevel::Render()
{
	CConsole::SetColor( (int)enColor::H_WHITE, (int)enColor::L_BLACK );
	CConsole::Draw( 39, 16, "Level : ", m_Level );
}

//----------------------------------.
// ���������C�����̎擾.
//----------------------------------.
void CLevel::SetDeleteLine( const int& line )
{ 
	m_AddDeleteLine += line;
	m_Level = m_AddDeleteLine / 10 + 1;
	if( m_Level != m_OldLevel ){
		Beep( 740, 50 );
		Beep( 830, 50 );
		Beep( 880, 100 ); 

	}
	m_OldLevel = m_Level;
}

//----------------------------------.
// �u���b�N�����ɗ��Ƃ����Ԃ̎擾.
//----------------------------------.
int CLevel::GetDownTime() const
{
	int time = 30 - m_Level;
	if( time <= 5 ) time = 5;
	return time;
}