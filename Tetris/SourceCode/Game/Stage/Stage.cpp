#include "Stage.h"
#include <random>

CStage::CStage()
	: m_MainStage			()
	, m_Blocks				( 7 )
	, m_NextAndHoldBlocks	( 7 )
	, m_NowBlock			( nullptr )
	, m_NextBlock			( nullptr )
	, m_HoldBlock			( nullptr )
	, m_NowPosition			{ 0, 0 }
	, m_AfterFallingPosition{ 0, 0 }
	, m_BlockDownCount		( 0 )
	, m_BlockResetCount		( 7 )
	, m_NowBlockNumber		( 0 )
	, m_HoldBlockNumber		( 0 )
	, m_NextBlockNumber		( -1 )
	, m_BlockList			( 7 )
	, m_isPutBlock			( false )
	, m_isHoldBlock			( false )
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
		m_NowPosition.x++;
		for( int i = 0; i < 4; i++ ){
			if( IsOverlappedBlock( m_NowPosition, i ) == true ) m_NowPosition.x--;
		}
	}
	if( GetAsyncKeyState( VK_LEFT ) & 0x0001 ){
		m_NowPosition.x--;
		for( int i = 0; i < 4; i++ ){
			if( IsOverlappedBlock( m_NowPosition, i ) == true ) m_NowPosition.x++;
		}
	}

	if( GetAsyncKeyState( VK_UP ) & 0x0001 ){
		int isHit = false;
		for( ; isHit != true; ){
			m_NowPosition.y++;
			for( int i = 0; i < 4; i++ ){
				if( IsOverlappedBlock( m_NowPosition, i ) == false ) continue;

				m_NowPosition.y--;
				for( int i = 0; i < 4; i++ ){
					int x = m_NowPosition.x + m_NowBlock->GetPosition( i ).x;
					int y = m_NowPosition.y + m_NowBlock->GetPosition( i ).y;
					m_MainStage[y][x] = 3;
					m_ColorStage[y][x] = (int)m_NowBlock->GetColor();

					m_isHoldBlock = false;
					m_isPutBlock = true;
					isHit = true;
				}
				InitNowPosition();
				break;
			}
		}
	} else 
	if( GetAsyncKeyState( VK_DOWN ) & 0x0001 ){
		m_NowPosition.y++;
		BlockPutCheck();
	}
	if( GetAsyncKeyState( 'X' ) & 0x0001 ){
		m_NowBlock->RightRotation();
		for( int i = 0; i < 4; i++ ){
			if( IsOverlappedBlock( m_NowPosition, i ) == true ) m_NowBlock->LeftRotation();
		}
	}
	if( GetAsyncKeyState( 'Z' ) & 0x0001 ){
		m_NowBlock->LeftRotation();
		for( int i = 0; i < 4; i++ ){
			if( IsOverlappedBlock( m_NowPosition, i ) == true ) m_NowBlock->RightRotation();
		}
	}
	if( GetAsyncKeyState( 'C' ) & 0x0001 ){
		if( m_isHoldBlock == false ){
			if(m_HoldBlock == nullptr ){
				m_HoldBlockNumber = m_NowBlockNumber;
				m_HoldBlock = m_NextAndHoldBlocks[m_NowBlockNumber];
				InitNowPosition();
				m_isHoldBlock = true;

			} else {
				m_NowBlock = m_Blocks[m_HoldBlockNumber];
				m_HoldBlock = m_NextAndHoldBlocks[m_NowBlockNumber];

				int tmpNumber = m_HoldBlockNumber;
				m_HoldBlockNumber = m_NowBlockNumber;
				m_NowBlockNumber = tmpNumber;

				m_NowPosition.x = INIT_POSITION_X;
				m_NowPosition.y = INIT_POSITION_Y;

				m_isHoldBlock = true;
			}
		}
	}
}

void CStage::Update()
{
	Control();
	BlockDown();

	bool isHit = false;
	m_AfterFallingPosition = m_NowPosition;
	for( ; isHit != true; ){
		m_AfterFallingPosition.y++;
		for( int i = 0; i < 4; i++ ){
			if (IsOverlappedBlock( m_AfterFallingPosition, i ) == false) continue;

			m_AfterFallingPosition.y--;
			for( int i = 0; i < 4; i++ ){
				int x = m_AfterFallingPosition.x + m_NowBlock->GetPosition(i).x;
				int y = m_AfterFallingPosition.y + m_NowBlock->GetPosition(i).y;
				m_MainStage[y][x] = 4;
			}
			isHit = true;
			break;
		}
	}

	for( int i = 0; i < 4; i++ ){
		m_MainStage[m_NowPosition.y+m_NowBlock->GetPosition(i).y][m_NowPosition.x+m_NowBlock->GetPosition(i).x] = 2;
	}
	
}

void CStage::Render()
{
	auto holdNextBlockRender = [&]( std::shared_ptr<CBlockBase> pBlock, int pos_x )
	{
		if (pBlock == nullptr) return;
		for (int i = 0; i < 4; i++) {
			m_HoldAndNextBlock[1 + pBlock->GetPosition(i).y][1 + pBlock->GetPosition(i).x] = 1;
		}
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 8; x += 2) {
				if (m_HoldAndNextBlock[y][x / 2] == 1) {
					CConsole::SetColor((int)pBlock->GetColor() + 8, (int)pBlock->GetColor());
					CConsole::Draw(pos_x + x, 3 + y, "Å°");
				} else {
					CConsole::SetColor(0, 0);
					CConsole::Draw(pos_x + x, 3 + y, "  ");
				}
				m_HoldAndNextBlock[y][x/2] = 0;
			}
		}
	};
	holdNextBlockRender( m_HoldBlock, 4 );
	holdNextBlockRender( m_NextBlock, 40 );

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
				CConsole::SetColor( (int)m_NowBlock->GetColor()+8, (int)m_NowBlock->GetColor() );
				CConsole::Draw( 14+x, pos_y, "Å°");

				break;
			case 3:
				CConsole::SetColor( m_ColorStage[y][x/2]+8, m_ColorStage[y][x/2] );
				CConsole::Draw( 14+x, pos_y, "Å°");

				break;
			case 4:
				CConsole::SetColor( (int)m_NowBlock->GetColor() + 8, (int)enColor::L_BLACK);
				CConsole::Draw(14 + x, pos_y, "Å†");

				break;
			default:
				break;
			}
		}
		tmp_y++;
	}
	for( int i = 0; i < 4; i++ ){
		int x = m_NowPosition.x + m_NowBlock->GetPosition(i).x;
		int y = m_NowPosition.y + m_NowBlock->GetPosition(i).y;
		m_MainStage[y][x] = 0;
		x = m_AfterFallingPosition.x + m_NowBlock->GetPosition( i ).x;
		y = m_AfterFallingPosition.y + m_NowBlock->GetPosition( i ).y;
		m_MainStage[y][x] = 0;
	}
	BlockDelete();
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
	m_NowPosition.x = INIT_POSITION_X;
	m_NowPosition.y = INIT_POSITION_Y;

	int i = rand() % m_BlockResetCount;
	if( m_NextBlockNumber == -1 ){
		m_NowBlock = m_Blocks[m_BlockList[i]];
		m_NowBlockNumber = m_BlockList[i];

		m_BlockList.erase(m_BlockList.begin() + i);

		m_BlockResetCount--;

		i = rand() % m_BlockResetCount;

		m_NextBlockNumber = m_BlockList[i];
		m_NextBlock = m_NextAndHoldBlocks[m_NextBlockNumber];

		m_BlockList.erase(m_BlockList.begin() + i);

		m_BlockResetCount--;

	} else {
		m_NowBlock = m_Blocks[m_NextBlockNumber];
		m_NowBlockNumber = m_NextBlockNumber;

		m_NextBlockNumber = m_BlockList[i];

		m_NextBlock = m_NextAndHoldBlocks[m_NextBlockNumber];

		m_BlockList.erase(m_BlockList.begin() + i);

		m_BlockResetCount--;
	}

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
		m_NowPosition.y++;
		BlockPutCheck();
		m_BlockDownCount = 0;
	}
	m_BlockDownCount++;
}

void CStage::BlockPutCheck()
{
	for( int i = 0; i < 4; i++ ){
		if( IsOverlappedBlock( m_NowPosition, i ) == false ) continue;
		m_NowPosition.y--;
		for( int i = 0; i < 4; i++ ){
			int x = m_NowPosition.x + m_NowBlock->GetPosition( i ).x;
			int y = m_NowPosition.y + m_NowBlock->GetPosition( i ).y;
			m_MainStage[y][x] = 3;
			m_ColorStage[y][x] = (int)m_NowBlock->GetColor();
		}
		m_isHoldBlock = false;
		m_isPutBlock = true;
		InitNowPosition();
		
		break;
	}
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

bool CStage::IsOverlappedBlock( const Vector2D& pos, int index )
{
	int _x = pos.x + m_NowBlock->GetPosition( index ).x;
	int _y = pos.y + m_NowBlock->GetPosition( index ).y;
	return m_MainStage[_y][_x] != 0 ? true : false;
}