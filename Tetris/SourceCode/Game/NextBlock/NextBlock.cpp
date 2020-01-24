#include "NextBlock.h"

CNextBlock::CNextBlock()
	: m_BlockStage	( 4 )
	, m_pBlock		( nullptr )
	, m_BlockNumber	( -1 )
{
	for( int y = 0; y < 4; y++ ){
		for( int x = 0; x < 4; x++ ){
			m_BlockStage[y].emplace_back();
			m_BlockStage[y][x] = 0;
		}
	}
}

CNextBlock::~CNextBlock()
{
}

//--------------------------.
//	ï`âÊä÷êî.
//--------------------------.
void CNextBlock::Render()
{
	if( m_pBlock == nullptr ) return;
	for( int i = 0; i < 4; i++ ){
		m_BlockStage[m_pBlock->GetPosition(i).y+1][m_pBlock->GetPosition(i).x+1] = 1;
	}
	for( int y = 0; y < 4; y++ ){
		for (int x = 0; x < 8; x += 2) {
			RenderChar( x, y );
		}
	}
}

//--------------------------.
//	ï∂éöï`âÊ.
//--------------------------.
void CNextBlock::RenderChar( const int& x, const int& y )
{
	if( m_BlockStage[y][x/2] == 1 ){
		CConsole::SetColor((int)m_pBlock->GetColor() + 8, (int)m_pBlock->GetColor());
		CConsole::Draw( RENDER_POSITION_X + x, 3 + y, "Å°" );
	} else {
		CConsole::SetColor( 0, 0 );
		CConsole::Draw( RENDER_POSITION_X + x, 3 + y, "  " );
	}

	m_BlockStage[y][x/2] = 0;
}