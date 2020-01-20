#include "Stage.h"
#include <random>

CStage::CStage()
	: m_MainStage			()
	, m_Blocks				( 7 )
	, m_NextAndHoldBlocks	( 7 )
	, NowBlock				( nullptr )
	, NextBlock				( nullptr )
	, HoldBlock				( nullptr )
	, NowPosition			{ 0, 0 }
	, m_BlockDownCount		( 0 )
	, m_BlockResetCount		( 7 )
	, m_BlockList			( 7 )
	, m_isPutBlock			( false )
{
	for( int i = 0; i < 7; i++ ){
		m_BlockList[i] = i;
	}
	for( int y = 0; y < 4; y++ ){
		for( int x = 0; x < 4; x++ ){
			m_HoldAndNextBlock[y][x] = 0;
		}
	}
}

CStage::~CStage()
{
}

void CStage::Control()
{
	if( GetAsyncKeyState( VK_RIGHT ) & 0x0001 ){
		NowPosition.x++;
		for( int i = 0; i < 4; i++ ){
			if( IsOverlappedBlock( i ) == true ){
				NowPosition.x--;
			}
		}
	}
	if( GetAsyncKeyState( VK_LEFT ) & 0x0001 ){
		NowPosition.x--;
		for( int i = 0; i < 4; i++ ){
			if( IsOverlappedBlock( i ) == true ){
				NowPosition.x++;
			}
		}
	}
	if( GetAsyncKeyState( VK_DOWN ) & 0x0001 ){
		NowPosition.y++;
		for( int i = 0; i < 4; i++ ){
			if( IsOverlappedBlock( i ) == true ){
				if( IsOverlappedBlock( i ) == false ) continue;
				NowPosition.y--;
				for( int i = 0; i < 4; i++ ){
					m_MainStage[NowPosition.y + NowBlock->GetPosition( i ).y][NowPosition.x + NowBlock->GetPosition( i ).x] = 3;
					m_ColorStage[NowPosition.y + NowBlock->GetPosition( i ).y][NowPosition.x + NowBlock->GetPosition( i ).x] = (int)NowBlock->GetColor();
				}
				m_isPutBlock = true;
				InitNowPosition();
				break;
			}
		}
	}
	if( GetAsyncKeyState( 'X' ) & 0x0001 ){
		NowBlock->RightRotation();
		for( int i = 0; i < 4; i++ ){
			if( IsOverlappedBlock( i ) == true ){
				NowBlock->LeftRotation();
			}
		}
	}
	if( GetAsyncKeyState( 'Z' ) & 0x0001 ){
		NowBlock->LeftRotation();
		for( int i = 0; i < 4; i++ ){
			if( IsOverlappedBlock( i ) == true ){
				NowBlock->RightRotation();
			}
		}
	}
	if( GetAsyncKeyState( 'C' ) & 0x0001 ){
		if( HoldBlock == nullptr ){
			HoldBlock = NowBlock;
			InitNowPosition();
		} else {
			std::shared_ptr<CBlockBase> tmpBlock = HoldBlock;
			HoldBlock = NowBlock;
			NowBlock = tmpBlock;
			NowPosition.x = INIT_POSITION_X;
			NowPosition.y = INIT_POSITION_Y;
		}
	}
}

void CStage::Update()
{
	Control();
	BlockDown();

	for( int i = 0; i < 4; i++ ){
		m_MainStage[NowPosition.y+NowBlock->GetPosition(i).y][NowPosition.x+NowBlock->GetPosition(i).x] = 2;
	}
}

void CStage::Render()
{
	if( HoldBlock != nullptr ){
		for( int y = 0; y < 4; y++ ){
			for( int x = 0; x < 4; x++ ){
				m_HoldAndNextBlock[y][x] = 0;
			}
		}
		for( int i = 0; i < 4; i++ ){
			m_HoldAndNextBlock[1+HoldBlock->GetPosition( i ).y][1+HoldBlock->GetPosition( i ).x] = 1;
		}
		for( int y = 0; y < 4; y++ ){
			for( int x = 0; x < 8; x+=2 ){
				if( m_HoldAndNextBlock[y][x/2] == 1 ) {
					CConsole::SetColor( (int)HoldBlock->GetColor() + 8, (int)HoldBlock->GetColor() );
					CConsole::Draw( 4+x, 3+y, "Å°" );
				} else {
					CConsole::SetColor( 0, 0 );
					CConsole::Draw( 4+x, 3+y, "  " );
				}
			}
		}
	}
	int tmp_y = -3;
	for( int y = 0; y < HEIGHT; y++ ){
		int pos_y = -3 + y;
		if( tmp_y < 0 ){
			tmp_y++;
			continue;
		}
		for( int x = 0; x < WIDTH*2; x+=2 ){
			if( pos_y == 0 ){
				CConsole::SetColor( (int)enColor::H_WHITE, (int)enColor::L_WHITE );
				CConsole::Draw( 14+x, pos_y, "Å°");
				continue;
			}
			switch( m_MainStage[y][x/2] )
			{
			case 0:
				CConsole::SetColor( m_ColorStage[y][x/2], m_ColorStage[y][x/2] );
				CConsole::Draw( 14+x, pos_y, "  ");

				break;
			case 1:
				CConsole::SetColor( m_ColorStage[y][x/2]+8, m_ColorStage[y][x/2] );
				CConsole::Draw( 14+x, pos_y, "Å°");

				break;
			case 2:
				CConsole::SetColor( (int)NowBlock->GetColor()+8, (int)NowBlock->GetColor() );
				CConsole::Draw( 14+x, pos_y, "Å°");

				break;
			case 3:
				CConsole::SetColor( m_ColorStage[y][x/2]+8, m_ColorStage[y][x/2] );
				CConsole::Draw( 14+x, pos_y, "Å°");

				break;
			default:
				break;
			}
		}
		tmp_y++;
	}
	BlockDelete();
	for( int i = 0; i < 4; i++ ){
		m_MainStage[NowPosition.y+NowBlock->GetPosition(i).y][NowPosition.x+NowBlock->GetPosition(i).x] = 0;
	}
}

void CStage::CreateStage()
{
	for( int x = 0; x < WIDTH; x++ ){
		for( int y = 0; y < HEIGHT; y++ ){
			if( x == 0 || x == WIDTH-1 || y == HEIGHT-1 ){
				m_MainStage[y][x] = 1;
				m_ColorStage[y][x] = 7;
			} else {
				m_MainStage[y][x] = 0;
				m_ColorStage[y][x] = 0;
			}
		}
	}
}

void CStage::CreateBlock()
{
	auto initBlock = [&]( int index, std::vector<Vector2D> pos, enColor color, int rot )
	{
		m_Blocks[index] = std::make_shared<CBlockBase>( pos, color, rot );
		m_NextAndHoldBlocks[index] = std::make_shared<CBlockBase>( pos, color, rot );
	};
	initBlock( 0, { {0,0}, {0,-1}, { 0,1}, { 0,2} }, enColor::L_RED, 2 );
	initBlock( 1, { {0,0}, {0,-1}, { 0,1}, { 1,1} }, enColor::L_BLUE, 4 );
	initBlock( 2, { {0,0}, {0,-1}, { 0,1}, {-1,1} }, enColor::L_YELLOW, 4 );
	initBlock( 3, { {0,0}, {0,-1}, { 1,0}, { 1,1} }, enColor::L_PURPLE, 2 );
	initBlock( 4, { {0,0}, {0,-1}, {-1,0}, {-1,1} }, enColor::L_GREEN, 2 );
	initBlock( 5, { {0,0}, {0, 1}, { 1,0}, { 1,1} }, enColor::L_CYAN, 1 );
	initBlock( 6, { {0,0}, {0,-1}, { 1,0}, { 0,1} }, enColor::L_BLACK, 4 );
}

void CStage::InitNowPosition()
{
	NowPosition.x = INIT_POSITION_X;
	NowPosition.y = INIT_POSITION_Y;

	int i = rand() % m_BlockResetCount;
	NowBlock = m_Blocks[m_BlockList[i]];
	m_BlockList.erase(m_BlockList.begin()+i);

	m_BlockResetCount--;

	if( m_BlockResetCount == 0 ){
		for( int i = 0; i < 7; i++ ){
			m_BlockList.emplace_back();
			m_BlockList[i] = i;
		}
		m_BlockResetCount = 7;
	}
}

void CStage::BlockDown()
{
	if( m_BlockDownCount >= 30 ){
		NowPosition.y++;
		for( int i = 0; i < 4; i++ ){
			if( IsOverlappedBlock( i ) == false ) continue;
			NowPosition.y--;
			for( int i = 0; i < 4; i++ ){
				m_MainStage[NowPosition.y + NowBlock->GetPosition( i ).y][NowPosition.x + NowBlock->GetPosition( i ).x] = 3;
				m_ColorStage[NowPosition.y + NowBlock->GetPosition( i ).y][NowPosition.x + NowBlock->GetPosition( i ).x] = (int)NowBlock->GetColor();
			}
			m_isPutBlock = true;
			InitNowPosition();
			break;
		}
		m_BlockDownCount = 0;
	}
	m_BlockDownCount++;
}

void CStage::BlockDelete()
{
	if( m_isPutBlock == false ) return;
	
	for( int y = HEIGHT-2; y >= 0; y-- ){
		int blockCount = 0;
		for( int x = 1; x < WIDTH-1; x++ ){
			if( m_MainStage[y][x] == 3 ){
				blockCount++;
			}
		}
		if( blockCount == 10 ){
			for( int dy = y; dy >= 1; dy-- ){
				for( int x = 1; x < WIDTH - 1; x++ ){
					if( m_MainStage[dy-1][x] == 2 ) continue;
					m_MainStage[dy][x] = m_MainStage[dy-1][x];
					m_ColorStage[dy][x] = m_ColorStage[dy-1][x];
				}
			}
			y = HEIGHT - 1;
		}
	}
	m_isPutBlock = false;
}

bool CStage::IsOverlappedBlock( int index )
{
	int _x = NowPosition.x + NowBlock->GetPosition( index ).x;
	int _y = NowPosition.y + NowBlock->GetPosition( index ).y;
	return m_MainStage[_y][_x] != 0?true:false;
}