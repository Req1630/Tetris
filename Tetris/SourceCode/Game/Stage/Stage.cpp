#include "Stage.h"
#include <random>

CStage::CStage()
	: m_MainStage		()
	, m_Blocks			( 7 )
	, NowBlock			( nullptr )
	, NowPosition		{ 0, 0 }
	, m_BlockDownCount	( 0 )
	, m_BlockResetCount	( 7 )
	, m_BlockList		( 7 )
{
	for( int i = 0; i < 7; i++ ){
		m_BlockList[i] = i;
	}
}

CStage::~CStage()
{
}

void CStage::Update()
{
	auto isOverlappedBlock = [&]( int index ) -> bool
	{
		int _x = NowPosition.x+NowBlock->GetPosition(index).x;
		int _y = NowPosition.y+NowBlock->GetPosition(index).y;
		return m_MainStage[_y][_x] != 0 ? true : false;
	};
	if( GetAsyncKeyState(VK_RIGHT) & 0x0001 ){
		NowPosition.x++;
		for( int i = 0; i < 4; i++ ){
			if( isOverlappedBlock(i) == true ){
				NowPosition.x--;
			}
		}
	}
	if( GetAsyncKeyState(VK_LEFT) & 0x0001 ){
		NowPosition.x--;
		for( int i = 0; i < 4; i++ ){
			if( isOverlappedBlock(i) == true ){
				NowPosition.x++;
			}
		}
	}
	if( GetAsyncKeyState(VK_DOWN) & 0x0001 ){
		NowPosition.y++;
		for( int i = 0; i < 4; i++ ){
			if( isOverlappedBlock(i) == true ){
				if( isOverlappedBlock(i) == false ) continue;
				NowPosition.y--;
				for( int i = 0; i < 4; i++ ){
					m_MainStage[NowPosition.y+NowBlock->GetPosition(i).y][NowPosition.x+NowBlock->GetPosition(i).x] = 3;
					m_ColorStage[NowPosition.y+NowBlock->GetPosition(i).y][NowPosition.x+NowBlock->GetPosition(i).x] = (int)NowBlock->GetColor();
				}
				InitNowPosition();
				break;
			}
		}
	}
	if( GetAsyncKeyState('X') & 0x0001 ){
		NowBlock->RightRotation();
		for( int i = 0; i < 4; i++ ){
			if( isOverlappedBlock(i) == true ){
				NowBlock->LeftRotation();
			}
		}
	}
	if( GetAsyncKeyState('Z') & 0x0001 ){
		NowBlock->LeftRotation();
		for( int i = 0; i < 4; i++ ){
			if( isOverlappedBlock(i) == true ){
				NowBlock->RightRotation();
			}
		}
	}

	if( m_BlockDownCount >= 30 ){
		NowPosition.y++;
		for( int i = 0; i < 4; i++ ){
			if( isOverlappedBlock(i) == false ) continue;
			NowPosition.y--;
			for( int i = 0; i < 4; i++ ){
				m_MainStage[NowPosition.y+NowBlock->GetPosition(i).y][NowPosition.x+NowBlock->GetPosition(i).x] = 3;
				m_ColorStage[NowPosition.y+NowBlock->GetPosition(i).y][NowPosition.x+NowBlock->GetPosition(i).x] = (int)NowBlock->GetColor();
			}
			InitNowPosition();
			break;
		}
		m_BlockDownCount = 0;
	}
	m_BlockDownCount++;

	for( int i = 0; i < 4; i++ ){
		m_MainStage[NowPosition.y+NowBlock->GetPosition(i).y][NowPosition.x+NowBlock->GetPosition(i).x] = 2;
	}
}

void CStage::Render()
{
	int tmp_y = -3;
	for( int y = 0; y < HEIGHT; y++ ){
		int pos_y = -3 + y;
		if( tmp_y < 0 ){
			tmp_y++;
			continue;
		}
		for( int x = 0; x < WIDTH*2; x+=2 ){
			if( pos_y == 0 ){
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
	std::vector<Vector2D> pos = { {0,0}, {0,-1}, { 0,1}, { 0,2} };
	m_Blocks[0] = std::make_shared<CBlockBase>( pos, enColor::L_RED, 2 );

	pos = { {0,0}, {0,-1}, { 0,1}, { 1,1} };
	m_Blocks[1] = std::make_shared<CBlockBase>( pos, enColor::L_BLUE, 4 );

	pos = { {0,0}, {0,-1}, { 0,1}, {-1,1} };
	m_Blocks[2] = std::make_shared<CBlockBase>( pos, enColor::L_YELLOW, 4 );

	pos = { {0,0}, {0,-1}, { 1,0}, { 1,1} };
	m_Blocks[3] = std::make_shared<CBlockBase>( pos, enColor::L_PURPLE, 2 );

	pos = { {0,0}, {0,-1}, {-1,0}, {-1,1} };
	m_Blocks[4] = std::make_shared<CBlockBase>( pos, enColor::L_GREEN, 2 );

	pos = { {0,0}, {0, 1}, { 1,0}, { 1,1} };
	m_Blocks[5] = std::make_shared<CBlockBase>( pos, enColor::L_CYAN, 1 );

	pos = { {0,0}, {0,-1}, { 1,0}, { 0,1} };
	m_Blocks[6] = std::make_shared<CBlockBase>( pos, enColor::L_BLACK, 4 );
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